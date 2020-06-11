tas = require "nxtas"
local fileext = tas.fileext
local root = "sdmc:/scripts/"

controller = {}
controllerAttached = false
while true do
    hid_ScanInput()
    if hid_KeyboardDown(0x2e) and not controllerAttached then --equals
        controller = hiddbg_AttachController()
        controllerAttached = true
    end
    if hid_KeyboardDown(0x2d) and controllerAttached then --minus
        hiddbg_DetachController(controller)
        controllerAttached = false
    end
    if hid_KeyboardDown(0x3a) and controllerAttached then
        tas.runTas(root .."script1." .. fileext, controller)
    end
    if hid_KeyboardDown(0x3b) and controllerAttached then
        tas.runTas(root .. "script2." .. fileext, controller)
    end
    if hid_KeyboardDown(0x3c) and controllerAttached then
        tas.runTas(root .. "script3." .. fileext, controller)
    end
    if hid_KeyboardDown(0x3d) and controllerAttached then
        tas.runTas(root .. "script4." .. fileext, controller)
    end
    if hid_KeyboardDown(0x3e) and controllerAttached then
        tas.runTas(root .. "script5." .. fileext, controller)
    end
    if hid_KeyboardDown(0x3f) and controllerAttached then
        tas.runTas(root .. "script6." .. fileext, controller)
    end
    if hid_KeyboardDown(0x40) and controllerAttached then
        tas.runTas(root .. "script7." .. fileext, controller)
    end
    if hid_KeyboardDown(0x41) and controllerAttached then
        tas.runTas(root .. "script8." .. fileext, controller)
    end
    if hid_KeyboardDown(0x42) and controllerAttached then
        tas.runTas(root .. "script9." .. fileext, controller)
    end
    if hid_KeyboardDown(0x43) and controllerAttached then
        tas.runTas(root .. "script10." .. fileext, controller)
    end
    if hid_KeyboardDown(0x44) and controllerAttached then
        tas.runTas(root .. "script11." .. fileext, controller)
    end
    if hid_KeyboardDown(0x45) and controllerAttached then
        tas.runTas(root .. "script12." .. fileext, controller)
    end
    svc_SleepThread(6250000)
end