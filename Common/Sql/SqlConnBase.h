/*
 * author: lhq
 * date  : 2017.9.27
 * bref	 : sql connect base interface
 */

#ifndef	_SQL_CONN_BASE_H
#define	_SQL_CONN_BASE_H

#include "Common.h"
#include "SqlDefine.h"
#include "SystemApi.h"

class	SqlConnBase
{
public:
	SqlConnBase();
	~SqlConnBase();
public:
	virtual void		Connect()=0;
	virtual	void		Fetch() = 0;
	virtual void		Execute() = 0;
	virtual	void		Init(const char* host, const char* user, const char* passwd, const char* db, UINT port) = 0;
public:
	void				OnConnected() { m_ConnStatus = SQL_CONNECTED; }
	void				OnClosed() { m_ConnStatus = SQL_CLOSE; }
	void				OnConnectinged() { m_ConnStatus = SQL_CONNECTING; }
public:
	void				SetHostName(const string host_name) { if (!host_name.empty() && host_name.size() <= MAX_DB_HOST_LEN) { strncpy(m_DBHostName, host_name.c_str(), host_name.size()); } };
	const char*			GetHostName() { return m_DBHostName; }

	void				SetUserName(const string user_name) { if (!user_name.empty() && user_name.size() <= MAX_DB_NAME_LEN) { strncpy(m_DBUserName, user_name.c_str(), user_name.size()); } };
	const char*			GetUserName() { return m_DBUserName; }

	void				SetUserPwd(const string user_pwd) { if (!user_pwd.empty() && user_pwd.size() <= MAX_DB_PWD_LEN) { strncpy(m_DBUserPwd, user_pwd.c_str(), user_pwd.size()); } };
	const char*			GetUserPwd() { return m_DBUserPwd; }

	void				SetDBName(const string db_name) { if (!db_name.empty() && db_name.size() <= MAX_DB_NAME_LEN) { strncpy(m_DBName, db_name.c_str(), db_name.size()); } };
	const char*			GetDBName() { return m_DBName; }

	void				SetPort(UINT port) { if (IS_VALID(port)) { m_Port = port; } }
	UINT				GetPort() { return m_Port; }

	BYTE				GetStatus() { return m_ConnStatus; }
	void				SetStatus(BYTE status);

	void				SetError(int error){m_Error = error;}
private:

private:
	char				m_DBHostName[MAX_DB_HOST_LEN];
	char				m_DBName[MAX_DB_NAME_LEN];
	char				m_DBUserName[MAX_DB_NAME_LEN];
	char				m_DBUserPwd[MAX_DB_PWD_LEN];
	UINT				m_Port;
private:
	BYTE				m_ConnStatus;		//连接状态
	int					m_Error;
	SQLCHAR				m_ErrorMsg[MAX_DB_ERROR_MSG_LEN];
};

#endif
