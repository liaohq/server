#ifndef	_LUA_OTHER_H_
#define _LUA_OTHER_H_

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int luaopen_libmylua_other(lua_State* L);
int luaopen_libmylua_test(lua_State* L);

#ifdef	__cplusplus
}
#endif



#endif
