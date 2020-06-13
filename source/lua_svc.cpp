#include "lua_svc.hpp"

void registerSVC(lua_State* L)
{
    lua_register(L, "svc_SleepThread", lua_svc_SleepThread);
    lua_register(L, "svc_ReadMemory", lua_svc_ReadMemory);
}

// Takes an integer number of nanoseconds to sleep
int lua_svc_SleepThread(lua_State* L)
{
    int nanoseconds = lua_tointeger(L, -1);
    svcSleepThread(nanoseconds);

    return 0;
}

// Takes a 2 arguments, first a main address, then an array of offsets. This function will grab the value at the main address, then 
int lua_svc_ReadMemory(lua_State* L)
{
    size_t numOffsets = lua_rawlen(L, -1);

    u64 offsets[numOffsets];
    for(int i = 0; i < numOffsets; i++)
    {
        lua_pushinteger(L, i+1);
        lua_gettable(L, -2);
        offsets[i] = lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

    u64 mainAddr = lua_tointeger(L, -2);

    u64 pid;
    Result rc = pmdmntGetApplicationProcessId(&pid);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error getting process id: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error getting process id: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    Handle debugHandle;
    rc = svcDebugActiveProcess(&debugHandle, pid);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error debugging process: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error debugging process: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    u64 current = mainAddr;
    for(int i = 0; i < numOffsets; i++)
    {
        u64 buffer;
        rc = svcReadDebugProcessMemory(&buffer, debugHandle, current + offsets[i], 0x1);
        if(R_FAILED(rc))
        {
            std::size_t len = std::snprintf(nullptr, 0, "Error reading memory addr %#x: %#x",current, rc);
            char error[len+1];
            std::sprintf(error, "Error reading memory addr %#x: %#x",current, rc);
            lua_pushstring(L, error);
            lua_error(L);
        }

        current = buffer;
    }

    rc = svcTerminateDebugProcess(debugHandle);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error terminating debug process: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error terminating debug process: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    lua_pushinteger(L, current);

    return 1;
}