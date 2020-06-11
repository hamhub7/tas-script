#include "lua_hiddbg.h"

void registerHIDDBG(lua_State* L)
{
    lua_register(L, "hiddbg_AttachController", lua_hiddbg_AttachController);
    lua_register(L, "hiddbg_DetachController", lua_hiddbg_DetachController);
    lua_register(L, "hiddbg_SetButtons", lua_hiddbg_SetButtons);
    lua_register(L, "hiddbg_SetJoystick", lua_hiddbg_SetJoystick);
    lua_register(L, "hiddbg_SetState", lua_hiddbg_SetState);
}

// Returns a pro controller connected using bluetooth
int lua_hiddbg_AttachController(lua_State* L)
{
    HiddbgHdlsDeviceInfo device = { 0 };
    device.deviceType = HidDeviceType_FullKey3;
    device.npadInterfaceType = NpadInterfaceType_Bluetooth;
    device.singleColorBody = RGBA8_MAXALPHA(0, 0, 0);
    device.singleColorButtons = RGBA8_MAXALPHA(255, 255, 255);
    device.colorLeftGrip = RGBA8_MAXALPHA(255, 255, 255);
    device.colorRightGrip = RGBA8_MAXALPHA(255, 255, 255);

    Controller controller = { 0 };
    Result rc = hiddbgAttachHdlsVirtualDevice(&controller.handle, &device);
    if (R_FAILED(rc))
        fatalThrow(rc);

    controller.state.batteryCharge = 4;

    rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    lua_pushcontroller(L, controller);

    return 1;
}

// Takes a controller table and detaches it
int lua_hiddbg_DetachController(lua_State* L)
{
    Controller controller = lua_tocontroller(L);

    Result rc = hiddbgDetachHdlsVirtualDevice(controller.handle);
    if (R_FAILED(rc))
        fatalThrow(rc);

    return 0;
}

// Takes a controller table then a button field and updates the buttons (returns the controller)
int lua_hiddbg_SetButtons(lua_State* L)
{
    u64 buttons = lua_tointeger(L, -1);

    Controller controller = lua_tocontroller(L);

    controller.state.buttons = buttons;

    Result rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    lua_pushcontroller(L, controller);

    return 1;
}

// Takes a controller table then a joystick index then an x position and y position and updates the joystick in question (returns the controller)
int lua_hiddbg_SetJoystick(lua_State* L)
{
    s32 y = lua_tointeger(L, -1);
    s32 x = lua_tointeger(L, -1);

    int index = lua_tointeger(L, -1);

    Controller controller = lua_tocontroller(L);

    controller.state.joysticks[index].dx = x;
    controller.state.joysticks[index].dy = y;

    Result rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    lua_pushcontroller(L, controller);

    return 1;
}

// Takes a controller table and sets the state according to the controller's state. this means the controller must be edited in lua itself (this is not the preferred way of doing things, but it may be useful)
int lua_hiddbg_SetState(lua_State* L)
{
    Controller controller = lua_tocontroller(L);

    Result rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    lua_pushcontroller(L, controller);

    return 1;
}

// Utility for pushing a controller to the top of the stack
void lua_pushcontroller(lua_State* L, Controller controller)
{
    lua_createtable(L, 0, 2);

    lua_pushstring(L, "handle");
    lua_pushinteger(L, controller.handle);
    lua_settable(L, -3);

    lua_pushstring(L, "state");
    
        lua_createtable(L, 0, 6);

        lua_pushstring(L, "batteryCharge");
        lua_pushinteger(L, controller.state.batteryCharge);
        lua_settable(L, -3);

        lua_pushstring(L, "flags");
        lua_pushinteger(L, controller.state.flags);
        lua_settable(L, -3);

        lua_pushstring(L, "buttons");
        lua_pushinteger(L, controller.state.buttons);
        lua_settable(L, -3);

        lua_pushstring(L, "joysticks");

            lua_createtable(L, 2, 0);

            lua_pushinteger(L, 0);
            
                lua_createtable(L, 0, 2);

                lua_pushstring(L, "dx");
                lua_pushinteger(L, controller.state.joysticks[0].dx);
                lua_settable(L, -3);

                lua_pushstring(L, "dy");
                lua_pushinteger(L, controller.state.joysticks[0].dy);
                lua_settable(L, -3);

            lua_settable(L, -3);

            lua_pushinteger(L, 1);
            
                lua_createtable(L, 0, 2);

                lua_pushstring(L, "dx");
                lua_pushinteger(L, controller.state.joysticks[1].dx);
                lua_settable(L, -3);

                lua_pushstring(L, "dy");
                lua_pushinteger(L, controller.state.joysticks[1].dy);
                lua_settable(L, -3);

            lua_settable(L, -3);

        lua_settable(L, -3);

        lua_pushstring(L, "unk_x20");
        lua_pushinteger(L, controller.state.unk_x20);
        lua_settable(L, -3);

    lua_settable(L, -3);
}

// Utility for grabbing a controller from the top of the stack
Controller lua_tocontroller(lua_State* L)
{
    Controller result = { 0 };

    lua_pushstring(L, "handle");
    lua_gettable(L, -2);
    result.handle = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "state");
    lua_gettable(L, -2);
    
        lua_pushstring(L, "batteryCharge");
        lua_gettable(L, -2);
        result.state.batteryCharge = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "flags");
        lua_gettable(L, -2);
        result.state.flags = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "buttons");
        lua_gettable(L, -2);
        result.state.buttons = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "joysticks");
        lua_gettable(L, -2);
        
            lua_pushinteger(L, 0);
            lua_gettable(L, -2);
            
                lua_pushstring(L, "dx");
                lua_gettable(L, -2);
                result.state.joysticks[0].dx = lua_tointeger(L, -1);
                lua_pop(L, 1);

                lua_pushstring(L, "dy");
                lua_gettable(L, -2);
                result.state.joysticks[0].dy = lua_tointeger(L, -1);
                lua_pop(L, 1);

            lua_pop(L, 1);

            lua_pushinteger(L, 1);
            lua_gettable(L, -2);
            
                lua_pushstring(L, "dx");
                lua_gettable(L, -2);
                result.state.joysticks[1].dx = lua_tointeger(L, -1);
                lua_pop(L, 1);

                lua_pushstring(L, "dy");
                lua_gettable(L, -2);
                result.state.joysticks[1].dy = lua_tointeger(L, -1);
                lua_pop(L, 1);

            lua_pop(L, 1);

        lua_pop(L, 1);

        lua_pushstring(L, "unk_x20");
        lua_gettable(L, -2);
        result.state.unk_x20 = lua_tointeger(L, -1);
        lua_pop(L, 1);

    lua_pop(L, 1);

    return result;
}