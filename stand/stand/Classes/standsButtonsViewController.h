//
//  standsRootViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/30.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "standsNavigationController.h"
#include "myButton.h"

@interface standsButtonsViewController : UIViewController {
	
	
	xmlNode *node;
	XMLParser *XMLParser;
	NSMutableArray *buttons;
	NSString *documentsFolderPath;
	UIScrollView *scrollView;

}

- (IBAction) swapViewController:(id)sender;

- (id)initWithXMLNode:(xmlNode *)inNode;
- (void) loopNodes:(xmlNode *)inNode;
- (void) arrangeButtons:(int)width;
- (void) showButtons;
- (void) sizeButtonsWidth:(int)width height:(int)height;
- (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName;
- (xmlNode *) findNode:(xmlNode *)inNode :(NSString *)nodeName;
- (void) buttonPressed:(id)sender;

@property (nonatomic) xmlNode *node;
@property (nonatomic, retain) XMLParser *XMLParser;


@end
