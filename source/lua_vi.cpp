#include "lua_vi.h"
#include <fstream>

void registerVI(lua_State* L)
{
    lua_register(L, "vi_OpenDefaultDisplay", lua_vi_OpenDefaultDisplay);
    lua_register(L, "vi_CloseDisplay", lua_vi_CloseDisplay);
    lua_register(L, "vi_GetDisplayVsyncEvent", lua_vi_GetDisplayVsyncEvent);
}

// Opens the default display and returns it in table form
int lua_vi_OpenDefaultDisplay(lua_State* L)
{
    ViDisplay* disp = reinterpret_cast<ViDisplay *>(lua_newuserdata(L, sizeof(ViDisplay)));

    Result rc = viOpenDefaultDisplay(disp);
    if(R_FAILED(rc))
    {
        fatalThrow(rc);
    }

    return 1;
}

// Closes the display provided
int lua_vi_CloseDisplay(lua_State* L)
{
    ViDisplay* disp = reinterpret_cast<ViDisplay *>(lua_touserdata(L, -1));

    Result rc = viCloseDisplay(disp);
    if(R_FAILED(rc))
    {
        fatalThrow(rc);
    }

    return 1;
}

// Takes a display and returns a vsync event from that display
int lua_vi_GetDisplayVsyncEvent(lua_State* L)
{
    ViDisplay* disp = reinterpret_cast<ViDisplay *>(lua_touserdata(L, -1));

    Event* vsync_event = reinterpret_cast<Event *>(lua_newuserdata(L, sizeof(Event)));

    Result rc = viGetDisplayVsyncEvent(disp, vsync_event);
    if(R_FAILED(rc))
    {
        fatalThrow(rc);
    }

    return 1;
}