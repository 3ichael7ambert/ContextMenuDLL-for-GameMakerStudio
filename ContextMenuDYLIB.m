#import <Cocoa/Cocoa.h>

#define trace(...) { printf("[show_context_menu:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

void ShowContextMenu(double x, double y) {
    trace("Starting ShowContextMenu with x=%f, y=%f", x, y);

    NSMenu *menu = [[NSMenu alloc] initWithTitle:@"Context Menu"];
    if (!menu) {
        trace("Failed to create popup menu");
        return;
    }

    [menu addItemWithTitle:@"Option 1" action:@selector(menuItemSelected:) keyEquivalent:@""];
    [menu addItemWithTitle:@"Option 2" action:@selector(menuItemSelected:) keyEquivalent:@""];
    [menu addItemWithTitle:@"Option 3" action:@selector(menuItemSelected:) keyEquivalent:@""];
    
    NSPoint pt = NSMakePoint(x, y);
    NSEvent *event = [NSEvent mouseEventWithType:NSEventTypeRightMouseDown
                                         location:pt
                                    modifierFlags:0
                                        timestamp:0
                                     windowNumber:[[NSApp keyWindow] windowNumber]
                                          context:nil
                                      eventNumber:0
                                       clickCount:1
                                         pressure:1];
    [NSMenu popUpContextMenu:menu withEvent:event forView:nil];
    
    trace("Menu displayed");
}

@implementation NSApplication (ContextMenu)

+ (void)menuItemSelected:(NSMenuItem *)item {
    trace("Menu item selected: %@", [item title]);
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithFormat:@"%@ Selected", [item title]]];
    [alert runModal];
}

@end
