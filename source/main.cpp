// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ostream>
#include <fstream>
#include <string>

// Include the main libnx system header, for Switch development
#include <switch.h>

extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

// Include headers from other parts of the program
#include "lua_switch.h"
#include "lua_svc.h"
#include "lua_hid.h"
#include "lua_hiddbg.h"
#include "lua_vi.h"

lua_State* L;

extern "C"
{
    // Sysmodules should not use applet*.
    u32 __nx_applet_type = AppletType_None;

    // Adjust size as needed.
    #define INNER_HEAP_SIZE 0x400000
    size_t nx_inner_heap_size = INNER_HEAP_SIZE;
    char   nx_inner_heap[INNER_HEAP_SIZE];

    void __libnx_init_time(void);
    void __libnx_initheap(void);
    void __appInit(void);
    void __appExit(void);
}

void __libnx_initheap(void)
{
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	// Newlib
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char*)addr;
	fake_heap_end   = (char*)addr + size;
}

// Init/exit services, update as needed.
void __attribute__((weak)) __appInit(void)
{
    Result rc;

    // Initialize default services.
    rc = smInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    rc = setsysInitialize();
    if (R_SUCCEEDED(rc)) {
        SetSysFirmwareVersion fw;
        rc = setsysGetFirmwareVersion(&fw);
        if (R_SUCCEEDED(rc))
            hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
        setsysExit();
    }


    // HID
    rc = hidInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_HID));

    // FileSystem
    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();

    // hiddbg (virtual controllers)
    rc = hiddbgInitialize();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // vsync
    rc = viInitialize(ViServiceType_System);
    if(R_FAILED(rc))
        fatalThrow(rc);

    // time
    rc = timeInitialize();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // Attach Work Buffer
    rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalThrow(rc);
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void)
{
    // Close VM
    lua_close(L);
    // Cleanup default services.
    hiddbgReleaseHdlsWorkBuffer();
    timeExit();
    viExit();
    hiddbgExit();
    fsdevUnmountAll();
    fsExit();
    hidExit();
    smExit();
}

// Outputs to sdmc/test.log
void logToSd(std::string message)
{
    std::ofstream ofs;
    ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::app);
    if(ofs.is_open())
    {
        ofs << message << std::endl;
    }
    ofs.close();
}

// ---------- LUA UTILITY FUNCTIONS ---------

// Logs a message to the sd card
int lua_Log(lua_State* L)
{
    std::string msg = lua_tostring(L, 1);
    logToSd(msg);

    return 0;
}

void registerUtility(lua_State* L)
{
    lua_register(L, "Log", lua_Log);
}

// Checks the current result and prints an error if it failed
bool checkLua(lua_State* L, int result)
{
    if(result != LUA_OK)
    {
        std::string errormsg = lua_tostring(L, -1);
        logToSd(errormsg);
        return false;
    }
    return true;
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    // Initialization code can go here.
    std::ofstream ofs;
    ofs.open("sdmc:/test.log", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // Open new Lua VM
    L = luaL_newstate();
    luaL_openlibs(L);

    // Register Lua functions
    registerUtility(L);
    registerSVC(L);
    registerHID(L);
    registerHIDDBG(L);
    registerVI(L);
    registerSwitch(L);

    // Your code / main loop goes here.
    checkLua(L, luaL_dofile(L, "sdmc:/script/boot.lua"));

    return 0;
}