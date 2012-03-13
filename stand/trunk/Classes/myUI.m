//
//  myUI.m
//  stand
//
//  Created by scuzzy on 2012/03/13.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "myUI.h"


@implementation myUI

- (void)sendEvent:(UIEvent *)event
{
	//We need to see when someone interacts with the system
	if(event.type == UIEventTypeTouches)
	{
		NSLog(@"User touched the screen\n");
	}
	
	[super sendEvent:event];
}

@end
