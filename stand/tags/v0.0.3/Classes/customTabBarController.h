//
//  customTabBarController.h
//  stand
//
//  Created by scuzzy on 2012/03/15.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef CUSTOMTABBARCONTROLLER_H
#define CUSTOMTABBARCONTROLLER_H

@interface customTabBarController : UITabBarController {
	
	UIButton *threeDCapeSite;
	UIButton *navigation;
	UIButton *demo;
	UIButton *CTICCSite;

}

@property (nonatomic, retain) UIButton *threeDCapeSite;
@property (nonatomic, retain) UIButton *navigation;
@property (nonatomic, retain) UIButton *demo;
@property (nonatomic, retain) UIButton *CTICCSite;

- (void)hideTabBar;
- (void)addCustomButtons;
- (void)selectTab:(int)tabNumber;

- (void)hideNewTabBar;
- (void)showNewTabBar;	

- (void)tabPressed:(id)sender;

@end

#endif
