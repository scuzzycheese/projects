//
//  myUI.m
//  stand
//
//  Created by scuzzy on 2012/03/13.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "myUI.h"


@implementation myUI

@synthesize tabBarController;

- (void)sendEvent:(UIEvent *)event
{
	//We need to see when someone interacts with the system
	if(event.type == UIEventTypeTouches)
	{
		if(timer)
		{
			//Reset the timer if a user interacts with the syste
			[timer setFireDate:[NSDate dateWithTimeIntervalSinceNow:10]];
		}
	}
	
	[super sendEvent:event];
}

- (void)configureTimer
{
	timer = [NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(handleTimer) userInfo:nil repeats:YES];
	[timer fire];
}


- (void)handleTimer
{
	//We need to swap to the demo view now
	[tabBarController selectTab:1002];
}

@end
