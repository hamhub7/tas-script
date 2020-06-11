#include "lua_vi.h"

void registerVI(lua_State* L)
{
    lua_register(L, "vi_OpenDefaultDisplay", lua_vi_OpenDefaultDisplay);
    lua_register(L, "vi_GetDisplayVsyncEvent", lua_vi_GetDisplayVsyncEvent);
}

// Opens the default display and returns it in table form
int lua_vi_OpenDefaultDisplay(lua_State* L)
{
    ViDisplay disp;
    Result rc = viOpenDefaultDisplay(&disp);
    if(R_FAILED(rc))
        fatalThrow(rc);
    
    lua_pushdisplay(L, disp);

    return 1;
}

// Takes a display and returns a vsync event from that display
int lua_vi_GetDisplayVsyncEvent(lua_State* L)
{
    Event vsync_event;

    ViDisplay disp = lua_todisplay(L);

    Result rc = viGetDisplayVsyncEvent(&disp, &vsync_event);
    if(R_FAILED(rc))
        fatalThrow(rc);

    lua_pushevent(L, vsync_event);

    return 1;
}

// Pushes a ViDisplay in table form to the top of the lua stack
void lua_pushdisplay(lua_State* L, ViDisplay disp)
{
    lua_createtable(L, 0, 3);

    lua_pushstring(L, "display_id");
    lua_pushinteger(L, disp.display_id);
    lua_settable(L, -3);

    lua_pushstring(L, "display_name");
    
        lua_pushstring(L, "data");

            lua_createtable(L, 40, 0);

            for(int i = 0; i < 40; i++)
            {
                lua_pushinteger(L, i);
                lua_pushinteger(L, disp.display_name.data[i]);
                lua_settable(L, -3);
            }

        lua_settable(L, -3);

    lua_settable(L, -3);

    lua_pushstring(L, "initialized");
    lua_pushboolean(L, disp.initialized);
    lua_settable(L, -3);
}

// Returns a ViDisplay from the top of the lua stack
ViDisplay lua_todisplay(lua_State* L)
{
    ViDisplay result = { 0 };

    lua_pushstring(L, "display_id");
    lua_gettable(L, -2);
    result.display_id = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "display_name");
    lua_gettable(L, -2);
    
        lua_pushstring(L, "data");
        lua_gettable(L, -2);
    
            for(int i = 0; i < 40; i++)
            {
                lua_pushinteger(L, i);
                lua_gettable(L, -2);
                result.display_name.data[i] = lua_tointeger(L, -1);
                lua_pop(L, 1);
            }

        lua_pop(L, 1);

    lua_pop(L, 1);

    lua_pushstring(L, "initialized");
    lua_gettable(L, -2);
    result.initialized = lua_toboolean(L, -1);
    lua_pop(L, 1);
}

// Pushes an Event table to the top of the lua stack
void lua_pushevent(lua_State *L, Event event)
{
    lua_createtable(L, 0, 3);

    lua_pushstring(L, "revent");
    lua_pushinteger(L, event.revent);
    lua_settable(L, -3);

    lua_pushstring(L, "wevent");
    lua_pushinteger(L, event.wevent);
    lua_settable(L, -3);

    lua_pushstring(L, "autoclear");
    lua_pushboolean(L, event.autoclear);
    lua_settable(L, -3);
}