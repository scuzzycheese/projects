    //
//  standsViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standsViewController.h"


@implementation standsViewController


- (void)awakeFromNib
{
	UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	//[button addTarget:self action:@selector(aMethod:) forControlEvents:UIControlEventTouchDown];
	[button setTitle:@"Show View" forState:UIControlStateNormal];
	button.frame = CGRectMake(80.0, 210.0, 160.0, 40.0);
	[self.view addSubview:button];
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

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/


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
}


@end
