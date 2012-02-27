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
	
}

@property (nonatomic) xmlNode *node;
@property (nonatomic, retain) XMLParser *XMLParser;

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




@end
