/*
 * author: lhq
 * date  : 20174.4.8
 * bref  : socket pool
 */

#ifndef		_SOCKET_POOL_H
#define		_SOCKET_POOL_H

typedef	unsigned char  BYTE;

#include"Net/Socket.h"
#include<vector>

class	SocketPool
{
public:
	SocketPool()
	{
		m_Pool   = NULL;
		m_Active = NULL;
		m_Index = 0;
		m_IdleList.clear();
		m_PoolMaxSize=0;
	}
	~SocketPool()
	{
		if(NULL != m_Pool)
		{
			delete[] m_Pool;
		}

		if(NULL !=m_Active)
		{
			delete[] m_Active;
		}
	}

	static  SocketPool&		GetSingleton()
	{
		static SocketPool	_Ins;
		return _Ins;
	}

	void		Init(int max_size)
	{
		if(max_size<=0)
		{
			return ;
		}
		m_Pool = new Socket[max_size];
		m_Active = new BYTE[max_size];
		
		for(int i=0;i<max_size;i++)
		{
			m_Active[i]=false;
		}
	}

	int			GetMaxSize()
	{
		return m_PoolMaxSize;
	}

	Socket*		NewSocket()
	{
		SystemApi::Lock(m_LockFlag);
		if( !m_IdleList.empty())
		{
			int idx= m_IdleList[m_IdleList.size()-1];
			m_IdleList.pop_back();
			Socket* sock = &m_Pool[idx];
			if( NULL == sock)
			{
				SystemApi::UnLock(m_LockFlag);
				return NULL;
			}
		
			if( m_Active[idx])
			{
				cout<<"m_Active fail"<<endl;
				SystemApi::UnLock(m_LockFlag);
				return NULL;
			}
			m_Active[idx]=true;
			sock->SetContainerIdx(idx);
			SystemApi::UnLock(m_LockFlag);
			return sock;
		}

		Socket* sock = &m_Pool[m_Index];
		if(NULL == sock)
		{
			SystemApi::UnLock(m_LockFlag);
			return NULL;
		}
		sock->SetContainerIdx(m_Index);
		if( m_Active[m_Index])
		{
			cout<<"m_Active fail"<<endl;
			SystemApi::UnLock(m_LockFlag);
			return NULL;
		}

		m_Active[m_Index] = true;
		m_Index +=1;
		SystemApi::UnLock(m_LockFlag);
		return sock;
	}

	void		FreeSocket(Socket* sock)
	{
		if(NULL == sock)
		{
			return;
		}
		SystemApi::Lock(m_LockFlag);
		int container_idx = sock->GetContainerIdx();
		if( container_idx < 0 )
		{
			SystemApi::UnLock(m_LockFlag);
			return;
		}

		m_IdleList.push_back(container_idx);
		m_Active[container_idx] = false;
		sock->CleanUp();
		SystemApi::UnLock(m_LockFlag);
	}
private:
	Socket*			m_Pool;
	BYTE*			m_Active;
	vector<int>		m_IdleList;
	int				m_Index;
	int				m_PoolMaxSize;
	volatile long m_LockFlag;
};


#ifndef		SOCKET_POOL
#define		SOCKET_POOL		SocketPool::GetSingleton()
#endif

#endif
