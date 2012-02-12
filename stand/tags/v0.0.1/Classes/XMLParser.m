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

	
	self.dom = xmlReadFile([filename cString], NULL, 0);
	
	xmlErrorPtr error = xmlGetLastError();
	if(error)
	{
		NSLog(@"Error parsing stands.xml: %@", error->message);
	}
	
	self.node = xmlDocGetRootElement(dom);
	
	self.dataAvailable = YES;
	
	return self;
}


 
- (void)dealloc
{	
    [super dealloc];
	xmlFreeDoc(dom);
	xmlCleanupParser();
}

@end
