#include "lua_svc.hpp"

// Takes an integer number of nanoseconds to sleep
void lua_svc_SleepThread(s64 nanoseconds)
{
    svcSleepThread(nanoseconds);

    return;
}

// Takes a 2 arguments, first a main address, then an array of offsets, then a final size. This function will grab the value at [[[main address + offset 1] + offset 2] + offset 3] etc... with the size specified for the final value
std::vector<u8> lua_svc_ReadMemory(uintptr_t mainAddr, std::vector<size_t> offsets, size_t size)
{
    u64 pid;
    Result rc = pmdmntGetApplicationProcessId(&pid);
    if(R_FAILED(rc))
    {
        throw string_format("Error getting process id: %#x", rc);
    }

    Handle debugHandle;
    rc = svcDebugActiveProcess(&debugHandle, pid);
    if(R_FAILED(rc))
    {
        throw string_format("Error debugging process: %#x", rc);
    }

    uintptr_t current = mainAddr;
    for(size_t i = 0; i < offsets.size() - 1; i++)
    {
        u64 readSize = sizeof(uintptr_t); // Size of an address

        rc = svcReadDebugProcessMemory(&current, debugHandle, current + offsets[i], readSize);
        if(R_FAILED(rc))
        {
            throw string_format("Error reading memory addr %#lx: %#x", current, rc); 
        }
    }

    u8 buffer[size];
    rc = svcReadDebugProcessMemory(buffer, debugHandle, current + offsets.back(), size);
    if(R_FAILED(rc))
    {
        throw string_format("Error reading memory addr %#lx: %#x", current, rc); 
    }

    rc = svcCloseHandle(debugHandle);
    if(R_FAILED(rc))
    {
        throw string_format("Error closing debug handle: %#x", rc);
    }

    std::vector<u8> result(buffer, buffer + size);
    return result;
}

// Returns some userdata in the form of a hooked address that can be used to read process memory using another command
int lua_svc_MapProcessMemory(lua_State* L)
{
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

    Handle processHandle;
    NcmProgramLocation location;
    CfgOverrideStatus status;

    rc = pmdmntAtmosphereGetProcessInfo(&processHandle, &location, &status, pid);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error getting process info: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error getting process info: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    void* bruh = nullptr;
    rc = svcMapProcessMemory(bruh, processHandle, 0, 0);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error mapping process memory: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error mapping process memory: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    return 0;
}

// Returns the main address of the currently active process
u64 lua_svc_GetMainAddr()
{
    u64 pid;
    Result rc = pmdmntGetApplicationProcessId(&pid);
    if(R_FAILED(rc))
    {
        string_format("Error getting process id: %#x", rc);
    }

    LoaderModuleInfo procModules[2];
    s32 numModules = 0;
    rc = ldrDmntGetProcessModuleInfo(pid, procModules, 2, &numModules);
    if(R_FAILED(rc))
    {
        throw string_format("Error getting process module info: %#x", rc);
    }

    if(numModules == 2)
    {
        return procModules[1].base_address;
    }
    else
    {
        return procModules[0].base_address;
    }
}

void registerSVC(sol::state& lua)
{
    lua.set_function("svc_SleepThread", lua_svc_SleepThread);
    lua.set_function("svc_ReadMemory", lua_svc_ReadMemory);
    lua.set_function("svc_GetMainAddr", lua_svc_GetMainAddr);
}
