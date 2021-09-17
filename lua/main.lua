tas = require "lib/nxtas" --Edit this to change the scripting language used
colors = require "sys/colors"
hid = require "sys/hidenum"
local fileext = tas.fileext
local root = "sdmc:/scripts/"

local bodyColor = colors.rgb(4, 156, 216)
local buttonsColor = colors.rgb(0, 0, 0)
local gripLColor = colors.rgb(229, 37, 33)
local gripRColor = colors.rgb(229, 37, 3353)

function waitFrames(frames)
    local display = vi_OpenDefaultDisplay()
    local vsync_event = vi_GetDisplayVsyncEvent(display)
    for i=1,frames do
        EventWaitMax(vsync_event)
    end
    EventClose(vsync_event)
    vi_CloseDisplay(display)
end

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

function attached(ctrls, num)
    for i=1,num do
        if not hiddbg_IsControllerAttached(ctrls[i]) then
            return false
        end
    end
    return true
end

local tasOn = true
controllers = {}
while true do
    local ctrlCopy = {}
    for i=1,#controllers do
        if hiddbg_IsControllerAttached(controllers[i]) then
            table.insert(ctrlCopy, controllers[i])
        end
    end
    controllers = ctrlCopy

    hid_ScanInput()

    if tasOn then
        -- Adding/removing controllers
        if tas.multiplayer then
            if hid_KeyboardDown(hid.KeyboardKey.Plus) and #controllers < 8 then
                table.insert(controllers, hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor))
            elseif hid_KeyboardDown(hid.KeyboardKey.Minus) and #controllers > 0 and attached(controllers, #controllers) then
                hiddbg_DetachController(controllers[#controllers])
            end
        else
            if hid_KeyboardDown(hid.KeyboardKey.Plus) and #controllers < 1 then
                controllers[1] = hiddbg_AttachController(bodyColor, buttonsColor, gripLColor, gripRColor)
            elseif hid_KeyboardDown(hid.KeyboardKey.Minus) and #controllers > 0 and attached(controllers, 1) then
                hiddbg_DetachController(controllers[1])
            end
        end

        -- Running scripts
        if hid_KeyboardDown(hid.KeyboardKey.F1) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script1", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script1", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F2) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script2", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script2", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F3) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script3", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script3", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F4) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script4", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script4", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F5) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script5", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script5", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F6) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script6", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script6", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F7) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script7", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script7", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F8) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script8", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script8", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F9) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script9", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script9", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F10) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script10", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script10", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F11) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script11", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script11", controllers[1])
                end
            end
        elseif hid_KeyboardDown(hid.KeyboardKey.F12) then
            if tas.multiplayer and #controllers > 1 then
                if attached(controllers, #controllers) then
                    runMultiplayerScript("script12", controllers)
                end
            else
                if #controllers > 0 and attached(controllers, 1) then
                    runScript("script12", controllers[1])
                end
            end
        end

        -- Utility keybinds
        if hid_KeyboardDown(hid.KeyboardKey.Q) and #controllers > 0 then
            hiddbg_SetButtons(controllers[1], hid.ControllerKeys.A)
            waitFrames(5)
            hiddbg_SetButtons(controllers[1], 0)
            waitFrames(5)
        elseif hid_KeyboardDown(hid.KeyboardKey.W) and #controllers > 0 then
            for i,v in ipairs(controllers) do
                hiddbg_SetButtons(v, hid.ControllerKeys.L | hid.ControllerKeys.R)
                waitFrames(5)
                hiddbg_SetButtons(v, 0)
                waitFrames(5)
            end
        end
    end

    svc_SleepThread(6250000)
end