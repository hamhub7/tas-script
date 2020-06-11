#include "lua_hid.h"

void registerHID(lua_State* L)
{
    lua_register(L, "hid_ScanInput", lua_hid_ScanInput);
    lua_register(L, "hid_KeyboardDown", lua_hid_KeyboardDown);
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