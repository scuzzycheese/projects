//
//  standAppDelegate.h
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "ASIHTTPRequest.h"
#include "ZipArchive.h"

@interface standAppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate, ASIHTTPRequestDelegate, ZipArchiveDelegate> {
    UIWindow *window;
    UITabBarController *tabBarController;
	NSString *documentsFolderPath;
	NSString *updateZipFile;
}

- (void) workerThread;
- (void)requestFinished:(ASIHTTPRequest *)request;
- (void)requestFailed:(ASIHTTPRequest *)request;
- (void)ErrorMessage:(NSString *)msg;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UITabBarController *tabBarController;

@end
