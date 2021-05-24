#include "lua_hid.hpp"

static keyPad keyboard;

// Scans input
void lua_hid_ScanInput()
{
    keyboard.update();

    return;
}

// Takes a keycode (can be found in hid.h) and returns (boolean) if that key was pressed down
bool lua_hid_KeyboardDown(HidKeyboardKey key)
{
    return keyboard.keyDown(key);
}

void registerHID(sol::state &lua)
{
    lua.set_function("hid_ScanInput", lua_hid_ScanInput);
    lua.set_function("hid_KeyboardDown", lua_hid_KeyboardDown);
}
