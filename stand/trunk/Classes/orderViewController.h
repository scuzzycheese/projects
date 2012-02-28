//
//  orderViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/25.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "SMTP.h"
#include "XMLParser.h"


@class standsDisplayViewController;

@interface orderViewController : UIViewController {
	
	IBOutlet UIImageView *standPicture;
	standsDisplayViewController *standsController;
	IBOutlet UITextField *emailAddress;
	IBOutlet UITextField *name;
	IBOutlet UITextField *cellphoneNumber;
	IBOutlet UITextField *workNumber;
	
	IBOutlet UIActivityIndicatorView *busySendingEmail;
	
	IBOutlet UIBarButtonItem *sendEmailButton;
	
	NSString *orderEmail;
	NSString *fromEmail;
	NSString *watchdogEmail;
	NSString *smtpServer;
	int smtpPort;
	
	SMTP *smtp;
	

}
@property (nonatomic, retain) IBOutlet UIImageView *standPicture;
@property (nonatomic, retain) standsDisplayViewController *standsController;

@property (nonatomic, retain) IBOutlet UITextField *emailAddress;
@property (nonatomic, retain) IBOutlet UITextField *name;
@property (nonatomic, retain) IBOutlet UITextField *cellphoneNumber;
@property (nonatomic, retain) IBOutlet UITextField *workNumber;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *busySendingEmail;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *sendEmailButton;

- (IBAction)orderCancelButtonPressed:(id)sender;
- (IBAction)sendEmailButtonPressed:(id)sender;

- (void)sendEmail;
- (void)setConfigData;
- (xmlNode *)findXmlNode:(xmlXPathContextPtr)context with:(char *)expression;
- (void)resetForm;

@end
