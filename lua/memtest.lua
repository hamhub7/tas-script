hid = require "sys/hidenum"

local mainAddr = 0x00
local offsets = {
    0x6E98F8,
    0x350,
    0x90,
    0x154
}
local size = 0x4

while true do
    hid_ScanInput()

    if hid_KeyboardDown(hid.KeyboardKey.F1) then
        local value = svc_ReadMemory(mainAddr, offsets, size)
        Log(value)
    end

    if hid_KeyboardDown(hid.KeyboardKey.F2) then
        mainAddr = svc_GetMainAddr()
        Log(mainAddr)
    end

    if hid_KeyboardDown(hid.KeyboardKey.F3) then
        mainAddr = svc_GetMainAddr()
        Log(mainAddr)
        local value = svc_ReadMemory(mainAddr, offsets, size)
        Log(value)
    end

    svc_SleepThread(6250000)
end