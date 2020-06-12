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
    if hid_KeyboardDown(hid.KeyboardScancode.Equals) and not hiddbg_IsControllerAttached(controller) then --EQUALS
        controller = hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor)

    elseif hid_KeyboardDown(hid.KeyboardScancode.Minus) and hiddbg_IsControllerAttached(controller) then --MINUS
        hiddbg_DetachController(controller)

    elseif hid_KeyboardDown(hid.KeyboardScancode.F1) and hiddbg_IsControllerAttached(controller) then --F1
        local good, err = pcall(tas.runTas, root .."script1." .. fileext, controller)
        if not good then
            Log("Error occured (script1): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F2) and hiddbg_IsControllerAttached(controller) then --F2
        local good, err = pcall(tas.runTas, root .."script2." .. fileext, controller)
        if not good then
            Log("Error occured (script2): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F3) and hiddbg_IsControllerAttached(controller) then --F3
        local good, err = pcall(tas.runTas, root .."script3." .. fileext, controller)
        if not good then
            Log("Error occured (script3): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F4) and hiddbg_IsControllerAttached(controller) then --F4
        local good, err = pcall(tas.runTas, root .."script4." .. fileext, controller)
        if not good then
            Log("Error occured (script4): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F5) and hiddbg_IsControllerAttached(controller) then --F5
        local good, err = pcall(tas.runTas, root .."script5." .. fileext, controller)
        if not good then
            Log("Error occured (script5): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F6) and hiddbg_IsControllerAttached(controller) then --F6
        local good, err = pcall(tas.runTas, root .."script6." .. fileext, controller)
        if not good then
            Log("Error occured (script6): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F7) and hiddbg_IsControllerAttached(controller) then --F7
        local good, err = pcall(tas.runTas, root .."script7." .. fileext, controller)
        if not good then
            Log("Error occured (script7): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F8) and hiddbg_IsControllerAttached(controller) then --F8
        local good, err = pcall(tas.runTas, root .."script8." .. fileext, controller)
        if not good then
            Log("Error occured (script8): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F9) and hiddbg_IsControllerAttached(controller) then --F9
        local good, err = pcall(tas.runTas, root .."script9." .. fileext, controller)
        if not good then
            Log("Error occured (script9): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F10) and hiddbg_IsControllerAttached(controller) then --F10
        local good, err = pcall(tas.runTas, root .."script10." .. fileext, controller)
        if not good then
            Log("Error occured (script10): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F11) and hiddbg_IsControllerAttached(controller) then --F11
        local good, err = pcall(tas.runTas, root .."script11." .. fileext, controller)
        if not good then
            Log("Error occured (script11): " .. err)
        end

    elseif hid_KeyboardDown(hid.KeyboardScancode.F12) and hiddbg_IsControllerAttached(controller) then -- F12
        local good, err = pcall(tas.runTas, root .."script12." .. fileext, controller)
        if not good then
            Log("Error occured (script12): " .. err)
        end

    end
    svc_SleepThread(6250000)
end