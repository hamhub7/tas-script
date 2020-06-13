#include "lua_svc.hpp"
#include <fstream>

void registerSVC(lua_State* L)
{
    lua_register(L, "svc_SleepThread", lua_svc_SleepThread);
    lua_register(L, "svc_ReadMemory", lua_svc_ReadMemory);
    lua_register(L, "svc_GetMainAddr", lua_svc_GetMainAddr);
}

// Takes an integer number of nanoseconds to sleep
int lua_svc_SleepThread(lua_State* L)
{
    int nanoseconds = lua_tointeger(L, -1);
    svcSleepThread(nanoseconds);

    return 0;
}

// Takes a 2 arguments, first a main address, then an array of offsets. This function will grab the value at [[[main address + offset 1] + offset 2] + offset 3] etc...
int lua_svc_ReadMemory(lua_State* L)
{
    std::vector<u64> offsets;
    if(!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2))
        {
            offsets.push_back((u64)lua_tonumber(L, -1));
            lua_pop(L, 1);

            std::ofstream ofs;
            ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
            if(ofs.is_open())
            {
                ofs << "offset " << offsets.back() << std::endl;
            }
            ofs.close();
        }
    }
    else
    {
        std::ofstream ofs;
        ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
        if(ofs.is_open())
        {
            ofs << "nil offsets" << std::endl;
        }
        ofs.close();
    }
    
    u64 size = lua_tointeger(L, -2);
    std::ofstream ofs;
    ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
    if(ofs.is_open())
    {
        ofs << "size " << size << std::endl;
    }
    ofs.close();

    u64 mainAddr = lua_tointeger(L, -3);
    ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
    if(ofs.is_open())
    {
        ofs << "main " << mainAddr << std::endl;
    }
    ofs.close();

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
    for(u64 i = 0; i < offsets.size(); i++)
    {
        std::ofstream ofs;
        ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
        if(ofs.is_open())
        {
            ofs << "offset " << offsets[i] << " back " << offsets.back() << std::endl;
        }
        ofs.close();

        u64 readSize = 0x8; // Size of an address
        if(&offsets[i] == &offsets.back())
        {
            std::ofstream ofs;
            ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
            if(ofs.is_open())
            {
                ofs << "in there pogchammo " << size << std::endl;
            }
            ofs.close();

            readSize = size;
        }

        ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
        if(ofs.is_open())
        {
            ofs << "reading " << current + offsets[i] << std::endl;
        }
        ofs.close();

        u64 buffer;
        rc = svcReadDebugProcessMemory(&buffer, debugHandle, current + offsets[i], readSize);
        if(R_FAILED(rc))
        {
            std::size_t len = std::snprintf(nullptr, 0, "Error reading memory addr %#lx: %#x",current, rc);
            char error[len+1];
            std::sprintf(error, "Error reading memory addr %#lx: %#x",current, rc);
            lua_pushstring(L, error);
            lua_error(L);
        }

        ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
        if(ofs.is_open())
        {
            ofs << "read " << buffer << std::endl;
        }
        ofs.close();

        current = buffer;
    }

    rc = svcCloseHandle(debugHandle);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error closing debug handle: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error closing debug handle: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    lua_pushinteger(L, current);

    return 1;
}

// Returns the main address of the currently active process
int lua_svc_GetMainAddr(lua_State* L)
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

    LoaderModuleInfo procModules[2];
    s32 numModules = 0;
    rc = ldrDmntGetProcessModuleInfo(pid, procModules, 2, &numModules);
    if(R_FAILED(rc))
    {
        std::size_t len = std::snprintf(nullptr, 0, "Error getting process module info: %#x", rc);
        char error[len+1];
        std::sprintf(error, "Error getting process module info: %#x", rc);
        lua_pushstring(L, error);
        lua_error(L);
    }

    if(numModules == 2)
    {
        lua_pushinteger(L, procModules[1].base_address);
    }
    else
    {
        lua_pushinteger(L, procModules[0].base_address);
    }

    return 1;
}