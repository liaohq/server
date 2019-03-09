#include "LuaMgr.h"
#include "Lua-head.h"

LuaMgr	g_LuaMgr;

LuaMgr::LuaMgr()
{
	CleanUp();
}

LuaMgr::~LuaMgr()
{


}

void	LuaMgr::PreInit()
{

}

void	LuaMgr::Init()
{
	L = luaL_newstate();
	if( NULL == L)
	{
		GAME_ASSERT_MSG(false,"luaL_newstate error");
		return;
	}

	luaL_openlibs(L);
}

void	LuaMgr::Start()
{
	luaopen_libmylua_test(L);
	luaopen_libmylua_other(L);

	GDTest* ptr = new GDTest;
	ptr->MemPai = 1;
	ptr->Level = 59;

	lua_pushlightuserdata(L,ptr);
	lua_setfield(L,LUA_REGISTRYINDEX,"GDTest");
	
	lua_pop(L,1);
	int* tmp = new int;
	*tmp =1000;

	lua_pushlightuserdata(L,tmp);
	lua_setfield(L,LUA_REGISTRYINDEX,"world_id");
}

void	LuaMgr::Stop()
{
	lua_close(L);	
	L = NULL;
}

void	LuaMgr::CleanUp()
{
}

void	LuaMgr::LoadLua(const char* src)
{
	if( NULL == src)
	{
		GAME_ASSERT_MSG(false,"LuaMgr::LoadLua src NULL");
		return ;
	}


	int ret = luaL_loadfile(L,src);
	if( ret != 0 )
	{
		const char* err = lua_tostring(L,-1);
		GAME_ASSERT_MSG(false,"load_file error:%d,errmsg=%s",ret,err);
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

}
	
void	LuaMgr::LuaDoFile(const char * src)
{
	if( NULL == src)
	{
		GAME_ASSERT_MSG(false,"LuaMgr::LuaDoFile src NULL");
		return ;
	}


	int ret = luaL_dofile(L,src);
	if( ret != 0 )
	{
		const char* err = lua_tostring(L,-1);
		GAME_ASSERT_MSG(false,"LuaDoFile dofile error:%d,errmsg=%s",ret,err);
	}

	//lua_settop(L,0);
	//cout<< lua_gettop(L) <<endl;
	//lua_settop(L,0);

//	int lua_size = lua_gettop(L);
//   	
//   	cout<<"lua_size="<< lua_size  <<endl;
//   	lua_settop(L,1);
//   	lua_size = lua_gettop(L);
//   	cout<<"after settop lua_size="<< lua_size  <<endl;

}
