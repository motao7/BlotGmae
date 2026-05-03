--- LodComponent.lua
--- LOD 组件基类
---
--- 每个"需要被LOD管理"的对象持有一个此基类的实例。
--- 负责：
---   ⑥ LOD等级计算算法（基于距离比例阈值）
---   ⑦ 状态变化去重（避免重复设置相同LOD）
---   ⑧ 超远距离特殊处理
---   ⑨ 生命周期钩子（OnLodActive / OnOutOfMaxDistance）

local LodDefine = require("LodSystem.LodDefine")
local LodGrid = require("LodSystem.LodGrid")

local LodComponent = {}

--- ============================================================
---  工厂方法：创建一个 LOD 组件实例
---  @param OwnerActor       被管理的Actor（远程角色等）
---  @param RegionType       分区类型（ERegionType.*）
---  @param MaxLodDistance   最大生效距离（UU）
---  @param LodRate          各级LOD的距离比例数组，如 {0.3, 0.3, 0.4}
---                          表示 LOD0: 0~30%, LOD1: 30~60%, LOD2: 60~100%
--- ============================================================
function LodComponent.Create(OwnerActor, RegionType, MaxLodDistance, LodRate)
    local self = setmetatable({}, { __index = LodComponent })

    self.OwnerActor           = OwnerActor
    self.ComponentRegionType  = RegionType or LodDefine.ERegionType.NoneRegion
    self.MaxLodDistance       = MaxLodDistance or 10000.0
    self.LodRate              = LodRate or {}
    self.MaxLod               = #self.LodRate          -- 最大LOD等级数

    --- 运行时状态
    self.CurrentPlayerDistance = 0.0
    self.CurrentLod             = -1     -- -1 = 未初始化/
    self.bOutOfMaxDistance      = false
    self.bEnabled               = true

    --- 注册到空间网格
    LodGrid.Register(self)

    return self
end

--- ============================================================
--  技术点 ⑥：LOD等级计算（核心算法）
--
--  算法原理：
--    LodRate 是一组累加的比例值，从后向前匹配。
--    设 MaxLodDistance=10000, LodRate={0.3, 0.3, 0.4}
--    则各等级触发阈值为：
--      >MaxLodDistance: 超距处理 
--      LOD3: distance >= (1-0.3)*10000 = 7000   ← 最近，最高精度
--      LOD2: distance >= (1-0.6)*10000 = 4000
--      LOD1: distance >= (1-1.0)*10000 = 0      ← 最远（不会命中，兜底为LOD2）
--      LOD0: distance <0   贴脸
--     
--      从远到近遍历，利用“远处玩家更多”的先验知识，可以提前退出循环。
-- ============================================================

function LodComponent:ProcessDistance(PlayerDistance)
    if not self.bEnabled then return end

    self.CurrentPlayerDistance = PlayerDistance

    -- 超过最大距离
    if PlayerDistance > self.MaxLodDistance then
        if not self.bOutOfMaxDistance then
            self.bOutOfMaxDistance = true
            self:_SetActiveLod(-1)  -- 特殊标记：超距
            self:OnOutOfMaxDistance()
        end
        return
    end

    -- 回到有效范围
    self.bOutOfMaxDistance = false

    -- 无LodRate → 始终LOD0
    if #self.LodRate == 0 then
        self:_SetActiveLod(0)
        return
    end

    --反向遍历LodRate，找到第一个匹配的等级
    local TotalRate = 0.0
    for i = #self.LodRate, 1, -1 do
        TotalRate = TotalRate + self.LodRate[i]
        local Threshold = (1.0 - TotalRate)*self.MaxLodDistance
        -- 命中,例如LodRate[i] = {0.3, 0.3, 0.4} 
        --最后Lod0为当PlayerDistance<=Threahold围殴1-(0.3+0.4)*MaxLoadDistance
        if PlayerDistance > Threshold then
            self:_SetActiveLod(i)
            return
        end
    end

    --兜底:最高精度-负距离 贴脸设置最高精度
    self:_SetActiveLod(0)
end

function LodComponent:_SetActiveLod(NewLod)
    if self.CurrentLod == NewLod then
        return  -- 未变化，跳过
    end

    self.CurrentLod = NewLod
    self:OnLodActive(NewLod)
end

--- ============================================================
--  技术点 ⑧ & ⑨：子类覆写的回调钩子
--
--  OnLodActive(NewLod):      进入新的LOD等级时调用
--  OnOutOfMaxDistance():     超出最大距离时调用（显示极简模型或隐藏）
-- ============================================================
function LodComponent:OnLodActive(NewLod)
    local ownerName = self.OwnerActor and self.OwnerActor:GetName() or "Unknown"
    print(string.format("[LOD] Actor: %s, LOD等级: %d -> %d", 
        ownerName, self.CurrentLod, NewLod))
    self.CurrentLod = NewLod
end

function LodComponent:OnOutOfMaxDistance()
    local ownerName = self.OwnerActor and self.OwnerActor:GetName() or "Unknown"
    print(string.format("[LOD] Actor: %s, 超出最大距离 (距离=%.1f, 阈值=%.1f)", 
        ownerName, self.CurrentPlayerDistance, self.MaxLodDistance))
end

--- 获取Actor的世界位置（供Grid使用）
function LodComponent:GetWorldLocation()
    if self:IsValid() then
        return self.OwnerActor:GetActorLocation()
    end
    return FVector(0, 0, 0)
end

--- 检查Owner是否仍然有效
function LodComponent:IsValid()
    return self.OwnerActor ~= nil
       and not self.OwnerActor:IsPendingKill()
       and self.bEnabled
end

--- 销毁此组件（注销网格 + 清理）
function LodComponent:Destroy()
    self.bEnabled = false
    LodGrid.Unregister(self)
    self.OwnerActor = nil
    self.CurrentLod = -1
end

--- 手动强制刷新到指定LOD（用于测试）
function LodComponent:ForceLod(Lod)
    self:_SetActiveLod(Lod)
end

return LodComponent