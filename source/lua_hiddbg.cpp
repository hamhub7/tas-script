#include "lua_hiddbg.hpp"

// Returns a pro controller connected using bluetooth, accepting arguments for the bodyColor then buttonsColor then gripLColor then gripRcolor
Controller lua_hiddbg_AttachController(u32 bodyColor, u32 buttonsColor, u32 gripLColor, u32 gripRColor)
{
    HiddbgHdlsDeviceInfo device = {0};
    device.deviceType = HidDeviceType_FullKey3;
    device.npadInterfaceType = HidNpadInterfaceType_Bluetooth;
    device.singleColorBody = bodyColor;
    device.singleColorButtons = buttonsColor;
    device.colorLeftGrip = gripLColor;
    device.colorRightGrip = gripRColor;

    Controller controller = {0};

    Result rc = hiddbgAttachHdlsVirtualDevice(&controller.handle, &device);
    if (R_FAILED(rc))
    {
        throw string_format("Error attaching controller: %#x", rc);
    }

    controller.state.battery_level = 4;

    rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if (R_FAILED(rc))
    {
        throw string_format("Error setting controller state: %#x", rc);
    }

    return controller;
}

// Takes a controller userdata and detaches it
void lua_hiddbg_DetachController(Controller *controller)
{
    Result rc = hiddbgDetachHdlsVirtualDevice(controller->handle);
    if (R_FAILED(rc))
    {
        throw string_format("Error disconnecting controller: %#x", rc);
    }

    return;
}

// Takes a controller userdata and returns whether the handle is connected
bool lua_hiddbg_IsControllerAttached(Controller *controller)
{
    bool isAttached;

    Result rc = hiddbgIsHdlsVirtualDeviceAttached(controller->handle, &isAttached);
    if (R_FAILED(rc))
    {
        throw string_format("Error checking if controller attached: %#x", rc);
    }

    return isAttached;
}

// Takes a controller userdata then a button field and updates the buttons
void lua_hiddbg_SetButtons(Controller *controller, u64 buttons)
{
    controller->state.buttons = buttons;

    Result rc = hiddbgSetHdlsState(controller->handle, &controller->state);
    if (R_FAILED(rc))
    {
        throw string_format("Error setting button state: %#x", rc);
    }

    return;
}

// Takes a controller userdata then a joystick index then an x position and y position and updates the joystick in question
void lua_hiddbg_SetJoystick(Controller *controller, int stickIndex, s32 x, s32 y)
{
    HidAnalogStickState *stick = nullptr;
    if (stickIndex == 1)
    {
        stick = &controller->state.analog_stick_l;
    }
    else if (stickIndex == 2)
    {
        stick = &controller->state.analog_stick_r;
    }
    else
    {
        throw "Invalid joystick specified";
    }

    stick->x = x;
    stick->y = y;

    Result rc = hiddbgSetHdlsState(controller->handle, &controller->state);
    if (R_FAILED(rc))
    {
        throw string_format("Error setting joystick state: %#x", rc);
    }

    return;
}

void registerHIDDBG(sol::state &lua)
{
    lua.set_function("hiddbg_AttachController", lua_hiddbg_AttachController);
    lua.set_function("hiddbg_DetachController", lua_hiddbg_DetachController);
    lua.set_function("hiddbg_IsControllerAttached", lua_hiddbg_IsControllerAttached);
    lua.set_function("hiddbg_SetButtons", lua_hiddbg_SetButtons);
    lua.set_function("hiddbg_SetJoystick", lua_hiddbg_SetJoystick);
}
