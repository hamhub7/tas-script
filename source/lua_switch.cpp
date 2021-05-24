#include "lua_switch.hpp"

// Throws a fatal with a custom error code
void lua_FatalThrow(u32 errorCode)
{
    fatalThrow(errorCode);

    return;
}

// Takes an event and a timeout and waits for it for the specific timeout
void lua_EventWait(Event *event, u64 timeout)
{
    Result rc = eventWait(event, timeout);
    if (R_FAILED(rc))
    {
        throw string_format("Error waiting for event: %#x", rc);
    }

    return;
}

// Takes an event and waits for it for the maximum timeout
void lua_EventWaitMax(Event *event)
{
    Result rc = eventWait(event, UINT64_MAX);
    if (R_FAILED(rc))
    {
        throw string_format("Error waiting for event(max): %#x", rc);
    }

    return;
}

// Closes the event specified
void lua_EventClose(Event *event)
{
    eventClose(event);

    return;
}

void registerSwitch(sol::state &lua)
{
    lua.set_function("FatalThrow", lua_FatalThrow);
    lua.set_function("EventWait", lua_EventWait);
    lua.set_function("EventWaitMax", lua_EventWaitMax);
    lua.set_function("EventClose", lua_EventClose);
}
