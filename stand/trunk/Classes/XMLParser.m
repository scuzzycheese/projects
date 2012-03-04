//
//  XMLParser.m
//  stand
//
//  Created by scuzzy on 2012/02/03.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "XMLParser.h"


@implementation XMLParser

@synthesize node;
@synthesize dom;
@synthesize dataAvailable;

- (id) initWithFilename:(NSString *)filename
{
	self = [super init];

	
	self.dom = xmlReadFile([filename UTF8String], NULL, 0);
	
	xmlErrorPtr error = xmlGetLastError();
	if(error)
	{
		NSLog(@"Error parsing stands.xml: %@", error->message);
	}
	
	self.node = xmlDocGetRootElement(dom);
	
	self.dataAvailable = YES;
	
	return self;
}


+ (NSString *) findNodeValue:(xmlNode *)inNode :(NSString *)nodeName
{
	while(inNode)
	{
		if(inNode->type == XML_ELEMENT_NODE && strcmp(inNode->name, [nodeName UTF8String]) == 0)
		{
			break;
		}
		inNode = inNode->next;
	}
	return [NSString stringWithCString:inNode->children->content encoding:NSUTF8StringEncoding];
}

+ (xmlNode *) findNode:(xmlNode *)inNode :(NSString *)nodeName
{
	while(inNode)
	{
		if(inNode->type == XML_ELEMENT_NODE && strcmp(inNode->name, [nodeName UTF8String]) == 0)
		{
			break;
		}
		inNode = inNode->next;
	}
	return inNode;
}


 
- (void)dealloc
{	
    [super dealloc];
	xmlFreeDoc(dom);
	xmlCleanupParser();
}

@end
