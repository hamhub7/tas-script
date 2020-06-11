local nxtas = {}

nxtas.fileext = "txt"

function bit(int n)
    return bit.lshift(1, n)
end

local buttons = {}
buttons.A = bit(0);
buttons.B = bit(1);
buttons.X = bit(2);
buttons.Y = bit(3);
buttons.LSTICK = bit(4);
buttons.RSTICK = bit(5);
buttons.L = bit(6);
buttons.R = bit(7);
buttons.ZL = bit(8);
buttons.ZR = bit(9);
buttons.PLUS = bit(10);
buttons.MINUS = bit(11);
buttons.DLEFT = bit(12);
buttons.DUP = bit(13);
buttons.DRIGHT = bit(14);
buttons.DDOWN = bit(15);

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

return nxtas