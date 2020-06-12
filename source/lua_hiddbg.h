#pragma once

#include <switch.h>
#include <cstring>
#include <string>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

typedef struct
{
    u64 handle;
    HiddbgHdlsState state;
} Controller;

void registerHIDDBG(lua_State* L);

int lua_hiddbg_AttachController(lua_State* L);
int lua_hiddbg_DetachController(lua_State* L);
int lua_hiddbg_IsControllerAttached(lua_State* L);
int lua_hiddbg_SetButtons(lua_State* L);
int lua_hiddbg_SetJoystick(lua_State* L);