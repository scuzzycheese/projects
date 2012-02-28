//
//  SMTP.m
//  stand
//
//  Created by scuzzy on 2012/02/27.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SMTP.h"


@implementation SMTP

@synthesize fromAddress;
@synthesize smtpServer;


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
	
	if(fromAddress != nil)
	{
		char buffer[1024];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"HELO Stand\r\n" maxLength:strlen("HELO Stand\r\n")];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"MAIL FROM:" maxLength:strlen("MAIL FROM:")];
		[outputStream write:[fromAddress UTF8String] maxLength:strlen([fromAddress UTF8String])];
		[outputStream write:"\r\n" maxLength:strlen("\r\n")];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"RCPT TO:<" maxLength:strlen("RCPT TO:<")];
		[outputStream write:[emailAddress UTF8String] maxLength:strlen([emailAddress UTF8String])];
		[outputStream write:">\r\n" maxLength:strlen(">\r\n")];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"DATA\r\n" maxLength:strlen("DATA\r\n")];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"From: \"iPad\" <scuzzy@mweb.co.za>\r\n" maxLength:strlen("From: \"iPad\" <scuzzy@mweb.co.za>\r\n")];
		
		[outputStream write:"Subject: " maxLength:strlen("Subject: ")];
		[outputStream write:[subject UTF8String] maxLength:strlen([subject UTF8String])];
		[outputStream write:"\r\n\r\n" maxLength:strlen("\r\n\r\n")];
		[outputStream write:[contents UTF8String] maxLength:strlen([contents UTF8String])];
		[outputStream write:"\r\n.\r\n" maxLength:strlen("\r\n.\r\n")];
		while([self readBytesFromSocketInto:buffer buffSize:sizeof(buffer)] == 0);
		
		[outputStream write:"QUIT" maxLength:strlen("QUIT")];
	}
	
}

@end
