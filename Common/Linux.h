/*
 * author: lhq
 * date  : 2017.4.3
 * bref  : linux definition
 */

#ifndef		_LINUX_H
#define		_LINUX_H

#ifdef	_WINDOWS

#else
#include <errno.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <execinfo.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

typedef	int			SOCKET;
typedef	pthread_t	TID;

#ifndef	FALSE
#define	FALSE false
#endif


#define	 THREAD_API			void*
#define	 TLS				__thread

typedef long long			INT64;

#ifdef USE_REDIS
#include "linux/hiredis.h"
#endif

class GameLock
{
public:
	GameLock() { pthread_mutex_init(&m_Lock, NULL); }
	~GameLock() { pthread_mutex_destroy(&m_Lock); }

	void	Lock() { pthread_mutex_lock(&m_Lock); }
	void    UnLock() { pthread_mutex_unlock(&m_Lock); }
private:
	pthread_mutex_t		m_Lock;
};

#endif



#endif
