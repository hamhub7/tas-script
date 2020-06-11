local tiger = {}

tiger.fileext = "tig"

local buttons = {}
buttons.A = 1;
buttons.B = 2;
buttons.X = 4;
buttons.Y = 8;
buttons.LSTICK = 16;
buttons.RSTICK = 32;
buttons.L = 64;
buttons.R = 128;
buttons.ZL = 256;
buttons.ZR = 512;
buttons.PLUS = 1024;
buttons.MINUS = 2048;
buttons.DLEFT = 4096;
buttons.DUP = 8192;
buttons.DRIGHT = 16384;
buttons.DDOWN = 32768;

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

    local frame = splitLine[1]

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

function tiger.runTas(filename, controller)
    local file = io.open(filename, "r")
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

        frame = frame + 1
        if controlMsg["frame"] == "+" or tonumber(controlMsg["frame"]) == frame then
            runLine(controlMsg, controller)
            readFile = true
            frame = 0
        else
            readFile = false
        end
        EventWaitMax(vsync_event)

    end

    clearInputs(controller)
    EventClose(vsync_event)
    vi_CloseDisplay(display)
    io.close(file)
end

return tiger