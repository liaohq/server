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
}

void	NetServer::Start()
{
	m_NetHandle.Start();
}

void	NetServer::Stop()
{
	m_NetHandle.Stop();
}

void	NetServer::CleanUp()
{
}

int		NetServer::AcceptThread(ThreadInfo& info)
{
	

	return RET_SUCCESS;
}

