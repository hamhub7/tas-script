#pragma once

#pragma once

#include <switch.h>
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
void lua_pushcontroller(lua_State* L, Controller controller);
Controller lua_tocontroller(lua_State* L);

int lua_hiddbg_AttachController(lua_State* L);
int lua_hiddbg_DetachController(lua_State* L);
int lua_hiddbg_SetButtons(lua_State* L);
int lua_hiddbg_SetJoytick(lua_State* L);
int lua_hiddbg_SetState(lua_State* L);