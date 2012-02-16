//
//  XMLParser.h
//  stand
//
//  Created by scuzzy on 2012/02/03.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>



@interface XMLParser : NSObject
{
	BOOL dataAvailable;
	xmlNode *node;
	xmlDoc *dom;
}


- (id) initWithFilename:(NSString *)filename;

@property (nonatomic, assign) xmlNode *node;
@property (nonatomic, assign) xmlDoc *dom;
@property (nonatomic, assign) BOOL dataAvailable;

@end