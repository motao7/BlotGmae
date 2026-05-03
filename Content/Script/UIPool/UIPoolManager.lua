-----------------------------------------------------------------------
-- ★ 精华3+4+5: PoolManager — 三池协同 + 两级销毁
--
-- 三池:
--   StagePool  — StageHold, 按Type永久缓存, Level切换时清理
--   CacheQueue — Cache/HugeCache, FIFO淘汰, 容量上限
--   ItemPool   — SubUI列表项, 高频Pop/Push
--
-- 两级销毁 (这是安全复用的核心):
--   onReset:  入池前轻量重置 — 清事件/定时器/数据, 保留Widget树结构
--   onDestroy: 彻底释放 — RemoveFromParent + 递归销毁子UI
--
-- 为什么不能只有Destroy?
--   Destroy = RemoveFromParent + 重建 = 下次打开需要重新Construct
--   Reset   = 只清数据         = 下次打开只需Reinit, 跳过Construct
--   Construct(创建UI树)耗时 ~3ms, Reinit(绑定数据)耗时 ~0.3ms
-----------------------------------------------------------------------

local UIPoolManager = {}
UIPoolManager.__index = UIPoolManager

local UITypePool = require("UIPool.UITypePool")
local UIPriorityCacheQueue = require("UIPool.UIPriorityCacheQueue")

function UIPoolManager.New(Config)
    return setmetatable(
        {
            StagePool = UITypePool.New(Config.StagePoolMaxPerType),           --------- StagePool长期持有关卡切换清除
            CacheQueue = UIPriorityCacheQueue.New(Config.CacheQueueHugeMaxNum,Config.CacheQueueTotalNum), --------- CacheQueue短期持有, 按优先级淘汰
            ItemPool = UITypePool.New(Config.ItemPoolMaxPerType),            --------- ItemPool专门给物品图标用的, 预设较小的MaxPreType
        },
        UIPoolManager
    )
end

-- Register阶段: 只注册CacheType和生命周期回调, 不创建Widget实例
function UIPoolManager:Register(WidgetType, Config)
    _G.UICfg.Register(WidgetType, Config)
end

--先查询StageHold池，在查询Cache池，最后才创建新实例
function UIPoolManager:Acquire(WidgetType, ...)
    local Config = _G.UICfg.Get(WidgetType)
    if not Config then return nil end

    local Widget

    if Config.CacheType == _G.UICfg.CacheType.StageHold then
        Widget = self.StagePool:Pop(WidgetType)
    elseif Config.CacheType == _G.UICfg.CacheType.Cache or Config.CacheType == _G.UICfg.CacheType.HugeCache then
        Widget = self.CacheQueue:DequeueByType(WidgetType)
    end

    if Widget then
        --核心亮点，缓存命中只需调用OnReinit，跳过昂贵的Construct流程
        if Config.OnReinit then Config.OnReinit(Widget, ...) end
        return Widget
    end

    if Config.OnCreate then
        Widget = Config.OnCreate(WidgetType, ...)
        return Widget
    end

    return nil
end

--归还主页面到对象池，先调用OnReset重置状态，再根据CacheType放入对应的池
function UIPoolManager:Release(WidgetType, Widget)
    local Config = _G.UICfg.Get(WidgetType)
    if not Config or not Widget then return false end

    --不缓存直接销毁
    if Config.CacheType == _G.UICfg.CacheType.None then
        if Config.OnDestroy then Config.OnDestroy(Widget) end
        return false
    end

    --精华:只轻量化重置, 保留Widget树结构, 以便下次复用, 避免Destroy+Construct的性能开销
    if Config.OnReset then Config.OnReset(Widget) end
    if Config.CacheType == _G.UICfg.CacheType.StageHold then
        local ok = self.StagePool:Push(WidgetType, Widget)
        if not ok and Config.OnDestroy then Config.OnDestroy(Widget) end
        return ok
    end

    --Cache/HugeCache放入CacheQueue, 由CacheQueue负责淘汰策略
    local EvicitedType, EvicitedWidget = self.CacheQueue:Enque(WidgetType, Widget, Config.CacheType)
    
    --Enque时有返回代表队列满->走Destory
    if EvicitedWidget then 
        local EvictedConfig = _G.UICfg.Get(EvicitedType)
        if EvictedConfig and EvictedConfig.OnDestroy then
            EvictedConfig.OnDestroy(EvicitedWidget)
        end
    end
    return true
end

--- ★ 精华4: SubUI列表项获取 — 最高频的性能关键路径
--- 场景: 背包100格, 每格CreateWidget 3-5ms
---       池化后: Pop(O(1)) + Reinit(0.3ms) = 0.3ms/格
---       总计: 100×3ms=300ms → 100×0.3ms=30ms
function UIPoolManager:AcquireItem(ItemType,...)
    local Widget = self.ItemPool:Pop(ItemType)

    local Config = _G.UICfg.Get(ItemType)
    if not Config then return nil end

    if Widget then
        if Config.OnReinit then Config.OnReinit(Widget, ...) end
        return Widget
    end

    if Config.OnCreate then
        Widget = Config.OnCreate(ItemType, ...)
        return Widget
    end

    return nil
end

--同样的，先Reset再Push入ItemPool
function UIPoolManager:ReleaseItem(ItemType, Widget)
    if not Widget then return false end

    local Config = _G.UICfg.Get(ItemType)
    if not Config then return nil end

    if Config.OnReset then Config.OnReset(Widget) end
    local ok = self.ItemPool:Push(ItemType, Widget)
    if not ok then
        --TODO:池满彻底移除,编写RemoveFromParent
        if Widget.RemoveFromParent then Widget:RemoveFromParent() end
    end
    return ok
end

-- StagePool按关卡切换清理接口
function UIPoolManager:ClearStage()
    self.StagePool:ReleaseAll(function(Widget)
        if Widget and Widget.RemoveFromParent then Widget:RemoveFromParent() end
    end)
end

-- CacheQueue批量清理接口
function UIPoolManager:ClearCache()
    self.CacheQueue:ReleaseAll(function(Widget)
        if Widget and Widget.RemoveFromParent then Widget:RemoveFromParent() end
    end)
end

-- 清理所有池
function UIPoolManager:ReleaseAll()
    local OnWidgetDestroy = function(Widget)
        if Widget and Widget.RemoveFromParent then Widget:RemoveFromParent() end
    end
    self.StagePool:ReleaseAll(OnWidgetDestroy)
    self.CacheQueue:ReleaseAll(OnWidgetDestroy)
    self.ItemPool:ReleaseAll(OnWidgetDestroy)
end

return UIPoolManager