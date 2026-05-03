--- LodManager.lua
--- LOD 管理器（驱动器）
---
--- 挂载在本地玩家身上，周期性地：
---   ① 获取本地玩家位置
---   ② 通过空间网格查找附近的所有LOD组件
---   ③ 逐个计算距离并驱动LOD更新
---
--- 技术点：
---  ⑩ 定时节流（不每帧更新，默认1秒一次）
---  ⑪ 仅本地玩家端执行（Client-only）
---  ⑫ 遍历所有已注册的区域类型
---  ⑬ 可选调试绘制

local LodDefine = require("LodSystem.LodDefine")
local LodGrid = require("LodSystem.LodGrid")

local LodManager = {}

-- lua侧本地属性
LodManager._PlayerActor = nil   --本地玩家pawn
LodManager._UpdateInterval = LodDefine.UpdateInterval  
LodManager._bEnableDebugDraw = false
LodManager._TimerID = nil
LodManager._bRunning = false 

--- ============================================================
---  初始化管理器（在游戏开始/进入战场时调用）
---  @param LocalPlayerPawn  本地玩家的 Pawn/Actor
---  @param UpdateInterval   更新间隔（秒），nil则用默认值
--- ============================================================
function LodManager:Initialize(LocalPlayerPawn, UpdateInterval)
    if self._bRunning then
        self:Shutdown()
    end

    self._PlayerActor   = LocalPlayerPawn
    self._UpdateInterval = UpdateInterval or LodDefine.DEFAULT_UPDATE_INTERVAL
    self._bRunning       = true

    self._TimerHandle = UE.UKismetSystemLibrary.K2_SetTimer(
        self, 
        "_OnTick" ,                     -- 委托: 绑定到 self 上
        self._updateInterval,           -- 循环间隔
        true                            -- bLooping=true 循环执行                
    )
end

--- ============================================================
--  技术点 ⑩：定时回调（替代C++ TickComponent）
--  每隔 UpdateInterval 秒执行一次
-- ============================================================
function LodManager:_OnTick()
    if not self._bRunning then return end
    if not self._PlayerActor then return end
    if self._PlayerActor:IsPendingKill() then return end

--TODO:Only 模拟player
    -- 技术点 ⑪：仅客户端执行
    -- （UnLua环境中可通过 DataMgr 或类似方式判断）
    local PlayerLoc = self._PlayerActor:GetActorLocation()

    -- 技术点 ⑫：遍历所有区域类型
    for RegionType, Config in pairs(LodDefine.RegionConfig) do
        local bFound, Components = LodGrid.GetNeighborComponents(RegionType, PlayerLoc)

        if bFound and #Components > 0 then
            for _, Comp in ipairs(Components) do
                if Comp:IsValid() then
                    local TargetLoc = Comp:GetWorldLocation()
                    -- 使用 UE4 的 FVector::Dist 计算欧几里得距离
                    local Distance = FVector.Dist(PlayerLoc, TargetLoc)
                    Comp:ProcessDistance(Distance)
                else
                    -- 组件已失效，自动清理
                    Comp:Destroy()
                end
            end
        end
    end

    -- 技术点 ⑬：调试绘制（可选）
    if self._bEnableDebugDraw then
        self:_DebugDraw(PlayerLoc)
    end
end

--- ============================================================
--  技术点 ⑬：调试绘制（复刻原版 DrawDebugBox 逻辑）
-- ============================================================
function LodManager:_DebugDraw(PlayerLoc)
    for RegionType, Config in pairs(LodDefine.RegionConfig) do
        if Config.SideLength == math.huge then goto continue end

        local SideLength = Config.SideLength
        local CX = LodGrid.GetRegionIndex(PlayerLoc.X, SideLength)
        local CY = LodGrid.GetRegionIndex(PlayerLoc.Y, SideLength)

       -- 绘制9个邻居格子
        local Offsets = {
            {0,0}, {0,-1}, {0,1}, {-1,0}, {-1,-1}, {-1,1}, {1,0}, {1,-1}, {1,1}
        }
        for _, off in ipairs(Offsets) do
            local gx, gy = CX + off[1], CY + off[2]
            local CenterX = gx * SideLength
            local CenterY = gy * SideLength
            local BoxCenter = UE.FVector(CenterX, CenterY, PlayerLoc.Z)
            local BoxExtent = UE.FVector(SideLength/2, SideLength/2, 100.0)

            UE.UKismetSystemLibrary.DrawDebugBox(
                self._PlayerActor,
                BoxCenter,
                BoxExtent,
                Config.DebugColor,
                UE.FRotator.ZeroRotator,
                1.0,    -- 持续时间
                10.0    -- 线宽
            )
        end

        ::continue::
    end
end

--- 关闭管理器（离开游戏/切换场景时调用）
function LodManager:Shutdown()
    self._bRunning = false
    if self._TimerHandle then
        UE.UKismetSystemLibrary:K2_ClearTimerDelegate(self._TimerHandle)
    end
    LodGrid.ClearAll()
    log("[LodGrid] Shutdown")
end

--- 开启/关闭调试绘制
function LodManager:SetDebugDraw(bEnable)
    self._bEnableDebugDraw = bEnable
end

return LodManager