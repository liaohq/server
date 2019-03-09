/*
* author: lhq
* date  : 2017.1.4
* bref	 : sql manager
*/

#ifndef	_SQL_MGR_H
#define	_SQL_MGR_H

#include "SqlConnBase.h"

class	SqlMgr
{
public:
	SqlMgr();
	~SqlMgr();

	static SqlMgr&	GetSingleton(int sql_type)
	{
		static SqlMgr	_Ins[SQL_TYPE_NUM];
		if (!BETWEEN(sql_type, SQL_TYPE_ACCOUNT, SQL_TYPE_NUM))
		{
			GAME_ASSERT_MSG(false, "SqlMgr::GetSingleton sql_type 数据库类型异常");
			return _Ins[SQL_TYPE_GAME];
		}

		return _Ins[sql_type];
	}

public:
	void			Init(const char* host, const char* user, const char* passwd, const char* db, UINT port);
private:
	SqlConnBase*	m_ConnInstance;
};

//账号库
#ifndef DB_ACCOUNT_SQL
#define	DB_ACCOUNT_SQL	SqlMgr::GetSingleton(SQL_TYPE_ACCOUNT)
#endif

//游戏库
#ifndef DB_GAME_SQL
#define	DB_GAME_SQL	SqlMgr::GetSingleton(SQL_TYPE_GAME)
#endif




#endif
