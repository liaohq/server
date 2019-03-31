#include "RedisConn.h"
#include "stdafx.h"


RedisConn  g_RedisConn;


RedisConn::RedisConn()
{

}

RedisConn::~RedisConn()
{

}

void	RedisConn::PreInit()
{
	m_connHandle = redisConnect((char*)"119.23.13.125", 6379);
	if (m_connHandle->err) 
	{
		GAME_ASSERT_MSG(FALSE,"Redis Connect error:%s\n",m_connHandle->errstr);
		return;
	}

	PRINT_MSG("Redis Connect Success");
}

void	RedisConn::Init()
{

}


void	RedisConn::Start()
{
	Test();
}


void	RedisConn::Stop()
{

}

void	RedisConn::CleanUp()
{

}

void	RedisConn::Test()
{

	//set data
	struct RedisData
	{
		int English;
		int Math;
	};

	RedisData* tmp_data=new RedisData;
	tmp_data->English=100;
	tmp_data->Math=200;

	
	//INT64  key=(INT64)tmp_data;
	//PRINT_MSG(key);

	
	size_t data_len=sizeof(tmp_data);
	const char* send_msg=(const char*)tmp_data;
	
	m_reply = (redisReply*)redisCommand(m_connHandle,"set i %b", send_msg, data_len);
	if(m_reply == NULL)
	{
		GAME_ASSERT_MSG(FALSE,"Redis Reply fail,err_str:%s\n",m_connHandle->errstr);
		return;
	}

	printf("Redis Replay:%s\n",m_reply->str);

	m_reply = (redisReply*)redisCommand(m_connHandle,"get i");
	if(m_reply == NULL)
	{
		GAME_ASSERT_MSG(FALSE,"Redis Reply fail,err_str:%s\n",m_connHandle->errstr);
		return;
	}

	RedisData* msg = (RedisData*)m_reply->str;
	printf("Redis Replay,len:%d, :%d %d \n", m_reply->len, msg->English, msg->Math );

}
