    //
//  orderViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/25.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "orderViewController.h"
#include "standsDisplayViewController.h"


@implementation orderViewController
@synthesize standPicture;
@synthesize standsController;

@synthesize emailAddress;
@synthesize name;
@synthesize cellphoneNumber;
@synthesize workNumber;

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self)
	{
		smtp = [[SMTP alloc] init];
    }
    return self;
}
 


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


- (IBAction)orderCancelButtonPressed:(id)sender
{
	[self.standsController returnToDefaultView];
}

- (IBAction)sendEmailButtonPressed:(id)sender
{
	NSLog(@"Attempting to send e-mail\n");
	[smtp openSocketTo:@"relay.mweb.co.za" port:25];
	[smtp setFromAddress:@"iPad <scuzzy@mweb.co.za>"];
	[smtp sendEmailTo:@"scuzzy@reverseorder.net" subject:@"moo" contents:@"test"];
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
	[smtp release];
	//[standPicture release];
}


@end
