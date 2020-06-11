#include "lua_switch.h"
#include <fstream>

void registerSwitch(lua_State* L)
{
    lua_register(L, "FatalThrow", lua_FatalThrow);
    lua_register(L, "EventWait", lua_EventWait);
    lua_register(L, "EventWaitMax", lua_EventWaitMax);
}

// Throws a fatal with a custom error code
int lua_FatalThrow(lua_State* L)
{
    u32 errorCode = lua_tointeger(L, -1);
    fatalThrow(errorCode);

    return 0;
}

// Takes an event and a timeout and waits for it for the specific timeout
int lua_EventWait(lua_State* L)
{
    u64 timeout = lua_tointeger(L, -1);

    Event* event = reinterpret_cast<Event *>(lua_touserdata(L, -1));

    Result rc = eventWait(event, timeout);
    if(R_FAILED(rc))
    {
        fatalThrow(rc);
    }

    return 0;
}

// Takes an event and waits for it for the maximum timeout
int lua_EventWaitMax(lua_State* L)
{
    Event* event = reinterpret_cast<Event *>(lua_touserdata(L, -1));

    Result rc = eventWait(event, UINT64_MAX);
    if(R_FAILED(rc))
    {
        fatalThrow(rc);
    }

    return 0;
}