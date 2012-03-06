//
//  standsDisplayViewController.h
//  stand
//
//  Created by scuzzy on 2012/02/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "XMLParser.h"
#include "orderViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface standsDisplayViewController : UIViewController <UIGestureRecognizerDelegate>{

	xmlNode *node;
	XMLParser *XMLParser;
	NSString *documentsFolderPath;

	NSMutableArray *pictureViews;
	
	int currentViewIndex;
	
	UIButton *rightButton;
	
	UIButton *leftButton;
	
	UIButton *orderButton;
	
	orderViewController *orderForm;
	
	id cancelNotifyObject;
	SEL cancelNotifyMethod;
	id emailSentNotifyObject;
	SEL emailSentNotifyMethod;
	
}

@property (nonatomic) xmlNode *node;
@property (nonatomic, retain) XMLParser *XMLParser;
@property (nonatomic) int currentViewIndex;
@property (nonatomic, retain) UIButton *orderButton;

@property (nonatomic, retain) id cancelNotifyObject;
@property (nonatomic) SEL cancelNotifyMethod;
@property (nonatomic, retain) id emailSentNotifyObject;
@property (nonatomic) SEL emailSentNotifyMethod;

- (void)handleSwipeRight;
- (void)buttonSwipeRight:(id)sender;

- (void)handleSwipeLeft;
- (void)buttonSwipeLeft:(id)sender;

- (id)initWithXMLNode:(xmlNode *)inNode;

- (void) loopNodes:(xmlNode *)inNode;

- (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName;
- (xmlNode *) findNode:(xmlNode *)inNode :(NSString *)nodeName;
- (void)addLeftRightButtonsToView:(UIView *)view;
- (void)removeLeftRightButtonsFromCurrentView;




- (void)slideSwapView:(UIView *)newView direction:(NSInteger)dir;
- (void)flipView:(UIView *)newView direction:(NSInteger)dir;

- (void)orderButtonPressed:(id)sender;
- (void)returnToDefaultView;

- (void)notifyCancel:(id)object withSelector:(SEL)selector;
- (void)notifyEmailSent:(id)object withSelector:(SEL)selector;




@end
