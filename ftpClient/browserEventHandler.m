#import "browserEventHandler.h"

@implementation browserEventHandler


- (void)awakeFromNib
{
	printf("Registering drag types\n");
	[self registerForDraggedTypes: [NSArray arrayWithObject: NSFilenamesPboardType]];
}


- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
	printf("prepair for drag\n");
	return TRUE;
}


- (void)mouseDown: (NSEvent *)event
{
	printf("mouse down event\n");
}

- (void)mouseUp: (NSEvent *)event
{
	printf("mouse up event\n");
}

- (void)mouseDragged: (NSEvent *)event
{

	printf("mouse drag event\n");

	NSImage *dragImage;
	NSPoint dragPosition;

	NSString *fileOne = [NSString stringWithString: @"/Users/scuzzy/Desktop/reverseorderLogo.tga"];
	NSString *fileTwo = [NSString stringWithString: @"/Users/scuzzy/Desktop/reverseorderLogo.tga"];
 
    // Write data to the pasteboard
	NSArray *fileList = [NSArray arrayWithObjects: fileOne, fileTwo, NULL];
    NSPasteboard *pboard = [NSPasteboard pasteboardWithName:NSDragPboard];
    [pboard declareTypes:[NSArray arrayWithObject:NSFilenamesPboardType] owner:nil];
    [pboard setPropertyList:fileList forType:NSFilenamesPboardType];
 
    // Start the drag operation
    dragImage = [[NSWorkspace sharedWorkspace] iconForFile:fileOne];
    dragPosition = [self convertPoint:[event locationInWindow] fromView:NULL];
    dragPosition.x -= 16;
    dragPosition.y -= 16;
    [self
		dragImage:dragImage
		at:dragPosition
		offset:NSZeroSize
        event:event
        pasteboard:pboard
        source:self
        slideBack:TRUE
	];
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{

	printf("I got drag operation\n");

    NSPasteboard *pboard = [sender draggingPasteboard];
 
    if([[pboard types] containsObject: NSFilenamesPboardType])
	{
        NSArray *files = [pboard propertyListForType: NSFilenamesPboardType];
        int numberOfFiles = [files count];
		
	
		
        // Perform operation using the list of files
    }
    return YES;
}

@end
