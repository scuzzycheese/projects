/* browserEventHandler */

#ifndef browserEventHandlerH
#define browserEventHandlerH

#import <Cocoa/Cocoa.h>

@interface browserEventHandler : NSBrowser
{
}

- (void)mouseDown: (NSEvent *)event;

@end
#endif