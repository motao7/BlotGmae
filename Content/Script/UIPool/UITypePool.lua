-----------------------------------------------------------------------
-- ★ 精华1: UITypePool — 按类型分桶的LIFO栈池
--
-- 性能要点:
--   按Type分桶后, Pop时直接hash查找桶 → O(1)出栈, 无需遍历
-----------------------------------------------------------------------
local UITypePool = {}
UITypePool.__index = UITypePool

--buckets是一个表，用来存储不同类型的对象池
--和一个MaxPreType属性，表示每种类型的对象池中最大储存的对象数量
function UITypePool.New(MaxPreType)
    return setmetatable(
        {
            Buckets = {}, 
            MaxPreType = MaxPreType or 10
        },
        UITypePool
    )
end

-- 将对象推入指定类型的对象池
-- @return boolean true=入池成功，false=入池失败（池已满或参数无效）
function UITypePool:Push(WidgetType, Widget)
    if not Widget or not WidgetType then return false end

    local Bucket = self.Buckets[WidgetType]
    if not Bucket then
        Bucket = {}
        self.Buckets[WidgetType] = Bucket
    end

    if #Bucket < self.MaxPreType then
        table.insert(Bucket, Widget)
        return true
    end

    return false                    
end

function UITypePool:Pop(WidgetType)
    local Bucket = self.Buckets[WidgetType]
    if Bucket and #Bucket > 0 then
        return table.remove(Bucket)
    end
    return nil
end

function UITypePool:ClearType(WidgetType, OnWidgetDestroy)
    local Bucket = self.Buckets[WidgetType]
    if Bucket then
        if OnWidgetDestroy then
            for _, Widget in ipairs(Bucket) do
                OnWidgetDestroy(Widget)
            end
        end
        self.Buckets[WidgetType] = nil
    end
end

function UITypePool:ReleaseAll(OnWidgetDestroy)
    for _, Bucket in pairs(self.Buckets) do
        if OnWidgetDestroy then
            for _, Widget in ipairs(Bucket) do
                OnWidgetDestroy(Widget)
            end
        end
    end
    self.Buckets = {}
end

-- 获取当前所有存在的所有Bucket(栈)的类型
function UITypePool:GetTypes()
    local Types = {}
    for Type, _ in pairs(self.Buckets) do
        table.insert(Types, Type)
    end
    return Types
end

function UITypePool:GetCount(WidgetType)
    local Bucket = self.Buckets[WidgetType]
    return Bucket and #Bucket or 0
end

function UITypePool:GetTotalCount()
    local total = 0
    for _, Bucket in pairs(self.Buckets) do
        total = total + #Bucket
    end
    return total
end

return UITypePool