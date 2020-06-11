#pragma once

#include <switch.h>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

void registerVI(lua_State* L);
void lua_pushdisplay(lua_State* L, ViDisplay disp);
ViDisplay lua_todisplay(lua_State* L);
void lua_pushevent(lua_State *L, Event event);

int lua_vi_OpenDefaultDisplay(lua_State* L);
int lua_vi_GetDisplayVsyncEvent(lua_State* L);