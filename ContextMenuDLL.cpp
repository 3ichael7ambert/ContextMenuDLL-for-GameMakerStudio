#include <windows.h>

extern "C" __declspec(dllexport) void ShowContextMenu(int x, int y) {
    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, 1, "Option 1");
    AppendMenu(hMenu, MF_STRING, 2, "Option 2");

    POINT pt = { x, y };
    HWND hwnd = GetForegroundWindow();
    SetForegroundWindow(hwnd);

    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);

    if (cmd == 1) {
        MessageBox(hwnd, "Option 1 Selected", "Info", MB_OK);
    } else if (cmd == 2) {
        MessageBox(hwnd, "Option 2 Selected", "Info", MB_OK);
    }
}
