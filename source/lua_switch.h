#pragma once

#include <switch.h>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

void registerSwitch(lua_State* L);
Event lua_toevent(lua_State* L);

int lua_FatalThrow(lua_State* L);
int lua_EventWait(lua_State* L);
int lua_EventWaitMax(lua_State* L);