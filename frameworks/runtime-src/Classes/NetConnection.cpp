#include "NetConnection.h"
//#include "NetOpcodes.h"
//#include "Hall.h"
//#include "SRoom.h"
//#include "SWorldSession.h"
#include "Utility/md5.h"
#include "Utility/Util.h"
#include "Utility/Timer.h"
//#include "StorageManager.h"
//#include "SHero.h"
#include "PlatformUtility.h"
#include "CCLuaEngine.h"

//using namespace PocketHero;
enum
{
	SENDMGS,
	SENDOK,
	NETWORK_EVENT_NUMS,
};

const char* NetEvent[NETWORK_EVENT_NUMS] = 
{
	"NETWORK_SENDMGS",
	"NETWORK_SENDMGSOK",
};


void* NetThreadBody( void* param )
{
	CNetConnection* lpNetConn = (CNetConnection*)param;

	fd_set readSet;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000*50;
	bool isInitiativeClose = true;
	while( lpNetConn->m_running )
	{
		FD_ZERO( &readSet );
		FD_SET( lpNetConn->m_socket, &readSet );
		bool needBreak = false;
		int32 selectRet = select( lpNetConn->m_socket + 1, &readSet, NULL, NULL, &timeout );
		switch ( selectRet )
		{
		case 0:
			// timeout
			break;
		case -1:
			// select error
			needBreak = true;
			CCLOGINFO("network select socket error");
			break;
		default:
			if ( FD_ISSET( lpNetConn->m_socket, &readSet ) )
			{
				int32 recved = recv( lpNetConn->m_socket, lpNetConn->m_recvBuffer + lpNetConn->m_recvDataLen, lpNetConn->m_recvBuffSize - lpNetConn->m_recvDataLen, 0 );
				if ( recved <= 0 )
				{
#ifdef WIN32
                    int32 errNo1 = GetLastError();
					if ( errNo1 != EAGAIN && errNo1 != WSAEWOULDBLOCK && errNo1 != WSAEINTR )
					{
						CCLOGINFO("recv error, %d",errNo1);
						needBreak = true;
					}
#else
                    int32 errNo1 = errno;
					if ( errNo1 != EAGAIN && errNo1 != EWOULDBLOCK && errNo1 != EINTR )
                    {
						CCLOGINFO("recv error, %d",errNo1);
						needBreak = true;
					}
#endif
				}
				else
					needBreak = !lpNetConn->OnRecv( recved );
			}
			break;
		}

		pthread_mutex_lock( lpNetConn->m_sendBufferLock );
		if ( lpNetConn->m_sendDataLen > 0 )
		{
			// 这里就调用一次send,如果没有完全复制到缓冲区,就等下次循环再发送
			int32 sendRet = send( lpNetConn->m_socket, lpNetConn->m_sendBuffer, lpNetConn->m_sendDataLen, 0 );
			if ( sendRet <= 0 )
			{
#ifdef WIN32
				int32 errNo1 = GetLastError();
				if ( errNo1 != EAGAIN && errNo1 != WSAEWOULDBLOCK && errNo1 != WSAEINTR )
				{
					CCLOGINFO("send error, %d",errNo1);
					needBreak = true;
				}
#else
				int32 errNo1 = errno;
				if ( errNo1 != EAGAIN && errNo1 != EWOULDBLOCK && errNo1 != EINTR )
                {
                    CCLOGINFO("send error, %d",errNo1);
					needBreak = true;
                }
#endif
			}
			else
			{
				lpNetConn->m_sendDataLen -= sendRet;
				if ( lpNetConn->m_sendDataLen > 0 )
					memmove( lpNetConn->m_sendBuffer, lpNetConn->m_sendBuffer + sendRet, lpNetConn->m_sendDataLen );
				else
					lpNetConn->m_bSendMgsOK = true;
			}
		}
		if ( !needBreak )
			lpNetConn->FlushData();
		pthread_mutex_unlock( lpNetConn->m_sendBufferLock );

		if ( needBreak )
		{
			isInitiativeClose = false;
			break;
		}
	}

	if ( isInitiativeClose )
	{
#ifdef WIN32
		closesocket( lpNetConn->m_socket );
#else
		close( lpNetConn->m_socket );
#endif
		CCLOGINFO("close socket");
	}
	lpNetConn->m_socket = -1;
    CCLOGINFO("!!!!!!!!!!!!!!!!!!!!network pthread shutdown!!!!!!!!!!!!!!!!!!!!!");
	return NULL;
}

CNetConnection::CNetConnection( uint32 recvBufferSize, uint32 sendBufferSize )
	: m_header( 0, 0 )
{
#ifdef WIN32
	WSADATA wsaData;
	int err = 0;
	err = WSAStartup( MAKEWORD(2,2), &wsaData );
	if ( err != 0 )
		assert( false );
#endif
	m_running = false;
	m_socket = -1;
	m_lastFrameSocket = -1;
	m_recvBuffSize = recvBufferSize;
	m_recvBuffer = new char[m_recvBuffSize];
	m_recvDataLen = 0;
	m_sendBuffSize = sendBufferSize;
	m_sendBuffer = new char[m_sendBuffSize];
	m_sendDataLen = 0;
	m_sendBufferLock = NULL;

	m_loginIp = "127.0.0.1";
	m_gameServerIp = "127.0.0.1";
	m_loginPort = 0;
	m_gameServerPort = 0;
	m_handle = NULL;
	m_accountId = 0;
	m_loginState = NLS_LOGINSERVER;
	m_sessionKey = "";
	m_realmId = 0;
	m_lastPingTick = time( NULL );
	m_recvLargePkt = NULL;
	m_sendingPkt = NULL;
	m_sendPktCached = 0;
	m_topRank = 0;
	m_timeRank = 0;
	m_levelRank = 0;
	m_connectType = 0;
	m_pongSumTime = 0;
	m_pongCount = 0;
	m_pingCode = 0;

	m_UserName = "";
	m_PassWord = "";
	m_clientSeed = 0;
	m_Version = 0;
	memset(m_clientMd5,0,17);

	m_nFuncId = 0;
	m_bSendMgsOK = false;
}

CNetConnection::~CNetConnection()
{
	if ( IsConnected() )
		DisConnect();

	WorldPacket* pkt = NULL;
	while ( m_recvQueue.next( pkt ) )
		SAFE_DELETE( pkt );

	while ( m_sendQueue.next( pkt ) )
		SAFE_DELETE( pkt );

	SAFE_DELETE( m_recvBuffer );
	SAFE_DELETE( m_sendBuffer );
	SAFE_DELETE( m_handle );
	SAFE_DELETE( m_sendBufferLock );
	SAFE_DELETE( m_recvLargePkt );
	SAFE_DELETE( m_sendingPkt );
}

bool CNetConnection::IsConnected( int32 state )
{
	if ( !PlatformUtility::IsNetUseable() )
	{
		// 外网崩溃日志显示在网络线程操作socket时崩溃,这里不应该直接赋值socket(本意可能是想置socket的值,然后在update里面去disconnect,但这样就影响了网络线程)
		// 应该使用Disconnect方法
		if ( m_socket != -1 )
			DisConnect( true );
		return false;
	}

	if ( state == -1 )
		return m_socket != -1;
	
	return (m_socket != -1) && (m_loginState == state);
}

void CNetConnection::CloseSocket()
{
	m_running = false;
	m_socket = -1;

	m_recvDataLen = 0;
	m_sendDataLen = 0;
	m_haveParseHeader = false;

	WorldPacket* pkt = NULL;
	while ( m_recvQueue.next( pkt ) )
		SAFE_DELETE( pkt );

	while ( m_sendQueue.next( pkt ) )
		SAFE_DELETE( pkt );

	/*
	{
		uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
		SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
		if ( lpSession )
		{
			if ( m_sendPktCached > (MAX_HERO_PACKET_SIZE / 2) )
				((SHero*)lpSession->GetPlayer())->SetUploadPercent( 0 );

			if ( m_loginState == NLS_GAMESERVER )
			{
				WorldPacket data( SMSG_NET_CONNECT_RESPONSE, 10 );
				data << uint8(NET_CONNECT_FAIL);
				data << (uint16)0;
				lpSession->SendPacket( &data );
			}
		}
	}
	*/
	SAFE_DELETE( m_recvLargePkt );
	SAFE_DELETE( m_sendingPkt );
	m_sendPktCached = 0;
	m_loginState = NLS_LOGINSERVER;
}

bool CNetConnection::IsAuthed()
{
	return m_accountId != 0;
}

bool CNetConnection::ConnectLoginServer(const char* address)
{
	bool bRet = false;

	// 首先从存档文件中取得loginServer的ip和端口
	bool parseRet = ParseIpAndPort( address, m_loginIp, m_loginPort );
	if ( !parseRet )
		return false;

	if ( ConnectServer( m_loginIp.c_str(), m_loginPort ) )
	{
		// 启动网络线程
		SAFE_DELETE( m_handle );
		m_handle = new pthread_t();
		SAFE_DELETE( m_sendBufferLock );
		m_sendBufferLock = new pthread_mutex_t();
		pthread_mutex_init( m_sendBufferLock, NULL );
		m_running = true;
		pthread_create( m_handle, NULL, NetThreadBody, this );
		m_loginState = NLS_LOGINSERVER;
		bRet = true;
	}
	if(!bRet)
		CCLOGINFO("login server failed!");
	else
		CCLOGINFO("login server success");
	return bRet;
}

void CNetConnection::DisConnect( bool force )
{
	if ( force || IsConnected() )
	{
		m_running = false;
		void* returnValue = NULL;
		pthread_join( *m_handle, &returnValue );
	}
	CloseSocket();
	m_lastFrameSocket = -1;
}

bool CNetConnection::Next()
{
	return !m_recvQueue.empty();
}

void CNetConnection::ReleasePacket(WorldPacket* recv)
{
	SAFE_DELETE(recv);
}

WorldPacket* CNetConnection::GetPacket()
{
	WorldPacket* packet = NULL;
	m_recvQueue.next(packet);
	return packet;
}

bool CNetConnection::IsLoginState(int state)
{
	return m_loginState == state;
}

bool CNetConnection::ConnectFailed()
{
	return m_lastFrameSocket != m_socket && m_socket == -1;
}

void CNetConnection::Update()
{
	if(m_bSendMgsOK)
	{
		executeEvent(NetEvent[SENDOK]);
		m_bSendMgsOK = false;
	}

// 	if ( m_recvQueue.empty() )
// 		return;
// 
// 	WorldPacket* packet = NULL;
// 	while( m_recvQueue.next( packet ) )
// 	{
// 		bool bError = false;
// 		switch ( m_loginState )
// 		{
// 		case NLS_LOGINSERVER:
// 			{
// 				/*
// 				if ( packet->GetOpcode() >= NUM_LOGIN_MSG_TYPES )
// 				{
// 					bError = true;
// 					assert( false );
// 				}
// 				NetOpcodeHandler const& opHandle = loginOpcodeTable[packet->GetOpcode()];
// 				try
// 				{
// 					(this->*opHandle.handler)(*packet);
// #ifdef WIN32
// 				}
// 				catch (ByteBufferException&)
// 				{
// 					bError = true;
// 					assert( false );
// 				}
// #endif
// 				*/
// 			}
// 			break;
// 		case NLS_GAMESERVER:
// 			{
// 				/*
// 				if ( packet->GetOpcode() >= NUM_GAME_MSG_TYPES )
// 				{
// 					bError = true;
// 					assert( false );
// 				}
// 				NetOpcodeHandler const& opHandle = gameOpcodeTable[packet->GetOpcode()];
// #ifdef WIN32
// 				try
// 				{
// #endif
// 					(this->*opHandle.handler)(*packet);
// #ifdef WIN32
// 				}
// 				catch (ByteBufferException&)
// 				{
// 					bError = true;
// 					assert( false );
// 				}
// #endif
// 				*/
// 			}
// 			break;
// 		default:
// 			{
// 				bError = true;
// 				assert( false );
// 			}
// 			break;
// 		}
// 
// 		SAFE_DELETE( packet );
// 		if ( bError )
// 		{
// 			DisConnect();
// 		}
// 	}
}

void CNetConnection::SendPacket( WorldPacket* packet )
{
	if(m_sendBufferLock)
		pthread_mutex_lock( m_sendBufferLock );
	WorldPacket* lpNewPacket = new WorldPacket( *packet );
	m_sendQueue.add( lpNewPacket );
	if ( m_sendDataLen == 0 )
		FlushData();
	if(m_sendBufferLock)
		pthread_mutex_unlock( m_sendBufferLock );
}

bool CNetConnection::OnRecv( uint32 Bytes )
{
	bool bRet = false;
	m_recvDataLen += Bytes;

	while( m_recvDataLen > 0 )
	{
		int parseRet = ParsePacketHeader();
		if ( parseRet < 0 )
		{
			bRet = false;
			break;
		}
		else if ( parseRet == 1 )
		{
			bRet = true;
			break;
		}

		parseRet = ParsePacketBody();
		if ( parseRet < 0 )
		{
			bRet = false;
			break;
		}
		bRet = true;
	}
	return bRet;
}

int CNetConnection::ParsePacketHeader()
{
	if ( !m_haveParseHeader )
	{
		if ( m_recvDataLen < sizeof( HeroPacketHeader ) )
			return 1;

		memcpy( &m_header, m_recvBuffer, sizeof(HeroPacketHeader) );
		m_header.packetLength = ntohl( m_header.packetLength );
		m_header.cmd = ntohs( m_header.cmd );

		if ( ((m_header.flag & HERO_PACKET_LARGE) == 0) && ( m_header.packetLength > MAX_HERO_PACKET_SIZE || m_header.packetLength < sizeof( HeroPacketHeader ) ) )
		{
			sLog.outDebug( "ClientSession::parsePacketHeader Can not recv packet, it's too long or too small, length = %d", m_header.packetLength );
			return -1;
		}
		if ( ((m_header.flag & HERO_PACKET_LARGE) != 0) && ( m_header.packetLength > MAX_HERO_PACKET_SIZE*100 || m_header.packetLength < sizeof( HeroPacketHeader ) ) )
		{
			sLog.outDebug( "ClientSession::parsePacketHeader Can not recv packet, it's too long or too small, length = %d", m_header.packetLength );
			return -1;
		}
		m_haveParseHeader = true;
	}

	if ( IsRecvingLargePkt() )
		return 2;
	else
	{
		if ( m_haveParseHeader && m_recvDataLen >= m_header.packetLength )
			return 0;
	}
	return 1;
}

int CNetConnection::ParsePacketBody()
{
	uint32 dataLength = m_header.packetLength - sizeof( HeroPacketHeader );

	if ( IsRecvingLargePkt() )
	{
		uint32 readOffset = 0;
		if ( NULL == m_recvLargePkt )
		{
			m_recvLargePkt = new WorldPacket( m_header.cmd, dataLength );
			// 因为第一个包包含包头
			readOffset = sizeof( HeroPacketHeader );
		}
		// 得到要附加到大包中的数据长度
		uint32 appendLength = m_recvDataLen - readOffset;
		if ( m_recvLargePkt->wpos() + appendLength > dataLength )
			appendLength = dataLength - m_recvLargePkt->wpos();
		m_recvLargePkt->append( m_recvBuffer + readOffset, appendLength );

		uint32 realReaded = readOffset + appendLength;
		if ( m_recvDataLen - realReaded > 0 )
			memmove( m_recvBuffer, m_recvBuffer + realReaded, m_recvDataLen - realReaded );
		m_recvDataLen -= realReaded;

		if ( m_recvLargePkt->wpos() == dataLength )
		{
			m_recvQueue.add( m_recvLargePkt );
			m_recvLargePkt = NULL;
			m_haveParseHeader = false;
			/*
			uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
			SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
			if ( lpSession )
				((SHero*)lpSession->GetPlayer())->SetUploadPercent( 0 );
			*/
		}
	}
	else
	{
		WorldPacket* lpNewPacket = new WorldPacket( m_header.cmd, dataLength );
		if ( !lpNewPacket )
		{
			sLog.outDebug( "ClientSession::parsePacketBody error! no memory to alloc!" );
			return -1;
		}
		lpNewPacket->append( m_recvBuffer + sizeof( HeroPacketHeader ), dataLength );
		m_recvQueue.add( lpNewPacket );

		if ( m_recvDataLen > m_header.packetLength )
			memmove( m_recvBuffer, m_recvBuffer + m_header.packetLength, m_recvDataLen - m_header.packetLength );
		m_recvDataLen -= m_header.packetLength;

		m_haveParseHeader = false;
	}

	return 0;
}

void CNetConnection::RelayMessage( uint16 newCmd, WorldPacket& packet )
{
	WorldPacket data( newCmd, packet.size() + 4 );
	data << packet.GetOpcode();
	data << m_loginState;
	data.append( packet.contents(), packet.size() );
	/*
	uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
	SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
	if ( lpSession )
		lpSession->SendPacket( &data );
	*/
}

void CNetConnection::NotifyClientNeedWait( bool needWait, uint16 cmd )
{
	/*
	uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
	SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
	if ( lpSession )
		lpSession->NotifyClientNeedWait( needWait, cmd );
		*/
}

std::string CNetConnection::GenerateRandomStr()
{
	
	uint32 randomInt = urand( 0, 1000000000 );
	char randomStr[17] = "";
	sprintf( randomStr, "%d", randomInt );

	md5_state_t ctx;
	md5_init( &ctx );
	md5_append( &ctx, (const md5_byte_t*)randomStr, strlen( randomStr ) );
	md5_finish( &ctx, (md5_byte_t*)randomStr );
	randomStr[16] = '\0';
	
	std::string encoded;
	hexEncodeByteArray((uint8*)randomStr, 16, encoded);

	return encoded;
}

bool CNetConnection::ParseIpAndPort( const char* address, std::string& ip, uint16& port )
{
	bool bRet = false;
	if ( address && strlen( address ) < strlen("255.255.255.255:65535") )
	{
		char chTemp[32] = "";
		strcpy( chTemp, address );
		char* lpSplit = strchr( chTemp, ':' );
		if ( lpSplit )
		{
			*lpSplit = '\0';
			++lpSplit;
			ip = std::string( chTemp );
			port = atoi( lpSplit );
			bRet = true;
		}
	}
	return bRet;
}

std::string CNetConnection::CalculateShaPassHash(std::string& name, std::string& password)
{
	std::string encoded = name;
	encoded += ":";
	encoded += password;

	md5_state_t ctx;
	md5_init(&ctx);
	md5_append(&ctx, (const md5_byte_t*)encoded.c_str(), encoded.length());
	char md5[17];
	md5_finish( &ctx, (md5_byte_t*)md5  );
	md5[16] = '\0';
	encoded = md5;

	hexEncodeByteArray((uint8*)md5, 16, encoded);
	return encoded;
}

bool CNetConnection::IsRecvingLargePkt()
{
	bool bRet = false;
	if ( m_haveParseHeader && (m_header.flag & HERO_PACKET_LARGE) )
		bRet = true;
	return bRet;
}

void CNetConnection::FlushData()
{
	uint32 uSended = 0;
	bool nowSend = false;
	if ( m_sendingPkt )
	{
		// 如果当前正在发送某个包
		uint32 packetSize = m_sendingPkt->wpos() + sizeof( HeroPacketHeader );
		if ( m_sendPktCached < sizeof( HeroPacketHeader ) )
		{
			uint32 sendSize = 0;
			HeroPacketHeader temp( m_sendingPkt->GetOpcode(), packetSize );
			temp.packetLength = htonl( temp.packetLength );
			temp.cmd = htons( temp.cmd );
			if ( packetSize <= MAX_HERO_PACKET_SIZE )
			{
				memcpy( m_sendTempBuff, &temp, sizeof( HeroPacketHeader ) );
				if ( m_sendingPkt->wpos() )
					memcpy( m_sendTempBuff + sizeof( HeroPacketHeader ), m_sendingPkt->contents(), m_sendingPkt->wpos() );
				sendSize = sizeof( HeroPacketHeader ) + m_sendingPkt->wpos();
			}
			else
			{
				temp.flag |= HERO_PACKET_LARGE;
				memcpy( m_sendTempBuff, &temp, sizeof( HeroPacketHeader ) );
				memcpy( m_sendTempBuff + sizeof( HeroPacketHeader ), m_sendingPkt->contents(), MAX_HERO_PACKET_SIZE - sizeof( HeroPacketHeader ) );
				sendSize = MAX_HERO_PACKET_SIZE;
			}
			uSended = CacheData( m_sendTempBuff + m_sendPktCached, sendSize - m_sendPktCached  );
		}
		else
		{
			uint32 remainSize = packetSize - m_sendPktCached;
			uSended = CacheData( (char*)m_sendingPkt->contents() + (m_sendPktCached - sizeof( HeroPacketHeader )), remainSize  );
		}

		m_sendPktCached += uSended;
		if ( m_sendPktCached == packetSize )
		{
			if ( m_sendPktCached > (MAX_HERO_PACKET_SIZE / 2) )
			{
				/*
				uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
				SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
				if ( lpSession )
					((SHero*)lpSession->GetPlayer())->SetUploadPercent( 0 );
				*/
			}

			SAFE_DELETE( m_sendingPkt );
			m_sendPktCached = 0;
		}
		else
			return;
	}

	while( m_sendQueue.next( m_sendingPkt ) )
	{
		nowSend = true;
		uint32 packetSize = m_sendingPkt->wpos() + sizeof( HeroPacketHeader );
		uint32 sendSize = 0;
		HeroPacketHeader temp( m_sendingPkt->GetOpcode(), packetSize );
		CCLOGINFO("[C++-print]  ready to send :0x%x",m_sendingPkt->GetOpcode());
		temp.packetLength = htonl( temp.packetLength );
		temp.cmd = htons( temp.cmd );
		if ( packetSize <= MAX_HERO_PACKET_SIZE )
		{
			memcpy( m_sendTempBuff, &temp, sizeof( HeroPacketHeader ) );
			if ( m_sendingPkt->wpos() )
				memcpy( m_sendTempBuff + sizeof( HeroPacketHeader ), m_sendingPkt->contents(), m_sendingPkt->wpos() );
			sendSize = sizeof( HeroPacketHeader ) + m_sendingPkt->wpos();
		}
		else
		{
			temp.flag |= HERO_PACKET_LARGE;
			memcpy( m_sendTempBuff, &temp, sizeof( HeroPacketHeader ) );
			memcpy( m_sendTempBuff + sizeof( HeroPacketHeader ), m_sendingPkt->contents(), MAX_HERO_PACKET_SIZE - sizeof( HeroPacketHeader ) );
			sendSize = MAX_HERO_PACKET_SIZE;
		}

		uSended = CacheData( m_sendTempBuff, sendSize );
		assert( m_sendPktCached == 0 );
		m_sendPktCached += uSended;

		if ( m_sendPktCached == packetSize )
		{
			if ( m_sendPktCached > (MAX_HERO_PACKET_SIZE / 2) )
			{
				/*
				uint32 serverSessionId = sHall.getServerRoom()->getServerSession();
				SWorldSession* lpSession = sHall.getServerRoom()->findSession( serverSessionId );
				if ( lpSession )
					((SHero*)lpSession->GetPlayer())->SetUploadPercent( 0 );
				*/
			}

			SAFE_DELETE( m_sendingPkt );
			m_sendPktCached = 0;
		}
		else
			break;
	}

	if(nowSend)
		executeEvent(NetEvent[SENDMGS]);
}

void CNetConnection::OnFirstChallenge()
{
	/*
	WorldPacket netData( CMD_REALM_LIST, 0 );
	SendPacket( &netData );
	*/
}

void CNetConnection::SetPingCode( int opcode )
{
	m_pingCode = opcode;
}

void CNetConnection::OnSendPing()
{
	if(m_pingCode > 0)
	{
		WorldPacket packet(m_pingCode, 8);
		packet << getMSTime();
		packet << uint32(0);
		SendPacket( &packet );
	}
}

void CNetConnection::OnRecvPong( uint32 pingTime )
{
	uint32 timeDiff = getMSTimeDiff( pingTime, getMSTime() );
	m_pongSumTime += timeDiff;
	m_pongCount++;
}

uint32 CNetConnection::GetAvgPing()
{
	uint32 uRet = 0;
	if ( m_pongCount > 0 )
		uRet = m_pongSumTime / m_pongCount;
	return uRet;
}

void CNetConnection::ClearPingStatistics()
{
	m_pongSumTime = 0;
	m_pongCount = 0;
}

uint32 CNetConnection::CacheData( char* data, uint32 dataLength )
{
	uint32 uSended = 0;
	if ( m_sendDataLen < m_sendBuffSize )
	{
		uSended = dataLength;
		if ( m_sendDataLen + dataLength > m_sendBuffSize )
			uSended = m_sendBuffSize - m_sendDataLen;
		memcpy( m_sendBuffer + m_sendDataLen, data, uSended );
		m_sendDataLen += uSended;
	}
	return uSended;
}

bool CNetConnection::ConnectGameServer()
{
	bool bRet = false;
    if(m_gameAddress.empty())
        return bRet;
	// 首先从配置文件中取得loginServer的ip和端口
	std::map<uint32,std::string>::const_iterator it = m_gameAddress.find( m_realmId );
	if ( it == m_gameAddress.end() )
		return false;

	if ( !ParseIpAndPort( it->second.c_str(), m_gameServerIp, m_gameServerPort ) )
		return false;

	if ( ConnectServer( m_gameServerIp.c_str(), m_gameServerPort ) )
	{
		// 启动网络线程
		SAFE_DELETE( m_handle );
		m_handle = new pthread_t();
		m_running = true;
		pthread_create( m_handle, NULL, NetThreadBody, this );
		m_loginState = NLS_GAMESERVER;
		bRet = true;
	}
	return bRet;
}

// 采取异步connect的方式,连接服务器
bool CNetConnection::ConnectServer( const char* ip, uint16 port )
{
	DisConnect();
	 
	if ( !PlatformUtility::IsNetUseable() )
		return false;
	
	// 创建socket句柄
	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return false;
	}

	// 设置连接参数
#ifdef WIN32
	SOCKADDR_IN sockaddr_in;
#else
	struct sockaddr_in sockaddr_in;
#endif
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons( port );
#ifdef WIN32
	sockaddr_in.sin_addr.S_un.S_addr = inet_addr( ip );
#else
	sockaddr_in.sin_addr.s_addr = inet_addr( ip );
#endif
	memset( sockaddr_in.sin_zero, 0, sizeof( sockaddr_in.sin_zero ) );

	// 设置socket为非阻塞模式
	unsigned long ul = 1;
    int iError = 0;
#ifdef WIN32
	iError = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul);
#else
	int flags;
	if ( (flags = fcntl(m_socket, F_GETFL, 0)) < 0 )
	{
		iError = -1;
	}
	else
	{
		flags = flags | O_NONBLOCK;
		iError = fcntl(m_socket, F_SETFL, flags );
	}
#endif
	if(iError < 0 )
	{
		m_socket = -1;
		return false;
	}

	fd_set writeSet;
	timeval timeout;
	timeout.tv_sec = 4;
	timeout.tv_usec = 0;
	if ( connect( m_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in) ) != 0 )
	{
		FD_ZERO( &writeSet );
		FD_SET( m_socket, &writeSet );
		int selectRet = select( m_socket + 1, NULL, &writeSet, NULL, &timeout );
		switch ( selectRet )
		{
		case 0:
		case -1:
			{
				m_socket = -1;
				return false;
			}
			break;
		default:
			if ( FD_ISSET( m_socket, &writeSet ) )
			{
				char error = 1;
#ifdef WIN32
				int len = sizeof(char);
#else
                socklen_t len = sizeof(char);
#endif
				getsockopt( m_socket, SOL_SOCKET, SO_ERROR, &error, &len );
				if ( error != 0 )
				{
					m_socket = -1;
					return false;
				}
			}
			break;
		}
	}

	// 重新设置为阻塞
// 	ul = 0;
// #ifdef WIN32
// 	iError = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul);
// #else
// 	iError = fcntl(m_socket, F_SETFL, flags & (~O_NONBLOCK));
// #endif
// 	if(iError == -1)
// 	{
// #ifdef WIN32
// 		closesocket( m_socket );
// #else
// 		close( m_socket );
// #endif
// 		m_socket = -1;
// 		return false;
// 	}

	// 设置发送缓冲区和接收缓冲区大小
	int32 nRcvBuffSize = CLIENT_RECV_BUFFER_SIZE;
	int32 nSendBuffSize = CLIENT_SEND_BUFFER_SIZE;
	iError = setsockopt( m_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRcvBuffSize, sizeof( int32 ) );
	if ( iError == 0 )
		iError = setsockopt( m_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuffSize, sizeof( int32 ) );
	if ( iError == -1 )
	{
#ifdef WIN32
		closesocket( m_socket );
#else
		close( m_socket );
#endif
		m_socket = -1;
		return false;
	}

	m_lastFrameSocket = m_socket;
	return true;
}

void CNetConnection::setVersion(uint32 version)
{
	m_Version = version;
}

const char* CNetConnection::getClientMd5()
{
	return &m_clientMd5[0];
}

uint32 CNetConnection::getClientSeed() 
{
	return m_clientSeed;
}
std::string CNetConnection::getUserName()
{
	return m_UserName;
}

void CNetConnection::SetUserNameAndPassWord(std::string uName, std::string pWord)
{
	m_UserName = uName;
	m_PassWord = pWord;
}

void CNetConnection::GetClientMd5Str(U8Ptr* loginSeed, std::string& rClientSeed, std::string& rClientMd5Str, std::string& rClientUnk)
{

}

void CNetConnection::SendLoginPacket(WorldPacket* recvPacket)
{
	
}

void CNetConnection::SendSignInPacket()
{

}

void CNetConnection::HandleLoginRealmListResponse( WorldPacket& recvPacket )
{
	
}

void CNetConnection::HandleGameAuthChallengeResponse( WorldPacket& recvPacket )
{

}

void CNetConnection::sendAuthSessionMessage()
{

}

void CNetConnection::registerScriptFunc(int handleId)
{
    unregisterScriptHandler();
    m_nFuncId = handleId;
}

void CNetConnection::unregisterScriptHandler()
{
    if (m_nFuncId)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_nFuncId);
        m_nFuncId = 0;
    }
}

void CNetConnection::executeEvent(const char *event)
{
    if(m_nFuncId)
    {
		CommonScriptData data(m_nFuncId,event);
		ScriptEvent scriptEvent(kCommonEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

uint32 CNetConnection::getSendPercent()
{
	if ( m_sendingPkt )
	{
		uint32 packetSize = m_sendingPkt->wpos() + sizeof( HeroPacketHeader );
		if ( packetSize > (MAX_HERO_PACKET_SIZE / 2) )
			return (uint32)(m_sendPktCached * 100.0f / packetSize);
	}

	return 100;
}

uint32 CNetConnection::getRecvPercent()
{
	if ( m_recvLargePkt )
	{
		return (uint32)(m_recvLargePkt->wpos() * 100.0f / m_recvLargePkt->size());
	}

	return 100;
}