controller = {}
while true do
    hid_ScanInput()
    if hid_KeyboardDown(0x1e) then
        controller = hiddbg_AttachController()
    end
    if hid_KeyboardDown(0x1f) then
        hiddbg_DetachController(controller["handle"])
    end
    if hid_KeyboardDown(0x20) then
        svc_SleepThread(1000000000)
        controller["state"]["buttons"] = 1;
        hiddbg_SetState(controller)
        svc_SleepThread(1000000000)
        controller["state"]["buttons"] = 0;
        hiddbg_SetState(controller)
        svc_SleepThread(1000000000)
    end
    svc_SleepThread(6250000)
end