/*
* author: lhq
* date  : 2018.8.3
* bref	 : net epoll
*/

#ifndef		_NET_EPOLL_H
#define		_NET_EPOLL_H

#ifndef	_WINDOWS
#include "Common.h"
#include "CommonHead.h"
#include "Base/Thread.h"
#include "SocketDefine.h"

class NetEpoll
{
public:
	NetEpoll();
	~NetEpoll();

public:
	void					PreInit();
	void					Init();
	void					Start();
	void					CleanUp();
	void					Stop();
public:
	void					RegisterSocket(int sock);
	void					UnRegisterSocket(int sock);
private:
	int						WorkThread(ThreadInfo&  info);
private:
	ThreadBox<NetEpoll>		m_WorkThread;
	int						m_EpollFD;
	int						m_ListenFd;
};

#endif




#endif
