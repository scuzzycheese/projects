//
//  SMTP.h
//  stand
//
//  Created by scuzzy on 2012/02/27.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SMTP : NSObject <NSStreamDelegate> 
{

	NSInputStream *inputStream;
	NSOutputStream *outputStream;
	NSString *fromAddress;
	NSString *smtpServer;
	
}
@property (nonatomic, retain) NSString *fromAddress;
@property (nonatomic, retain) NSString *smtpServer;


- (void)openSocketTo:(NSString *)host port:(NSInteger)port;
- (void)sendEmailTo:(NSString *)emailAddress subject:(NSString *)subject contents:(NSString *)contents;
- (int)readBytesFromSocketInto:(char *)buffer buffSize:(int)bufferSize;

@end
