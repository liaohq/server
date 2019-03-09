/*
* author: lhq
* date  : 2018.8.13
* bref	 : lua mgr
*/

#ifndef		_LUA_MGR_H
#define		_LUA_MGR_H

#include "Common.h"
#include "CommonHead.h"
#include "Base/Module.h"

#ifdef	__cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef	__cplusplus
}
#endif

class LuaMgr:public Module
{
public:
	LuaMgr();
	~LuaMgr();

public:
	void				PreInit();
	void				Init();
	void				Start();
	void				Stop();
	void				CleanUp();

public:
	void				LoadLua(const char* src);
	void				LuaDoFile(const char* src);
private:
	lua_State*			L;
};

extern   LuaMgr  g_LuaMgr;

#ifndef  LUA_MGR
#define  LUA_MGR   g_LuaMgr
#endif

#endif
