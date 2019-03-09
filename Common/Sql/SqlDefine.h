/*
* author: lhq
* date  : 2017.9.27
* bref	 : sql define
*/

#ifndef	_SQL_DEFINE_H
#define _SQL_DEFINE_H

#include "AssertMgr.h"


//sql基础配置定义
enum	SQL_CONFIG_DEFINE
{
	MAX_DB_HOST_LEN = 128,
	MAX_DB_NAME_LEN = 64,
	MAX_DB_PWD_LEN = 64,
	MAX_DB_COL_NAME_LEN = 64, //列名最大长度
	MAX_DB_COL_BUFFER = 8192,  //每列缓存区大小
	MAX_DB_COL_BUFFER_NUM = 400, //列缓存区最大数量
	MAX_DB_SQL_LEN = 419600 * 2,	//sql语句最大长度
	MAX_DB_ERROR_MSG_LEN=511,//
};

//数据库类型
enum	SQL_TYPE
{
	SQL_TYPE_ACCOUNT,		//账号库
	SQL_TYPE_GAME,			//游戏库

	SQL_TYPE_NUM,
};

//连接状态
enum  SQL_CONN_STATUS
{
	SQL_CONNECTING,		//连接中
	SQL_CONNECTED,		//已连接
	SQL_CLOSE,			//已断开

	SQL_STATUS_NUM,
};


typedef	 unsigned char  SQLCHAR;

#endif
