#include "Lua-head.h"



static int Lua_MyTest(lua_State* L)
{
	lua_pushnumber(L,123);
	return 1;
}

static int Lua_BaseOperate(lua_State* L)
{
	lua_pushnumber(L,123);
	lua_pushstring(L,"BaseOperate");


	return 2;
}

static int Lua_ErrorTest(lua_State* L)
{
	luaL_error(L,"luaL_error test");

	return 1;
}

static int Lua_NewtableTest(lua_State* L)
{
	lua_newtable(L);
	
	lua_pushnumber(L,1);
	lua_pushstring(L,"hello");


	//lua_settable(L,-3);
	lua_settable(L,1);
	
	lua_pushnumber(L,2);
	lua_pushstring(L,"world");

	//lua_settable(L,-3);
	lua_settable(L,1);

	return 1;
}

static int Lua_GettableTest(lua_State* L)
{
	lua_getglobal(L,"student");
	
	lua_pushstring(L,"name");
	lua_gettable(L,-2);

	cout<<"name="<<lua_tostring(L,-1)<<endl;

//	lua_pop(L,1);
//
//	lua_pushstring(L,"age");
//	lua_gettable(L,-2);

	lua_pushstring(L,"age");
	lua_gettable(L,-3);

	
	cout<<"age="<<lua_tonumber(L,-1)<<endl;
	
	return 1;
}

static int Lua_GetfieldTest(lua_State* L)
{
	lua_getfield(L,LUA_REGISTRYINDEX,"GDTest");
	GDTest* data = (GDTest*)lua_touserdata(L,-1);
	
	lua_pop(L,1);
	lua_getfield(L,LUA_REGISTRYINDEX,"world_id");
	
	int* world_id = (int*)lua_touserdata(L,-1);

	lua_pushnumber(L,data->MemPai);
	lua_pushnumber(L,data->Level);
	lua_pushnumber(L,*world_id);
	
	return 3;
}

static int Lua_NewUserData(lua_State* L)
{
	int size = luaL_checkinteger(L,1);	

	int total_size = sizeof(int)*size;
	lua_newuserdata(L,total_size);


	return 1;
}

static int Lua_GetUserData(lua_State* L)
{
	int* data_list = (int*)lua_touserdata(L,1);
	int  index = luaL_checkinteger(L,2);

	lua_pushnumber(L,data_list[index]);
	return 1;
}

static int Lua_SetUserData(lua_State* L)
{
	int* data_list = (int*)lua_touserdata(L,1);
	int  index = luaL_checkinteger(L,2);
	int  value = luaL_checkinteger(L,3);

	data_list[index] = value;

	return 1;
}

static struct luaL_Reg FuncList[]=
{
	{"MyTest",Lua_MyTest},
	{"BaseOperate",Lua_BaseOperate},
	{"ErrorTest",Lua_ErrorTest},
	{"NewtableTest",Lua_NewtableTest},
	{"GettableTest",Lua_GettableTest},
	{"GetfieldTest",Lua_GetfieldTest},

	{"NewUserData",Lua_NewUserData},
	{"GetUserData",Lua_GetUserData},
	{"SetUserData",Lua_SetUserData},
	
	{NULL,NULL},
};

LUAMOD_API int
luaopen_libmylua_test(lua_State* L)
{
	//lua_register(L,"MyTest",Lua_MyTest);

	luaL_newlib(L,FuncList);
	
	//luaL_newlibtable(L,FuncList);
	//luaL_setfuncs(L,FuncList,0);
	
	//lua_newtable(L);
	//luaL_setfuncs(L,FuncList,0);
		  
	return 1;
}
