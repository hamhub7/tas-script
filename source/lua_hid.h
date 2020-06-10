#pragma once

#include <switch.h>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

void registerHID(lua_State* L);

int lua_hid_ScanInput(lua_State* L);
int lua_hid_KeyboardDown(lua_State* L);