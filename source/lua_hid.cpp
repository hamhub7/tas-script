#include "lua_hid.hpp"

// Scans input
void lua_hid_ScanInput()
{
    hidScanInput();

    return;
}

// Takes a keycode (can be found in hid.h) and returns (boolean) if that key was pressed down
bool lua_hid_KeyboardDown(HidKeyboardScancode key)
{
    return hidKeyboardDown(key);
}

// Takes a keycode and returns if that mouse buttons was pressed down
bool lua_hid_MouseDown(HidMouseButton key)
{
    return hidMouseButtonsDown() & key;
}

void registerHID(sol::state& lua)
{
    lua.set_function("hid_ScanInput", lua_hid_ScanInput);
    lua.set_function("hid_KeyboardDown", lua_hid_KeyboardDown);
    lua.set_function("hid_MouseDown", lua_hid_MouseDown);
}
