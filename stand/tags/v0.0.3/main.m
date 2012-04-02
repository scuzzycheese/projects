//
//  main.m
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "myUI.h"

int main(int argc, char *argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString *appClass = @"myUI";
    int retVal = UIApplicationMain(argc, argv, appClass, nil);
    [pool release];
    return retVal;
}

