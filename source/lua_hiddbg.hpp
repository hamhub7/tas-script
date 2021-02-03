#pragma once

#include <switch.h>
#include <cstring>
#include <string>
#include <sol/sol.hpp>

#include "format.hpp"

typedef struct
{
    HiddbgHdlsHandle handle;
    HiddbgHdlsState state;
} Controller;

void registerHIDDBG(sol::state& lua);
