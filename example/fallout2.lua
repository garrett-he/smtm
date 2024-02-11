-- Finds the Fallout window
local wnd = win.FindWindow(nil, "FALLOUT II")

-- Finds the process ID
local result, pid = win.GetWindowThreadProcessId(wnd)

-- Opens the process
local proc = win.OpenProcess(nil, 0, pid)

-- Reads current experience
local status, result, bytes = win.ReadProcessMemory(proc, 0x00678724, 4)

print("Reading current experience...")
print("Status: " .. tostring(status))
print("Experience: " .. smtm.udatatointeger(result))
print("Bytes read: " .. bytes)
print()

if status then
    print("Writing current experience...")
    status = win.WriteProcessMemory(proc, 0x00678724, smtm.integertoudata(100), 4)
    print("Status: " .. tostring(status))
end