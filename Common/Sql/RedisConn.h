/*
 * author: lhq
 * date  : 2019.3.23
 * bref	 : redis connect base interface
 */

#ifndef	_REDIS_CONN_H
#define	_REDIS_CONN_H

#include "Common.h"
#include "Base/Module.h"
#include "SystemApi.h"

class RedisConn:public Module
{
public:
	RedisConn();
	~RedisConn();

public:
	void				PreInit();
	void				Init();
	void				Start();
	void				Stop();
	void				CleanUp();

public:
	void				Test();
private:
	redisContext*		m_connHandle;
	redisReply*			m_reply;
};

extern   RedisConn  g_RedisConn;

#ifndef  REDIS_MGR
#define  REDIS_MGR   g_RedisConn
#endif

#endif
