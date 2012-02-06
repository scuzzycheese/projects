//
//  standsViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "ASIHTTPRequest.h"
#include "ZipArchive.h"
#include "XMLParser.h"
#include "standsRootViewController.h"


@interface standsNavigationController : UINavigationController <UINavigationBarDelegate, UINavigationControllerDelegate, ASIHTTPRequestDelegate, ZipArchiveDelegate> {

	NSString *documentsFolderPath;
	NSString *updateZipFile;
	
	XMLParser *XMLParser;
	
}

- (IBAction) swapView:(id)sender;

- (void) workerThread;
- (void)requestFinished:(ASIHTTPRequest *)request;
- (void)requestFailed:(ASIHTTPRequest *)request;
- (void)ErrorMessage:(NSString *)msg;


@property (nonatomic, retain) XMLParser *XMLParser;


@end
