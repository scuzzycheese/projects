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


/*
- (void)awakeFromNib
{
}
 */

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
	
	/*
	
	UIActivityIndicatorView *busyIndicator = [[UIActivityIndicatorView alloc] init];
	busyIndicator.frame = CGRectMake(10, 10, 100, 100);
	
	[[self.viewControllers objectAtIndex:0] addSubview:busyIndicator];
	

	[busyIndicator release];	
	
	*/
	
	

}


- (void) workerThread
{
	
	standAppDelegate *appDel = [UIApplication sharedApplication].delegate;
	while(!appDel.XMLParser)
	{
		NSLog(@"Waiting for the XML Parser to exist...\n");
		sleep(1);
	}
	
	self.XMLParser = appDel.XMLParser;
	if([self.XMLParser dataAvailable])
	{
		NSLog(@"XML Data is parsed...\n");
	}
	
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
