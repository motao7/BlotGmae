-- InitGame.lua
local UIConfig = require("UIPool.UIConfig")  
local UIPoolManager = require("UIPool.UIPoolManager")

-- 创建全局变量
_G.UIPoolMgr = UIPoolManager.New({StagePoolMaxPerType = 100,
    CacheQueueHugeMaxNum = 300,CacheQueueTotalNum = 500,ItemPoolMaxPerType =100})
_G.UICfg = UIConfig

