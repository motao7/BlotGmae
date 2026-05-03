local UIPoolTest = {}

-- ============ 测试配置 ============
local Config = {
    -- 功能测试配置
    TestItemType = "WBP_TestWidget",
    CacheItemType = "CacheItem",
    HugeItemType = "HugeItem",
    StageItemType = "StageItem",
    NoneItemType = "NoneItem",
    WidgetPath = "/Game/PerformenceOptimization/WBP_TestWidget.WBP_TestWidget_C",

    -- 性能测试配置
    Iterations = 500,
}

-- ============ Widget 创建 ============
local widgetClass = nil

local function GetWidgetClass()
    if not widgetClass then
        widgetClass = _G.ResPoolMgr:SyncLoad(Config.WidgetPath)
        if not widgetClass then
            print("[Error] 无法加载 Widget 类: " .. Config.WidgetPath)
            return nil
        end
    end
    return widgetClass
end

local function CreateTestWidget()
    local class = GetWidgetClass()
    if not class then return nil end

    local Widget = NewObject(class,_G.TestManager)

    if Widget then return Widget end

    print("[Error] 无法创建 Widget 实例")
    return nil
end

-- ============ 辅助函数 ============
local function PrintSuccess(msg)
    print(string.format("[✓] %s", msg))
end

local function PrintError(msg)
    print(string.format("[✗] %s", msg))
end

local function PrintInfo(msg)
    print(string.format("[i] %s", msg))
end

local function PrintTitle(title)
    print("\n========== " .. title .. " ==========")
end

-- ============ Insights 辅助函数 ============
local function AddBookmark(name)
    UE.UKismetSystemLibrary.ExecuteConsoleCommand(_G.UIPoolMgr, 'Trace.Bookmark "' .. name .. '"')
end

local function AddScreenshot(name, includeUI)
    includeUI = includeUI or false
    local cmd = string.format('Trace.Screenshot "%s" %s', name, tostring(includeUI))
    UE.UKismetSystemLibrary.ExecuteConsoleCommand(_G.UIPoolMgr, cmd)
end

local function SaveSnapshot(name)
    UE.UKismetSystemLibrary.ExecuteConsoleCommand(_G.UIPoolMgr, 'Trace.SnapshotFile ' .. name)
end

-- ============ 注册测试类型 ============
function UIPoolTest.RegisterAllTypes()
    PrintTitle("注册测试类型")
    
    if not GetWidgetClass() then return false end
    
    -- 注册 Cache 类型 (CacheType = 1)
    _G.UIPoolMgr:Register(Config.CacheItemType, {
        CacheType = 1,
        OnCreate = function(type, id, name)
            print("[OnCreate] Cache类型创建实例")
            local widget = CreateTestWidget()
            if widget then
                widget.id = id
                widget.name = name
                widget.createTime = os.clock()
            end
            return widget
        end,
        OnReset = function(widget)
            print("[OnReset] Cache类型重置")
            widget.id = nil
            widget.name = nil
            if widget.RemoveFromParent then widget:RemoveFromParent() end
        end,
        OnReinit = function(widget, id, name)
            print("[OnReinit] Cache类型重新初始化, id=" .. tostring(id))
            widget.id = id
            widget.name = name
            if widget.SetVisibility then widget:SetVisibility(UE.ESlateVisibility.Visible) end
        end,
        OnDestroy = function(widget)
            print("[OnDestroy] Cache类型销毁")
            if widget.RemoveFromParent then widget:RemoveFromParent() end

            -- 强制开始销毁（跳过 GC 等待队列）
if widget.ConditionalBeginDestroy then
    widget:ConditionalBeginDestroy()
end
        end
    })
    
    -- 注册 HugeCache 类型 (CacheType = 2)
    _G.UIPoolMgr:Register(Config.HugeItemType, {
        CacheType = 2,
        OnCreate = function(type, id)
            print("[OnCreate] HugeCache类型创建实例")
            local widget = CreateTestWidget()
            if widget then widget.id = id end
            return widget
        end,
        OnReset = function(widget)
            print("[OnReset] HugeCache类型重置")
            widget.id = nil
        end,
        OnReinit = function(widget, id)
            print("[OnReinit] HugeCache类型重新初始化, id=" .. tostring(id))
            widget.id = id
        end,
    })
    
    -- 注册 StageHold 类型 (CacheType = 3)
    _G.UIPoolMgr:Register(Config.StageItemType, {
        CacheType = 3,
        OnCreate = function(type, level)
            print("[OnCreate] StageHold类型创建实例, level=" .. tostring(level))
            local widget = CreateTestWidget()
            if widget then widget.level = level end
            return widget
        end,
        OnReset = function(widget)
            print("[OnReset] StageHold类型重置")
            widget.level = nil
        end,
        OnReinit = function(widget, level)
            print("[OnReinit] StageHold类型重新初始化, level=" .. tostring(level))
            widget.level = level
        end,
    })
    
    -- 注册 None 类型 (CacheType = 0，不缓存)
    _G.UIPoolMgr:Register(Config.NoneItemType, {
        CacheType = 0,
        OnCreate = function(type)
            print("[OnCreate] None类型创建实例（不缓存）")
            return CreateTestWidget()
        end,
        OnDestroy = function(widget)
            print("[OnDestroy] None类型销毁")
            if widget.RemoveFromParent then widget:RemoveFromParent() end
        end,
    })
    
    PrintSuccess("所有测试类型注册完成")
    return true
end

-- ============ 性能测试（带 Insights 标记） ============

function UIPoolTest.WithVsWithoutPool()
    print("\n========== 有池 vs 无池对比 ==========")
    
    local HalfIterations = Config.Iterations

    AddBookmark("Test_WithoutPool_Start")

    local items = {}
    for i = 1, HalfIterations do
        items[i] = _G.UIPoolMgr:Acquire(Config.NoneItemType)
    end
    for i = 1, HalfIterations do
        _G.UIPoolMgr:Release(Config.NoneItemType, items[i])
    end

    for i = 1, HalfIterations do
        items[i] = _G.UIPoolMgr:Acquire(Config.NoneItemType)
    end
    for i = 1, HalfIterations do
        _G.UIPoolMgr:Release(Config.NoneItemType, items[i])
    end
    
    AddBookmark("Test_WithoutPool_End")

    AddBookmark("Test_WithPool_Start")

    for i = 1, HalfIterations do
        items[i] = _G.UIPoolMgr:Acquire(Config.CacheItemType)
    end
    for i = 1, HalfIterations do
        _G.UIPoolMgr:Release(Config.CacheItemType, items[i])
    end

    AddBookmark("Test_WithPool_Reuse")

    for i = 1, HalfIterations do
        items[i] = _G.UIPoolMgr:Acquire(Config.CacheItemType)
    end
    for i = 1, HalfIterations do
        _G.UIPoolMgr:Release(Config.CacheItemType, items[i])
    end
    
    AddBookmark("Test_WithPool_End")

    _G.UIPoolMgr:ReleaseAll()
end

function UIPoolTest.TestControlledMemoryAndHighPriority()
    print("\n╔════════════════════════════════════════════════════════════╗")
    print("║  亮点3: 智能淘汰 - 内存可控 + HugeCache 高优先级保护        ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    local hugeMax = _G.UIPoolMgr.CacheQueue.HugeMax
    local totalMax = _G.UIPoolMgr.CacheQueue.TotalMax
    
    print(string.format("\n配置: HugeCache配额=%d, 总容量=%d", hugeMax, totalMax))
    
    -- 清空队列
    _G.UIPoolMgr.CacheQueue.Entries = {}
    _G.UIPoolMgr.CacheQueue.HugeCount = 0
    
    -- 步骤2: 创建大量普通 Cache（只 Acquire 不 Release）
    local extraCount = totalMax*5
    print(string.format("\n步骤2: 创建 %d 个普通 Cache（池外持有）", extraCount))
    
    local heldItems = {}
    for i = 1, extraCount do
        local w = _G.UIPoolMgr:Acquire(Config.CacheItemType)
        table.insert(heldItems, w)
    end
    print(string.format("  创建完成，队列大小: %d", #_G.UIPoolMgr.CacheQueue.Entries))
    
    -- 步骤3: 释放所有，触发淘汰
    print("\n步骤3: 释放所有普通 Cache（触发淘汰）")
    for i, w in ipairs(heldItems) do
        _G.UIPoolMgr:Release(Config.CacheItemType, w)
    end
    
    -- 关键：清除 heldItems 引用，让 Lua GC 可以回收
    print("\n步骤4: 清除 heldItems 数组引用")
    for i = 1, #heldItems do
        heldItems[i] = nil
    end
    heldItems = nil
    
    -- 主动触发 Lua GC（可选）
    collectgarbage("collect")
    
    -- 最终结果
    local finalCount = #_G.UIPoolMgr.CacheQueue.Entries
    local finalHuge = _G.UIPoolMgr.CacheQueue.HugeCount
    
    print("\n========== 淘汰结果 ==========")
    print(string.format("最终队列大小: %d / %d", finalCount, totalMax))
    print(string.format("其中 HugeCache: %d / %d", finalHuge, hugeMax))
    
    if finalCount <= totalMax then
        print("✓ 内存可控：未超过容量上限")
    end
    if finalHuge == hugeMax then
        print("✓ HugeCache 全部保留，普通 Cache 被淘汰")
    end
    
    -- 步骤5: 清理池
    _G.UIPoolMgr:ReleaseAll()
end

local function GetMemoryKB()
    local entries = _G.UIPoolMgr and _G.UIPoolMgr.CacheQueue and _G.UIPoolMgr.CacheQueue.Entries
    if not entries then
        return 0
    end
    local count = #entries
    return count * 50  -- 每个对象估算 50KB
end

function UIPoolTest.TestControlledMemoryAndHighPriority()
    print("\n╔════════════════════════════════════════════════════════════╗")
    print("║  亮点3: 智能淘汰 - 内存可控 + HugeCache 高优先级保护        ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    local hugeMax = _G.UIPoolMgr.CacheQueue.HugeMax
    local totalMax = _G.UIPoolMgr.CacheQueue.TotalMax
    
    print(string.format("\n配置: HugeCache配额=%d, 总容量=%d, 单对象≈50KB", hugeMax, totalMax))
    print(string.format("理论最大内存: %.1fMB\n", (totalMax * 50) / 1024))
    
    AddBookmark("Test_AddHugeCache")
    -- 步骤1: 放入 HugeCache
    print(string.format("步骤1: 放入 %d 个 HugeCache", hugeMax))
    
    local HugeWidges = {}
    for i = 1, hugeMax do
        HugeWidges[i] = _G.UIPoolMgr:Acquire(Config.HugeItemType)
    end
    for i = 1, hugeMax do
        _G.UIPoolMgr:Release(Config.HugeItemType, w)
    end
    print(string.format("  当前内存: %.2fMB", GetMemoryKB() / 1024))
    
    AddBookmark("Test_AddNormalCache")
    -- 步骤2: 放入大量普通 Cache
    local extraCount = totalMax*50
    print(string.format("\n步骤2: 放入 %d 个普通 Cache（超出容量）", extraCount))
    
    local ExtraCache = {}
    for i = 1, extraCount do
        ExtraCache[i] = _G.UIPoolMgr:Acquire(Config.CacheItemType)
    end

    for i = 1, extraCount do
        _G.UIPoolMgr:Release(Config.CacheItemType,ExtraCache[i])
        if i % 10 == 0 then
            print(string.format("  已放入 %d 个, 当前内存: %.2fMB", i, GetMemoryKB() / 1024))
        end
    end
    
    -- 最终结果
    local finalCount = #_G.UIPoolMgr.CacheQueue.Entries
    local finalHuge = _G.UIPoolMgr.CacheQueue.HugeCount
    local finalMem = GetMemoryKB() / 1024
    
    print("\n========== 淘汰结果 ==========")
    print(string.format("最终队列大小: %d / %d", finalCount, totalMax))
    print(string.format("其中 HugeCache: %d / %d", finalHuge, hugeMax))
    print(string.format("最终内存: %.2fMB / %.2fMB", finalMem, (totalMax * 50) / 1024))
    
    print("\n========== 结论 ==========")
    if finalCount <= totalMax then
        print("✓ 内存可控：未超过容量上限")
    end
    if finalHuge == hugeMax then
        print("✓ HugeCache 全部保留（高优先级保护）")
        print("✓ 被淘汰的都是普通 Cache")
    end
    print("\n核心价值：即使创建了 大量对象，内存稳定在安全线内")

    AddBookmark("Test_TestControlledMemoryAndHighPriorityEnd")
    _G.UIPoolMgr:ReleaseAll()
end

function UIPoolTest.RunAllPerformanceScenarios()
    print("\n╔════════════════════════════════════════════════════════════╗")
    print("║     UI Pool Manager - Unreal Insights 性能测试套件         ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    -- UIPoolTest.WithVsWithoutPool()
    -- UIPoolTest.TestGetWidgetSpeed()
    UIPoolTest.TestControlledMemoryAndHighPriority()

end

return UIPoolTest