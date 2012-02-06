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
	bool dataAvailable;
	xmlNode *node;
	xmlDoc *dom;
}


- (id) initWithFilename:(NSString *)filename;

@property (nonatomic) xmlNode *node;
@property (nonatomic) xmlDoc *dom;
@property (nonatomic) bool dataAvailable;

@end
