tas = require "lib/nxtas"
colors = require "sys/colors"
hid = require "sys/hidenum"
local fileext = tas.fileext
local root = "sdmc:/scripts/"

local bodyColor = colors.rgb(43, 43, 43)
local buttonsColor = colors.rgb(0, 0, 0)
local gripLColor = colors.rgb(20, 184, 82)
local gripRColor = colors.rgb(249, 81, 139)

controller = nil
while true do
    hid_ScanInput()
    if hid_KeyboardDown(hid.KeyboardScancode.Equal) and not hiddbg_IsControllerAttached(controller) then --EQUALS
        controller = hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor)

    elseif hid_KeyboardDown(hid.KeyboardScancode.Minus) and hiddbg_IsControllerAttached(controller) then --MINUS
        hiddbg_DetachController(controller)

    elseif hid_KeyboardDown(hid.KeyboardScancode.F1) and hiddbg_IsControllerAttached(controller) then --F1
        hiddbg_ChangeControllerColor(controller, colors.rgb(255, 255, 255), colors.rgb(255, 255, 255))

    end
    svc_SleepThread(6250000)
end