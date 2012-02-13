    //
//  standsRootViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/30.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standsButtonsViewController.h"
#include <string.h>
#include "standsDisplayViewController.h"


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
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	documentsFolderPath = [documentsFolderPath stringByAppendingString:@"/"];
	[documentsFolderPath retain];
	
	buttons = [NSMutableArray array];
	[buttons retain];
	
	xmlNode *tmpNode = inNode->children;
	while(tmpNode)
	{
		if(tmpNode->type == XML_ELEMENT_NODE && strcmp(tmpNode->name, "stands") == 0)
		{
			xmlNode *standsNodeKid = tmpNode->children;

			NSString *picPath = [self findNodeValue:standsNodeKid :@"picture"];
			NSString *standName = [self findNodeValue:standsNodeKid :@"name"];
			
			
			NSLog(@"NODE NAME: %@\n", [NSString stringWithCString:tmpNode->name encoding:NSUTF8StringEncoding]);
			UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
			
			[button setNode:tmpNode];
			[button addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
			
			UIImage	*btnImage = [UIImage imageWithContentsOfFile:[documentsFolderPath stringByAppendingString:picPath]];
			
			[button setBackgroundImage:btnImage forState:UIControlStateNormal];
			
			[button setTitle:standName forState:UIControlStateNormal];			
		
			[buttons addObject:button];
		}
		if(tmpNode->type == XML_ELEMENT_NODE && strcmp(tmpNode->name, "stand") == 0)
		{
			xmlNode *standNodeKid = tmpNode->children;
			NSString *standName = [self findNodeValue:standNodeKid :@"name"];
			NSString *picPath = NULL;
			
			while(standNodeKid)
			{
				if(standNodeKid->type == XML_ELEMENT_NODE && strcmp(standNodeKid->name, "pictures") == 0)
				{
					picPath = [self findNodeValue:standNodeKid->children :@"picture"];
				}
				standNodeKid = standNodeKid->next;
			}
			
			
			NSLog(@"NODE NAME: %@\n", [NSString stringWithCString:tmpNode->name encoding:NSUTF8StringEncoding]);
			NSLog(@"PIC PATH: %@\n", [documentsFolderPath stringByAppendingString:picPath]);
			UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
			[button setNode:tmpNode];
			[button addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];

			
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

- (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName
{
	while(inNode)
	{
		if(inNode->type == XML_ELEMENT_NODE && strcmp(inNode->name, [nodeName UTF8String]) == 0)
		{
			break;
		}
		inNode = inNode->next;
	}
	return [NSString stringWithCString:inNode->children->content encoding:NSUTF8StringEncoding];
}

- (xmlNode *) findNode:(xmlNode *)inNode :(NSString *)nodeName
{
	while(inNode)
	{
		if(inNode->type == XML_ELEMENT_NODE && strcmp(inNode->name, [nodeName UTF8String]) == 0)
		{
			break;
		}
		inNode = inNode->next;
	}
	return inNode;
}




- (void) buttonPressed:(id)sender
{
	UIButton *button = (UIButton *)sender;
	NSLog(@"button pressed\n");
	
	xmlNode *buttonNode = [button node];
	
	if(buttonNode->type == XML_ELEMENT_NODE && strcmp(buttonNode->name, "stands") == 0)
	{
		standsButtonsViewController *newStandsMenu = [[standsButtonsViewController alloc] initWithXMLNode:buttonNode];
		
		NSString *itemName = [self findNodeValue:buttonNode->children :@"name"];
		
		[newStandsMenu setTitle:itemName];
		
		[self.navigationController pushViewController:newStandsMenu animated:YES];
		
		[newStandsMenu release];	
		
	}
	if(buttonNode->type == XML_ELEMENT_NODE && strcmp(buttonNode->name, "stand") == 0)
	{
		standsDisplayViewController *newStandVC = [[standsDisplayViewController alloc] initWithXMLNode:buttonNode];
		
		NSString *itemName = [self findNodeValue:buttonNode->children :@"name"];
		
		[newStandVC setTitle:itemName];
		
		[self.navigationController pushViewController:newStandVC animated:YES];
		
		[newStandVC release];	
		
	}
	
	
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
	//Set the scroll frame to the same size as the view frame
	scrollView.frame = [self.view bounds];
	
	//work out how long we need the scroll to scroll to
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

@end