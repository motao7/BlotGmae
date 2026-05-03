local LodDefine = {}

LodDefine.ERegionType =
{
    NoneRegion    = 0,   --不分区，全局遍历对象
    WeaponSrapper =1,    --武器包装分区(细颗粒度)
    Character     =2,    --角色分区(粗颗粒度)
}

LodDefine.RegionConfig =
{
    [LodDefine.ERegionType.NoneRegion] =
    {
        SideLength = math.huge, --无限大，不分区，所有组件在一个格子
        DebugColor = {R=0,G=0,B=1,A=1}  --Blue
    },
    [LodDefine.ERegionType.WeaponSrapper]=
    {
        SideLength = 1000.0,
        DebugColor = {R=0,G=1,B=0,A=1}  --Green
    },
    [LodDefine.ERegionType.Character]=
    {
        SideLength = 1300.0,
        DebugColor = {R=1,G=1,B=0,A=1}  --Yellow
    }
}

LodDefine.UpdateInterval = 1.0
return LodDefine