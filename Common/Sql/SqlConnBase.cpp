#include "SqlConnBase.h"


SqlConnBase::SqlConnBase()
{
	memset(m_DBHostName,0,sizeof(m_DBHostName));
	memset(m_DBName,0,sizeof(m_DBHostName));
	memset(m_DBUserName,0,sizeof(m_DBHostName));
	memset(m_DBUserPwd,0,sizeof(m_DBHostName));
	memset(m_ErrorMsg,0,sizeof(m_ErrorMsg));
	m_Port = INVALID_ID;
	m_ConnStatus = SQL_CLOSE;
}

SqlConnBase::~SqlConnBase()
{

}

void SqlConnBase::SetStatus(BYTE status)
{
	if (!BETWEEN(status, SQL_CONNECTING, SQL_STATUS_NUM))
	{
		GAME_ASSERT_MSG(FALSE, "SqlConnBase::SetStatus not between define range");
		return;
	}

	m_ConnStatus = status;
}

