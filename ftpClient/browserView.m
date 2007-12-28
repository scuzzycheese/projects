#import "browserView.h"
#include <sys/types.h>
#include <sys/stat.h>

@implementation browserView

- (IBAction)browse:(id)sender
{	
	/*browse button actuator*/
}



- (IBAction)singleClick:(id)sender
{	
	NSBrowserCell *cell = [sender selectedCell];
	int lastCol = [sender lastColumn];
	char *path;
	asprintf(&path, "%s/%s", [[self fsPathCol: lastCol] UTF8String], [[cell stringValue] UTF8String]);
	NSString *nsPath = [[NSString alloc] initWithCString: path];
	[nsPath autorelease];
	free(path);
	NSDictionary *fileAttr = [fileManager fileAttributesAtPath: nsPath traverseLink: TRUE];
	
	if([[fileAttr fileType] UTF8String] && [[fileAttr fileType] compare: NSFileTypeRegular] == NSOrderedSame)
	{
		char *data;
		asprintf(&data, "SIZE: %llu\nNAME: %s\n", [fileAttr fileSize], [[cell stringValue] UTF8String]);
		[fileInfo setStringValue: [NSString stringWithCString: data]];
		free(data);
		[cell setLeaf: TRUE];
		
	    NSImage *imageForFile = [[NSWorkspace sharedWorkspace] iconForFile: nsPath];
		NSSize imageSize = [imageForFile size];
		imageSize.width = imageSize.width * 2.5;
		imageSize.height = imageSize.height * 2.5;
		[imageForFile setSize: imageSize];
		[fileImage setImage: imageForFile];
	}
}

- (void)init
{
	dirHolder = NULL;
	fileList = NULL;
}

- (void)awakeFromNib
{
	fileManager = [NSFileManager defaultManager];
	
	/*since this is a custom view, set it's min column width*/
	[myFiles setMinColumnWidth: (float)150];
	
	/*we want horizontal scrollers*/
	[myFiles setHasHorizontalScroller: TRUE];
	
	/*set selection options, make sure we can select more than one and branches*/
	[myFiles setAllowsMultipleSelection: TRUE];
	//[myFiles setAllowsBranchSelection: TRUE];
}


- (NSString *)fsPathCol:(int)column
{
    NSString *filePath = NULL;
    if(column == 0) filePath = [NSString stringWithCString: "/"];
    else filePath = [myFiles pathToColumn: column];
    return filePath;
}

/*use lazy initialization, since we don't want to touch the file system too much*/
- (int)browser:(NSBrowser *)sender numberOfRowsInColumn:(int)column
{
	/*this seems to me to be a better way to do this*/
	NSArray *tempArray = [fileManager directoryContentsAtPath: [self fsPathCol: column]];
	
	NSDictionary *fileAttr = [fileManager fileAttributesAtPath: [self fsPathCol: column] traverseLink: TRUE];
	if([[fileAttr fileType] compare: NSFileTypeRegular] == NSOrderedSame)
	{
		return 0;
	}
	else if([[fileAttr fileType] compare: NSFileTypeDirectory] == NSOrderedSame)
	{
		return [tempArray count];
	}
	else return 0;
}



- (void)browser:(NSBrowser *)sender willDisplayCell:(id)cell atRow:(int)row column:(int)column
{	

	NSDictionary *fileAttr = [fileManager fileAttributesAtPath: [self fsPathCol: column] traverseLink: TRUE];
	if([[fileAttr fileType] compare: NSFileTypeRegular] == NSOrderedSame)
	{
		/*I need something here to make it work apparently*/
	}
	else if([[fileAttr fileType] compare: NSFileTypeDirectory] == NSOrderedSame)
	{
		if(row == 0 || strcmp(dirHolder, [[self fsPathCol: column] UTF8String]) != 0 || !fileList)
		{
			if(fileList) [fileList release];
			NSArray *tmpArray = [fileManager directoryContentsAtPath: [self fsPathCol: column]];
			fileList = [[NSArray alloc] initWithArray: tmpArray copyItems: YES];
			free(dirHolder);
			dirHolder = malloc(strlen([[self fsPathCol: column] UTF8String]) + 1);
			memcpy(dirHolder, [[self fsPathCol: column] UTF8String], strlen([[self fsPathCol: column] UTF8String]) + 1);
		}
		NSString *fileName = [fileList objectAtIndex: row];
		
		char *data;
		asprintf(&data, "%s/%s", [[self fsPathCol: column] UTF8String], [fileName UTF8String]);
		
		NSDictionary *intFileAttr = [fileManager fileAttributesAtPath: [NSString stringWithCString: data] traverseLink: TRUE];
		if([[intFileAttr fileType] compare: NSFileTypeDirectory] != NSOrderedSame)
		{
			[cell setLeaf: TRUE];
		}
		/*set the title of our frame*/
		[cell setTitle: fileName];
	}
	
}


@end
