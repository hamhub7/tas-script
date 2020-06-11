#include "lua_svc.h"

void registerSVC(lua_State* L)
{
    lua_register(L, "svc_SleepThread", lua_svc_SleepThread);
}

// Takes an integer number of nanoseconds to sleep
int lua_svc_SleepThread(lua_State* L)
{
    int nanoseconds = lua_tointeger(L, -1);
    svcSleepThread(nanoseconds);

    return 0;
}