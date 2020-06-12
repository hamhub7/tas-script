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

function nxtas.runMuliplayerTas(filenames, controllers)
    if rawlen(filenames) ~= rawlen(controllers) then
        error("filenames and controllers were not the same size")
    end
    local numPlayers = rawlen(filenames) --should do a check here to make sure we dont add any more controllers than allowed

    local display = vi_OpenDefaultDisplay()
    local vsync_event = vi_GetDisplayVsyncEvent(display)

    local players = {}
    for i = 1, numPlayers do
        table.insert(players, coroutine.create(runTasCoroutine))
    end

    while true do
        local shouldBreak = true
        for i,co in ipairs(players) do
            if coroutine.status(co) ~= "dead" then
                shouldBreak = false
                break
            end
        end
        if shouldBreak then break end

        for i,co in ipairs(players) do
            if coroutine.status(co) ~= "dead" then
            coroutine.resume(co, filenames[i], controllers[i])
            end
        end

        EventWaitMax(vsync_event)
    end

    EventClose(vsync_event)
    vi_CloseDisplay(display)
end

function runTasCoroutine(filename, controller)
    local file = io.open(filename, "r")
    if not file then
        error("file " .. filename .. " could not be opened")
    end
    io.input(file)

    local frame = 0
    local readFile = true
    local controlMsg = {}
    while true do
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

        frame = frame + 1
        
        coroutine.yield()
    end

    clearInputs(controller)
    io.close(file)
end

return nxtas