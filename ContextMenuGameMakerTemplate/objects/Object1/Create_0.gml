/// @description Insert description here
// You can write your code in this editor
//contextMenuInit();

// Initialize the context menu
global.showContextMenu = external_define("ContextMenuDLL.dll", "ShowContextMenu", dll_cdecl, ty_real, 2, ty_real, ty_real);

