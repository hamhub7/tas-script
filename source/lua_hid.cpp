#include "lua_hid.h"

void registerHID(lua_State* L)
{
    lua_register(L, "hid_ScanInput", lua_hid_ScanInput);
    lua_register(L, "hid_KeyboardDown", lua_hid_KeyboardDown);
    lua_register(L, "hid_MouseDown", lua_hid_MouseDown);
}

// Scans input
int lua_hid_ScanInput(lua_State* L)
{
    hidScanInput();

    return 0;
}

// Takes a keycode (can be found in hid.h) and returns (boolean) if that key was pressed down
int lua_hid_KeyboardDown(lua_State* L)
{
    HidKeyboardScancode key = (HidKeyboardScancode)lua_tointeger(L, -1);
    bool isDown = hidKeyboardDown(key);
    lua_pushboolean(L, isDown);

    return 1;
}

// Takes a keycode and returns if that mouse buttons was pressed down
int lua_hid_MouseDown(lua_State* L)
{
    HidMouseButton key = (HidMouseButton)lua_tointeger(L, -1);
    u64 mDown = hidMouseButtonsDown();
    lua_pushboolean(L, mDown & key);

    return 1;
}