#pragma once

#include <switch.h>

class keyPad
{
private:
    HidKeyboardState currState = {0};
    HidKeyboardState oldState = {0};

public:
    void update();
    bool keyDown(HidKeyboardKey key);
};