---@type BP_ResourcePoolManager_C
local ResourcePoolManager = UnLua.Class()

-- ==================== 生命周期 ====================
function ResourcePoolManager:Initialize(Initializer)
    -- 修复：正确的类名引用
    local ResourcePoolClass = require("ResourcePool.ResourcePool")
    self.Pool = ResourcePoolClass:new({MaxLruSize = 100, ExpireTime = 60})
    
    -- 保存配置
    self.Config = {MaxLruSize = 100, ExpireTime = 60}
    
    -- 注意：全局单例的计时器需要特殊处理，暂不自动启动
    -- 或者通过外部传入 World/GameInstance 上下文
    -- self:StartCleanupTimer(5.0)

    _G.ResPoolMgr = self
end

function ResourcePoolManager:ReceiveBeginPlay()
end

function ResourcePoolManager:Deinitialize()
    self:StopCleanupTimer()
    
    if self.Pool then
        self.Pool:ClearAll()
        self.Pool = nil
    end
end

-- ==================== 对外 API ====================
function ResourcePoolManager:SyncGet(Path)
    if not self.Pool then return nil end
    
    local StableObj = self.Pool:GetFromStable(Path)
    if StableObj then
        return StableObj
    end
    
    local LruObj = self.Pool:GetFromLru(Path)
    if LruObj then
        return LruObj
    end
    
    local LoadedObj = self:SyncLoad(Path)
    if LoadedObj then
        self.Pool:AddLruPool(Path, LoadedObj)
    end
    
    return LoadedObj
end

--Callback参数格式: function(LoadedObj) end
function ResourcePoolManager:AsyncGet(Path, Callback)
    if not self.Pool then
        if Callback then Callback(nil) end
        return
    end
    
    local StableObj = self.Pool:GetFromStable(Path)
    if StableObj then
        if Callback then Callback(StableObj) end
        return
    end
    
    local LruObj = self.Pool:GetFromLru(Path)
    if LruObj then
        if Callback then Callback(LruObj) end
        return
    end
    
    self:AsyncLoad(Path, Callback, 100)
end

function ResourcePoolManager:AddToStable(Path, Object)
    if self.Pool then
        self.Pool:AddStablePool(Path, Object)
    end
end

function ResourcePoolManager:AddToLru(Path, Object)
    if self.Pool then
        self.Pool:AddLruPool(Path, Object)
    end
end

function ResourcePoolManager:Remove(Path)
    if self.Pool then
        self.Pool:LruErase(Path)
    end
end

function ResourcePoolManager:IsStable(Path)
    return self.Pool and self.Pool:IsStable(Path) or false
end

function ResourcePoolManager:GetStats()
    if self.Pool then
        return self.Pool:GetStats()
    end
    return { LruSize = 0, StableSize = 0, MaxLruSize = 0, ExpireTime = 0 }
end

function ResourcePoolManager:ClearAll()
    if self.Pool then
        self.Pool:ClearAll()
    end
end

-- ==================== 计时器管理 ====================
-- 注意：计时器需要 UE Object 上下文，全局单例使用时需要传入 World
function ResourcePoolManager:StartCleanupTimer(Interval, Context)
    if not Context then
        print("ResourcePoolManager:StartCleanupTimer - Context is required!")
        return
    end
    
    if self.CleanupTimerHandle then
        self:StopCleanupTimer()
    end
    
    -- 修复：正确的 UE API
    self.CleanupTimerHandle = UE.UKismetSystemLibrary.K2_SetTimer(
        Context,           -- 需要 UE Object (Actor/World/GameInstance)
        "OnCleanupTimer",  -- 函数名（字符串）
        Interval,          -- 间隔时间
        true               -- 循环
    )
end

function ResourcePoolManager:StopCleanupTimer()
    if self.CleanupTimerHandle and self.TimerContext then
        UE.UKismetSystemLibrary.K2_ClearTimer(self.TimerContext, "OnCleanupTimer")
        self.CleanupTimerHandle = nil
        self.TimerContext = nil
    end
end

function ResourcePoolManager:OnCleanupTimer()
    if self.Pool then
        local Cleaned = self.Pool:CleanupExpired()
        if Cleaned > 0 then
            print(string.format("ResourcePoolManager: Cleaned %d expired items", Cleaned))
        end
    end
end

-- 设置计时器上下文（在游戏初始化时调用）
function ResourcePoolManager:SetTimerContext(Context)
    self.TimerContext = Context
    if Context then
        self:StartCleanupTimer(5.0, Context)
    end
end

-- ==================== 同步加载 ====================
function ResourcePoolManager:SyncLoad(Path)
    if not Path then return nil end
    
    local ok, obj = pcall(function()
        return UE.UObjectPoolBlueprintLibrary.RequestSyncLoad(Path, 100, "RCP_Sync", false)
    end)
    
    return ok and obj or nil
end

-- ==================== 异步加载 ====================
function ResourcePoolManager:AsyncLoad(Path, Callback, Priority)
    if not Path or not Callback then return nil end
    
    local ok, reqId = pcall(function()
        return UE.UObjectPoolBlueprintLibrary.RequestAsyncLoad(
            Path,
            function(UserData, LoadedPath, LoadedObj, ReqId)
                if LoadedObj and self.Pool then
                    self.Pool:AddLruPool(LoadedPath, LoadedObj)
                end
                Callback(LoadedObj)
            end,
            Priority or 100,
            "RCP_Async",
            true,
            false
        )
    end)
    
    return ok and reqId or nil
end

return ResourcePoolManager