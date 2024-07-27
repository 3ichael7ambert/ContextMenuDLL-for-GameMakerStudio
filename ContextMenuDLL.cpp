#include <windows.h>
#include <richedit.h>
#include <iostream>
#include "resource.h"

// Function pointer for GameMaker script
typedef void (__cdecl *GMLScriptFunction)(const char*);

// Global pointer to the GameMaker function
GMLScriptFunction gml_script_function = nullptr;

#define trace(...) { printf("[show_context_menu:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

// Dialog Procedure for Rich Edit Dialog
INT_PTR CALLBACK RichEditDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG: {
            HWND hRichEdit = GetDlgItem(hDlg, IDC_RICHHEDIT);
            SendMessage(hRichEdit, EM_SETTEXTMODE, TM_RICHTEXT, 0);

            // Set rich text
            const char* richText = 
                "<b><i>Developed by 3ichael 7ambert</i></b><br>"
                "<b>Window_shape by YellowAfterLife</b><br>"
                "<i>Debugging by Ray Johnson</i>";

            // Initialize CHARFORMAT2A
            CHARFORMAT2A cf;
            ZeroMemory(&cf, sizeof(cf)); // Initialize all members to zero
            cf.cbSize = sizeof(cf); // Set size of the structure
            cf.dwMask = CFM_BOLD | CFM_ITALIC; // Specify attributes to modify
            cf.dwEffects = CFE_BOLD | CFE_ITALIC; // Set effects you want
            cf.crTextColor = RGB(0, 0, 0); // Example color (black)

            SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
            SendMessage(hRichEdit, EM_REPLACESEL, FALSE, (LPARAM)richText);

            return TRUE;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                EndDialog(hDlg, IDOK);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

// Function to display the context menu
extern "C" __declspec(dllexport) void ShowContextMenu(double x, double y) {
    trace("Starting ShowContextMenu with x=%f, y=%f", x, y);

    HMENU hMenu = CreatePopupMenu();
    if (!hMenu) {
        trace("Failed to create popup menu");
        return;
    }

    // Create submenu for color options (Option 2)
    HMENU hSubMenu = CreatePopupMenu();
    if (!hSubMenu) {
        trace("Failed to create submenu");
        DestroyMenu(hMenu);
        return;
    }
    AppendMenuA(hSubMenu, MF_STRING, 4, "Black");
    AppendMenuA(hSubMenu, MF_STRING, 5, "Red");
    AppendMenuA(hSubMenu, MF_STRING, 6, "Yellow");
    AppendMenuA(hSubMenu, MF_STRING, 7, "Silver");
    AppendMenuA(hSubMenu, MF_STRING, 8, "Pink");

    // Add Option 2 to the main menu and attach the submenu
    AppendMenuA(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "Character");

    // Add "About" option
    AppendMenuA(hMenu, MF_STRING, 3, "About");

    HWND hwnd = GetForegroundWindow();
    if (hwnd == NULL) {
        trace("Failed to get foreground window");
        DestroyMenu(hMenu);
        return;
    }
    trace("Foreground window handle: %p", hwnd);

    POINT pt = { static_cast<LONG>(x), static_cast<LONG>(y) };
    ClientToScreen(hwnd, &pt);
    trace("Screen coordinates: x=%d, y=%d", pt.x, pt.y);

    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
    trace("Menu item selected: %d", cmd);

    // Handle menu selection with a switch statement
    switch (cmd) {
        case 1:
            MessageBox(hwnd, "Option 1 Selected", "Info", MB_OK);
            break;
        case 4: // Black
        case 5: // Red
        case 6: // Yellow
        case 7: // Silver
        case 8: // Pink
            {
                const char* colorName;
                switch (cmd) {
                    case 4: colorName = "black"; break;
                    case 5: colorName = "red"; break;
                    case 6: colorName = "yellow"; break;
                    case 7: colorName = "silver"; break;
                    case 8: colorName = "pink"; break;
                }
                
                // Call the GML script function
                if (gml_script_function) {
                    trace("Calling GML function with color: %s", colorName);
                    gml_script_function(colorName);
                } else {
                    trace("GML script function not set");
                }
                break;
            }
        case 3: { // About
            // Ensure the Rich Edit control is available
            HMODULE hMsftEdit = LoadLibrary("msftedit.dll");
            if (!hMsftEdit) {
                trace("Failed to load msftedit.dll");
            } else {
                trace("msftedit.dll loaded successfully");

                // Check if resource exists
                HRSRC hResource = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_RICHHEDIT_DIALOG), RT_DIALOG);
                if (hResource == NULL) {
                    trace("Failed to find dialog resource, error code: %lu", GetLastError());
                } else {
                    if (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_RICHHEDIT_DIALOG), hwnd, RichEditDlgProc) == -1) {
                        DWORD dwError = GetLastError();
                        trace("Failed to create dialog box, error code: %lu", dwError);
                    }
                }
                FreeLibrary(hMsftEdit);
            }
            break;
        }
        default:
            trace("No valid menu item selected");
            break;
    }

    DestroyMenu(hMenu);
    trace("Menu destroyed");
}

// Function to set the GML script function
extern "C" __declspec(dllexport) void SetGMLScriptFunction(GMLScriptFunction func) {
    gml_script_function = func;
    trace("GML script function set: %p", gml_script_function);
}
