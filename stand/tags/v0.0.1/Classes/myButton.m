//
//  myButton.m
//  stand
//
//  Created by scuzzy on 2012/02/10.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "myButton.h"
#import <objc/runtime.h>


@implementation UIButton(Property)

static char UIB_NODE_KEY;

@dynamic node;

-(void)setNode:(xmlNode *)node
{
    objc_setAssociatedObject(self, &UIB_NODE_KEY, node, OBJC_ASSOCIATION_ASSIGN);
}

-(xmlNode *)node
{
    return (xmlNode *)objc_getAssociatedObject(self, &UIB_NODE_KEY);
}

@end