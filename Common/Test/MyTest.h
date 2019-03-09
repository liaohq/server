/*
 * author: lhq
 * date  : 2017.8.26
 * bref	 : mytest entrance
 */

#ifndef	_MY_TEST_H
#define _MY_TEST_H

#include "Common.h"
#include "MyTestDefine.h"
#include "FastDelegate.h"
#include "Net/NetSelect.h"

typedef fastdelegate::FastDelegate< void(void*) >	TEST_FUNC;
typedef fastdelegate::FastDelegate<void(const string&)>  OUT_PUT_FUNC;


class	MyTest
{
public:
	MyTest();
	~MyTest();
	void			Init();
	void			CleanUp();
public:
	void			MyTestEntrance();
private:
	//共享内存测试
	void			ShareMemoryTest(void* arg);
	void			ShareMemorySetData();
	void			ShareMemoryGetData();

	//protobuf 
	void			ProtobufTest(void* arg);

	//net select test
	void			NetSelectTest(void* arg);

	//TEST_STRING_HELPER
	void			StringHelperTest(void* arg);
	//libuv test
	void			LibuvTest(void* arg);

	//mysql
	void			MysqlTest(void* arg);

	//redis
	void			RedisTest(void* arg);
	//table config
	void			TableConfigTest(void* arg);
	//assert
	void			AssertTest(void* arg);
	//other
	void			OtherTest(void* arg);
	//dump
	void		    DumpTest(void* arg);
	//Lua
	void			LuaTest(void* arg);
	//sigsegv
	void			SigSegvTest(void* arg);
private:
	TEST_FUNC		m_TestFunc[TEST_END];             //FastDelegate class func test
	BYTE			m_TestFuncIsEnable[TEST_END];
	OUT_PUT_FUNC	m_OutFunc;                        //FastDelegate 非类函数回调测试
	NetSelect		m_Select;
};


extern	MyTest	g_MyTest;

#ifndef	MY_TEST
#define MY_TEST	g_MyTest	
#endif

#endif
