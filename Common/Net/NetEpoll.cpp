#include "NetEpoll.h"
#include "SocketDefine.h"


NetEpoll::NetEpoll()
{
	CleanUp();
}

NetEpoll::~NetEpoll()
{


}
void    NetEpoll::PreInit()
{

}

void	NetEpoll::Init()
{
	m_WorkThread.AddThread(this,&NetEpoll::WorkThread);
}

void	NetEpoll::Start()
{
	m_WorkThread.Start();

	m_EpollFD = SystemApi::EpollCreate(EPOLL_SIZE);

}

void	NetEpoll::CleanUp()
{
	m_EpollFD = INVALID_SOCKET;
}

void    NetEpoll::Stop()
{
}

int		NetEpoll::WorkThread(ThreadInfo& info)
{
	if(m_EpollFD ==  INVALID_SOCKET)
	{ 
		return RET_SUCCESS;
	}

	struct epoll_event  event_list[EPOLL_WAIT_EVENT_SIZE];
	int nfds = epoll_wait(m_EpollFD,event_list,EPOLL_WAIT_EVENT_SIZE,500);
	for(int i=0;i<nfds;i++)
	{
		struct epoll_event cur_ev = event_list[i];
		int cur_sock = cur_ev.data.fd;
		if(cur_sock == INVALID_SOCKET)
		{
			continue;
		}

		if( cur_ev.events & EPOLLIN)
		{
			const int buf_size = 1024;
			char buf[buf_size];
			while(1)
			{
				memset(&buf,0,sizeof(buf));
				int read_num = read(cur_ev.data.fd,buf,buf_size);
				if(read_num == 0)
				{
					UnRegisterSocket(cur_sock);
					break;
				}
				else if(read_num == -1  )
				{
					break;
				}
				

				buf[read_num]='\0';
			    
				stringstream oss;
				oss<<"recv client "<< cur_sock << ", curTime: "<<TIME_API.GetCurrentTimeStr()<<endl;
				oss<<buf;
				cout<<oss.str()<<endl;

				write(cur_sock,buf,read_num);
				

				//if(read_num == buf_size)
				{
					cur_ev.events = EPOLLOUT|EPOLLET;
					SystemApi::EpollControl(m_EpollFD,EPOLL_CTL_MOD,cur_sock,&cur_ev);
				}
			}
		}
		else if(cur_ev.events & EPOLLOUT)
		{
			cout<<"epollout msg"<<endl;
			cur_ev.events = EPOLLIN|EPOLLET;
			SystemApi::EpollControl(m_EpollFD,EPOLL_CTL_MOD,cur_sock,&cur_ev);
	
		}

	}
	return RET_SUCCESS;
}

void    NetEpoll::RegisterSocket(int sock)
{
	if(sock == INVALID_SOCKET )
	{
		return;
	}

	if( m_EpollFD ==  INVALID_SOCKET)
	{
		GAME_ASSERT_MSG(false,"epoll_fd error");
		return;
	}

	SystemApi::SetNonBlocking(sock);

	struct epoll_event  ev;
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = sock;

	SystemApi::EpollControl(m_EpollFD,EPOLL_CTL_ADD,sock,&ev);
	
	cout<<"new client connect :"<<sock<<endl;
}

void    NetEpoll::UnRegisterSocket(int sock)
{
	if(sock == INVALID_SOCKET)
	{
		GAME_ASSERT_MSG(false,"UnRegisterSocket error,sock invalid");
		return ;
	}

	if( m_EpollFD ==  INVALID_SOCKET)
	{
		GAME_ASSERT_MSG(false,"epoll_fd error");
		return;
	}
	
	SystemApi::SocketClose(sock);
	cout<<" client disconnect :"<<sock<<endl;
}

