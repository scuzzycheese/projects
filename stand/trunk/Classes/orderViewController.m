    //
//  orderViewController.m
//  stand
//
//  Created by scuzzy on 2012/01/25.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "orderViewController.h"
#include "standsDisplayViewController.h"


@implementation orderViewController
@synthesize standPicture;
@synthesize standsController;

@synthesize emailAddress;
@synthesize name;
@synthesize cellphoneNumber;
@synthesize workNumber;

@synthesize busySendingEmail;

@synthesize sendEmailButton;


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self)
	{
		smtp = [[SMTP alloc] init];
    }
    return self;
}
 


/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	[self setConfigData];
}
 


- (IBAction)orderCancelButtonPressed:(id)sender
{
	[self.standsController returnToDefaultView];
	if(self.standsController.cancelNotifyObject && self.standsController.cancelNotifyMethod)
	{
		[self.standsController.cancelNotifyObject performSelector:self.standsController.cancelNotifyMethod withObject:self];
	}
}

- (IBAction)sendEmailButtonPressed:(id)sender
{
	[sendEmailButton setEnabled:NO];
	[busySendingEmail setHidden:NO];
	[busySendingEmail startAnimating];
	
	
	
	NSLog(@"Attempting to send e-mail\n");
	
	/*
	[smtp openSocketTo:@"relay.mweb.co.za" port:25];
	[smtp setFromAddress:@"iPad <scuzzy@mweb.co.za>"];
	[smtp sendEmailTo:@"scuzzy@reverseorder.net" subject:@"Order for Suite" contents:composer];
	 */
	
	[NSThread detachNewThreadSelector:@selector(sendEmail) toTarget:self withObject:nil];
	
}

- (void)resetForm
{
	name.text = @"";
	emailAddress.text = @"";
	cellphoneNumber.text = @"";
	workNumber.text = @"";
}

- (void)sendEmail
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSString *composer = [[NSString alloc] initWithString:@"Suite order: "];
	composer = [[composer stringByAppendingString:standsController.title] stringByAppendingString:@"\r\n\r\nName: "];
	composer = [[composer stringByAppendingString:name.text] stringByAppendingString:@"\r\nE-Mail Address: "];
	composer = [[composer stringByAppendingString:emailAddress.text] stringByAppendingString:@"\r\nCellPhone Number: "];
	composer = [[composer stringByAppendingString:cellphoneNumber.text] stringByAppendingString:@"\r\nWork Number: "];
	composer = [composer stringByAppendingString:workNumber.text];
	
	[smtp openSocketTo:smtpServer port:smtpPort];
	[smtp setFromAddress:fromEmail];
	[smtp sendEmailTo:orderEmail subject:@"Order for Suite" contents:composer];
	
	[busySendingEmail stopAnimating];
	[busySendingEmail setHidden:YES];
	[sendEmailButton setEnabled:YES];
	
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Order Sent." 
													message:@"An order for this suite has been sent to a sales agent."
												   delegate:nil 
										  cancelButtonTitle:@"OK"
										  otherButtonTitles:nil];
	[alert show];
	[alert release];
	
	
	if(self.standsController.emailSentNotifyObject && self.standsController.emailSentNotifyMethod)
	{
		[self.standsController.emailSentNotifyObject performSelector:self.standsController.emailSentNotifyMethod withObject:self];
	}
	[self.standsController returnToDefaultView];
	
	[pool release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;
}

- (void)setConfigData
{
	
	xmlXPathContextPtr contextPtr = xmlXPathNewContext(standsController.node->doc);
	
	
	xmlNode *confNode;
	if(confNode = [self findXmlNode:contextPtr with:"//config/orderEmail"])
	{
		orderEmail = [[NSString alloc] initWithCString:confNode->children->content encoding:NSUTF8StringEncoding];
	}
	if(confNode = [self findXmlNode:contextPtr with:"//config/fromEmail"])
	{
		fromEmail = [[NSString alloc] initWithCString:confNode->children->content encoding:NSUTF8StringEncoding];
	}
	if(confNode = [self findXmlNode:contextPtr with:"//config/watchdogEmail"])
	{
		watchdogEmail = [[NSString alloc] initWithCString:confNode->children->content encoding:NSUTF8StringEncoding];
	}
	if(confNode = [self findXmlNode:contextPtr with:"//config/smtpServer"])
	{
		smtpServer = [[NSString alloc] initWithCString:confNode->children->content encoding:NSUTF8StringEncoding];
		smtpPort = atoi(xmlGetProp(confNode, "port"));
	}
	
	xmlXPathFreeContext(contextPtr);
	
	
	
}

- (xmlNode *)findXmlNode:(xmlXPathContextPtr)context with:(char *)expression
{
	if(xpathObj)
	{
		xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
	}
	xpathObj = xmlXPathEvalExpression(expression, context);
	if(xpathObj->nodesetval->nodeNr > 0)
	{
		return xpathObj->nodesetval->nodeTab[0];
	}
	return NULL;
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
	[smtp release];
	
	if(orderEmail != nil) [orderEmail release];
	if(fromEmail != nil) [fromEmail release];
	if(watchdogEmail != nil) [watchdogEmail release];
	if(smtpServer != nil) [smtpServer release];
	if(xpathObj)
	{
		xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
	}
	//[standPicture release];
}


@end
