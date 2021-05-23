// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ostream>
#include <fstream>
#include <string>

// Include the main libnx system header, for Switch development
#include <switch.h>

#include <sol/sol.hpp>

// Include headers from other parts of the program
#include "lua_switch.hpp"
#include "lua_svc.hpp"
#include "lua_hid.hpp"
#include "lua_hiddbg.hpp"
#include "lua_vi.hpp"

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

    rc = ldrDmntInitialize();
    if(R_FAILED(rc))
        fatalThrow(rc);

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

    rc = pmdmntInitialize();
    if(R_FAILED(rc))
        fatalThrow(rc);

    // Attach Work Buffer
    rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalThrow(rc);

    hidInitializeKeyboard();
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void)
{
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

std::string logpath = "sdmc:/test.log";

// Outputs to sdmc/test.log
void logToSd(std::string message)
{
    std::ofstream ofs;
    ofs.open(logpath, std::ofstream::out | std::ofstream::app);
    if(ofs.is_open())
    {
        ofs << message << std::endl;
    }
    ofs.close();
}

// ---------- LUA UTILITY FUNCTIONS ---------

// Sets up logging
void lua_SetupLog(std::string logpath)
{
    std::ofstream ofs;
    ofs.open(logpath, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    return;
}

// Logs a message to the sd card
void lua_Log(std::string msg)
{
    logToSd(msg);

    return;
}

void registerUtility(sol::state& lua)
{
    lua.set_function("SetupLog", lua_SetupLog);
    lua.set_function("Log", lua_Log);
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // Register Lua functions
    registerUtility(lua);
    registerSVC(lua);
    registerHID(lua);
    registerHIDDBG(lua);
    registerVI(lua);
    registerSwitch(lua);

    // Your code / main loop goes here.
    sol::protected_function_result result = lua.safe_script_file("sdmc:/script/boot.lua");
    if(!result.valid()) {
        sol::error err = result;
        logToSd(err.what());
    }

    return 0;
}