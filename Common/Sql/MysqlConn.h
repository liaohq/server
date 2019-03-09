/*
 * author: lhq
 * date  : 2017.9.27
 * bref	 : Mysql
 */

#ifndef	_MYSQL_CONN_H
#define	_MYSQL_CONN_H

#include "SqlConnBase.h"
#include "mysql.h"

class	MysqlConn:public SqlConnBase
{
public:
	MysqlConn();
	~MysqlConn();
public:
	virtual	void	Connect();
	virtual	void	Fetch();
	virtual	void	Execute();
public:
	void			Init(const char* host,const char* user,const char* passwd,const char* db,UINT port);
	int				GetError(){return mysql_errno(&m_Mysql);}
	const char*		GetErrorMsg(){return mysql_error(&m_Mysql);}
private:
	void			CleanUp();
private:
	MYSQL			m_Mysql;
	MYSQL_RES*		m_Result;
};


#endif
