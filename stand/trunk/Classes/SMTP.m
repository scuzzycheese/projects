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
				
				while([inputStream hasBytesAvailable])
				{
					len = [inputStream read:buffer maxLength:sizeof(buffer)];
					if(len > 0)
					{
						
						NSString *output = [[NSString alloc] initWithBytes:buffer length:len encoding:NSASCIIStringEncoding];
						
						if(nil != output)
						{
							NSLog(@"server said: %@", output);
						}
						[output release];
					}
				}
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
	
	[outputStream write:"HELO Stand\r\n" maxLength:strlen("HELO Stand\r\n")];
	
}

@end
