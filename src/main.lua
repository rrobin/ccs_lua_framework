-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

log = function(...)
    glabel:setString(string.format(...))
    cclog(...)
end

require("init")

CardEntry = 
{
    filename = "card.dbc",
    fmt = "isbiiiibibiii",
    [1] = "id",
    [2] = "name",
    [3] = "level",
    [4] = "hp",
    [5] = "damage",
    [6] = "agility",
    [7] = "exp",
    [8] = "quality",
    [9] = "spellId",
    [10] =  "Class",
    [11] = "leadership",
    [12] = "price",
    [13] = "display",
}

SceneEntry =
{
    filename = "scene.dbc",
    fmt = "nssiiibibffiiiiiii",
    [1] = "id",
    [2] = "name", 
    [3] = "description",
    [4] = "icon",
    [5] = "bgm",
    [6] = "group",
    [7] = "reqLv",
    [8] = "reqEnergy",
    [9] = "waves",
    [10] = "difficultHp",
    [11] = "difficultDamage",
    [12] = "roundforskill",          
    [13] = "redodds",                    
    [14] = "yellowodds",
    [15] = "greenodds",
    [16] = "blueodds",
    [17] = "skullodds",
    [18] = "moneyodds",
}

SceneGroup =
{
    filename = "scenegroup.dbc",
    fmt = "nssi",
    [1] = "id",
    [2] = "name",
    [3] = "description",
    [4] = "icon",
}

local _creatureCard = function()
return
{
    [1] = "id",
    [2] = "lv",
    [3] = "spellLv",
}
end

 CreatureEntry =
{
    filename = "creature.dbc",
    fmt = "nsbiiiiifffffibbibbibbibbibbii",
    [1] = "id",
    [2] = "name",
    [3] = "level",
    [4] = "icon",
    [5] = Array("mana",4,0),
    [6] = Array("getMane",5,0),
    [7] = Array("cards",5,_creatureCard()),
    [8] = "sceneId",
    [9] = "waves",
}

SpellEntry = 
{
    filename = "spell.dbc",
    fmt = "issibbbiiiiiiiiiiiiiiiiiii",
    [1] = "id",
    [2] =  "name",
    [3] = "description",
    [4] = "icon",
    [5] =  "star",
    [6] =  "Class",
    [7] =  "rare",
    [8] = "level",
    [9] = "effect",
    [10] =  "va",
    [11] =  "vb",
    [12] =  "vc",
    [13] =  "vd",
    [14] = "target",
    [15] = "cost_red",
    [16] = "cost_yellow",
    [17] = "cost_green",
    [18] = "cost_blue",
    [19] = "aura_one",
    [20] = "auone1",
    [21] = "auone2",
    [22] = "aura_two",
    [23] = "autwo1",
    [24] = "autwo2",
    [25] = "cooldown",
    [26] = "SpellVisual",
}

CardDisplay =
{
    filename = "carddisplay.dbc",
    fmt = "nii",
    [1] = "id",
    [2] = "icon_id",
    [3] = "BigIcon_id",
}

Icon =
{
    filename = "icon.dbc",
    fmt = "ns",
    [1] = "id",
    [2] = "Path",
}

Card_UpGrade =
{
    filename = "card_upgrade.dbc",
    fmt = "iiiiiii",
    [1] = "quality",
    [2] = "level",
    [3] = "req_goid",
    [4] = "own_exp",
    [5] = "next_ext",
    [6] = "health_a",
    [7] = "attack_a",
}

Player_UpGrate = 
{
    filename = "player_upgrate.dbc",
    fmt = "iiiiiiiiiiiiiiii",
    [1] = "classid",
    [2] = "level",
    [3] = "next_exp",
    [4] = "leadship",
    [5] = "stamina",
    [6] = "up_hp",
    [7] = "uplimt_r",
    [8] = "profit_r",
    [9] = "uplimt_y",
    [10] = "profit_y",
    [11] = "uplimt_g",
    [12] = "profit_g",
    [13] = "uplimt_b",
    [14] = "profit_b",
    [15] = "profit_m",
    [16] = "profit_d",
}

loot_template = 
{
    filename = "loot_template.dbc",
    fmt = "iiiiiii",
    [1] = "entry",
    [2] = "item",
    [3] = "chanceorquestchance",
    [4] = "groupid",
    [5] = "mincountorref",
    [6] = "maxcount",
    [7] = "condition_id",
}

card_sell =
{
    filename = "card_sell.dbc",
    fmt = "iii",
    [1] = "quality",
    [2] = "level",
    [3] = "gold",
}

card_reveltion =
{
    filename = "card_reveltion.dbc",
    fmt = "niiiiii",
    [1] = "entry",
    [2] = "next_entry",
    [3] = "card_1",
    [4] = "card_2",
    [5] = "card_3",
    [6] = "card_4",
    [7] = "card_5",
}

PocketHeroLocaleStringEntry = 
{
    filename = "string.dbc",
    fmt = "nsssssssss",
    [1]   =   "id",
    [2]   =    Array("content",9,""),
}


CResourceEntry = 
{
    filename = "client_resource.dbc",
    fmt = "nsii",
    [1]  = "id",
    [2]  = "path",
    [3]  = "type",               
    [4]  = "phase",             
}

GameMapInit =
{
    filename = "GameMapInit.dbc",
    fmt = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
    [1] = "id", --关卡id
    [2] = Array("area",49,0),  --宝石位置
}

SpellVisualEntry = -- sizeof(0x80)
{
    filename = "spellVisual.dbc",
    fmt = "niiiiiibiiiiiiiiiifiiffff",
    [1] ="m_ID", 
    [2] ="m_precastKit",                -- 咏唱时的特效
    [3] ="m_castKit",                   -- 施放成功时的特效
    [4] ="m_impactKit",                 -- 打击到目标的特效
    [5] ="m_stateKit",                  -- 得到状态时的特效
    [6] ="m_stateDoneKit",              -- 状态消失时的特效
    [7] ="m_channelKit",                -- 连线引导的特效
    [8] =  "m_hasMissile",                -- 是否有飞行模型
    [9] ="m_missileModel",              -- 飞行道具的模型
    [10] ="m_missilePathType",           -- 飞行轨迹类型 手榴弹轨迹
    [11] ="m_missileSound",
    [12] = "m_flags",                     -- 标识位,详见SpellVisualFlag枚举
    [13] ="m_casterImpactKit",           -- unused   
    [14] ="m_targetImpactKit",           -- unused
    [15] ="m_instantAreaKit",            -- 立即在区域显示的Kit
    [16] ="m_impactAreaKit",             -- 冲击到区域时的Kit?
    [17] ="m_persistentAreaKit",         -- 持续在区域显示的Kit
    [18] ="m_missileFollowGroundHeight",         -- 下坠物距离地面的高度
    [19] = "m_missileFollowGroundDropSpeed",      -- 下坠速度
    [20] ="m_missileFollowGroundApproach",       -- 下坠方式
    [21] ="m_missileFollowGroundFlags",          -- 下坠标识位
    [22] = "m_missileCastOffsetX", 
    [23] = "m_missileCastOffsetY", 
    [24] = "m_missileImpactOffsetX", 
    [25] = "m_missileImpactOffsetY",  
}

SpellVisualKit = 
{
    filename = "spellVisualkit.dbc",
    fmt = "niiiiiiiiiiiiii",
    [1] = "m_id",
    [2] = "animationData",
    [3] = Array("EffectId",11,0),
    [4] = "soundId",
    [5] = "cameraId",
    --  []  flag,           -- 终于还是在kit中加入了flag
    --  uint8   red,
    --  uint8   green,
    --  uint8   blue,
    --  uint8   alpha,
}

SpellVisualEffect = 
{
    filename = "spellVisualeffect.dbc",
    fmt = "nssiiffi",
    [1] = "m_id",
    [2] =  "path",           -- resource path
    [3] =  "name",           -- effcet name that in the resource's config
    [4] = "flags",          -- flag color or scale or slow or loop or misc
    [5] = "color",          -- colour owner
    [6] =  "scale",          -- scale owner 
    [7] =  "slow",           -- slow play default:1.0f
    [8] = "delay",
}

function checkfunc(dbcstores)
    local lastId = 0
    local n = 0
    local calc = 0
    local errorlist = {}
    for k,v in pairs(dbcstores) do
        if lastId == 0 then
            lastId = k
        end

        if v.id ~= lastId then
            local check = (n * (n + 1))/2
            if check ~= calc then
                errorlist[#errorlist+1] = {id = lastId,num = n}
            end
            lastId = v.id
            n = 0
            calc = 0
        end

        if v.id == lastId then
            n = n + 1
            calc = calc + v.level
        end
    end
    return errorlist
end

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    --[[   
    local time = os.time()
    sCardStores = uber.dbc.load( CardEntry )
    sCreatureStores = uber.dbc.load( CreatureEntry )
    sSceneStores = uber.dbc.load( SceneEntry )
    sSceneGroupStores = uber.dbc.load( SceneGroup )
    sSpellStores = uber.dbc.load( SpellEntry )
    sCardDisplayStores = uber.dbc.load( CardDisplay )
    sIconStores = uber.dbc.load( Icon )
    sCardUpGradeStores = uber.dbc.load( Card_UpGrade )
    sPlayerUpGradeStores = uber.dbc.load( Player_UpGrate )
    sLootStores = uber.dbc.load( loot_template )
    sCardSellStores = uber.dbc.load( card_sell )
    sCardReveltionStores = uber.dbc.load( card_reveltion )
    sStringStores = uber.dbc.load( PocketHeroLocaleStringEntry )
    sResourceStores = uber.dbc.load( CResourceEntry )
    sGameMapInitStores = uber.dbc.load( GameMapInit )
    sSpellVisualStores = uber.dbc.load( SpellVisualEntry )
    sSpellVisualKitStores = uber.dbc.load( SpellVisualKit )
    sSpellEffectStores = uber.dbc.load( SpellVisualEffect )

    for k,v in pairs(sCreatureStores) do
        cclog(v.id .."   " .. v.name)
    end
    cclog("load time :"..os.time()-time.."s")
 
    local t = checkfunc(sCardStores)
    for k,v in pairs(t) do
        cclog("Card id:"..v.id.." nums :"..v.num)
    end]]
--[[
    local object = require("BrightSprite").new("mage","firespell")
    object:setPosition(cc.CENTER)
    local array = CCArray:create()
    array:addObject(CCDelayTime:create(13/25))
    array:addObject(CCScriptAction:create(8/25,function(time) 
            object._brightness = 0.7*time
            end))
    --亮度渐变为170%
    --array:addObject(CCDelayTime:create(8/25))
    array:addObject(CCScriptAction:create(8/25,function(time) 
            object._brightness = 0.7*(1-time)
            end))
    --array:addObject(CCDelayTime:create(8/25))
    array:addObject(CCFadeOut:create(7/25))
    local array2 = CCArray:create()
    array2:addObject(CCSequence:createWithTwoActions(CCCallFunc:create(function() 
        object:setScale(3.25)
        object:setOpacity(0)
        end),CCDelayTime:create(36/25)))
    array2:addObject(CCSequence:create(array))
    array2:addObject(CCRotateBy:create(36/25,-58))
    array2:addObject(CCSequence:createWithTwoActions(CCFadeIn:create(13/25),CCDelayTime:create(23/25)))
    array2:addObject(CCSequence:createWithTwoActions(CCScaleTo:create(13/25,1),CCDelayTime:create(23/25)))
    object:runAction(CCRepeatForever:create(CCSpawn:create(array2)))
    local object = require("BrightSprite").new("暗系法阵.png")--GameObject.new("rm")
    object:setPosition(cc.CENTER)
    local brightAction = CCScriptAction:create(1.0,function(time)
        object._brightness = 1.0*time
        end)
    local brightAction2 =  CCScriptAction:create(1.0,function(time)
        object._brightness = 1.0-1.0*time
        end)
    local array = CCArray:create()
    array:addObject(brightAction)
    array:addObject(CCDelayTime:create(0.5))
    array:addObject(brightAction2)
    object:runAction(CCRepeatForever:create(CCSequence:create(array)))--CCSequence:createWithTwoActions(brightAction,brightAction2)
    --object:playAction("stand")
    ]]
--[[
    network.loginAddress = "192.168.1.147:3800"--"192.168.1.110:3724"
    local scene = cc.Scene:create()
    local layer = cc.Layer:create()
    scene:addChild(layer)
    glabel = ccui.label({ text = "悠倍欢迎你", fontSize = 40, x = cc.CENTER.x, y = winSize.height/5*4 })
    layer:addChild(glabel)
    local login = ccui.loadWidget("Login/Login.ExportJson")
    SET_POS(login,cc.CENTER.x-login:getSize().width/2,cc.CENTER.y-login:getSize().height/2)
 
    function upIme(uiwidget)
        local pos = uiwidget:getPosition()
        SET_POS(uiwidget,pos.x,pos.y+5)
    end

    function downIme(uiwidget)
        local pos = uiwidget:getPosition()
        SET_POS(uiwidget,pos.x,pos.y-5)
    end
    local name = login:getChild("TF_name")
    name:setText(PlatformUtility:getAccount())
    name:addTextFieldEvent({[ccui.TextFiledEventType.attach_with_ime] = upIme,
        [ccui.TextFiledEventType.detach_with_ime] = downIme})
    local password = login:getChild("TF_password")
    password:addTextFieldEvent({[ccui.TextFiledEventType.attach_with_ime] = upIme,
        [ccui.TextFiledEventType.detach_with_ime] = downIme})
    password:setText(PlatformUtility:getPassword())
    local confirm = login:getChild("TextField_29")
    confirm:addTextFieldEvent({[ccui.TextFiledEventType.attach_with_ime] = upIme,
        [ccui.TextFiledEventType.detach_with_ime] = downIme})
    confirm:setVisible(false)
    confirm:setTouchEnable(false)
    --confirm:setText("123456")

    local connect = login:getChild("login")
    connect:addTouchEvent({[ccui.TouchEventType.ended] = function(uiwidget)
            local nameStr = name:getStringValue()
            local pswStr = password:getStringValue()
            
            if network.ConnectLoginServer(network.loginAddress) == false then
               log("连接登陆服务器失败!")
               return
            end
            local AnonymLogin = false
            if nameStr == "" then
                local AnonymAccount = PlatformUtility:getAnonymAccount()
                if AnonymAccount == "" then
                    local send_packet = WorldPacket:new(CMD_CREATE_ANONYMOUS_ACCOUNT,60)
                    local macAddress = PlatformUtility:GetDeviceMacAddress()
                    send_packet:setStr(macAddress)
                    network.send(send_packet)
                    log("创建匿名账号")
                    return
                end
                nameStr = AnonymAccount
                AnonymLogin = true
                log("匿名账号登陆")
            else
                PlatformUtility:setAccount(nameStr)
            end

            if pswStr == "" then
                if AnonymLogin == true then
                    pswStr = "000000"
                else
                    log("请输入密码")
                    return
                end
            else
                if AnonymLogin == false then
                    PlatformUtility:setAccount(pswStr)
                    log("注册账号登陆")
                end
            end

            network.SetUserNameAndPassWord(nameStr,pswStr)
            local send_packet = WorldPacket:new(CMD_AUTH_LOGON_CHALLENGE_2,100)
            send_packet:setStr("zhCN")
            send_packet:setStr(nameStr)
            network.send(send_packet)
         end})
    local create = login:getChild("create")
    create:setTitleText("注销")
    create:addTouchEvent({[ccui.TouchEventType.ended] = function(uiwidget)
            PlatformUtility:setAccount("")
            PlatformUtility:setPassword("")
            name:setText("")
            password:setText("")
            log("注销了记录的注册账号")
        end})
    local btn = ccui.button({ x = cc.CENTER.x - 200 , y = cc.CENTER.y,
            normal = "3.png",
            listener = {[ccui.TouchEventType.ended] = function()
            log("发送ping")
            local sendpacket = WorldPacket:new(CMSG_GAME_PING,12)
            sendpacket:setU32(os.time())
            sendpacket:setU32(0)
            network.send(sendpacket)
            end},
            })
    btn2 = ccui.button({ x = cc.CENTER.x + 200 , y = cc.CENTER.y,
            normal = "6.png",
            touch = false,
            listener = {[ccui.TouchEventType.ended] = function()
                if network.reConnect() == false then
                    log("重新连接服务器失败，是否重试?")
                end
              end},
            })
    -- 重新设置需要重连的界面
    network.onNeedReConnect = function()
        log("网络断开，是否重新连接?")
        btn2:setVisible(true)
        btn2:setTouchEnabled(true)
    end
    network.onReConnect = function()
        btn2:setVisible(false)
        btn2:setTouchEnabled(false)
    end
   
    btn2:setVisible(false)
    layer:addChild(login)
    layer:addChild(btn)
    layer:addChild(btn2)
    --scene:addChild(object)
    network.SetPingCode(CMSG_GAME_PING)
    sharedDirector:runWithScene(scene)
]]
    local shaders = { {v = "shaders/TPC_noMvp.vsh", f = "shaders/BanishShader.fsh", n = "BanishShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/FrozenShader.fsh", n = "FrozenShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/GrayScalingShader.fsh", n = "GrayScalingShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/IceShader.fsh", n = "IceShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/PoisonShader.fsh", n = "PoisonShader"},
    {v = "shaders/TPC_noMvp.vsh", f = "shaders/StoneShader.fsh", n = "StoneShader"},
    --{v = "shaders/TPC_noMvp.vsh", f = "shaders/ghostlike_filterX.fsh", n = "ghostlike_filterX"},
    }
    
    local scene = cc.Scene:create()
    local layer = cc.LayerColor:create(cc.c4b(100, 100, 200, 255),winSize.width,winSize.height)
    scene:addChild(layer)
    
    --local sprite = cc.Sprite:AutoCreate("autocombat_on")
    --layer:addChild(sprite)
    --sprite:setPosition(cc.CENTER)
    --[[
    for k,v in ipairs(shaders) do
        display.addShader(v.v,v.f,v.n)
        local spr = cc.Sprite:create("boss24.png")
        layer:addChild(spr)
        spr:setShader(v.n)
        spr:setPosition(cc.p(((k-1)%3+1)*spr:getSize().width,(math.modf((k-1)/3))*cc.CENTER.y+spr:getSize().height/2+20))
        local label = ccui.label({text = string.gsub(v.n,"Shader",""),
            font = "Lolita.TTF",
            fontSize = 24,
            x = spr:getPositionX(),
            y = spr:getPositionY()-spr:getSize().height/2})
        layer:addChild(label)
        local node = tolua.cast(label:getVirtualRenderer(),"cc.Label")
        node:enableOutline(cc.c4b(0,0,0,255),2)
    end
    
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("Character/bandiangou/bandiangou.ExportJson")
    local armature = ccs.Armature:create("bandiangou")
    armature:setPosition(cc.CENTER)
    
    armature:getAnimation():play("跑步")
    layer:addChild(armature)
    
    local label = ccui.label({
        text = 1.0,
        x = cc.CENTER.x,
        y = cc.CENTER.y-80,
        })
    layer:addChild(label)
    local slider = ccui.slider({
        bar     = "sliderTrack.png",
        ball_n  = "sliderThumb.png",
        ball_p  = "sliderThumb.png",
        progress = "sliderProgress.png",
        x = cc.CENTER.x,
        y = cc.CENTER.y-60,
        eventHandle = function(uiwidget)
            local percent = uiwidget:getPercent()
            armature:getAnimation():setSpeedScale(2*percent/100)
            label:setString(string.format("%.2f",2*percent/100))
        end,
        })
    slider:setPercent(50)
    
    layer:addChild(slider)
    ]]

    local resTable = {
                        "warrior","priest","mage","dz_zt_02a","dz_sk_xs","qs_sk_04","qs_zt_05",
                        "ms_sk_04f","qs_zt_02","ms_sk_03g","fs_ht_09","npc_sk_03_1","fs_ht_07",
                        "npc_sk_03_5","buf_sanbi","lr_zt_01","buf_shjs","buf_kongju","buf_zhuzhou1",
                        "buf_hunmi","zs_sk_05f","zs_sk_05g","fs_sk_04","lr_zt_dk","qs_zt_03","zs_sk_09f",
                        "zs_sk_09g","zs_ht_02","buf_jiansu","zs_sk_07","zs_at_04","ms_at_02","ms_at_01",
                        "ms_cs_01","ms_zt_04","ms_sk_01","ms_sk_02","ms_at_03","ms_cs_03","ms_at_fly2",
                        "fs_at_01","fs_fly_01","fs_at_03","fa_hurt_03","fs_fly_02","fs_at_02","fs_ht_04",
                        "fs_fly_03","npc_sk_03_2","fs_skill_07_1","fs_ht_10","wolfg","dragonfb","dz_ht_bj",
                        "buf_pojia","buf_meihuo","lr_sk_bx","ws_cs_qgp","ws_cs_qgp2"
                    }
    
    cclog("gonna loading")
    uber.TimingBegin()
    for i = 1,#resTable do
        local sprite = cc.Sprite:create()
        sprite:load(resTable[i])
        sprite:playAction("stand")
        sprite:setPosition(cc.p(100*(i%6 + 1),300 + (math.modf(i/6))*100))
        layer:addChild(sprite)
    end
    uber.TimingEnd("loading time:")
    local label = ccui.label({text = "耗时:"..uber.endTime-uber.beginTime})
    label:setColor(cc.c3b(0,0,0))
    label:setPosition(cc.p(cc.CENTER.x,200))
    layer:addChild(label)

    cc.runScene(scene)
    require("MyApp"):new()
end

xpcall(main, __G__TRACKBACK__)
