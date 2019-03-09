#include "Lua-head.h"



static int Lua_MyOtherTest(lua_State* L)
{
	lua_pushstring(L,"hello world my other test");
	return 1;
}

static struct luaL_Reg FuncList[]=
{
	{"MyOtherTest",Lua_MyOtherTest},
	{NULL,NULL},
};

LUAMOD_API int
luaopen_libmylua_other(lua_State* L)
{
	luaL_newlib(L,FuncList);	
	return 1;
}
