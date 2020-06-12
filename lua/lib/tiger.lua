local tiger = {}

tiger.fileext = "tig"
tiger.multiplayer = false

function bitsUpTo(x) 
    local res = 0
    local c = 1
    while c < x + 1 do
        res = res | 1 << c
        c = c + 1
    end
    return res
end

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
    DDOWN   = 1 << 15,
    NONE    = 0,
    ALL     = bitsUpTo(15)
}

function bitNot(x,y)
    return x - (x & y)
end

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

function paramName(str)
    return string.upper(strSplit("{", str)[1])
end

function separateBrackets(str) 
    return strSplit(",", strSplit("}", strSplit("{", str)[2])[1])
end

function sign(x) 
    if math.abs(x) == x then
        return 1;
    else 
        return -1;
    end
end

function signIndependentCeil(x) 
    if x == 0 then
        return 0
    elseif sign(x) == 1 then
        return math.ceil(x)
    else 
        return math.floor(x)
    end
end

function remove_key(x) 
    if string.sub(x,1,4) ~= "KEY_" then
        return x;
    else 
        return string.sub(x,5)
    end
end

function keysInt(keysList) 
    local keys = 0
    for i,v in ipairs(keysList) do
        for k in pairs(buttons) do
            if k == remove_key(v) then
                keys = keys + buttons[k]
                break
            end
        end
    end
    return keys
end

function makeStickCartesian(ang, mag) 
    ang = tonumber(ang)
    mag = tonumber(mag)
    if mag > 32767 then
        mag = sign(mag) * 32767
    end
    ang = ang * 3.14159265358979323 / 180
    local res = {}
    res.dx = signIndependentCeil(math.sin(ang) * mag)
    res.dy = signIndependentCeil(math.cos(ang) * mag)
    return res
end


function scanLine(line, activeKeys)
    local splitLine = strSplit(" ", line)

    local frame = splitLine[1]

    table.remove(splitLine, 1)
    local params = splitLine;
    
    local onKeys = {}
    local offKeys = {}
    local lstickPos = {}
    local rstickPos = {}
    local keysModifier = 0
    for i,v in ipairs(params) do 
        local param = paramName(v)
        local inside = separateBrackets(v)
        if param == "LSTICK" then
            local parsedLstick = inside
            lstickPos = makeStickCartesian(parsedLstick[1], parsedLstick[2])
        elseif param == "RSTICK" then 
            local parsedRstick = inside
            rstickPos = makeStickCartesian(parsedRstick[1], parsedRstick[2])
        elseif param == "ON" then
            for n,el in ipairs(inside) do
                table.insert(onKeys, el)
            end
        elseif param == "OFF" then
            for n,el in ipairs(inside) do
                table.insert(offKeys, el)
            end
        elseif param == "RAW" then
            activeKeys = 0
            for n,el in ipairs(inside) do
                table.insert(onKeys, el)
            end
        end
    end

    local controlMsg = {}
    controlMsg["frame"] = frame
    controlMsg["keys"] = bitNot(activeKeys | keysInt(onKeys), keysInt(offKeys))
    controlMsg["joyleft"] = {}
    controlMsg["joyleft"]["x"] = lstickPos.dx
    controlMsg["joyleft"]["y"] = lstickPos.dy
    controlMsg["joyright"] = {}
    controlMsg["joyright"]["x"] = rstickPos.dx
    controlMsg["joyright"]["y"] = rstickPos.dy

    return controlMsg
end

function runLine(controlMsg, controller)
    if controlMsg["keys"] ~= nil then
        hiddbg_SetButtons(controller, controlMsg["keys"])
    end
    if controlMsg["joyleft"]["x"] ~= nil then
        hiddbg_SetJoystick(controller, 1, controlMsg["joyleft"]["x"], controlMsg["joyleft"]["y"])
    end
    if controlMsg["joyright"]["x"] ~= nil then
        hiddbg_SetJoystick(controller, 2, controlMsg["joyright"]["x"], controlMsg["joyright"]["y"])
    end
end

function tiger.runTas(filename, controller)
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
    local activeKeys = 0
    while true do
        if readFile then
            local line = io.read()
            if line == nil then break end
            controlMsg = scanLine(line, activeKeys)
            activeKeys = controlMsg["keys"]
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
