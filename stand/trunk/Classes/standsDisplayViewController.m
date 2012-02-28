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

	//We want to keep a reference to the node
	self.node = inNode;
	
	//Again a nasty hack
	if(self.interfaceOrientation == UIInterfaceOrientationLandscapeLeft || self.interfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
		self.view.frame = CGRectMake(0, 0, 1024, 655);
	}
	else
	{
		self.view.frame = CGRectMake(0, 0, 768, 914);
	}
	//[newStandVC.view setAutoresizingMask:(UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight)];
	
	[self loopNodes:inNode];
	
	return self;
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	NSLog(@"Loaded new View\n");
	
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
	
	[self.view setBackgroundColor:[UIColor blackColor]];
	
	
	orderForm = [[orderViewController alloc] initWithNibName:@"orderForm" bundle:nil];
	[orderForm setStandsController:self];
	[orderForm retain];
	 

	/*
	//NOTE: Trying this below to inject objects into object placeholders in the nib
	orderForm = [[orderViewController alloc] init];
	NSDictionary *proxyDict = [NSDictionary dictionaryWithObject:self forKey:@"standsDisplayController"];
	NSDictionary *optionsDict = [NSDictionary dictionaryWithObject:proxyDict forKey:UINibExternalObjects];
	[[NSBundle mainBundle] loadNibNamed:@"orderForm" owner:orderForm options:optionsDict];
	 */
	
}

- (void)addLeftRightButtonsToView:(UIView *)view
{
	[view addSubview:leftButton];
	[view bringSubviewToFront:leftButton];
	[view addSubview:rightButton];
	[view bringSubviewToFront:rightButton];
	
	[view addSubview:orderButton];
	[view bringSubviewToFront:orderButton];
	
	[view setUserInteractionEnabled:YES];
}

- (void)removeLeftRightButtonsFromCurrentView
{
	[leftButton removeFromSuperview];
	[rightButton removeFromSuperview];
	[orderButton removeFromSuperview];
}

- (void)handleSwipeRight
{
	currentViewIndex ++;
	if(currentViewIndex >= [pictureViews count])
	{
		currentViewIndex = 0;
	}
	
	[self slideSwapView:[pictureViews objectAtIndex:currentViewIndex] direction:1];
	
	NSLog(@"Swipe Right\n");
}
- (void)buttonSwipeRight:(id)sender
{
	[self handleSwipeRight];
}

- (void)handleSwipeLeft
{
	currentViewIndex --;
	if(currentViewIndex < 0)
	{
		currentViewIndex = [pictureViews count] - 1;
	}
	
	[self slideSwapView:[pictureViews objectAtIndex:currentViewIndex] direction:2];
	
	NSLog(@"Swipe Left\n");	
}
- (void)buttonSwipeLeft:(id)sender
{
	[self handleSwipeLeft];
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
	[self removeLeftRightButtonsFromCurrentView];
	[self addLeftRightButtonsToView:newView];
	
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

- (void)orderButtonPressed:(id)sender
{	
	NSLog(@"Order button pressed\n");
	[orderForm resetForm];
	[self flipView:orderForm.view direction:UIViewAnimationOptionTransitionFlipFromRight];
	//I don't know why this works, but loading the image after the flip seems to do the trick
	[orderForm.standPicture setImage:[[pictureViews objectAtIndex:currentViewIndex] image]];
}

- (void)returnToDefaultView
{
	NSLog(@"Default View Called\n");
	[self flipView:[pictureViews objectAtIndex:currentViewIndex] direction:UIViewAnimationOptionTransitionFlipFromLeft];
}


- (void) loopNodes:(xmlNode *)inNode
{
	
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	documentsFolderPath = [documentsFolderPath stringByAppendingString:@"/"];
	[documentsFolderPath retain];

	UIImage *leftButtonImage = [[UIImage imageNamed:@"left_arrow"] stretchableImageWithLeftCapWidth:100 topCapHeight:90];
	UIImage *rightButtonImage = [[UIImage imageNamed:@"right_arrow"] stretchableImageWithLeftCapWidth:100 topCapHeight:90];
	
	rightButton = [UIButton buttonWithType:UIButtonTypeCustom];
	[rightButton addTarget:self action:@selector(buttonSwipeRight:) forControlEvents:UIControlEventTouchUpInside];
	rightButton.frame = CGRectMake(self.view.frame.size.width - 100, 0, 100, self.view.frame.size.height);
	[rightButton setImage:rightButtonImage forState:UIControlStateNormal];
	[rightButton setContentMode:UIViewContentModeCenter];
	[rightButton retain];
	
	leftButton = [UIButton buttonWithType:UIButtonTypeCustom];
	[leftButton addTarget:self action:@selector(buttonSwipeLeft:) forControlEvents:UIControlEventTouchUpInside];
	leftButton.frame = CGRectMake(0, 0, 100, self.view.frame.size.height);
	[leftButton setImage:leftButtonImage forState:UIControlStateNormal];
	[leftButton setContentMode:UIViewContentModeCenter];
	[leftButton retain];
	
	
	//BUSI adding this button to swap to the order form
	orderButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[orderButton addTarget:self action:@selector(orderButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
	orderButton.frame = CGRectMake(100, self.view.frame.size.height - 35, 100, 35);
	[orderButton setTitle:@"Order" forState:UIControlStateNormal];
	[orderButton retain];
	

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
			
			if(image != nil)
			{
				UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
				[imageView setBackgroundColor:[UIColor blackColor]];
			
				[pictureViews addObject: imageView];
			
				[imageView release];
			}
			else
			{
				NSLog(@"Could not load image: %@\n", picturePath);
			}

		}


		picturesNode = picturesNode->next;
	}
	[self addLeftRightButtonsToView:[pictureViews objectAtIndex:0]];
	[self.view addSubview:[pictureViews objectAtIndex:0]];
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
	[orderForm release];
	
	///NOTE: I think these get released automatically, but I need to double check
	//I get an error when I release them
	//[rightButton release];
	//[leftButton release];
}


@end
