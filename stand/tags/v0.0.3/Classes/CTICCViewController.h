//
//  CTICCViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CTICCViewController : UIViewController <UIWebViewDelegate> {

	IBOutlet UIWebView *CTICCWebView;
	
}

@property (nonatomic, retain) IBOutlet UIWebView *CTICCWebView;

- (IBAction) webGoHome:(id)sender;

@end
