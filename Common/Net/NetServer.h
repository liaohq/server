/*
* author: lhq
* date  : 2018.5.3
* bref	 : net server
*/

#ifndef		_NET_SERVER_H
#define		_NET_SERVER_H

#include "Common.h"
#include "Base/Module.h"
#include "NetLibuv.h"
#include "NetEpoll.h"
#include "SocketDefine.h"

class NetServer:public Module
{
public:
	NetServer();
	~NetServer();

public:
	void				PreInit();
	void				Init();
	void				Start();
	void				Stop();
	void				CleanUp();

private:
	int 				AcceptThread(ThreadInfo& info);
private:
#ifdef	USE_LIBUV
	NetLibuv			m_NetHandle;
#else
	NetEpoll			m_NetHandle;
#endif
	ThreadBox<NetServer> m_AcceptThread;
	int					m_ListenFd;
};

extern   NetServer  g_NetServer;

#ifndef  NET_SERVER_MGR
#define  NET_SERVER_MGR   g_NetServer
#endif


#endif
