    //
//  standsDisplayViewController.m
//  stand
//
//  Created by scuzzy on 2012/02/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standsDisplayViewController.h"


@implementation standsDisplayViewController

@synthesize node;
@synthesize XMLParser;

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

- (id)initWithXMLNode:(xmlNode *)inNode
{
	self = [super init];
	[self loopNodes:inNode];
	return self;
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	UISwipeGestureRecognizer *swipeRight = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeRight)];
	swipeRight.numberOfTouchesRequired = 1;
	swipeRight.direction = UISwipeGestureRecognizerDirectionRight;

	UISwipeGestureRecognizer *swipeLeft = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeLeft)];
	swipeLeft.numberOfTouchesRequired = 1;
	swipeLeft.direction = UISwipeGestureRecognizerDirectionLeft;
	
	[self.view addGestureRecognizer:swipeRight];
	[self.view addGestureRecognizer:swipeLeft];

	[swipeRight release];
	[swipeLeft release];
}


- (void)handleSwipeRight
{
	currentViewIndex ++;
	if(currentViewIndex >= [pictureViews count])
	{
		currentViewIndex = 0;
	}
	
	//[self flipView:[pictureViews objectAtIndex:currentViewIndex] direction:UIViewAnimationOptionTransitionFlipFromLeft];
	[self slideSwapView:[pictureViews objectAtIndex:currentViewIndex] direction:1];
	
	NSLog(@"Swipe Right\n");
}

- (void)handleSwipeLeft
{
	currentViewIndex --;
	if(currentViewIndex < 0)
	{
		currentViewIndex = [pictureViews count] - 1;
	}
	
	//[self flipView:[pictureViews objectAtIndex:currentViewIndex] direction:UIViewAnimationOptionTransitionFlipFromRight];
	[self slideSwapView:[pictureViews objectAtIndex:currentViewIndex] direction:2];
	
	NSLog(@"Swipe Left\n");	
}

/*
- (void)swapViewSlide
{
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:1.0];
	[UIView setAnimationTransition:UIViewAnimationTransitionFl ipFromLeft forView:window cache:YES];
	
	[[mainScreenController view] removeFromSuperview];
	[window addSubview:[myNextScreenController view]];
	[UIView commitAnimations];
}
 */


- (void)slideSwapView:(UIView *)newView direction:(NSInteger)dir
{
	UIView *tempContainer = self.view;

	UIView *topSubView = [[tempContainer subviews] objectAtIndex:0];
	if(topSubView)
	{
		[topSubView removeFromSuperview]; 
	}
	[tempContainer addSubview:newView];

	CATransition *animation = [CATransition animation];
	[animation setDuration:0.5];
	[animation setType:kCATransitionPush];
	if(dir == 1) [animation setSubtype:kCATransitionFromLeft];
	else [animation setSubtype:kCATransitionFromRight];
	[animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];
	
	[[[self.view superview] layer] addAnimation:animation forKey:@"SwitchToView1"];
}

- (void)flipView:(UIView *)newView direction:(NSInteger)dir
{
	
	UIView *tempContainer = self.view;
	

	[UIView transitionWithView:tempContainer
			duration:1
			options:dir
			animations:^
			{
				UIView *topSubView = [[tempContainer subviews] objectAtIndex:0];
				if(topSubView)
				{
					[topSubView removeFromSuperview]; 
				}
				[tempContainer addSubview:newView];
				//CGAffineTransform transform = CGAffineTransformMakeScale(4.0, 4.0);
				//tempContainer.transform = transform;
			} 
			completion:^(BOOL finished)
			{
				//[tempContainer release]; 
			}
	 ];
	
}


- (void) loopNodes:(xmlNode *)inNode
{
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	documentsFolderPath = [documentsFolderPath stringByAppendingString:@"/"];
	[documentsFolderPath retain];

	
	pictureViews = [NSMutableArray array];
	[pictureViews retain];
	
	
	xmlNode *tmpNode = inNode->children;
	xmlNode *picturesNode = [self findNode:tmpNode :@"pictures"]->children;
	while(picturesNode)
	{
		if(picturesNode->type == XML_ELEMENT_NODE && strcmp(picturesNode->name, "picture") == 0)
		{
			NSString *picturePath = [NSString stringWithCString:picturesNode->children->content encoding:NSUTF8StringEncoding];
			UIImage	*image = [UIImage imageWithContentsOfFile:[documentsFolderPath stringByAppendingString:picturePath]];
			
			UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
			
			[pictureViews addObject: imageView];
			
			//[self.view addSubview:imageView];
									
			
			[imageView release];
			
			//This break is just for testing, we actually have to load all the pictures into separate views
			//break;
		}
		picturesNode = picturesNode->next;
	}
	[self.view addSubview:[pictureViews objectAtIndex:0]];
	//[self swapViewAt:0];
	
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
	[pictureViews release];
}


@end
