#include <windows.h>
#include <iostream>

extern "C" __declspec(dllexport) void ShowContextMenu(double x, double y) {
    // Log the function call
    OutputDebugString("ShowContextMenu called\n");

    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, 1, "Option 1");
    AppendMenu(hMenu, MF_STRING, 2, "Option 2");

    POINT pt = { static_cast<LONG>(x), static_cast<LONG>(y) };
    HWND hwnd = GetForegroundWindow();
    SetForegroundWindow(hwnd);

    // Log the coordinates
    char buffer[256];
    sprintf(buffer, "Coordinates: %ld, %ld\n", pt.x, pt.y);
    OutputDebugString(buffer);

    double cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);

    if (cmd == 1) {
        MessageBox(hwnd, "Option 1 Selected", "Info", MB_OK);
    } else if (cmd == 2) {
        MessageBox(hwnd, "Option 2 Selected", "Info", MB_OK);
    }
    
    //DestroyMenu(hMenu); // Clean up the menu to prevent memory leaks
}
