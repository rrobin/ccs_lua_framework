function HandleLoginFirstChallenge(packet)

end

function HandleLoginChallengeResponse(packet)
	local opRet = packet:getU8()
	if opRet ~= 0 then
		log("LoginChallenge error opcode:#"..opRet)
	else
		network.SendLoginPacket(packet)
	end
end

function HandleLoginRealmListResponse(packet)
	network.LoginRealmListResponse(packet)
	log("枚举服务器列表")
	network.ConnectGameServer()
end

function HandleLoginProofResponse(packet)
	local opRet = packet:getU8()
	if opRet ~= 0 then
		log("LoginProof error opcode:#"..opRet)
	else
		local account = PlatformUtility:getAccount()
		local anonymous = PlatformUtility:getAnonymAccount()
		if account ~= "" and anonymous ~= "" then
			if string.sub(anonymous,4,8) == "AUTO" then
				local send_packet1 = WorldPacket:new(CMD_BIND_ACCOUNT,70)
				send_packet1:setStr(account)
				send_packet1:setStr(anonymous)
				network.send(send_packet1)
				log("~~~~~~~~Account exists,Bind~~~~~~~~")
			else
				log("Unknown Error,Bind Failed")
			end
		else
			local send_packet2 = WorldPacket:new(CMD_REALM_LIST,0)
	    	network.send(send_packet2)
	    	log("~~~~~~~~Current Account is nil,Login with Anonym~~~~~~~~~~~~")
		end
	end
end

function HandleCreateAccountResponse(packet)
	local opRet = packet:getU8()
	if opRet == 0 then
		--注册成功
		log("注册成功")
	else
		log("注册失败 code:#"..opRet)
	end
end

function HandleGameAuthChallengeResponse(packet)
    network.GameAuthChallengeResponse(packet)
	network.setVersion(12387)
	network.sendAuthSessionMessage()
end

function HandleGameAuthSessionResponse(packet)
	local opRet = packet:getU8()
	if opRet == 0x60 then
		--重连服务器成功，重新发送消息
		if network.reconnect then
           network.reSend()
        else
        	local send_packet = WorldPacket:new(CMSG_GAME_CHAR_ENUM,0)
	    	network.send(send_packet)
        end		
	else
		log("账号验证失败 code:#"..opRet)
	end
end

function HandlerGameCharEnumResponse(packet)
	local opRet = packet:getU32()
	if opRet == 0 then --无错误
		local char_num = packet:getU8()
		if char_num == 0 then
			local send_packet = WorldPacket:new(CMSG_GAME_CHAR_CREATE,4)
			send_packet:setStr("nameStr")
			network.send(send_packet)
			log("创建人物")
		elseif char_num == 1 then
			local guid = packet:getU32()
			local last_logout = packet:getU32()
			local nickName = packet:getStr()
			local send_packet = WorldPacket:new(CMSG_GAME_PLAYER_LOGIN,4)
			send_packet:setU32(guid)
			network.send(send_packet)
			log(nickName.."登录游戏")
		end
	else
		log("枚举人物失败，code:"..opRet)
	end
end

function HandlerGameCharCreateResponse(packet)
	local opRet = packet:getU32()
	if opRet == 0 then
		local send_packet = WorldPacket:new(CMSG_GAME_CHAR_ENUM,0)
	    network.send(send_packet)
	else
		log("创建人物失败, error code:"..opRet)
	end
end

function HandleGamePlayerLoginResponse(packet)
	local opRet = packet:getU32()
	if opRet ~= 0 then
		log("游戏人物登录失败，code:"..opRet)
	    return
    end
	log("成功进入游戏内，开始测试")
end

function HandleAccountBindResponse(packet)
	local opRet = packet:getU8()
	if opRet == 0 then
		log("~~~~~~~~~~~~~~~~Anonym Bind Done~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        PlatformUtility:setAnonymAccount("")
        local send_packet = WorldPacket:new(CMD_REALM_LIST,0)
	    network.send(send_packet)
	else 
		log("~~~~~~~~~~~~~~~Account Has been Binded,Direct Login~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
		local send_packet = WorldPacket:new(CMD_REALM_LIST,0)
	    network.send(send_packet)
	end
end

function HandleAnonyCreateResponse(packet)
	local opRet = packet:getU8()
	if opRet == 0 then 
		AnonymAccount = packet:getStr()
		log("创建匿名账号成功:"..AnonymAccount)
		PlatformUtility:setAnonymAccount(AnonymAccount)
		local psw = "000000"
		local nameStr = PlatformUtility:getAccount()
		local pswStr = PlatformUtility:getPassword()
		if nameStr == "" or pswStr == "" then
		    network.SetUserNameAndPassWord(AnonymAccount,psw)
			local send_packet = WorldPacket:new(CMD_AUTH_LOGON_CHALLENGE_2,160)
		    send_packet:setStr("zhCN")
			send_packet:setStr(AnonymAccount)
			network.send(send_packet)
        else
        	network.SetUserNameAndPassWord(nameStr,pswStr)
        	local send_packet = WorldPacket:new(CMD_AUTH_LOGON_CHALLENGE_2,160)
		    send_packet:setStr("zhCN")
			send_packet:setStr(nameStr)
			network.send(send_packet)
		end
	else
		log("Anonym create Failed")
	end
end

function Handle_Ping(packet)
	log("收到ping回应")
end