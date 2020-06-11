#include "lua_switch.h"

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

    Event event = lua_toevent(L);

    Result rc = eventWait(&event, timeout);
    if(R_FAILED(rc))
        fatalThrow(rc);

    return 0;
}

// Takes an event and waits for it for the maximum timeout
int lua_EventWaitMax(lua_State* L)
{
    Event event = lua_toevent(L);

    Result rc = eventWait(&event, UINT64_MAX);
    if(R_FAILED(rc))
        fatalThrow(rc);

    return 0;
}

// Returns an Event from the top of the lua stack
Event lua_toevent(lua_State* L)
{
    Event result = { 0 };

    lua_pushstring(L, "revent");
    lua_gettable(L, -2);
    result.revent = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "wevent");
    lua_gettable(L, -2);
    result.wevent = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "autoclear");
    lua_gettable(L, -2);
    result.autoclear = lua_toboolean(L, -1);
    lua_pop(L, 1);

    return result;
}