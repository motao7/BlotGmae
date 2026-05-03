-- ResourcePool.lua
-- 纯 Lua 类，不依赖任何 UE 特性
-- 只被 Manager 调用，不对外暴露
local M = {}

-- ==================== 配置 ====================
M.Config = {
    LruMaxNum  = 100,
    ExpireTime = 60,
}

-- ==================== 构造 ====================
function M:new(Config)
    local instance = {}
    setmetatable(instance, self)
    self.__index = self
    
    Config = Config or {}
    instance.LruMax     = Config.LruMaxNum or M.Config.LruMaxNum
    instance.ExpireTime = Config.ExpireTime or M.Config.ExpireTime
    
    instance.LruPool    = {}     -- [path] = { time, object }
    instance.StablePool = {}     -- [path] = object
    instance.Orders     = {}     -- 有序path列表, 尾部最新, 头部最老
    instance.IndexMap   = {}     -- [path] = position in order
    instance.LastCheckTime = os.time()
    
    return instance
end

-- ==================== LRU 内部方法 ====================
function M:LruMoveToTail(Path)
    local i = self.IndexMap[Path]
    if not i then return end
    
    table.remove(self.Orders, i)
    
    for j = i, #self.Orders do 
        self.IndexMap[self.Orders[j]] = j 
    end
    
    table.insert(self.Orders, Path)
    self.IndexMap[Path] = #self.Orders
end

function M:LruRemoveHead()
    if #self.Orders == 0 then return end
    
    local Head = table.remove(self.Orders, 1)
    self.IndexMap[Head] = nil
    self.LruPool[Head] = nil
end

function M:LruShrink(TargetNum)
    while #self.Orders >= TargetNum do 
        self:LruRemoveHead() 
    end
end

function M:LruInsert(Path, Object)
    if not Path or not Object then return end
    
    if self.StablePool[Path] then
        self.StablePool[Path] = Object 
        return
    end
    
    if self.LruPool[Path] then
        self.LruPool[Path] = { time = os.time(), obj = Object }
        self:LruMoveToTail(Path)
        return
    end
    
    self:LruShrink(self.LruMax - 1)
    
    table.insert(self.Orders, Path)
    self.IndexMap[Path] = #self.Orders
    self.LruPool[Path] = { time = os.time(), obj = Object }
end

function M:LruErase(Path)
    self.LruPool[Path] = nil
    
    local index = self.IndexMap[Path]
    if not index then return end
    
    table.remove(self.Orders, index)
    
    for j = index, #self.Orders do 
        self.IndexMap[self.Orders[j]] = j 
    end
    
    self.IndexMap[Path] = nil
end

-- ==================== TTL 清理 ====================
function M:CleanupExpired()
    local now = os.time()
    local ToClean = {}
    
    for _, Path in ipairs(self.Orders) do
        local entry = self.LruPool[Path]
        if entry and (now - entry.time > self.ExpireTime) then
            table.insert(ToClean, Path)
        else
            break
        end
    end
    
    for _, Path in ipairs(ToClean) do
        self:LruErase(Path)
    end
    
    return #ToClean
end

-- ==================== 公开 API（仅 Manager 调用）====================
function M:AddLruPool(Path, Object)
    if not Path or not Object then return end
    self:LruInsert(Path, Object)
end

function M:AddStablePool(Path, Object)
    if not Path then return end
    self.StablePool[Path] = Object
    self:LruErase(Path)
end

function M:GetFromLru(Path)
    local entry = self.LruPool[Path]
    if entry then
        entry.time = os.time()
        self:LruMoveToTail(Path)
        return entry.obj
    end
    return nil
end

function M:GetFromStable(Path)
    return self.StablePool[Path]
end

function M:IsStable(Path)
    return self.StablePool[Path] ~= nil
end

function M:GetLruCount()
    local n = 0
    for _ in pairs(self.LruPool) do n = n + 1 end
    return n
end

function M:GetStableCount()
    local n = 0
    for _ in pairs(self.StablePool) do n = n + 1 end
    return n
end

function M:GetStats()
    return {
        LruSize = self:GetLruCount(),
        StableSize = self:GetStableCount(),
        MaxLruSize = self.LruMax,
        ExpireTime = self.ExpireTime
    }
end

function M:ClearLru()
    self.LruPool = {}
    self.Orders = {}
    self.IndexMap = {}
end

function M:ClearStable()
    self.StablePool = {}
end

function M:ClearAll()
    self:ClearLru()
    self:ClearStable()
end

return M