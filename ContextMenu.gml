// Define constants if they are not already defined by GameMaker Studio
if (typeof(dll_cdecl) == undefined) {
    dll_cdecl = 0;
}
if (typeof(ty_void) == undefined) {
    ty_void = 0;
}
if (typeof(ty_real) == undefined) {
    ty_real = 1;
}

// Define the initialization macro
#define contextMenuInit
/// Initializes the context menu by defining the external function.
global.showContextMenu = external_define("ContextMenuDLL.dll", "ShowContextMenu", dll_cdecl, 0 , 2, ty_real, ty_real);

// Define the cleanup macro
#define contextMenuCleanup
/// Cleans up the context menu by freeing the external function definition.
external_free(global.showContextMenu);

// Define a function to show the context menu
function showContextMenuAtMousePosition() {
    var xx = display_mouse_get_x();
    var yy = display_mouse_get_y();
    external_call(global.showContextMenu, xx, yy);
}
