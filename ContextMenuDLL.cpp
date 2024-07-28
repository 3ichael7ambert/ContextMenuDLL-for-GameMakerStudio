#include <windows.h>
#include <iostream>

#define WM_USER_MENU_SELECT (WM_USER + 1)

typedef void (__cdecl *GMLScriptFunction)(int);

GMLScriptFunction gml_script_function = nullptr;

#define trace(...) { printf("[show_context_menu:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

extern "C" __declspec(dllexport) void SetGMLScriptFunction(double func) {
    gml_script_function = (GMLScriptFunction)(uintptr_t)func;
    trace("GML script function set: %p", gml_script_function);
}

extern "C" __declspec(dllexport) void ShowContextMenu(double x, double y, const char* win_handle_str) {
    trace("Starting ShowContextMenu with x=%f, y=%f, win_handle_str=%s", x, y, win_handle_str);

    HWND hwnd;
    sscanf(win_handle_str, "%p", &hwnd);
    trace("Converted window handle: %p", hwnd);

    HMENU hMenu = CreatePopupMenu();
    if (!hMenu) {
        trace("Failed to create popup menu");
        return;
    }

    // Populate menu with color submenus
    HMENU hSubMenuColor = CreatePopupMenu();
    if (!hSubMenuColor) {
        trace("Failed to create color submenu");
        DestroyMenu(hMenu);
        return;
    }
    AppendMenuA(hSubMenuColor, MF_STRING, 4, "Black");
    AppendMenuA(hSubMenuColor, MF_STRING, 5, "Red");
    AppendMenuA(hSubMenuColor, MF_STRING, 6, "Yellow");
    AppendMenuA(hSubMenuColor, MF_STRING, 7, "Silver");
    AppendMenuA(hSubMenuColor, MF_STRING, 8, "Pink");

    // Populate menu with instrument submenus
    HMENU hSubMenuInstrument = CreatePopupMenu();
    if (!hSubMenuInstrument) {
        trace("Failed to create instrument submenu");
        DestroyMenu(hMenu);
        return;
    }
    AppendMenuA(hSubMenuInstrument, MF_STRING, 9, "Guitar");
    AppendMenuA(hSubMenuInstrument, MF_STRING, 10, "Piano");
    AppendMenuA(hSubMenuInstrument, MF_STRING, 11, "Drums");

    // Add submenus and other menu items
    AppendMenuA(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuColor, "Character");
    AppendMenuA(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuInstrument, "Instrument");
    AppendMenuA(hMenu, MF_STRING, 3, "About");

    if (hwnd == NULL) {
        trace("Failed to get valid window handle");
        DestroyMenu(hMenu);
        return;
    }
    trace("Window handle: %p", hwnd);

    POINT pt = { static_cast<LONG>(x), static_cast<LONG>(y) };
    ClientToScreen(hwnd, &pt);
    trace("Screen coordinates: x=%d, y=%d", pt.x, pt.y);

    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
    trace("Menu item selected: %d", cmd);

    if (cmd > 0) {
        trace("Posting message WM_USER_MENU_SELECT with cmd: %d", cmd);
        PostMessage(hwnd, WM_USER_MENU_SELECT, cmd, 0);
    }

    DestroyMenu(hMenu);
    trace("Menu destroyed");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_USER_MENU_SELECT:
            trace("Received WM_USER_MENU_SELECT with command: %d", (int)wParam);
            if (gml_script_function) {
                trace("Calling GML script function with command: %d", (int)wParam);
                gml_script_function((int)wParam);
            } else {
                trace("GML script function not set");
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        // Handle other messages
        // ...
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
