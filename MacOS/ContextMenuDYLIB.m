#import <Cocoa/Cocoa.h>

#define trace(...) { NSLog(@"[show_context_menu:%d] %@", __LINE__, [NSString stringWithFormat:__VA_ARGS__]); }

__attribute__((visibility("default"))) void ShowContextMenu(double x, double y);

void ShowContextMenu(double x, double y) {
    trace(@"Starting ShowContextMenu with x=%f, y=%f", x, y);

    NSMenu *menu = [[NSMenu alloc] initWithTitle:@"Context Menu"];
    if (!menu) {
        trace(@"Failed to create popup menu");
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
    NSView *view = [[NSApp keyWindow] contentView];
    if (view == nil) {
        trace(@"Failed to get content view");
        return;
    }
    [NSMenu popUpContextMenu:menu withEvent:event forView:view];

    trace(@"Menu displayed");
}

@implementation NSApplication (ContextMenu)

+ (void)menuItemSelected:(NSMenuItem *)item {
    trace(@"Menu item selected: %@", [item title]);
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithFormat:@"%@ Selected", [item title]]];
    [alert runModal];
}

@end
