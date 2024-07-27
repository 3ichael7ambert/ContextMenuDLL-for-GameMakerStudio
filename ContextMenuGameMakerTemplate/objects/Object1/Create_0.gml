/// @description Insert description here
// You can write your code in this editor
//contextMenuInit();

// Initialize the context menu
if os_type == os_windows {
global.showContextMenu = external_define("ContextMenuDLL.dll", "ShowContextMenu", dll_cdecl, ty_real, 2, ty_real, ty_real);
}

if os_type == os_macosx {
global.showContextMenu = external_define("ContextMenu.dylib", "ShowContextMenu", dll_cdecl, ty_real, 2, ty_real, ty_real);

}