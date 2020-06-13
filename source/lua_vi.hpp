#pragma once

#include <switch.h>
#include <string>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

void registerVI(lua_State* L);

int lua_vi_OpenDefaultDisplay(lua_State* L);
int lua_vi_CloseDisplay(lua_State* L);
int lua_vi_GetDisplayVsyncEvent(lua_State* L);