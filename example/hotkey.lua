local active = win.GetActiveWindow()

wapi.RegisterHotKey(active, 1, MOD_CONTROL, 65)

repeat
    local status, hwnd, msg, wparam, lparam, mtime, x, y = win.GetMessage(active, 0, 0)

    if msg == WM_HOTKEY then
        print("Ctrl+A pressed")
    end
until status == false