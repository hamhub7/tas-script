#include "lua_hiddbg.h"
#include <fstream>

void registerHIDDBG(lua_State* L)
{
    lua_register(L, "hiddbg_AttachController", lua_hiddbg_AttachController);
    lua_register(L, "hiddbg_DetachController", lua_hiddbg_DetachController);
    lua_register(L, "hiddbg_SetButtons", lua_hiddbg_SetButtons);
    lua_register(L, "hiddbg_SetJoytick", lua_hiddbg_SetJoytick);
    lua_register(L, "hiddbg_SetState", lua_hiddbg_SetState);
}

// Returns a pro controller connect using bluetooth
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

int lua_hiddbg_DetachController(lua_State* L)
{
    u64 handle = lua_tointeger(L, -1);

    Result rc = hiddbgDetachHdlsVirtualDevice(handle);
    if (R_FAILED(rc))
        fatalThrow(rc);

    return 0;
}

// Takes a controller table then a button string and updates the buttons
int lua_hiddbg_SetButtons(lua_State* L)
{
    return 0;
}

int lua_hiddbg_SetJoytick(lua_State* L)
{
    return 0;
}

int lua_hiddbg_SetState(lua_State* L)
{
    Controller controller = lua_tocontroller(L);

    Result rc = hiddbgSetHdlsState(controller.handle, &controller.state);
    if(R_FAILED(rc))
        fatalThrow(rc);

    return 0;
}

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