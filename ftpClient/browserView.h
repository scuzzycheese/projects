/* browserView */

#import <Cocoa/Cocoa.h>
#include <stdio.h>
#include "browserEventHandler.h"


@interface browserView : NSObject
{
    IBOutlet NSImageView *fileImage;
    IBOutlet NSTextField *fileInfo;
    IBOutlet browserEventHandler *myFiles;
    IBOutlet browserEventHandler *remoteFiles;
	
	NSFileManager *fileManager;
	NSArray *fileList;
	
	char *dirHolder;
	

	
}
- (NSString *)fsPathCol:(int)column;
- (IBAction)browse:(id)sender;
- (IBAction)singleClick:(id)sender;
- (void)init;
@end
