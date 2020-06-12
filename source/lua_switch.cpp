#include "lua_switch.h"

void registerSwitch(lua_State* L)
{
    lua_register(L, "FatalThrow", lua_FatalThrow);
    lua_register(L, "EventWait", lua_EventWait);
    lua_register(L, "EventWaitMax", lua_EventWaitMax);
    lua_register(L, "EventClose", lua_EventClose);
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
        std::size_t len = std::snprintf(nullptr, 0, "Error waiting for event: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error waiting for event: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
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
        std::size_t len = std::snprintf(nullptr, 0, "Error waiting for event(max): %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error waiting for event(max): %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    return 0;
}

// Closes the event specified
int lua_EventClose(lua_State* L)
{
    Event* event = reinterpret_cast<Event *>(lua_touserdata(L, -1));

    eventClose(event);

    return 0;
}