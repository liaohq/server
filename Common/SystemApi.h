/*
 * author: lhq
 * data	 : 2017.8.29
 * bref	 : system api 
 */

#ifndef		_SYSTEM_API_H
#define		_SYSTEM_API_H

#include "Common.h"


enum	SYSTEM_LOCK_STATUS
{
	SLS_UNLOCK=0,
	SLS_LOCKED=1,
};

class SystemApi
{
public:
	static  int		OpenShareMemory(key_t  key,size_t data_len)
	{
		if(data_len<=0)
		{
			return -1;
		}

#ifdef	_WINDOWS
		
#else
		return shmget(key,data_len,0);
#endif
	}

	static	int		CreateShareMemory(key_t key,size_t data_len)
	{
		if(data_len<=0)
		{
			return -1;
		}

#ifdef	_WINDOWS
		
#else
		return shmget(key,data_len,0666|IPC_CREAT);
#endif
	}

	static  char*		AttachShareMemory(int sh_id)
	{

#ifdef	_WINDOWS
		
#else
		return (char*)shmat(sh_id,NULL,0);
#endif

	}

	static  int		DetachShareMemory(void* shmaddr)
	{
		if(shmaddr == NULL)
		{
			return -1;
		}

#ifdef	_WINDOWS
		
#else
		return shmdt(shmaddr);
#endif
	}

	static  int		DeleteShareMemory(int sh_id)
	{

#ifdef	_WINDOWS
		
#else
		return shmctl(sh_id,IPC_RMID,0);
#endif
	}

	static int		GetSystemError()
	{
#ifdef	_WINDOWS
		return GetLastError();
#else
		return	errno;
#endif
	}

	static  string	GetSystemErrorString()
	{
#ifdef	_WINDOWS
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR)&lpMsgBuf,
			0,
			NULL
		);

		return (char*)lpMsgBuf;
#else

		return strerror(errno);
#endif
	}

	static	void	SystemSleep(int sleep_times_sec)
	{
		if (sleep_times_sec<=0)
		{
			return;
		}

#ifdef	_WINDOWS
		Sleep(sleep_times_sec * 1000);		//windows 毫秒为单位
#else
		sleep(sleep_times_sec);
#endif
	}

	static long&  LockConflictTimes()
	{
		static long _ConflictTimes;
		return _ConflictTimes;
	}

	// atom lock
	static bool   Lock(volatile long& flag, bool is_multi_thread = true, UINT max_conflict_times = 200)
	{
		if (is_multi_thread)
		{
			UINT conflict_times = 0;
			while (flag == SLS_LOCKED || InterlockedCompareExchange(flag, SLS_LOCKED, SLS_UNLOCK) != SLS_UNLOCK)
			{
				conflict_times++;
				if (conflict_times == max_conflict_times)
				{
					InterlockedIncrement(LockConflictTimes());
					SystemSleep(0);
					conflict_times = 0;
				}
				continue;
			}
			return true;
		}
		else
		{
			if (flag != SLS_UNLOCK)
			{
				return false;
			}

			flag = SLS_LOCKED;
			return true;
		}
	}

	//atom unlock
	static void   UnLock(volatile long& flag, bool is_multi_thread = true)
	{
		if (is_multi_thread)
		{
			InterlockedExchange(flag, SLS_UNLOCK);
		}
		else
		{
			flag = SLS_UNLOCK;
		}
	}

	static long   InterlockedExchange(volatile long& flag, long val)
	{
#ifdef _WINDOWS
		return ::InterlockedExchange((volatile long*)&flag, val);
#else
		return __sync_lock_test_and_set((volatile long*)&flag, val);
#endif
	}

	static long   InterlockedCompareExchange(volatile long&flag, long val, long old_val)
	{
#ifdef _WINDOWS
		return ::InterlockedCompareExchange((volatile long*)&flag, val, old_val);
#else
		return __sync_val_compare_and_swap((volatile long*)&flag, old_val, val);
#endif
	}

	static long	  InterlockedExchangeAdd(volatile long& val, long addval)
	{
#ifdef	_WINDOWS
		return ::InterlockedExchangeAdd((volatile long*)&val, addval);
#else
		return __sync_add_and_fetch((volatile long*)&val, addval);
#endif
	}

	static long  InterlockedIncrement(volatile long& val)
	{
#ifdef _WINDOWS	
		return ::InterlockedIncrement((volatile long*)&val);
#else
		return __sync_add_and_fetch((volatile long*)&val, 1);
#endif
	}

	static long InterlockedDecrement(volatile long& val)
	{
#ifdef _WINDOWS
		return ::InterlockedDecrement((volatile long*)&val);
#else
		return  __sync_sub_and_fetch((volatile long*)&val, 1);
#endif
	}

	static void  SetNonBlocking(int sock)
	{
		int opt=fcntl(sock,F_GETFL);
		if(opt<0)
		{
			return;
		}
		opt |=O_NONBLOCK;
		
		if( fcntl(sock,F_SETFL,opt)<0 )
		{
			//todo log
			return;
		}
	}

	static int  EpollCreate(int size)
	{
		int epfd = epoll_create(size);
		return epfd;
	}

	static void EpollControl(int epfd,int opt_type,int sock,epoll_event* event)
	{
		int ret = epoll_ctl(epfd,opt_type,sock,event);
		if(ret != 0)
		{
			return;
		}
	}

	static void SocketClose(int sock)
	{
		close(sock);
	}
};


#endif
