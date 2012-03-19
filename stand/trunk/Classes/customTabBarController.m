//
//  customTabBarController.m
//  stand
//
//  Created by scuzzy on 2012/03/15.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "customTabBarController.h"


@implementation customTabBarController

@synthesize threeDCapeSite;
@synthesize navigation;
@synthesize demo;
@synthesize CTICCSite;


- (void)viewDidAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
	
	[self hideTabBar];
	[self addCustomButtons];
}

- (void)hideTabBar
{
	for(UIView *view in self.view.subviews)
	{
		if([view isKindOfClass:[UITabBar class]])
		{
			view.hidden = YES;
			break;
		}
	}
}

- (void)addCustomButtons
{
	// Initialise our two images
	UIImage *btnImage = [UIImage imageNamed:@"NavBar_01.png"];
	UIImage *btnImageSelected = [UIImage imageNamed:@"NavBar_01_s.png"];
	
	self.threeDCapeSite = [UIButton buttonWithType:UIButtonTypeCustom]; //Setup the button
	threeDCapeSite.frame = CGRectMake(0, 430, 80, 50); // Set the frame (size and position) of the button)
	[threeDCapeSite setBackgroundImage:btnImage forState:UIControlStateNormal]; // Set the image for the normal state of the button
	[threeDCapeSite setBackgroundImage:btnImageSelected forState:UIControlStateSelected]; // Set the image for the selected state of the button
	[threeDCapeSite setTag:1000]; // Assign the button a "tag" so when our "click" event is called we know which button was pressed.
	[threeDCapeSite setSelected:true]; // Set this button as selected (we will select the others to false as we only want Tab 1 to be selected initially
	
	// Now we repeat the process for the other buttons
	btnImage = [UIImage imageNamed:@"NavBar_02.png"];
	btnImageSelected = [UIImage imageNamed:@"NavBar_02_s.png"];
	
	self.navigation = [UIButton buttonWithType:UIButtonTypeCustom];
	navigation.frame = CGRectMake(80, 430, 80, 50);
	[navigation setBackgroundImage:btnImage forState:UIControlStateNormal];
	[navigation setBackgroundImage:btnImageSelected forState:UIControlStateSelected];
	[navigation setTag:1001];
	
	btnImage = [UIImage imageNamed:@"NavBar_03.png"];
	btnImageSelected = [UIImage imageNamed:@"NavBar_03_s.png"];
	
	self.demo = [UIButton buttonWithType:UIButtonTypeCustom];
	demo.frame = CGRectMake(160, 430, 80, 50);
	[demo setBackgroundImage:btnImage forState:UIControlStateNormal];
	[demo setBackgroundImage:btnImageSelected forState:UIControlStateSelected];
	[demo setTag:1002];
	
	btnImage = [UIImage imageNamed:@"NavBar_04.png"];
	btnImageSelected = [UIImage imageNamed:@"NavBar_04_s.png"];
	
	self.CTICCSite = [UIButton buttonWithType:UIButtonTypeCustom];
	CTICCSite.frame = CGRectMake(240, 430, 80, 50);
	[CTICCSite setBackgroundImage:btnImage forState:UIControlStateNormal];
	[CTICCSite setBackgroundImage:btnImageSelected forState:UIControlStateSelected];
	[CTICCSite setTag:1003];
	
	// Add my new buttons to the view
	[self.view addSubview:threeDCapeSite];
	[self.view addSubview:navigation];
	[self.view addSubview:demo];
	[self.view addSubview:CTICCSite];
	
	// Setup event handlers so that the buttonClicked method will respond to the touch up inside event.
	[threeDCapeSite addTarget:self action:@selector(tabPressed:) forControlEvents:UIControlEventTouchUpInside];
	[navigation addTarget:self action:@selector(tabPressed:) forControlEvents:UIControlEventTouchUpInside];
	[demo addTarget:self action:@selector(tabPressed:) forControlEvents:UIControlEventTouchUpInside];
	[CTICCSite addTarget:self action:@selector(tabPressed:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)selectTab:(int)tabNumber
{
	switch(tabNumber)
	{
		case 1000:
			[threeDCapeSite setSelected:true];
			[navigation setSelected:false];
			[demo setSelected:false];
			[CTICCSite setSelected:false];
			break;
		case 1001:
			[threeDCapeSite setSelected:false];
			[navigation setSelected:true];
			[demo setSelected:false];
			[CTICCSite setSelected:false];
			break;
		case 1002:
			[threeDCapeSite setSelected:false];
			[navigation setSelected:false];
			[demo setSelected:true];
			[CTICCSite setSelected:false];
			break;
		case 1003:
			[threeDCapeSite setSelected:false];
			[navigation setSelected:false];
			[demo setSelected:false];
			[CTICCSite setSelected:true];
			break;
	}	
	
	self.selectedIndex = tabNumber;
}


- (void)tabPressed:(id)sender
{
	int tagNum = [sender tag];
	[self selectTab:tagNum];
}

- (void)hideNewTabBar
{
	self.threeDCapeSite.hidden = 1;
    self.navigation.hidden = 1;
    self.demo.hidden = 1;
    self.CTICCSite.hidden = 1;
}

- (void)showNewTabBar
{
	self.threeDCapeSite.hidden = 0;
    self.navigation.hidden = 0;
    self.demo.hidden = 0;
    self.CTICCSite.hidden = 0;
}

- (void)dealloc {
	[threeDCapeSite release];
	[navigation release];
	[demo release];
	[CTICCSite release];
	
    [super dealloc];
}

@end
