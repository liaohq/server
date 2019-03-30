#include"stdafx.h"
#include"LogicServer.h"
#include"Pool/SocketPool.h"
#include"Test/MyTest.h"
#include "Net/NetServer.h"
#include "Lua-Src/LuaMgr.h"
#include "Sql/RedisConn.h"

LogicServer	g_LogicServer;



int main(int argc,char** argv)
{
#ifdef _WINDOWS
	WSADATA		wsadata;
	WSAStartup(MAKEWORD(2,2),&wsadata);
#endif

	stringstream oss;
	oss<<"Current Time: "<<TIME_API.GetCurrentTimeStr().c_str()<<endl;
	oss<<"The Server Starting  "<<endl;
	cout<<oss.str();	
	
	
	g_LogicServer.PreInit();
	g_LogicServer.Init();
	g_LogicServer.Start();
    g_LogicServer.HandleCmd();	
	g_LogicServer.Stop();
	g_LogicServer.CleanUp();

	cout<<"The Server Is Close Success"<<endl;

	return RET_SUCCESS;
}

void	LogicServer::PreInit()
{
	SOCKET_POOL.Init(1000);

	m_ModuleContainer.RegisterModule(&NET_SERVER_MGR, "netserver");
	m_ModuleContainer.RegisterModule(&LUA_MGR, "luaMgr");
	m_ModuleContainer.RegisterModule(&REDIS_MGR, "redisMgr");



	m_ModuleContainer.PreInit();
}

void	LogicServer::Init()
{
	m_ModuleContainer.Init();
}

void	LogicServer::Start()
{

	m_ModuleContainer.Start();
#ifdef USE_MY_TEST
	Test();
#endif 
}

void	LogicServer::Stop()
{
	m_ModuleContainer.Stop();
}

void	LogicServer::CleanUp()
{
	m_ModuleContainer.CleanUp();
}

void	LogicServer::HandleCmd()
{
	stringstream oss;
	oss<<"The Server Start Finish, ";
	oss<<"Input \"/exit\" To Shut Down The Server ";
	cout<<oss.str()<<endl;
	while(true)
	{
		string str;
		getline(cin,str);
		vector<string> strArr;
		StringHelper::Split(str,";",strArr);

		if( strArr.size()<1)
		{
			cout<<"input param str"<<endl;
			continue;
		}

		string opt_str = strArr[0];
		if( strcmp(opt_str.c_str(),"/exit") == 0)
		{
			cout<<"The Server Is Closing ..."<<endl;
			return;
		}
		else if( strcmp(opt_str.c_str(),"loadlua") == 0 )
		{
			if( strArr.size()>1)
			{
				string param_0 = strArr[1];
				LUA_MGR.LoadLua(param_0.c_str());
			}
			else
			{
				cout<<"lack file name"<<endl;
			}
			continue;
		}
		else if( strcmp(opt_str.c_str(),"luadofile") == 0)
		{
			if( strArr.size()>1)
			{
				string param_0 = strArr[1];
				LUA_MGR.LuaDoFile(param_0.c_str());
			}
			else
			{
				cout<<"lack file name"<<endl;
			}
			continue;

		}
	}
}

void	LogicServer::Test()
{
	MY_TEST.Init();
	MY_TEST.MyTestEntrance();
}
