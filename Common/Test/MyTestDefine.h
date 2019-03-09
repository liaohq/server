/*
 * author: lhq
 * date  : 2017.8.26
 * bref	 : mytest define
 */

#ifndef _MY_TEST_DEFINE_H
#define _MY_TEST_DEFINE_H

#pragma pack(push,4)

//测试类型
enum MY_TEST_TYPE
{
	TEST_SHARE_MEMORY, //共享内存
	TEST_GOOGLE_PROTOBUF,//google protobuf
	TEST_NET_SELECT,	//select
	TEST_STRING_HELPER, // stringhelper
	TEST_LIBUV,			// libuv
	TEST_MYSQL,			//mysql
	TEST_REDIS,			//redis
	TEST_TABLE_CONFIG,  //table config
	TEST_ASSERT,		//assert 
	TEST_OTHER,			//other common
	TEST_DUMP,			// dump test
	TEST_LUA,			// lua
	TEST_SIGSEGV,		//sigsegv
	TEST_END,
};


typedef  unsigned char  BYTE;

#ifndef	INVALID_ID
#define INVALID_ID -1
#endif

//share memroy define
enum	SM_KEY
{
	SM_DATA_PLAYER = 10001, //player data
};

//共享内存数据
struct  SM_Data
{
	int		Score;
	SM_Data(){ CleanUp();}
	void	CleanUp()
	{
		Score = INVALID_ID;
	}
};

struct ArrayTest
{
	int  Len;
	int	 Item[0];  //柔性数组
};

struct ListNode
{
	int Data;
	ListNode* Next;
};


//重载,隐藏
class ReLoad
{
public:
	void  Test1(){cout<<"ReLoad:Test1()"<<endl;}
	int   Test1(int arg ){cout<<"ReLoad:Test1() return int,arg="<<arg<<endl;return 0;}
};

class OtherReLoad:public ReLoad
{
public:
	void  Test1(){cout<<"OtherReLoad:Test1()"<<endl;}
};

//FastDelegate 非类函数回调测试
inline void OutPutMsg(const string& msg)
{
	if(msg.empty())
	{
		return;
	}
	cout<<msg.c_str()<<endl;
}

class	Father
{
public:
	virtual void Test(){cout<<"father"<<endl;}
private:
	int   m_Arg;
};

class	Father1:virtual public Father
{
public:
	virtual void Test(){cout<<"father1"<<endl;}
private:
	int   m_Arg1;
};

class	Father2:virtual public Father
{
public:
	virtual void Test(){cout<<"father2"<<endl;}
private:
	int   m_Arg2;
};

class  Child:public Father1,public Father2
{
public:
	virtual void Test(){cout<<"child"<<endl;}
private:
	int   m_Arg;
};

#pragma pack(pop)

#endif
