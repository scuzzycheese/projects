    //
//  standsRootViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/30.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standsButtonsViewController.h"


@implementation standsButtonsViewController

@synthesize node;
@synthesize XMLParser;




- (id)initWithXMLNode:(xmlNode *)inNode
{
	self = [super init];
	[self loopNodes:inNode];
	return self;
}


- (void) loopNodes:(xmlNode *)inNode
{
	buttons = [NSMutableArray array];
	[buttons retain];
	
	xmlNode *tmpNode = inNode;
	while(tmpNode)
	{
		if(tmpNode->type == XML_ELEMENT_NODE)
		{
			
			//TODO: break this into it's own method
			xmlNode *standNodeKids = tmpNode->children;

			NSString *picPath = [self findNodeValue:standNodeKids :@"picture"];
			NSString *standName = [self findNodeValue:standNodeKids :@"name"];
			
			
			NSLog(@"NODE NAME: %@\n", [NSString stringWithCString:tmpNode->name]);
			UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
			
			UIImage	*btnImage = [UIImage imageWithContentsOfFile:[documentsFolderPath stringByAppendingString:picPath]];
			
			[button setBackgroundImage:btnImage forState:UIControlStateNormal];
			
			[button setTitle:standName forState:UIControlStateNormal];			
		
			[buttons addObject:button];
		}
		tmpNode = tmpNode->next;
	}
	
	//scrollView.frame = [self.view bounds];
	
	[self sizeButtonsWidth:200 height:200];
	
	if(self.interfaceOrientation == UIInterfaceOrientationLandscapeLeft || self.interfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
		[self arrangeButtons:4];
	}
	else
	{
		[self arrangeButtons:3];
	}
	
	
	[self showButtons];
	
}

- (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName;
{
	while(inNode)
	{
		if(inNode->type == XML_ELEMENT_NODE && strcmp(inNode->name, [nodeName cString]) == 0)
		{
			break;
		}
		inNode = inNode->next;
	}
	return [NSString stringWithCString:inNode->children->content];
}

- (void) sizeButtonsWidth:(int)width height:(int)height
{	
	int numberButtons = [buttons count];
	for(int i = 0; i < numberButtons; i ++)
	{
		UIButton *button = [buttons objectAtIndex:i];
		button.frame = CGRectMake(0, 0, width, height);
	}
}

- (void) arrangeButtons:(int)width
{
	scrollView.frame = [self.view bounds];
	
	int maxFrameHeight = (scrollView.frame.size.width / width) * (([buttons count] / width) + 1);
	
	//scrollView.frame = CGRectMake(0, 0, scrollView.frame.size.width, maxFrameHeight);
	[scrollView setContentSize:CGSizeMake(scrollView.frame.size.width, maxFrameHeight)];
	
	int numberButtons = [buttons count];
	for(int i = 0; i < numberButtons; i ++)
	{
		int btnWStart = (scrollView.frame.size.width / width) * (i % width);
		int btnHStart = (i / width) * (scrollView.frame.size.width / width);
		int btnCentOffset = (scrollView.frame.size.width / width) / 2;
				
		UIButton *button = [buttons objectAtIndex:i];
		
		//button.frame = CGRectMake(0, 0, 200, 200);
		button.center = CGPointMake(btnWStart + btnCentOffset, btnHStart + btnCentOffset);
	}
}

- (void) showButtons
{
	int numberButtons = [buttons count];
	for(int i = 0; i < numberButtons; i ++)
	{
		UIButton *button = [buttons objectAtIndex:i];
		//[self.view addSubview:button];
		[scrollView addSubview:button];		
	}
}

//- (void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
- (void) didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationDelay:1.0];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
	
	if(self.interfaceOrientation == UIInterfaceOrientationLandscapeLeft || self.interfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
		[self arrangeButtons:4];
	}
	else
	{
		[self arrangeButtons:3];
	}




	
	[UIView commitAnimations];
	
}

- (IBAction) swapViewController:(id)sender
{
	
	UIViewController *testView = [[UIViewController alloc] init];
	
	[self.navigationController pushViewController:testView animated:YES];
	
	[testView release];	
	
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


// Implement loadView to create a view hierarchy programmatically, without using a nib.
/*
- (void)loadView 
{

}
 */



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad 
{
	[super viewDidLoad];
	
	
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	documentsFolderPath = [documentsFolderPath stringByAppendingString:@"/"];
	[documentsFolderPath retain];
	
	
	scrollView = [[UIScrollView alloc] initWithFrame:[self.view bounds]];
	[scrollView setDelegate:self];
	[scrollView setBouncesZoom:YES];
	
	[self.view addSubview:scrollView];
	

 
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
	[buttons release];
	[scrollView release];
}