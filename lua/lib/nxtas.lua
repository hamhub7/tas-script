local nxtas = {}

nxtas.fileext = "txt"
nxtas.multiplayer = true

local buttons = {
    A       = 1 << 0,
    B       = 1 << 1,
    X       = 1 << 2,
    Y       = 1 << 3,
    LSTICK  = 1 << 4,
    RSTICK  = 1 << 5,
    L       = 1 << 6,
    R       = 1 << 7,
    ZL      = 1 << 8,
    ZR      = 1 << 9,
    PLUS    = 1 << 10,
    MINUS   = 1 << 11,
    DLEFT   = 1 << 12,
    DUP     = 1 << 13,
    DRIGHT  = 1 << 14,
    DDOWN   = 1 << 15
}

function clearInputs(controller)
    hiddbg_SetButtons(controller, 0)
    hiddbg_SetJoystick(controller, 1, 0, 0)
    hiddbg_SetJoystick(controller, 2, 0, 0)
end

function strSplit(delim,str)
    local t = {}

    for substr in string.gmatch(str, "[^".. delim.. "]*") do
        if substr ~= nil and string.len(substr) > 0 then
            table.insert(t,substr)
        end
    end

    return t
end

function scanLine(line)
    local splitLine = strSplit(" ", line) --frame, keys, joyleft, joyright

    local frame = tonumber(splitLine[1])

    local keys = 0
    if splitLine[2] ~= "NONE" then
        local splitKeys = strSplit(";", splitLine[2])

        for i,v in ipairs(splitKeys) do
            local keystr = string.sub(v, 5)

            for k in pairs(buttons) do
                if k == keystr then
                    keys = keys + buttons[k]
                    break
                end
            end
        end
    end

    local splitJoyLeft = strSplit(";", splitLine[3])
    local leftdx = tonumber(splitJoyLeft[1])
    local leftdy = tonumber(splitJoyLeft[2])

    local splitJoyRight = strSplit(";", splitLine[4])
    local rightdx = tonumber(splitJoyRight[1])
    local rightdy = tonumber(splitJoyRight[2])


    local controlMsg = {}
    controlMsg["frame"] = frame
    controlMsg["keys"] = keys
    controlMsg["joyleft"] = {}
    controlMsg["joyleft"]["x"] = leftdx
    controlMsg["joyleft"]["y"] = leftdy
    controlMsg["joyright"] = {}
    controlMsg["joyright"]["x"] = rightdx
    controlMsg["joyright"]["y"] = rightdy

    return controlMsg
end

function runLine(controlMsg, controller)
    hiddbg_SetButtons(controller, controlMsg["keys"])
    hiddbg_SetJoystick(controller, 1, controlMsg["joyleft"]["x"], controlMsg["joyleft"]["y"])
    hiddbg_SetJoystick(controller, 2, controlMsg["joyright"]["x"], controlMsg["joyright"]["y"])
end

function nxtas.runTas(filename, controller)
    local file = io.open(filename, "r")
    if not file then
        error("file " .. filename .. " could not be opened")
    end
    io.input(file)

    local display = vi_OpenDefaultDisplay()
    local vsync_event = vi_GetDisplayVsyncEvent(display)

    local frame = 0
    local readFile = true
    local controlMsg = {}
    while true do
        hid_ScanInput()

        if hid_KeyboardDown(hid.KeyboardKey.Escape) then 
            clearInputs(controller)
            Log("Script cancelled")
            break 
        end

        if readFile then
            local line = io.read()
            if line == nil then break end
            controlMsg = scanLine(line)
        end


        if controlMsg["frame"] == frame then
            runLine(controlMsg, controller)
            readFile = true
        else
            clearInputs(controller)
            readFile = false
        end

        EventWaitMax(vsync_event)

        frame = frame + 1

    end

    EventClose(vsync_event)
    vi_CloseDisplay(display)
    clearInputs(controller)
    io.close(file)
end

function nxtas.runMultiplayerTas(filenames, controllers)
    local playersNum = #filenames
    if #controllers ~= playersNum then
        error("Controllers not the same number as filenames! Discontinuing...")
    end
    local files = {}
    local shouldRead = {}
    local readFiles = {}
    local path = nil
    for i=1,playersNum do
        path = filenames[i]
        local f = io.open(path)
        if not f then 
            error("file " .. path .. " could not be opened")
        end
        table.insert(files, f)
        table.insert(shouldRead, true)
        table.insert(readFiles, true)
    end

    local display = vi_OpenDefaultDisplay()
    local vsync_event = vi_GetDisplayVsyncEvent(display)

    local frame = 0
    local controlMsgs = {}
    local done = 0
    while done < playersNum do
        for c=1,playersNum do 
            if shouldRead[c] then 
                if readFiles[c] then
                    io.input(files[c])
                    local line = io.read()
                    if line == nil then
                        shouldRead[c] = false
                        done = done + 1
                    end
                    if shouldRead[c] then -- we have to include checking for this because it could have changed since the loop started
                        controlMsgs[c] = scanLine(line)
                    end
                end

                if shouldRead[c] then
                    if controlMsgs[c] ~= nil and controlMsgs[c]["frame"] == frame then
                        runLine(controlMsgs[c], controllers[c])
                        readFiles[c] = true
                    else
                        clearInputs(controllers[c])
                        readFiles[c] = false
                    end
                end
            else
                clearInputs(controllers[c])
            end
        end
        EventWaitMax(vsync_event)
        frame = frame + 1
    end

    EventClose(vsync_event)
    vi_CloseDisplay(display)
    for f=1,playersNum do 
        io.close(files[f])
        clearInputs(controllers[f])
    end
end

return nxtas
