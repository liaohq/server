#include "NetServer.h"

NetServer	g_NetServer;

NetServer::NetServer()
{
	CleanUp();
}

NetServer::~NetServer()
{


}

void	NetServer::PreInit()
{
	m_NetHandle.PreInit();
}

void	NetServer::Init()
{
	m_NetHandle.Init();
	m_AcceptThread.AddThread(this,&NetServer::AcceptThread);


	int listen_fd = socket(AF_INET,SOCK_STREAM,0);

	int one=1;
	if( setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one))<0)
	{
		GAME_ASSERT_MSG(false,"setsockopt reuseaddr error");
		return ;
	}

	struct sockaddr_in  servaddr;
	memset(&servaddr,0,sizeof(struct sockaddr_in));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listen_fd,LISTEN_MAX_NUM);

    //SystemApi::SetNonBlocking(listen_fd);


	m_ListenFd = listen_fd;
	
	cout<<"Listen on 0.0.0.0:8888"<<endl;
}

void	NetServer::Start()
{
	m_NetHandle.Start();
	m_AcceptThread.Start();
}

void	NetServer::Stop()
{
	m_NetHandle.Stop();
}

void	NetServer::CleanUp()
{
	m_ListenFd = INVALID_SOCKET;
}

int		NetServer::AcceptThread(ThreadInfo& info)
{
	if( m_ListenFd == INVALID_SOCKET )
	{
		return RET_SUCCESS;
	}

	struct sockaddr_in cliaddr;
	socklen_t clilen = sizeof(cliaddr);

	int connfd = accept(m_ListenFd,(struct sockaddr*)&cliaddr,&clilen);
	if(connfd <= 0 )
	{
		GAME_ASSERT_MSG(false,"accept fail");
		return RET_SUCCESS;
	}


	m_NetHandle.RegisterSocket(connfd);

	return RET_SUCCESS;
}

