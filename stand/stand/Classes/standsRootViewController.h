//
//  standsRootViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/30.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "standsNavigationController.h"

@interface standsRootViewController : UIViewController {
	
	
	xmlNode *node;
	XMLParser *XMLParser;

}

- (IBAction) swapViewController:(id)sender;
- (void)launchNavigation;
@property (nonatomic) xmlNode *node;
@property (nonatomic, retain) XMLParser *XMLParser;


@end
