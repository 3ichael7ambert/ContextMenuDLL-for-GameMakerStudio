// Define the initialization macro
#define contextMenuInit
/// Initializes the context menu by defining the external function.
global.showContextMenu = external_define("ContextMenuDLL.dll", "ShowContextMenu", dll_cdecl, ty_real, 2, ty_real, ty_real);

// Define the cleanup macro
#define contextMenuCleanup
/// Cleans up the context menu by freeing the external function definition.
external_free(global.showContextMenu);

// Define a function to show the context menu at the mouse position
#define ContextMenuMouse
    var xx = display_mouse_get_x();
    var yy = display_mouse_get_y();
    external_call(global.showContextMenu, xx, yy);




/*

// Initialize the context menu
global.showContextMenu = external_define("ContextMenu.dylib", "ShowContextMenu", dll_cdecl, ty_real, 2, ty_real, ty_real);

// Function to show the context menu at the mouse position
function showContextMenuAtMousePosition() {
    var xx = display_mouse_get_x();
    var yy = display_mouse_get_y();
    external_call(global.showContextMenu, xx, yy);
}

// Clean up the context menu
function cleanupContextMenu() {
    external_free(global.showContextMenu);
}

*/