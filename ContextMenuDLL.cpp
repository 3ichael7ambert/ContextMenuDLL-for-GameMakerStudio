#include <windows.h>
#include <iostream>

#define trace(...) { printf("[show_context_menu:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

extern "C" __declspec(dllexport) void ShowContextMenu(double x, double y) {
    trace("Starting ShowContextMenu with x=%f, y=%f", x, y);

    HMENU hMenu = CreatePopupMenu();
    if (!hMenu) {
        trace("Failed to create popup menu");
        return;
    }
    AppendMenuA(hMenu, MF_STRING, 1, "Option 1");
    AppendMenuA(hMenu, MF_STRING, 2, "Option 2");
    AppendMenuA(hMenu, MF_STRING, 3, "Option 3");

    HWND hwnd = GetForegroundWindow();
    if (hwnd == NULL) {
        trace("Failed to get foreground window");
        return;
    }
    trace("Foreground window handle: %p", hwnd);

    POINT pt = { static_cast<LONG>(x), static_cast<LONG>(y) };
    ClientToScreen(hwnd, &pt);
    trace("Screen coordinates: x=%d, y=%d", pt.x, pt.y);

    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
    trace("Menu item selected: %d", cmd);

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
            trace("No valid menu item selected");
            break;
    }

    //DestroyMenu(hMenu);
    trace("Menu destroyed");
}
