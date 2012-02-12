//
//  FirstViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "ThreeDCapeViewController.h"


@implementation ThreeDCapeViewController

@synthesize threeDCapeWebView;


- (void)awakeFromNib
{
	[threeDCapeWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://www.3dcape.co.za"]]];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
/*
- (void)viewDidLoad {
    [super viewDidLoad];
	
	[webViewer loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://www.3dcape.co.za"]]];
}
*/

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (IBAction) webGoHome:(id)sender
{
	[threeDCapeWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://www.3dcape.co.za"]]];
}

- (void)dealloc {
    [super dealloc];
	[threeDCapeWebView release];
}

@end
