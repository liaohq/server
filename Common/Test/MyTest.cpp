#include "stdafx.h"
#include "MyTest.h"
#include "Table/TableConfig.h"
#include "Packet/PDTest.pb.h"
#include "uv.h"
#include "mysql.h"
#include "Sql/SqlMgr.h"
#include "Lua-Src/Lua-head.h"
#include <signal.h>
#include <setjmp.h>


jmp_buf env;

MyTest	g_MyTest;



MyTest::MyTest()
{
	CleanUp();

	m_OutFunc = OUT_PUT_FUNC(&OutPutMsg);
	m_TestFunc[TEST_SHARE_MEMORY] = TEST_FUNC(this,&MyTest::ShareMemoryTest);
	m_TestFunc[TEST_GOOGLE_PROTOBUF] = TEST_FUNC(this,&MyTest::ProtobufTest);
	m_TestFunc[TEST_NET_SELECT] = TEST_FUNC(this,&MyTest::NetSelectTest);
	m_TestFunc[TEST_STRING_HELPER] = TEST_FUNC(this,&MyTest::StringHelperTest);
	m_TestFunc[TEST_LIBUV] = TEST_FUNC(this,&MyTest::LibuvTest);
	m_TestFunc[TEST_MYSQL] = TEST_FUNC(this, &MyTest::MysqlTest);
	m_TestFunc[TEST_REDIS] = TEST_FUNC(this, &MyTest::RedisTest);
	m_TestFunc[TEST_TABLE_CONFIG] = TEST_FUNC(this, &MyTest::TableConfigTest);
	m_TestFunc[TEST_ASSERT] = TEST_FUNC(this, &MyTest::AssertTest);
	m_TestFunc[TEST_OTHER]=TEST_FUNC(this,&MyTest::OtherTest);
	m_TestFunc[TEST_DUMP]=TEST_FUNC(this,&MyTest::DumpTest);
	m_TestFunc[TEST_LUA]=TEST_FUNC(this,&MyTest::LuaTest);
	m_TestFunc[TEST_SIGSEGV]=TEST_FUNC(this,&MyTest::SigSegvTest);
}

MyTest::~MyTest()
{
	CleanUp();
}

void MyTest::Init()
{
	m_TestFuncIsEnable[TEST_SHARE_MEMORY]    = false;
	m_TestFuncIsEnable[TEST_GOOGLE_PROTOBUF] = false;
	m_TestFuncIsEnable[TEST_NET_SELECT]      = false;
	m_TestFuncIsEnable[TEST_STRING_HELPER]   = false;
	m_TestFuncIsEnable[TEST_LIBUV]			 = false;
	m_TestFuncIsEnable[TEST_MYSQL]			 = false;
	m_TestFuncIsEnable[TEST_REDIS]			 = false;
	m_TestFuncIsEnable[TEST_TABLE_CONFIG]    = false;
	m_TestFuncIsEnable[TEST_ASSERT]			 = false;			 
	m_TestFuncIsEnable[TEST_OTHER]			 = false;
	m_TestFuncIsEnable[TEST_DUMP]			 = false;
	m_TestFuncIsEnable[TEST_LUA]			 = false;	
	m_TestFuncIsEnable[TEST_SIGSEGV]		 = false;
}

void MyTest::CleanUp()
{
	memset(m_TestFuncIsEnable,false,sizeof(BYTE)*TEST_END);
}

void MyTest::MyTestEntrance()
{
	for(int i=0;i<TEST_END;i++)
	{
		if(!m_TestFuncIsEnable[i])
		{
			continue;
		}

		TEST_FUNC cur_func = m_TestFunc[i];
		if(cur_func == NULL )
		{
			continue;
		}
		cur_func(NULL);
	}
	//GAME_ASSERT_MSG(false,"dump test");
	//TABLE_CONFIG.Test();
}

void MyTest::ShareMemoryTest(void* arg)
{
	if(m_OutFunc)
	{
		m_OutFunc("ShareMemoryTest Begin");
	}

	ShareMemorySetData();
	ShareMemoryGetData();
}

void MyTest::NetSelectTest(void* arg)
{
	m_Select.Init();
	m_Select.Start();
}

void MyTest::MysqlTest(void* arg)
{
	DB_ACCOUNT_SQL.Init("localhost", "root", "123456", "account", 3306);
}

void MyTest::RedisTest(void* arg)
{
	unsigned int j;
	redisContext *c;
	redisReply *reply;
	c = redisConnect((char*)"127.0.0.1", 6379);
	if (c->err) 
	{
		GAME_ASSERT_MSG(FALSE,"Redis Connect error:%s\n",c->errstr);
		return;
	}
	PRINT_MSG("Redis Connect Success");

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
	//reply = (redisReply*)redisCommandArgv(c,sizeof(tmp_data),&send_msg,&data_len);
	reply = (redisReply*)redisCommand(c,"set i %b", send_msg, data_len);
	if(reply == NULL)
	{
		GAME_ASSERT_MSG(FALSE,"Redis Reply fail,err_str:%s\n",c->errstr);
		return;
	}

	printf("Redis Replay:%s\n",reply->str);

	reply = (redisReply*)redisCommand(c,"get i");
	if(reply == NULL)
	{
		GAME_ASSERT_MSG(FALSE,"Redis Reply fail,err_str:%s\n",c->errstr);
		return;
	}

	RedisData* msg = (RedisData*)reply->str;
	printf("Redis Replay,len:%d, :%d %d \n", reply->len, msg->English, msg->Math );

}

void MyTest::TableConfigTest(void* arg)
{
	PRINT_MSG("table config  test begin");
}

void MyTest::AssertTest(void* arg)
{
	GAME_ASSERT(FALSE);
}

//虚函数测试
class IMyBase
{
public:
	virtual void Test()=0;
};

class MyBase:public IMyBase
{
public:
	virtual void Test(){cout<<"Mybase"<<endl;}
};

class OtherBase:public MyBase
{
public:
	virtual void Test(){cout<<"Otherbase"<<endl;}
};


//
class	MyTestA
{
public:
	MyTestA(){}
	~MyTestA(){}

	int		m_Arg1;
	int		m_Arg2;
};

class	MyTestB
{
public:
	MyTestB(){}
	virtual ~MyTestB(){}

	int		m_Arg1;
	short	m_Arg2;
};

class  MyTestC
{
public:
	MyTestC(){}
	~MyTestC(){}

	int    m_Arg1;
	char   m_Arg2;
	static int    m_Arg3;
};

void ListNodeTest(const ListNode* node)
{
	if(node == NULL)
	{
		return;
	}

	//cout<<"node value="<<node->Data<<endl;

	const ListNode* tmp=node;
	while(tmp)
	{
		cout<<"node value="<<tmp->Data<<endl;
		tmp=tmp->Next;
	}
}

bool CheckListIsLoop(const ListNode* node)
{
	return false;
}

void Test1()
{
   char a[] = "abc";
   char b[] = "abc";
   const char c[]="abc";
   const char d[]="abc";

   //char *e= "abc";
   //char *f= "abc";

   const char* g="abc";
   const char* h="abc";

   cout<<"char a[]==char b[]  "<<(a==b)<<endl;
   cout<<"const char c[]==const char d[]  "<<(c==d)<<endl;
   //cout<<"char *e==char *f  "<<(e==f)<<endl;
   cout<<"const char *g==const char *h  "<<(g==h)<<endl;

   //重载
   //ReLoad  reload;
   //reload.Test1();
   //reload.Test1(12);

   OtherReLoad  other_reload;
   //other_reload.Test1(12); error

   //隐藏
   ReLoad* reload_ptr = new OtherReLoad();
   reload_ptr->Test1();

   cout<<"1<<8 ="<<(1<<8)<<endl;
}


void MyTest::OtherTest(void* arg)
{
	//内存分布测试
	Child*  child_ptr = new Child();
	cout<<"child_ptr size:"<<sizeof( Child )<<endl;
	cout<<"sizeof(int)="<<sizeof(int)<<endl;
	//虚函数测试
	OtherBase* obase=new OtherBase();
	obase->Test();

	MyBase* my_base=obase;
	my_base->Test();

	IMyBase* ibase=my_base;
	ibase->Test();


	//ListNode* node_list = new ListNode();
	//node_list->Data =10;
	//node_list->Next = new ListNode();
	//node_list->Next->Data = 100;
	//ListNodeTest(node_list);
	
	//Test1
	Test1();
	//
	cout<<"sizeof(IMyBase)"<<sizeof(IMyBase)<<endl;
	cout<<"sizeof(MyBase)"<<sizeof(MyBase)<<endl;
	cout<<"sizeof(OtherBase)"<<sizeof(OtherBase)<<endl;
	cout<<"sizeof(MyTestA)"<<sizeof(MyTestA)<<endl;
	cout<<"sizeof(MyTestB)"<<sizeof(MyTestB)<<endl;
	cout<<"sizeof(MyTestC)"<<sizeof(MyTestC)<<endl;

	int a[]={1,2,3,4};
	int* ptr=(int*)(&a+1);
	cout<<"*(a+1)="<<*(a+1)<<endl;
    cout<<"*ptr-1="<< *(ptr-1)<<endl;

	//MyBase* tmp=0;
	//tmp->Test();
	cout<<"sizeof(ArrayTest)="<<sizeof(ArrayTest)<<endl;
	ArrayTest* arrayTest=(ArrayTest*)malloc(sizeof(ArrayTest)+sizeof(int)*10);
	for(int i=0;i<10;i++)
	{
		arrayTest->Item[i]=i;
	}
	for(int i=0;i<10;i++)
	{
		cout<<"value="<<arrayTest->Item[i]<<endl;
	}
	cout<<"sizeof(arrayTest)="<<sizeof(arrayTest)<<endl;
	enum AA{k=5,b,c} BB;
	BB=(enum AA)9;
	cout<<"BB="<<BB<<endl;
}

void MyTest::DumpTest(void* arg)
{
	try{
		int* my_ptr = new int;
		*my_ptr = 12;
		int* tmp_ptr = my_ptr;
		cout<<"*(int*)tmp_str"<<&tmp_ptr<<endl;
		delete my_ptr;
		cout<<"*(int*)tmp_str"<<&tmp_ptr<<endl;
		int* ptr = NULL;
		*ptr = 123;
	}
	catch(...)
	{
		cout<<"NULL ptr"<<endl;
	}
}

void MyTest::LuaTest(void* arg)
{
	/*
	cout<<"lua test"<<endl;
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);
	luaopen_libmylua_test(L);
	int ret = luaL_loadfile(L,"../../Common/Lua/test.lua");
	if( ret != 0 )
	{
		const char* err = lua_tostring(L,-1);
		GAME_ASSERT_MSG(false,"dofile error:%d,errmsg=%s",ret,err);
	}
	else
	{
		ret=lua_pcall(L,0,0,0);
		if (ret != RET_SUCCESS)
		{
			const char* err = lua_tostring(L,-1);
			GAME_ASSERT_MSG(false,"lua_pcall error=%d,errmsg=%s",ret,err);
		}
	}
	lua_close(L);
	*/
}

void ErrorDump()
{
#ifdef	_WINDOWS

#else
	const int MaxLevel = 200;
	void* buf[MaxLevel];
	int level = backtrace(buf, MaxLevel);

	char** back_str = (char**)backtrace_symbols(buf, level);
	for (int i = 0; i < level; i++)
	{
		printf("%s\n", back_str[i]);
	}
#endif

}
void RecvSignal(int sig)
{
#ifdef	_WINDOWS

#else
	cout << "receive signal " << sig << endl;
	ErrorDump();
	siglongjmp(env, 1);
#endif

}

void MyTest::SigSegvTest(void* arg)
{
#ifdef	_WINDOWS

#else
	for (int i = 0; i < 2; i++)
	{
		int ret = sigsetjmp(env, 1);  //savesigs 不为 0时，会保存当前的信号屏蔽表 
		if (ret == 0)
		{
			signal(SIGSEGV, RecvSignal);
			int *tmp = new int;
			*tmp = 12;
			cout << "*tmp=" << *tmp << " &tmp" << tmp << endl;

			delete tmp;
			tmp = NULL;
			*tmp = 15;
			cout << " &tmp" << tmp << endl;
		}
		else
		{
			cout << "SigSegvTest err,ret=" << ret << endl;
		}

}
#endif


}

void MyTest::LibuvTest(void* arg)
{
	PRINT_MSG("libuv test begin");

	uv_loop_t* loop = uv_loop_new();
	uv_run(loop,UV_RUN_DEFAULT);

}

void MyTest::StringHelperTest(void* arg)
{
	cout<<"stringhelpertest:"<<StringHelper::ToInt("123")<<endl;
	cout<<"A="<<(int)'A'<<endl;
	cout<<"F="<<(int)'F'<<endl;
	cout<<"0="<<(int)'0'<<endl;
	cout<<"9="<<(int)'9'<<endl;
	cout<<"a="<<(int)'a'<<endl;
	cout<<"f="<<(int)'f'<<endl;
	cout<<"7-0="<<(int)('7'-'0')<<endl;

	// replace test
	string tmp("asdfsfsfsaabb");
	int count = StringHelper::Replace(tmp,"aabb","...");
	cout<<"string repalce count = "<<count<<",tmp new="<<tmp.c_str()<<endl;
}

void MyTest::ShareMemorySetData()
{
#ifndef _WINDOWS
	int data_len = sizeof(SM_Data);
	int shm_id = shmget(SM_DATA_PLAYER,data_len,0666|IPC_CREAT);
	if(IS_INVALID_ID(shm_id))
	{
		PRINT_MSG("ShareMemorySetData shmget error");
		return;
	}


	cout<<"shm_id:"<<shm_id<<endl;

	void* data = shmat(shm_id,0,0);
	if(IS_NULL(data))
	{
		PRINT_MSG("ShareMemorySetData shmat error");
		return;
	}

	struct SM_Data* sm_data =(struct SM_Data*)data;
	sm_data->Score = 100;

	SystemApi::DetachShareMemory(data);
#endif

}

void MyTest::ShareMemoryGetData()
{
#ifndef _WINDOWS
	//int shm_id = shmget(SM_DATA_PLAYER,sizeof(SM_Data),0666|IPC_CREAT);
	int shm_id = SystemApi::OpenShareMemory(SM_DATA_PLAYER,sizeof(SM_Data)); 
	if(IS_INVALID_ID(shm_id))
	{
		cout<<strerror(errno)<<endl;
		shm_id = SystemApi::CreateShareMemory(SM_DATA_PLAYER,sizeof(SM_Data));
		if(IS_INVALID_ID(shm_id))
		{
			PRINT_MSG("ShareMemoryGetData shmget error");
			cout<<strerror(errno)<<endl;
			return;
		}
	}

	cout<<"shm_id:"<<shm_id<<endl;

	SM_Data* data = (SM_Data*)shmat(shm_id,NULL,0);
	if(IS_NULL(data))
	{
		PRINT_MSG("ShareMemoryGetData shmat error");
		return;
	}

	char  buf[256]={0};
	sprintf(buf,"共享内存 Score:%d",data->Score);
	PRINT_MSG(buf);

	int ret = shmctl(shm_id,IPC_RMID,0);
	if(ret == RET_SUCCESS)
	{
		PRINT_MSG("sharememory remove success");
	}
	else
	{
		PRINT_MSG("sharememory remove fail");
	}
#endif

}

void	MyTest::ProtobufTest(void* arg)
{
	
	msg::hellloworld  msg1;
	msg1.set_id(100900715);
	msg1.set_str("hello world");
	msg1.set_opt(8888);
	
	int msg1_len = msg1.ByteSize();

	string tmp_str;
	msg1.SerializeToString(&tmp_str);


	char buf[256];
	memset(buf,0,sizeof(buf));
	msg1.SerializeToArray(&buf,sizeof(buf));

	msg::hellloworld msg2;
	//msg2.ParseFromString(tmp_str);
	msg2.ParseFromArray(buf,sizeof(buf));

	cout<<"protobuf ParseFromString test,msg1 len:"<<msg1_len<<"; id:"<<msg2.id()<<"; str:"<<msg2.str()<<"; opt:"<<msg2.opt()<<endl;
}
