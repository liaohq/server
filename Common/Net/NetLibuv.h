/*
* author: lhq
* date  : 2018.5.3
* bref	 : net libuv
*/

#ifndef		_NET_LIBUV_H
#define		_NET_LIBUV_H

#include "Common.h"
#include "CommonHead.h"
#include "Base/Thread.h"
#include "uv.h"


typedef fastdelegate::FastDelegate< void(uv_stream_t *, int ) >	 NEW_CONNECT_FUNC;

class NetLibuv
{
public:
	NetLibuv();
	~NetLibuv();

public:
	void					PreInit();
	void					Init();
	void					Start();
	void					Stop();
	void					CleanUp();

public:
	static void				NewConnectCallBackFunc(uv_stream_t* server, int status);
	static void				SocketAfterCloseCallBackFunc(uv_handle_t *handle);
	static void				NewClientAllocBufferCallBackFunc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
	static void				ClientRecvCallBackFunc(uv_stream_t *handle, ssize_t nread, const uv_buf_t* buf);
private:
	int						WorkThread(ThreadInfo&  info);
private:
	BOOL					m_IsInit;
	uv_loop_t*				m_MainLoop;
	uv_tcp_t				m_Server;
	ThreadBox<NetLibuv>	    m_WorkThread;
};



#endif
