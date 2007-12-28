#import "generalClass.h"

@implementation generalClass

- (IBAction)closeAboutPanel:(id)sender
{
	[aboutPanel orderOut: sender];
}

- (IBAction)openAboutPanel:(id)sender
{
	[aboutPanel orderFront: sender];
}

@end
