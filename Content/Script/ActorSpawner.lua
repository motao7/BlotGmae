local M = UnLua.Class()

function M:CalculateSpawnLocations()
    if not self.ActorClass then
        print("[ActorSpawner] Error: ActorClass is nil")
        return {}
    end
    
    local origin = self:K2_GetActorLocation()
    local SpawnLocations = {}
    
    for i = 0, self.SpawnCountX - 1 do
        local SpawnX = origin.X + i * self.SpacingX
        for j = 0, self.SpawnCountY - 1 do
            local SpawnY = origin.Y + j * self.SpacingY
            table.insert(SpawnLocations, UE.FVector(SpawnX, SpawnY, origin.Z))
        end
    end
    
    return SpawnLocations
end

function M:DrawDebugPoints(Locations)
    if not Locations then return end
    local World = self:GetWorld()
    if not World then return end
    
    for _, Loc in ipairs(Locations) do
        UE.UKismetSystemLibrary.DrawDebugBox(
            World, Loc, UE.FVector(30, 30, 30),
            UE.FLinearColor(1, 0, 0, 1), UE.FRotator(0, 0, 0), 1.0, 2.0
        )
    end
end

function M:SpawnActors(Locations)
    if not Locations or not self.ActorClass then return end
    local World = self:GetWorld()
    if not World then return end
    
    for _, Loc in ipairs(Locations) do
        local Transform = UE.FTransform()
        Transform.Translation = Loc
        Transform.Rotation = UE.FRotator(0, 0, 0)
        Transform.Scale3D = UE.FVector(1, 1, 1)

        local Params = UE.FActorSpawnParameters()
        Params.Owner = self
        Params.SpawnCollisionHandlingOverride = UE.ESpawnActorCollisionHandlingMethod.AlwaysSpawn

        World:SpawnActor(self.ActorClass,Transform,Params)
    end
end

function M:ReceiveBeginPlay()
    local SpawnLocs = self:CalculateSpawnLocations()
    self:DrawDebugPoints(SpawnLocs)
    self:SpawnActors(SpawnLocs)
end

return M