tas = require "lib/nxtas" --Edit this to change the scripting language used
colors = require "sys/colors"
hid = require "sys/hidenum"
local fileext = tas.fileext
local root = "sdmc:/scripts/"

local bodyColor = colors.rgb(43, 43, 43)
local buttonsColor = colors.rgb(0, 0, 0)
local gripLColor = colors.rgb(20, 184, 82)
local gripRColor = colors.rgb(249, 81, 139)

function runScript(script, controller)
    local good, err = pcall(tas.runTas, root .. script .. "." .. fileext, controller)
    if not good then
        Log("Error occured (" .. script .. "): " .. err)
    end
end

function runMultiplayerScript(script, controllers)
    local filenames = {}
    for i=1,#controllers do
        filenames[i] = root .. script .. "-" .. i .. "." .. fileext
    end

    local good, err = pcall(tas.runMultiplayerTas, filenames, controllers)
    if not good then
        Log("Error occured (MP " .. script .. "): " .. err)
    end
end

function allAttached(controllers)
    for i,v in ipairs(controllers) do
        if not hiddbg_IsControllerAttached(v) then
            return false
        end
    end
    return true
end

local tasOn = true
controllers = {}
while true do
    hid_ScanInput()

    if tasOn then
        if hid_KeyboardDown(hid.KeyboardScancode.F1) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script1", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F2) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script2", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F3) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script3", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F4) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script4", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F5) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script5", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F6) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script6", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F7) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script7", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F8) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script8", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F9) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script9", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F10) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script10", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F11) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script11", controllers[1])
        elseif hid_KeyboardDown(hid.KeyboardScancode.F12) and hiddbg_IsControllerAttached(controllers[1]) then
            runScript("script12", controllers[1])
        end

        if tas.multiplayer then
            if hid_KeyboardDown(hid.KeyboardScancode.Equal) then
                table.insert(controllers, hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor))
            elseif hid_KeyboardDown(hid.KeyboardScancode.Minus) and hiddbg_IsControllerAttached(controllers[#controllers]) then
                hiddbg_DetachController(controllers[#controllers])
            elseif hid_KeyboardDown(hid.KeyboardScancode.Num1) and allAttached(controllers) and #controllers == 2 then
                runMultiplayerScript("script1", controllers)
            end
        else
            if hid_KeyboardDown(hid.KeyboardScancode.Equal) and not hiddbg_IsControllerAttached(controllers[1]) then
                controllers[1] = hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor)
            elseif hid_KeyboardDown(hid.KeyboardScancode.Minus) and hiddbg_IsControllerAttached(controllers[1]) then
                hiddbg_DetachController(controllers[1])
            end
        end
    end

    if hid_KeyboardDown(hid.KeyboardScancode.Esc) then
        tasOn = not tasOn
    end

    if tas.multiplayer then
        local ctrlCopy = {}
        for i=1,#controllers do
            if hiddbg_IsControllerAttached(controllers[i]) then
                table.insert(ctrlCopy, controllers[i])
            end
        end

        controllers = ctrlCopy
    end

    svc_SleepThread(6250000)
end