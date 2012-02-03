//
//  XMLParser.m
//  stand
//
//  Created by scuzzy on 2012/02/03.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "XMLParser.h"


@implementation XMLParser


- (id) initWithFilename:(NSString *)filename
{
	self = [super init];

	
	xmlDoc *dom = xmlReadFile([filename cString], NULL, 0);
	xmlNode *docElement = xmlDocGetRootElement(dom);

	xmlNode *tmpNode = docElement;
	for(tmpNode = docElement; tmpNode; tmpNode = tmpNode->next)
	{
		if(tmpNode->type == XML_ELEMENT_NODE)
		{
		}
	}
	return self;
}

- (void)dealloc
{	
    [super dealloc];
}

@end
