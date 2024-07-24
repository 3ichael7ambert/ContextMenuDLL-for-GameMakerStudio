#include <windows.h>
#include <iostream>

extern "C" __declspec(dllexport) void ShowContextMenu(double x, double y) {
    OutputDebugString("ShowContextMenu called\n"); // Debug message

    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, 1, "Option 1");
    AppendMenu(hMenu, MF_STRING, 2, "Option 2");
    AppendMenu(hMenu, MF_STRING, 3, "Option 3");

    HWND hwnd = GetForegroundWindow();
    if (hwnd == NULL) {
        OutputDebugString("Failed to get foreground window\n");
        return;
    }

    POINT pt = { static_cast<LONG>(x), static_cast<LONG>(y) };
    ClientToScreen(hwnd, &pt);

    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);

    OutputDebugString("Menu item selected: " + std::to_string(cmd) + "\n");

    switch (cmd) {
        case 1:
            MessageBox(hwnd, "Option 1 Selected", "Info", MB_OK);
            break;
        case 2:
            MessageBox(hwnd, "Option 2 Selected", "Info", MB_OK);
            break;
        case 3:
            MessageBox(hwnd, "Option 3 Selected", "Info", MB_OK);
            break;
        default:
            break;
    }

   // DestroyMenu(hMenu);
}

