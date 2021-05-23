#pragma once

#include <switch.h>
extern "C"
{
#include "lua535/lua.h"
#include "lua535/lauxlib.h"
#include "lua535/lualib.h"
}

class keyPad
{
private:
    HidKeyboardState currState = {0};
    HidKeyboardState oldState = {0};

public:
    void update();
    bool keyDown(HidKeyboardKey key);
};