    //
//  demoViewController.m
//  stand
//
//  Created by scuzzy on 2012/03/02.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "demoViewController.h"
#include "standAppDelegate.h"


@implementation demoViewController

@synthesize currentStand;
@synthesize toolBarButton;
@synthesize demoView;

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
	
	//NOTE: This may not need to be a thread, we'll see
	[NSThread detachNewThreadSelector:@selector(workerThread) toTarget:self withObject:nil];
	/*
	NSThread *myThread = [[NSThread alloc] initWithTarget:self selector:@selector(workerThread) object:nil];
	[myThread start];
	*/
	 
	nodeIndex = 0;
	timer = [NSTimer scheduledTimerWithTimeInterval:5 target:self selector:@selector(timerChange) userInfo:nil repeats:YES];
	[timer fire];
	
	[self.demoView setBackgroundColor:[UIColor blackColor]];
}



- (void) workerThread
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	standAppDelegate *appDel = (standAppDelegate *)[UIApplication sharedApplication].delegate;
	while(!appDel.XMLParser)
	{
		NSLog(@"DEMO - Waiting for the XML Parser to exist...\n");
		sleep(1);
	}
	
	//TODO: Add some validation into the XML parser perhapse?
	XMLParser *XMLParser = appDel.XMLParser;
	while(![XMLParser dataAvailable])
	{
		NSLog(@"DEMO - waiting for XML Data to parse...\n");
		sleep(1);
	}
	NSLog(@"DEMO - XML Data is finished parsing!\n");
	
	xmlXPathContextPtr contextPtr = xmlXPathNewContext(XMLParser.dom);
	standNodes = [self findXmlNodes:contextPtr with:"//stand"];
	xmlXPathFreeContext(contextPtr);
	[self swapToViewAtIndex:0];
	
	[pool release];
}


- (void) timerChange
{
	if(standNodes)
	{
		[self flipCurrentViewPage];
		if(currentDemoViewController.currentViewIndex == 0)
		{
			nodeIndex ++;
			if(nodeIndex >= standNodes->nodeNr) nodeIndex = 0; 	
			[self swapToViewAtIndex:nodeIndex];
		}
	}
}
		
- (void) swapToViewAtIndex:(int)index
{
	
	currentDemoViewController = [[standsDisplayViewController alloc] initWithXMLNode:standNodes->nodeTab[index]];
	[currentDemoViewController.view setBackgroundColor:[UIColor blackColor]];
	
	//install the notifiers
	[currentDemoViewController notifyCancel:self withSelector:@selector(notifyTimerRestart)];
	[currentDemoViewController notifyEmailSent:self withSelector:@selector(notifyTimerRestart)];
	
	NSString *itemName = [XMLParser findNodeValue:standNodes->nodeTab[index]->children :@"name"];
	
	[currentDemoViewController setTitle:itemName];
	
	[self.toolBarButton setTitle:itemName];
	
	//Delete the old view
	if([self.demoView subviews])
	{
		for(int i = 0; i < [[self.demoView subviews] count]; ++ i)
		{
			[[[self.demoView subviews] objectAtIndex:i] removeFromSuperview];
		}
	}
		
	[self.demoView addSubview:currentDemoViewController.view];
	
	//We want to stall the timer when this button is pressed
	[currentDemoViewController.orderButton addTarget:self action:@selector(handleOrderButton) forControlEvents:UIControlEventTouchUpInside];
	
	[currentDemoViewController release];
}

- (IBAction) handleOrderButton
{	
	NSLog(@"order button pressed in demo context\n");
	//Stop the timer
	[timer setFireDate:[NSDate dateWithTimeIntervalSinceNow:60]];
	NSLog(@"Timer paused\n");
}

- (void)notifyTimerRestart
{
	[timer setFireDate:[NSDate dateWithTimeIntervalSinceNow:5]];
	NSLog(@"Timer restart notified\n");
}
	   
- (void) flipCurrentViewPage
{
	[currentDemoViewController handleSwipeLeft];
}

- (xmlNode *)findXmlNodes:(xmlXPathContextPtr)context with:(char *)expression
{
	if(xpathObj)
	{
		xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
	}
	xpathObj = xmlXPathEvalExpression(expression, context);
	return xpathObj->nodesetval;
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


- (void)dealloc {
    [super dealloc];
	if(xpathObj)
	{
		xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
	}
}


@end
