--[[
	-- 在这里require所有的消息处理文件
]]
require("MgsHandle.loginHandlers")

----------------------------------------------------

--[[
	-- LoginNetOpcodes
	-- 这里添加登陆的消息协议
	-- 示例:
	-- CMD_AUTH_LOGON_CHALLENGE_1 		= 0x001 -- 登陆挑战
]]
CMD_AUTH_LOGON_CHALLENGE_2											= 0x001 --发送账号名和密码
CMD_AUTH_LOGON_PROOF												= 0x002
CMD_AUTH_RECONNECT_CHALLENGE										= 0x003
CMD_AUTH_RECONNECT_PROOF											= 0x004
CMD_REALM_LIST														= 0x005 -- 请求服务器
CMD_CREATE_ACCOUNT													= 0x006
CMD_AUTH_LOGON_CHALLENGE_1										    = 0x007                                              
CMD_DETECT_CLIENT                                                   = 0x008
CMD_CREATE_ANONYMOUS_ACCOUNT                                        = 0x009
CMD_BIND_ACCOUNT                                                    = 0x00B

------------------------------------------------------

-- 这里添加登陆的消息协议处理函数

AddLoginHandler = function(opcode,name,handler)
	network.addHandler(opcode,NLS_LOGINSERVER,name,handler)
end

AddLoginHandler( CMD_AUTH_LOGON_CHALLENGE_1,"CMD_AUTH_LOGON_CHALLENGE_1",HandleLoginFirstChallenge)
AddLoginHandler( CMD_AUTH_LOGON_CHALLENGE_2,"第二次挑战",HandleLoginChallengeResponse)
AddLoginHandler( CMD_REALM_LIST,			"服务器列表",HandleLoginRealmListResponse)
AddLoginHandler( CMD_AUTH_LOGON_PROOF,		"登陆",HandleLoginProofResponse)
AddLoginHandler( CMD_CREATE_ACCOUNT,		"创建角色",HandleCreateAccountResponse)
AddLoginHandler( CMD_CREATE_ANONYMOUS_ACCOUNT,"匿名帐号创建",HandleAnonyCreateResponse)
AddLoginHandler( CMD_BIND_ACCOUNT,          "匿名帐号绑定",HandleAccountBindResponse)
AddLoginHandler( CMD_DETECT_CLIENT,			"版本验证", HandleDetectClient)
---------------------------------------------------------

--GameNetOpcodes
--[[
	-- 这里添加游戏内的消息协议
	-- 示例:
	-- SMSG_UPDATE_OBJECT 				= 0x001 -- object字段更新
]]
CMSG_GAME_PING 														= 0x802
SMSG_GAME_PING_RESPONSE 											= 0x803
SMSG_GAME_AUTH_CHALLENGE                                            = 0x804
CMSG_GAME_AUTH_SESSION												= 0x805
SMSG_GAME_AUTH_SESSION_RESPONSE                                     = 0x806
CMSG_GAME_CHAR_ENUM													= 0x900
SMSG_GAME_CHAR_ENUM_RESPONSE                                        = 0x901
CMSG_GAME_CHAR_CREATE												= 0x902
SMSG_GAME_CHAR_CREATE_RESPONSE                                      = 0x903
CMSG_GAME_PLAYER_LOGIN												= 0x904
SMSG_GAME_PLAYER_LOGIN_RESPONSE                                     = 0x905

----------------------------------------------------------

-- 这里添加游戏内的消息处理函数
AddGameHandler = function(opcode,name,handler)
	network.addHandler(opcode,NLS_GAMESERVER,name,handler)
end
AddGameHandler( SMSG_GAME_AUTH_CHALLENGE,		"SMSG_GAME_AUTH_CHALLENGE",HandleGameAuthChallengeResponse)
AddGameHandler( SMSG_GAME_AUTH_SESSION_RESPONSE,"SMSG_GAME_AUTH_SESSION_RESPONSE",HandleGameAuthSessionResponse)
AddGameHandler( SMSG_GAME_CHAR_ENUM_RESPONSE,	"SMSG_GAME_CHAR_ENUM_RESPONSE",HandlerGameCharEnumResponse)
AddGameHandler( SMSG_GAME_CHAR_CREATE_RESPONSE,	"SMSG_GAME_CHAR_CREATE_RESPONSE",HandlerGameCharCreateResponse)
AddGameHandler( SMSG_GAME_PLAYER_LOGIN_RESPONSE,"SMSG_GAME_PLAYER_LOGIN_RESPONSE",HandleGamePlayerLoginResponse)
AddGameHandler( SMSG_GAME_PING_RESPONSE,		"SMSG_GAME_PING_RESPONSE",Handle_Ping)
-----------------------------------------------------------