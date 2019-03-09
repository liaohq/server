/*
 * author: lhq
 * date  : 2018.8.4
 * bref	 : socket define
 */

#ifndef	_SOCKET_DEFINE_H_
#define	_SOCKET_DEFINE_H_


enum SOCK_COMMON_DEFINE
{
	LISTEN_MAX_NUM = 100,
	EPOLL_SIZE     = 10000,
	EPOLL_WAIT_EVENT_SIZE = 500,
};

#define INVALID_SOCKET -1


#endif
