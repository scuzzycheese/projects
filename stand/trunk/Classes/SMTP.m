//
//  SMTP.m
//  stand
//
//  Created by scuzzy on 2012/02/27.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SMTP.h"


@implementation SMTP


- (id)init
{
	self = [super init];
}


- (int)readBytesFromSocketInto:(char *)buffer buffSize:(int)bufferSize
{
	int len = 0;
	while([inputStream hasBytesAvailable])
	{
		len = [inputStream read:buffer maxLength:bufferSize];
		if(len > 0)
		{
			buffer[len] = '\0';
			NSLog(@"server said: %s\n", buffer);
		}
	}
	return len;
}

- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode
{
	
	switch (eventCode) 
	{
			
		case NSStreamEventOpenCompleted:
			NSLog(@"Stream opened");
			break;
			
		case NSStreamEventHasBytesAvailable:
			if (aStream == inputStream)
			{
				
				uint8_t buffer[1024];
				int len;
				
				//len = [self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)];
	
			}
			break;			
			
		case NSStreamEventErrorOccurred:
			NSLog(@"Can not connect to the host!");
			break;
			
		case NSStreamEventEndEncountered:
			break;
			
		default:
			NSLog(@"Unknown event");
	}
}

- (void)openSocketTo:(NSString *)host port:(NSInteger)port
{
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL, (CFStringRef)host, port, &readStream, &writeStream);
    inputStream = (NSInputStream *)readStream;
    outputStream = (NSOutputStream *)writeStream;
	
	[inputStream setDelegate:self];
	[outputStream setDelegate:self];
	
	[inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	
	[inputStream open];
	[outputStream open];
}


- (void)sendEmailTo:(NSString *)emailAddress subject:(NSString *)subject contents:(NSString *)contents
{
	char buffer[1024];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"HELO Stand\r\n" maxLength:strlen("HELO Stand\r\n")];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"MAIL FROM:IPad<scuzzy@mweb.co.za>\r\n" maxLength:strlen("MAIL FROM:IPad<scuzzy@mweb.co.za>\r\n")];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"RCPT TO:<" maxLength:strlen("RCPT TO:<")];
	[outputStream write:[emailAddress dataUsingEncoding:NSUTF8StringEncoding] maxLength:[[emailAddress dataUsingEncoding:NSUTF8StringEncoding] length]];
	[outputStream write:">\r\n" maxLength:strlen(">\r\n")];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"DATA\r\n" maxLength:strlen("DATA\r\n")];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"Subject: " maxLength:strlen("Subject: ")];
	[outputStream write:[subject dataUsingEncoding:NSUTF8StringEncoding] maxLength:[[subject dataUsingEncoding:NSUTF8StringEncoding] length]];
	[outputStream write:"\r\n\r\n" maxLength:strlen("\r\n\r\n")];
	[outputStream write:[contents dataUsingEncoding:NSUTF8StringEncoding] maxLength:[[contents dataUsingEncoding:NSUTF8StringEncoding] length]];
	[outputStream write:"\r\n.\r\n" maxLength:strlen("\r\n.\r\n")];
	while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
	
	[outputStream write:"QUIT" maxLength:strlen("QUIT")];
	
	
	
}

@end
