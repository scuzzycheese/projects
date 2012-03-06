//
//  demoViewController.h
//  stand
//
//  Created by scuzzy on 2012/03/02.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "standsDisplayViewController.h"


@interface demoViewController : UIViewController
{

	standsDisplayViewController *currentStand;
	IBOutlet UIBarButtonItem *toolBarButton;
	xmlNodeSet *standNodes;
	IBOutlet UIView *demoView;
	standsDisplayViewController *currentDemoViewController;
	
	NSTimer *timer;
	int nodeIndex;
	
}
@property (nonatomic, retain) standsDisplayViewController *currentStand;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *toolBarButton;
@property (nonatomic, retain) IBOutlet UIView *demoView;


- (void) workerThread;
- (xmlNode *)findXmlNodes:(xmlXPathContextPtr)context with:(char *)expression;
- (void) timerChange;
- (void) swapToViewAtIndex:(int)index;
- (void) flipCurrentViewPage;
- (IBAction) handleOrderButton;
- (void)notifyTimerRestart;


@end
