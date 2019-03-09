#include "MysqlConn.h"


MysqlConn::MysqlConn()
{
	m_Result = NULL;
	CleanUp();
}

MysqlConn::~MysqlConn()
{
	CleanUp();
}

void	MysqlConn::Init(const char* host, const char* user, const char* passwd, const char* db, UINT port)
{
	if (IS_NULL(host) || IS_NULL(user) || IS_NULL(passwd) || IS_NULL(db) )
	{
		GAME_ASSERT_MSG(FALSE, "MysqlConn::Init 参数异常");
		return;
	}

	SetHostName(host);
	SetUserName(user);
	SetUserPwd(passwd);
	SetDBName(db);
	SetPort(port);

	mysql_init(&m_Mysql);

	if (mysql_real_connect(&m_Mysql,host,user,passwd,db,port,NULL,0)==NULL)
	{
		GAME_ASSERT_MSG(FALSE,"mysql_real_connect fail,errno:%d,error_msg:%s",GetError(),GetErrorMsg());
		return;
	}

	PRINT_MSG("connect mysql success");
	
}

void	MysqlConn::Connect()
{


}

void    MysqlConn::Fetch()
{

}

void	MysqlConn::Execute()
{

}

void	MysqlConn::CleanUp()
{
	if ( m_Result )
	{
		mysql_free_result(m_Result);
	}

	OnClosed();
	
}
