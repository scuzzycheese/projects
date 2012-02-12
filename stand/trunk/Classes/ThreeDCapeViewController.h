//
//  FirstViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ThreeDCapeViewController : UIViewController <UIWebViewDelegate> {
	
	IBOutlet UIWebView *threeDCapeWebView;

}

@property (nonatomic, retain) IBOutlet UIWebView *threeDCapeWebView;

- (IBAction) webGoHome:(id)sender;

@end
