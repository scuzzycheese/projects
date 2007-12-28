/* generalClass */

#import <Cocoa/Cocoa.h>

@interface generalClass : NSObject
{
    IBOutlet NSPanel *aboutPanel;
}
- (IBAction)closeAboutPanel:(id)sender;
- (IBAction)openAboutPanel:(id)sender;
@end
