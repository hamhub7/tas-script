#include "lua_hid.h"

void registerHID(lua_State* L)
{
    lua_register(L, "hid_ScanInput", lua_hid_ScanInput);
    lua_register(L, "hid_KeyboardDown", lua_hid_KeyboardDown);
}

int lua_hid_ScanInput(lua_State* L)
{
    hidScanInput();

    return 0;
}

int lua_hid_KeyboardDown(lua_State* L)
{
    HidKeyboardScancode key = (HidKeyboardScancode)lua_tointeger(L, -1);
    bool isDown = hidKeyboardDown(key);
    lua_pushboolean(L, isDown);

    return 1;
}