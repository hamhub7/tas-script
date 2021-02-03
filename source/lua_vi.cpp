#include "lua_vi.hpp"

// Opens the default display and returns it in table form
ViDisplay lua_vi_OpenDefaultDisplay()
{
    ViDisplay disp;

    Result rc = viOpenDefaultDisplay(&disp);
    if(R_FAILED(rc))
    {
        throw string_format("Error opening default display: %#x", rc);
    }

    return disp;
}

// Closes the display provided
void lua_vi_CloseDisplay(ViDisplay& disp)
{
    Result rc = viCloseDisplay(&disp);
    if(R_FAILED(rc))
    {
        throw string_format("Error closing display: %#x", rc);
    }

    return;
}

// Takes a display and returns a vsync event from that display
Event lua_vi_GetDisplayVsyncEvent(ViDisplay& disp)
{
    Event vsync_event;

    Result rc = viGetDisplayVsyncEvent(&disp, &vsync_event);
    if(R_FAILED(rc))
    {
        throw string_format("Error getting vsync event: %#x", rc);
    }

    return vsync_event;
}

void registerVI(sol::state& lua)
{
    lua.set_function("vi_OpenDefaultDisplay", lua_vi_OpenDefaultDisplay);
    lua.set_function("vi_CloseDisplay", lua_vi_CloseDisplay);
    lua.set_function("vi_GetDisplayVsyncEvent", lua_vi_GetDisplayVsyncEvent);
}
