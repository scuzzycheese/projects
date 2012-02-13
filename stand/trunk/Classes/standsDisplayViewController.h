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

@interface standsDisplayViewController : UIViewController <UIGestureRecognizerDelegate>{

	xmlNode *node;
	XMLParser *XMLParser;
	NSString *documentsFolderPath;

	NSMutableArray *pictureViews;
	
	int currentViewIndex;
	
}

@property (nonatomic) xmlNode *node;
@property (nonatomic, retain) XMLParser *XMLParser;

- (void)handleSwipeRight;

- (id)initWithXMLNode:(xmlNode *)inNode;

- (void) loopNodes:(xmlNode *)inNode;

- (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName;
- (xmlNode *) findNode:(xmlNode *)inNode :(NSString *)nodeName;

- (void)swapViewAt:(int)index;

@end
