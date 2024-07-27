// Script assets have changed for v2.3.0 see
// https://help.yoyogames.com/hc/en-us/articles/360005277377 for more information

// Function to show the context menu at the mouse position
function showContextMenuAtMousePosition() {
    var xx = mouse_x;
    var yy = mouse_y;
    external_call(global.showContextMenu, xx, yy);
}

// Clean up the context menu
function cleanupContextMenu() {
    external_free(global.showContextMenu);
}