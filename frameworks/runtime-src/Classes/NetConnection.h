/*
	add by zhoujy 20121019
	负责客户端与服务器通信的连接,需要值得注意的是,虽然是单例,但是会重复连接和断开.
*/
#pragma once

#include "common.h"
#ifdef  WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#ifndef ANDROID
extern int errno;
#endif
#endif
#ifdef _WIN32
#include "pthread/pthread.h"
#else
#include <pthread.h>
#endif
#include "Utility/LockedQueue.h"
#include "Utility/WorldPacket.h"
#include <map>

#define HERO_PACKET_VERSION 1

#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

enum HeroPacketHeaderFlag
{
	HERO_PACKET_LARGE			= 0x01,
};

struct HeroPacketHeader
{
	uint32	packetLength;		/// 整个报文长度，含此int的4个字节。发送时网络字节序
	uint8	version;			/// 协议版本
	uint8	flag;				/// 包头标志
	uint16	cmd;				/// 消息ID，发送时网络字节序
	HeroPacketHeader( uint16 _cmd, uint32 _length )
	{
		packetLength = _length;
		version = HERO_PACKET_VERSION;
		flag = 0;
		cmd = _cmd;
	}
};

#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#define MAX_HERO_PACKET_SIZE 10240
#define CLIENT_RECV_BUFFER_SIZE 10240
#define CLIENT_SEND_BUFFER_SIZE 10240

void* NetThreadBody( void* param );

enum NetLoginState
{
	NLS_LOGINSERVER			= 0,
	NLS_GAMESERVER			= 1,
};

class CNetConnection
{
public:
	static CNetConnection& Instance()
	{
		static CNetConnection sConn(CLIENT_RECV_BUFFER_SIZE, CLIENT_SEND_BUFFER_SIZE);
		return sConn;
	}

	bool IsConnected( int32 state = -1 );
	void CloseSocket();			// 被主线程调用
	bool IsAuthed();
	bool ConnectLoginServer(const char* address);
    bool ConnectGameServer();
	void DisConnect( bool force = false );			// 被主线程调用
	void Update();
	void SendPacket( WorldPacket* pkt );
	bool OnRecv( uint32 Bytes );
	void FlushData();
	void OnFirstChallenge();
	uint32 GetConnectType(){ return m_connectType; }
	void SetConnectType( uint32 type ){ m_connectType = type; }
	void SetPingCode( int opcode );
	void OnSendPing();
	void OnRecvPong( uint32 pingTime );
	uint32 GetAvgPing();
	void ClearPingStatistics();

	void setVersion(uint32 version);
	const char* getClientMd5();
	uint32 getClientSeed();
	std::string getUserName();
	void SetUserNameAndPassWord(std::string uName, std::string pWord);
	void GetClientMd5Str(U8Ptr* loginSeed, std::string& rClientSeed, std::string& rClientMd5Str, std::string& rClientUnk);
	//登录与注册写死在代码中
	void SendLoginPacket(WorldPacket* packet);
	void SendSignInPacket();

	bool ConnectFailed();

	bool Next();
	void ReleasePacket(WorldPacket* recv);
	WorldPacket* GetPacket();
	bool IsLoginState(int state);
    void setLoginState(int state) { m_loginState = state; }
	int32 m_socket;
	int32 m_lastFrameSocket;

	char* m_recvBuffer;
	uint32 m_recvBuffSize;
	uint32 m_recvDataLen;

	char* m_sendBuffer;
	uint32 m_sendBuffSize;
	uint32 m_sendDataLen;
	pthread_mutex_t* m_sendBufferLock;

	HeroPacketHeader	m_header;
	bool				m_haveParseHeader;
	bool				m_running;
	int16				m_loginState;

	typedef UnLockedQueue<WorldPacket*> PacketQueue;
	PacketQueue			m_sendQueue;
	WorldPacket*		m_sendingPkt;			// 当前正在发送的包
	uint32				m_sendPktCached;		// 当前正在发送的包已经写入了多少字节到底层缓存

	bool				m_bSendMgsOK;

	// 消息处理函数
	void HandleNull( WorldPacket& recvPacket ){}
	void HandleClientSide( WorldPacket& recvPacket ){}
	void HandleLoginRealmListResponse( WorldPacket& recvPacket );
	void HandleGameAuthChallengeResponse( WorldPacket& recvPacket );

	void sendAuthSessionMessage();
	
	uint32 getSendPercent();
	uint32 getRecvPercent();

    void registerScriptFunc(int handleId);
    void unregisterScriptHandler();
    void executeEvent(const char* event);

	void updateEvent();
protected:
	CNetConnection( uint32 recvBufferSize, uint32 sendBufferSize );
	virtual ~CNetConnection();

	bool ConnectServer( const char* ip, uint16 port );
	// 返回0表示长度已够组装一个包,返回1表示长度未够组装一个包,返回-1表示解析头出错
	int ParsePacketHeader();
	// 返回0表示组包成功,返回-1表示失败
	int ParsePacketBody();
	// 转发一个消息给客户端
	void RelayMessage( uint16 newCmd, WorldPacket& packet );
	// 通知客户端取消遮罩
	void NotifyClientNeedWait( bool needWait, uint16 cmd = 0 );
	// 生成一个随机字符串
	static std::string GenerateRandomStr();
	static bool ParseIpAndPort( const char* address, std::string& ip, uint16& port );
	std::string CalculateShaPassHash(std::string& name, std::string& password);
	bool IsRecvingLargePkt();
	uint32 CacheData( char* data, uint32 dataLength );

	PacketQueue m_recvQueue;
	std::string m_loginIp;
	std::string m_gameServerIp;
	uint16 m_loginPort;
	uint16 m_gameServerPort;
	pthread_t* m_handle;
	uint32 m_accountId;
	std::string m_sessionKey;
	uint32 m_realmId;
	time_t m_lastPingTick;
	std::map<uint32,std::string> m_gameAddress;

	WorldPacket*		m_recvLargePkt;			// 当前正在接收的大包
	char				m_sendTempBuff[MAX_HERO_PACKET_SIZE];
	uint32 m_topRank;
	uint32 m_timeRank;
	uint32 m_levelRank;

	uint32 m_connectType;
	uint32 m_pongSumTime;
	uint32 m_pongCount;

	int		m_pingCode;
private:
	std::string m_UserName;   // 用户帐号
	std::string m_PassWord;   // 用户密码
	uint32 m_clientSeed;
	char m_clientMd5[17];
	uint32 m_Version;	//版本号
    
    int     m_nFuncId;
};

#define sNetConn CNetConnection::Instance()