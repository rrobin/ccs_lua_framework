network = network or {} 
cclog("required network module")
local sNetConn = CNetConnection:Instance()

local handler = function(event)
    if event == "NETWORK_SENDMGS" then
        network.onSendMessage()
    elseif event == "NETWORK_SENDMGSOK" then
        network.onSendSuccess()
    end
end

network.running = false         -- 运行状态
network.loginAddress = ""       --登陆服务器地址,需要手动设置
network.pingdt = 30             --ping的间隔时间30秒一次,初始设置为30则立即发送一次ping
network.pong   = true           --服务器的ping回应,发送之后设为false,如果下一次发送ping时间到了还没被设为true就断开连接返回登陆界面
network.needPing = false
network.state = nil
network.reconnect = false
network.loop = 0
network.handlers = {}
network.needSend = {} -- 断线重连中不用跳过的opcode

network.onNeedReConnect = function()
    cclog("network onNeedReConnect, you can reset network.onNeedReConnect function!")
end

network.onReConnectFail = function ()
    cclog("network onReConnectFail, you can reset network.onReConnectFail function!")
end

network.onSendMessage = function()
    cclog("network onSendMessage, you can reset network.onSendMessage function!")
end

network.onSendSuccess = function()
    cclog("network onSendSuccess, you can reset network.onSendSuccess function!")
end

network.onRecvMessage = function(opcode)
    cclog("network onRecvMessage, you can reset network.onRecvMessage function!")
end

network.onShutDown = function()
    cclog("network onShutDown, you can reset network.onShutDown function!")
end

network.onReConnect = function()
    cclog("network onReConnect, you can reset network.onReConnect function!")
end

network.onPingFailed = function()
    cclog("network.onPingFailed, you can reset network.onPingFailed function!")
    network.shutdown()
end

network.onConnectFailed = function()
    cclog("network.onConnectFailed, you can reset network.onConnectFailed function!")
    network.shutdown()
end

function network.send(packet)
    local opcode = packet:GetOpcode()
    if network.reconnect == true and not network.needSend[opcode] then
        return
    end
    if network.running == false then
        -- 首先主动断开一下
        network.disconnet()
        network.reSendpack = packet
        network.onNeedReConnect()
        return
    end
    cclog("send opcode = 0x%x",packet:GetOpcode())
    return sNetConn:SendPacket(packet)
end

function network.disconnet()
        return sNetConn:DisConnect()
end

function network.hasPacket()
        return sNetConn:Next()
end

function network.getPacket()
        return sNetConn:GetPacket()
end

function network.popPacket(packet)
        return sNetConn:ReleasePacket(packet)
end

function network.isLoginState(state)
    return sNetConn:IsLoginState(state)
end

function network.isState(state)
    return network.state == state
end

function network.ConnectLoginServer(address)
    if sNetConn:ConnectLoginServer(address) then
        network.state = NLS_LOGINSERVER
        network.startup()
        return true
    end
    return false
end

function network.ConnectGameServer()
    if sNetConn:ConnectGameServer() then
        network.state = NLS_GAMESERVER
        return true
    end
    return false
end

function network.SetUserNameAndPassWord(user,psw)
	return sNetConn:SetUserNameAndPassWord(user,psw)
end

function network.GetClientMd5Str(loginSeed)
	return sNetConn:GetClientMd5Str(loginSeed,"","","")
end

function network.SendLoginPacket(packet)
	return sNetConn:SendLoginPacket(packet)
end

function network.LoginRealmListResponse(packet)
    sNetConn:HandleLoginRealmListResponse(packet)
end

function network.GameAuthChallengeResponse(packet)
    return sNetConn:HandleGameAuthChallengeResponse(packet)
end

function network.getUserName()
    return sNetConn:getUserName()
end

function network.getClientSeed()
    return sNetConn:getClientSeed()
end

function network.getClientMd5()
    return sNetConn:getClientMd5()
end

function network.setVersion( version )
    sNetConn:setVersion(version)
end

function network.sendAuthSessionMessage( )
    sNetConn:sendAuthSessionMessage()
end

function network.SendSignInPacket()
    return sNetConn:SendSignInPacket()
end

function network.ConnectFailed()
    return sNetConn:ConnectFailed()
end

function network.IsConnected(state)
    state = state or -1
    return sNetConn:IsConnected(state)
end

function network.SetPingCode(opcode)
    return sNetConn:SetPingCode(opcode)
end

function network.Ping()
    return sNetConn:OnSendPing()
end

function network.OnRecvPong(time)
    network.pong = true
    return sNetConn:OnRecvPong(time)
end

function network.addHandler(opcode,state,n,h)
    if not network.handlers[state] then
        network.handlers[state] = {}
    end

    network.handlers[state][opcode] = { name = n, handler = h}
end

function network.reConnect()
    local ret = network.running
    if ret == false then
        if network.isState(NLS_LOGINSERVER) then
            ret = network.ConnectLoginServer(network.loginAddress)
        elseif network.isState(NLS_GAMESERVER) then
            ret = network.ConnectGameServer()
        end
        if ret then
            cclog("network reconnect success!")
            network.startup()
            if network.isState(NLS_GAMESERVER) then
                network.reconnect = true
            else
                network.reconnect = false
            end
            network.onReConnect()
        else
            cclog("network reconnect failed!")
            network.onReConnectFail()
        end
    end
    return ret
end

function network.reSend()
    local packet = network.reSendpack
    network.reSendpack = nil
    if packet then
        network.send(packet)
    end
    network.reconnect = false
end

function network.update()
    sNetConn:Update()
end

function network.startup()
    if network.running == false then
        local function loopfun(dt)

            network.update()

            -- 处理网络消息
            while network.hasPacket()
            do
                local packet = network.getPacket()
                local opcode = packet:GetOpcode()
                cclog(" recv opcode = 0x%x",opcode)
                network.onRecvMessage(opcde)
                if network.handlers[network.state] and network.handlers[network.state][opcode] then
                    network.handlers[network.state][opcode].handler(packet)
                end
                network.popPacket(packet)
            end

             -- 连接gameServer之后自动发送ping消息
            if network.isState(NLS_GAMESERVER) and network.needPing  then
                network.pingdt = network.pingdt + dt
                if network.pingdt > 30 then
                    if network.pong == false then
                        network.onPingFailed()
                    end 
                    network.Ping()
                    network.pingdt = 0
                    network.pong = false
                end 
            end

            if network.ConnectFailed() then
               network.onConnectFailed()
            end
        end
        network.loop = cc.Director:getInstance():getScheduler():scheduleScriptFunc(loopfun,0,false)
        network.running = true
        sNetConn:registerScriptFunc(handler)
    end

    return network.running
end

function network.shutdown()
    network.disconnet()
    cclog("network shutdown")
    network.onShutDown()
    if network.loop ~= 0 then
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(network.loop)
        network.loop = 0
    end
    network.running = false
    sNetConn:unregisterScriptHandler()
end
