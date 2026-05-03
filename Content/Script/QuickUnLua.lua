local QuickUnLua = {}

local HighFrequencyFuncList = {"OnTick"}

function QuickUnLua.Class(ClassName,Super)
    local NewClass = 
    {
        ClassName = ClassName,
        Super = Super,
        bClassHighFrequencyFuncCached = false
    }    

    --设置元表实现继承。
    setmetatable(NewClass,
        {
            --__index 当实例查找不到属性时，查找index指向对象，实现继承链
            __index = Super,
            --__call让实例表可以像函数一样调用->Instance(Class,...) =Instance.New(Class,...)
            __call = function(Class, ...) return Class.New(...) end
        }
    )

    --创建实例
    function NewClass:New(...)
        --实例为{}，实例__index为NewClass类
        local Instance = setmetatable({},{__index = NewClass})

        --将高频函数复制到实例，绕过元表查找
        if NewClass.IsClassHighFrequencyFuncCached then
            local FuncMap = NewC
        end
    end
end