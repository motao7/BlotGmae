local ResourcePoolTest = {}

function ResourcePoolTest.Test()
    local World = _G.ResPoolMgr:GetWorld()
    if not World then return end

    local ObejctPath = "/Game/PerformenceOptimization/BP_TestUObject.BP_TestUObject_C"
    local ObjectClass = _G.ResPoolMgr:SyncLoad(ObejctPath)

    print("========== [GC Test] Start ==========")
    
    ResourcePoolTest.Obj_A = UE.NewObject(ObjectClass)
    ResourcePoolTest.Obj_B = UE.NewObject(ObjectClass)

    -- 阶段2: 给 Obj_A 加上 Ref（模拟 UPROPERTY）
    if ResourcePoolTest.Obj_A then
        ResourcePoolTest.RefHandle_A = UnLua.Ref(ResourcePoolTest.Obj_A)  -- 保存句柄，阻止UE GC回收Obj_A
        print("Obj_A referenced with UnLua.Ref")
    end
    
end

-- 手动释放 Lua 引用
function ResourcePoolTest.ReleaseLuaReferences()
    print("========== [GC Test] Releasing Lua References ==========")
    
    -- 切断 Lua 变量引用
    ResourcePoolTest.Obj_A = nil
    ResourcePoolTest.Obj_B = nil
    
    UE.UKismetSystemLibrary.CollectGarbage()
end

return ResourcePoolTest