#include "lua_switch.h"

void registerSwitch(lua_State* L)
{
    lua_register(L, "FatalThrow", lua_FatalThrow);
}

// Throws a fatal with a custom error code
int lua_FatalThrow(lua_State* L)
{
    u32 errorCode = lua_tointeger(L, -1);
    fatalThrow(errorCode);

    return 0;
}