//
//  standsViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "standAppDelegate.h"
#include "standsButtonsViewController.h"


@interface standsNavigationController : UINavigationController <UINavigationBarDelegate, UINavigationControllerDelegate>
{	
	XMLParser *XMLParser;	
}

- (IBAction) swapView:(id)sender;

- (void) workerThread;



@property (nonatomic, retain) XMLParser *XMLParser;


@end
