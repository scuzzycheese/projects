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
	
	xmlNode *tmpNode = inNode;
	while(tmpNode)
	{
		if(tmpNode->type == XML_ELEMENT_NODE)
		{
			
			//TODO: break this into it's own method
			xmlNode *picNode = tmpNode->children;
			while(picNode)
			{
				if(picNode->type == XML_ELEMENT_NODE && strcmp(picNode->name, "picture") == 0)
				{
					break;
				}
				picNode = picNode->next;
			}
			NSString *picPath = [NSString stringWithCString:picNode->children->content];
			
			
			
			NSLog(@"NODE NAME: %@\n", [NSString stringWithCString:tmpNode->name]);
			UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
			
			NSString *wholePicPath = [documentsFolderPath stringByAppendingString:picPath];
			UIImage	*btnImage = [UIImage imageWithContentsOfFile:[documentsFolderPath stringByAppendingString:picPath]];
			
			[button setBackgroundImage:btnImage forState:UIControlStateNormal];
			
			[button setTitle:[NSString stringWithCString:tmpNode->name] forState:UIControlStateNormal];
			
			//Testing button
			button.frame = CGRectMake(10, 10, 100, 100);
			[self.view addSubview:button];
			
			
		
			[buttons addObject:button];
		}
		tmpNode = tmpNode->next;
	}	
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
	
	
	
 
	UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
 
	button.frame = CGRectMake(10, 10, 100, 100);
 
	[self.view addSubview:button];
	

 
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
}


@end
