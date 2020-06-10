#pragma once

#include <switch.h>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

void registerSVC(lua_State* L);

int lua_svc_SleepThread(lua_State* L);