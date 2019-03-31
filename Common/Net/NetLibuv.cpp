#include "NetLibuv.h"



NetLibuv::NetLibuv()
{
	CleanUp();
}

NetLibuv::~NetLibuv()
{


}

void	NetLibuv::PreInit()
{
	m_MainLoop = uv_default_loop();
	if (m_MainLoop==NULL)
	{
		GAME_ASSERT_MSG(FALSE, "uv_default_loop err");
		return;
	}

	int ret=uv_tcp_init(m_MainLoop, &m_Server);
	if (ret != RET_SUCCESS)
	{
		GAME_ASSERT_MSG(FALSE, "uv_tcp_init errno:%d,err_str:%s",ret,uv_err_name(ret));
		return;
	}

	struct sockaddr_in  bind_addr;
	ret=uv_ip4_addr("0.0.0.0", 8888, &bind_addr);
	if (ret != RET_SUCCESS)
	{
		GAME_ASSERT_MSG(FALSE, "uv_ip4_addr errno:%d,err_str:%s", ret, uv_err_name(ret));
		return;
	}

	ret=uv_tcp_bind(&m_Server, (const struct sockaddr*)&bind_addr, 0);
	if (ret != RET_SUCCESS)
	{
		GAME_ASSERT_MSG(FALSE, "uv_tcp_bind errno:%d,err_str:%s", ret, uv_err_name(ret));
		return;
	}

	ret = uv_listen((uv_stream_t*)&m_Server, 50, &NetLibuv::NewConnectCallBackFunc);
	if (ret != RET_SUCCESS)
	{
		GAME_ASSERT_MSG(FALSE, "uv_tcp_bind errno:%d,err_str:%s", ret, uv_err_name(ret));
		return;
	}

	PRINT_MSG("Libuv Listen on 0.0.0.0:8888");

}

void	NetLibuv::Init()
{
	m_WorkThread.AddThread(this,&NetLibuv::WorkThread);
}

int		NetLibuv::WorkThread(ThreadInfo& info)
{
	cout<<"Net Begin Work"<<endl;
	uv_run(m_MainLoop, UV_RUN_DEFAULT);
	return RET_SUCCESS;
}

void	NetLibuv::Start()
{
	m_WorkThread.Start();
}

void	NetLibuv::Stop()
{
	uv_stop(m_MainLoop);
	uv_close((uv_handle_t*)&m_Server, &NetLibuv::SocketAfterCloseCallBackFunc);
}

void	NetLibuv::CleanUp()
{
	m_IsInit = FALSE;
}

void	NetLibuv::NewConnectCallBackFunc(uv_stream_t* server, int status)
{
	if (status <0)
	{
		//todo log
		return;
	}

	uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(server->loop, client);


	uv_buf_t*  new_buf = new uv_buf_t;
	new_buf->base = new char[1024];
	new_buf->len = 1024;
	memset(new_buf->base, 0, 1024);
	client->data = new_buf;

	if (uv_accept(server,(uv_stream_t*)client) == 0)
	{
		cout << "accpet client,sock=" << client->socket<< endl;
		uv_read_start((uv_stream_t*)client, &NetLibuv::NewClientAllocBufferCallBackFunc, &NetLibuv::ClientRecvCallBackFunc);
	}

}

void	NetLibuv::SocketAfterCloseCallBackFunc(uv_handle_t *handle)
{
}

void	NetLibuv::NewClientAllocBufferCallBackFunc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	if (!handle->data) {
		return;
	}


	*buf = *(uv_buf_t*)handle->data;
	uv_tcp_t* client = (uv_tcp_t*)handle;

}

void    NetLibuv::ClientRecvCallBackFunc(uv_stream_t *handle, ssize_t nread, const uv_buf_t* buf)
{

	if (!handle->data) {
		return;
	}
	
	uv_tcp_t* client = (uv_tcp_t*)handle;

	if (nread < 0) {
		if (nread == UV_EOF) {
			fprintf(stdout, "socket(%d)主动断开\n", client->socket);
		}
		else if (nread == UV_ECONNRESET) {
			fprintf(stdout, "socket(%d)异常断开\n", client->socket);
		}
		else {
			fprintf(stdout, "socket(%d)异常断开:%s\n", client->socket, uv_err_name(nread));
		}
		uv_close((uv_handle_t*)handle, &NetLibuv::SocketAfterCloseCallBackFunc);
		return;
	}
	
	cout << "client socket:" << client->socket << ",recv msg:" << buf->base << endl;
	memset(buf->base, 0, buf->len);

}



void    NetLibuv::RegisterSocket(int sock)
{

}

void    NetLibuv::UnRegisterSocket(int sock)
{

}
