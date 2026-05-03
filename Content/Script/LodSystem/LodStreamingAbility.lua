--- LodStreamingAbility.lua
--- Mesh 流式LOD 切换能力（具体业务实现）
---
--- 基于 LodStreamingAbility
---   ⑭ StaticMesh 多级LOD替换（TSoftObjectPtr 异步加载）
---   ⑮ SkeletalMesh 多级LOD替换（支持姿势重置选项）
---   ⑯ 超远距离极简Mesh替换
---   ⑰ 竞态防护（异步回调校验当前LOD等级）


local LodComponent = require("LodSystem.LodComponent")
local LodDefine = require("LodSystem.LodDefine")

local LodStreamingAbility = {}

--- ============================================================
---  工厂方法：创建一个具备流式Mesh切换能力的LOD组件
---
---  @param OwnerActor       被管理的Actor
---  @param Config           配置表，格式见下方示例
---  @param RegionType       分区类型（可选，默认NoneRegion）
---
---  配置表示例：
---  {
---      MaxLodDistance = 8000.0,
---      LodRate = {0.35, 0.35, 0.30},   -- LOD0/1/2 各占35%/35%/30%
---      StaticMeshes = {                   -- StaticMesh LOD组
---          {
---              ComponentTag = "BodyMesh",       -- Actor上的组件Tag名
---              LodAssets = {                      -- 各LOD的资源软引用路径
---                  "/Game/Mesh/Character_High",
---                  "/Game/Mesh/Character_Mid",
---                  "/Game/Mesh/Character_Low",
---              },
---              OutOfDistanceAsset = "/Game/Mesh/Character_Tiny",  -- 超远用
---          },
---      },
---      SkeletalMeshes = {                 -- SkeletalMesh LOD组（同理）
---          {
---              ComponentTag = "SkeletalBody",
---              LodAssets = { ... },
---              OutOfDistanceAsset = "...",
---              bReInitPose = true,           -- 切换时重置蒙太奇姿势
---          },
---      },
---  }
--- ============================================================

function LodStreamingAbility.Create(OwnerActor, Config, RegionType)
    --创建基类实例
    local Base = LodComponent.Create(
        OwnerActor, RegionType or LodDefine.ERegionType.NoneRegion,
        Config.MaxLodDistance, Config.LodRate
    )

    local self = setmetatable(Base, { __index = LodStreamingAbility })

    self.StaticMeshEntries = {}
    self.SkeletalMeshEntries = {}

    -- 解析配置表，创建静态Mesh组件
    if Config.StaticMeshes then
        for _, EntryCfg in ipairs(Config.StaticMeshes) do
            local Entry =
            {
                Tag = EntryCfg.ComponentTag,
                LodAssets = EntryCfg.LodAssets or {},
                OutOfDistAsset = EntryCfg.OutOfDistanceAsset,
                ComponentRef = nil --运行时填充static对应的Component
            }

            local FoundComps = OwnerActor:GetComponentsByTag(UE.UStaticMeshComponent.StaticClass(),Entry.Tag)
            if #FoundComps > 0 then Entry.ComponentRef = FoundComps[1] end
            table.insert(self.StaticMeshEntries, Entry)
        end
    end

    if Config.SkeletalMeshes then
        for _, EntryCfg in ipairs(Config.SkeletalMeshes) do
            local Entry =
            {
                Tag = EntryCfg.ComponentTag,
                LodAssets = EntryCfg.LodAssets or {},
                OutOfDistAsset = EntryCfg.OutOfDistanceAsset,
                bReInitPose = EntryCfg.bReInitPose or false,
                ComponentRef = nil --运行时填充static对应的Component
            }

            local FoundComps = OwnerActor:GetComponentsByTag(UE.UStaticMeshComponent.StaticClass(),Entry.Tag)
            if #FoundComps > 0 then
                Entry.ComponentRef = FoundComps[1]
            end
            table.insert(self.StaticMeshEntries, Entry)
        end
    end

    return self
end

function LodStreamingAbility:OnLodActive(NewLod)
    self:_SwitchStaticMeshes(NewLod)
    self:_SwitchSkeletalMeshes(NewLod)
end

function LodStreamingAbility:OnOutOfMaxDistance()
    self:_SetStaticMeshesToOutDistance()
    self:_SetSkeletalMeshesToOutDistance()
end

--- ============================================================
--  技术点 ⑭ & ⑮：LOD激活回调 —— 执行实际的资源切换
-- =============================================================

function LodStreamingAbility:_SwitchStaticMeshs(TargetLod)
    for _, Entry in ipairs(self.StaticMeshEntries) do
        local Comp = Entry.ComponentRef
        if not Comp or Comp:IsPendingKill() then goto next_entry end

        --边界检查
        if TargetLod >=#Entry.LodAssers then goto next_entry end
        
        --Lua数组1-based
        local AssetPath =Entry.LodAssets[TargetLod+1]
        if not AssetPath then goto next_entry end
        
--TODO:ResourcePool介入
        --尝试同步获取
        local LoadedObj = _G.ResPoolMgr:SyncGet(AssetPath)
        if LoadedObj then
            if Comp:GetStaticMesh() == LoadedObj then goto next_entry end
            Comp:SetStaticMesh(LoadedObj)
        else
            local SelfCopy = self
            local CompCopy = Comp
            local ExpectedLod = TargetLod

--TODO:检查代码
            --异步加载
            _G.ResPoolMgr:AsyncGet(AssetPath, function(LoadedObj)
                if not SelfCopy:IsValid() or SelfCopy.CurrentLod ~= ExpectedLod then return end
                if not CompCopy or CompCopy:IsPendingKill() then return end
            
                CompCopy:SetStaticMesh(LoadedObj)
           end
            )
        end

        ::next_entry::
    end
end

--- ============================================================
--  SkeletalMesh LOD 切换（同上，额外支持 bReInitPose）
-- ============================================================

function LodStreamingAbility:_SwitchSkeletalMeshEntries(TargetLod)
    for _, Entry in ipairs(self.SkeletalMeshEntries) do
        local Comp = Entry.ComponentRef
        if not Comp or Comp:IsPendingKill() then goto next_entry end

        --边界检查
        if TargetLod >=#Entry.LodAssers then goto next_entry end
        
        --Lua数组1-based
        local AssetPath =Entry.LodAssets[TargetLod+1]
        if not AssetPath then goto next_entry end
        
--TODO:ResourcePool介入
        --尝试同步获取
        local LoadedObj = _G.ResPoolMgr:SyncGet(AssetPath)
        if LoadedObj then
            if Comp:GetStaticMesh() == LoadedObj then goto next_entry end
            Comp:SetStaticMesh(LoadedObj)
        else
            local SelfCopy = self
            local CompCopy = Comp
            local ExpectedLod = TargetLod

--TODO:检查代码
            --异步加载
            _G.ResPoolMgr:AsyncGet(AssetPath, function(LoadedObj)
                if not SelfCopy:IsValid() or SelfCopy.CurrentLod ~= ExpectedLod then return end
                if not CompCopy or CompCopy:IsPendingKill() then return end

                --竞态保护是什么?
                -- if SelfWeak.CurrentLod ~= ExpectedLod then return end
                --     if not CompWeak or CompWeak:IsPendingKill() then return end

                --     local NewMesh = Cast_UObject(USkeletalMesh, LoadedObject)
                --     if not NewMesh then return end
                --     if CompWeak:GetSkeletalMesh() == NewMesh then return end
                CompCopy:SetSkeletalMesh(LoadedObj)
           end
            )
        end

        ::next_entry::
    end
end
--- ============================================================
--  技术点 ⑯：超距回调 —— 替换为超远极简模型
-- ============================================================

function LodStreamingAbility:_SetStaticMeshsToOutDistance()
    for _, Entry in ipairs(self.StaticMeshEntries) do
        local Comp = Entry.ComponentRef
        if not Comp or Comp:IsPendingKill() then goto next_entry end

        local AssetPath = Entry.OutOfDistAsset
        if not AssetPath then 
            Comp:SetStaticMesh(nil)
            goto next_entry
        end

        --同步获取/没有尝试异步
        local Obj = _G.ResPoolMgr:SyncGet(AssetPath)
        if Obj then
            if Comp:GetStaticMesh() == Obj then goto next_entry end
            Comp:SetStaticMesh(Obj)
        else
            local CompCopy = Comp
            _G.ResPoolMgr:AsyncGet(AssetPath, 
                function(LoadedObj)
                    if not CompCopy or CompCopy:IsPendingKill() then return end
                    CompCopy:SetStaticMesh(LoadedObj)
                end
            )
        end

        ::next_entry::
    end
end

function LodStreamingAbility:_SetSkeletalMeshsToOutDistance()
    for _, Entry in ipairs(self.SkeletalMeshEntries) do
        local Comp = Entry.ComponentRef
        if not Comp or Comp:IsPendingKill() then goto next_entry end

        local AssetPath = Entry.OutOfDistAsset
        if not AssetPath then 
            Comp:SetSkeletalMesh(nil)
            goto next_entry
        end

        --同步获取/没有尝试异步
        local Obj = _G.ResPoolMgr:SyncGet(AssetPath)
        if Obj then
            if Comp:GetStaticMesh() == Obj then goto next_entry end
            Comp:SetSkeletalMesh(Obj)
        else
            local CompCopy = Comp
            _G.ResPoolMgr:AsyncGet(AssetPath, 
                function(LoadedObj)
                    if not CompCopy or CompCopy:IsPendingKill() then return end
                    CompCopy:SetSkeletalMesh(LoadedObj)
                end
            )
        end

        ::next_entry::
    end
end

return LodStreamingAbility