#include "SqlMgr.h"
#include "MysqlConn.h"



SqlMgr::SqlMgr()
{
	m_ConnInstance = NULL;
}

SqlMgr::~SqlMgr()
{
	SAFE_DELETE(m_ConnInstance);
}

void	SqlMgr::Init(const char* host, const char* user, const char* passwd, const char* db, UINT port)
{
#ifdef USE_MYSQL
	m_ConnInstance = new MysqlConn();
#else

#endif
	if (IS_NULL(m_ConnInstance))
	{
		GAME_ASSERT_MSG(FALSE, "SqlMgr::Init m_ConnInstance数据库实例为空");
		return;
	}

	m_ConnInstance->Init(host, user, passwd, db, port);
}
