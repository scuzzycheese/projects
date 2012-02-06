    //
//  standsViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standsNavigationController.h"


@implementation standsNavigationController

@synthesize XMLParser;


- (void)awakeFromNib
{
}

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	NSThread *myThread = [[NSThread alloc] initWithTarget:self selector:@selector(workerThread) object:nil];
	[myThread start];

}


- (void) workerThread
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	//NSString *appFolderPath = [[NSBundle mainBundle] resourceURL];
	
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	
	
	updateZipFile = [documentsFolderPath stringByAppendingString:@"/update.zip"];
	//NSLog(@"File to download:%@", fileToDownload);
	
	ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:[NSURL URLWithString:@"http://192.168.0.3/downloads/update.zip"]];
	[request setDownloadDestinationPath:updateZipFile];
	[request setDelegate:self];
	[request startAsynchronous];
	
	while(1)
	{
		/*
		 UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"No network connection" 
		 message:@"You must be connected to the internet to use this app." 
		 delegate:nil 
		 cancelButtonTitle:@"OK"
		 otherButtonTitles:nil];
		 [alert show];
		 [alert release];
		 */
		
		sleep(10);
	}
	[pool release];
}

- (void)requestFinished:(ASIHTTPRequest *)request
{
	NSLog(@"Successfully downloaded the update file.\n");
	
	ZipArchive *ziper = [[ZipArchive alloc] init];
	
	[ziper UnzipOpenFile:updateZipFile];
	[ziper UnzipFileTo:documentsFolderPath overWrite:YES];
	
	[ziper release];
	
	NSString *standsXMLFile = [documentsFolderPath stringByAppendingString:@"/stands.xml"];
	
	self.XMLParser = [[XMLParser alloc] initWithFilename:standsXMLFile];
	
	
	standsRootViewController *rootVC = [self.viewControllers objectAtIndex:0];
	[rootVC setXMLParser:self.XMLParser];
	[rootVC launchNavigation];
	
}

- (void)requestFailed:(ASIHTTPRequest *)request
{
	NSError *error = [request error];
	NSLog(@"Failed to download the update file: %@\n", [error description]);
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Download failed" 
													message:[error localizedDescription]
												   delegate:nil 
										  cancelButtonTitle:@"OK"
										  otherButtonTitles:nil];
	[alert show];
	[alert release];
}


//Have to test this still
- (void)ErrorMessage:(NSString *)msg
{
	NSLog(@"Error unziping file: %@\n", msg);
}




- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (IBAction) swapView:(id)sender
{ 

	
	
	
	
	
	
	
}


- (void)dealloc {
    [super dealloc];
}


@end
