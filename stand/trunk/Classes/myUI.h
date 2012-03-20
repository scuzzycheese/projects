//
//  myUI.h
//  stand
//
//  Created by scuzzy on 2012/03/13.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "customTabBarController.h"


@interface myUI : UIApplication {

	customTabBarController *tabBarController;
	NSTimer *timer;
	
}
@property (nonatomic, retain) UITabBarController *tabBarController;
@property (nonatomic, retain) NSTimer *timer;

- (void)configureTimer;
- (void)handleTimer;

@end
