#include "browserViewRemote.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

@implementation browserViewRemote


- (void)awakeFromNib
{
	/*will impliment this later*/
	/*
	char *myOwnFileData = "~/.ftpClient";
	FILE *unFile = fopen(myOwnFileData, "r+");
	struct stat fdData;
	stat(myOwnFileData, &fdData);
	*/
	/*temporary code for the above system of keeping your password in a keychain*/
	
	char *myOwnFileData;
	NSString *liveUsername = NSUserName();
	asprintf(&myOwnFileData, "/Users/%s/.ftpClient", [liveUsername UTF8String]);
	FILE *unFile;
	if(unFile = fopen(myOwnFileData, "r"))
	{
		struct stat fdData;
		stat(myOwnFileData, &fdData);
		char *fileData = malloc(fdData.st_size + 1);
		memset(fileData, '\0', fdData.st_size + 1);
		fread(fileData, fdData.st_size, 1, unFile);
		fclose(unFile);
	
		NSString *userPassData = [NSString stringWithCString: fileData];
		NSArray *userPassArray = [userPassData componentsSeparatedByString:@":"];
		if([userPassArray count] > 1)
		{
			[username setStringValue: [userPassArray objectAtIndex: 0]];
			[password setStringValue: [userPassArray objectAtIndex: 1]];
		}
	}
	free(myOwnFileData);
	
	
	

	fileManager = [NSFileManager defaultManager];
	curl = NULL;
	dirStore = newHashObject();
	path = NULL;
	//ftpServer = "ftp://ftp.sm01.co.uk";
	ftpServer = "ftp://localhost";
	[files setMinColumnWidth: (float)150];
	[files setHasHorizontalScroller: TRUE];
	
	/*set selection options, make sure we can select more than one and branches*/
	[files setAllowsMultipleSelection: TRUE];
	//[files setAllowsBranchSelection: TRUE];
	
	
	[progress setDoubleValue: (double)0]; 
	//[progress setUsesThreadedAnimation: TRUE];
	
	[throttle setMaxValue: (double)100];
	[throttle setMinValue: (double)0];
	[throttle setNumberOfTickMarks: 10];
	[throttle setAllowsTickMarkValuesOnly: TRUE];
}


/*keychain access stuff*/

/*
OSStatus StorePasswordKeychain(char *username, char *password) 
{
	OSStatus status;
	status = SecKeychainAddGenericPassword
	(
		NULL,					// default keychain
		KEYCHAIN_NAME_LEN,		// length of service name
		KEYCHAIN_NAME,			// service name
		strlen(username),		// length of account name
		username,				// account name
		strlen(password),		// length of password
		password,				// pointer to password data
		NULL					// the item reference
	);
    return(status);
}


OSStatus GetPasswordKeychain(char *username, char *password, int *passwordLen, SecKeychainItemRef *itemRef)
{
	OSStatus status1;
	
	status1 = SecKeychainFindGenericPassword
	(
		NULL,					// default keychain
		KEYCHAIN_NAME_LEN,		// length of service name
		KEYCHAIN_NAME,			// service name
		strlen(username),		// length of account name
		username,				// account name
		passwordLen,			// length of password
		password,				// pointer to password data
		itemRef					// the item reference
	);
	return (status1);
}


OSStatus ChangePasswordKeychain(char *newPassword, SecKeychainItemRef itemRef)
{
    OSStatus status;
	
	const char *account = "NewAccount";
    const char *service = "NewService";
    // Set up attribute vector (each attribute consists of {tag, length, pointer}):
    SecKeychainAttribute attrs[] = 
	{
		{
			kSecAccountItemAttr,
			strlen(account),
			(char *)account
		},
		{
			kSecServiceItemAttr,
			strlen(service),
			(char *)service
		}
	};
    const SecKeychainAttributeList attributes = { sizeof(attrs) / sizeof(attrs[0]), attrs };
	
	status = SecKeychainItemModifyAttributesAndData
	(
		itemRef,				// the item reference
		&attributes,			// no change to attributes
		strlen(newPassword),	// length of password
		newPassword				// pointer to password data
	);
	return (status);
}

*/

- (NSString *)fsPathCol:(int)column
{
    NSString *filePath = NULL;
    if(column == 0) filePath = [NSString stringWithCString: "/"];
    else filePath = [files pathToColumn: column];
    return filePath;
}

- (NSString *)fsPathLocalCol:(int)column
{
    NSString *filePath = NULL;
    if(column == 0) filePath = [NSString stringWithCString: "/"];
    else filePath = [localFiles pathToColumn: column];
    return filePath;
}

size_t myFileReaderFunction(void *ptr, size_t size, size_t nmemb, void *stream)
{
	struct multiHoldThrottle recvData = *(struct multiHoldThrottle *)stream;
	FILE *dataFile = (FILE *)recvData.fd;
	int dataRead = fread(ptr, size, nmemb, dataFile);
	
	/*THROTTLE sleeper*/
	int throtVal = 100 - (int)[recvData.throttle floatValue];
	throtVal *= 1000;
	usleep(throtVal);
	
	return dataRead;
}

- (IBAction)copyToServer:(id)sender
{
	[NSThread detachNewThreadSelector: @selector(copyToServerThread:) toTarget:self withObject: sender];
}
- (void)copyToServerThread:(id)sender
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	/*unhide our progress bar*/
	[progress setHidden: NO];
	
	/*disable all out controlls*/
	[copyToServer setEnabled: NO];
	[copyToClient setEnabled: NO];
	[localFiles setEnabled: NO];
	[files setEnabled: NO];
	
	NSArray *cells = [localFiles selectedCells];
	int lastCol = [localFiles lastColumn];
	int lastColRemote = [files lastColumn];
	int i;
	for(i = 0; i < [cells count]; i ++)
	{
		NSBrowserCell *cell = [cells objectAtIndex: i];
		char *fileToPush;
		asprintf
		(
			&fileToPush, 
			"%s%s%s", 
			[[self fsPathLocalCol: lastCol] UTF8String], 
			(lastCol == 0) ? "" : "/", 
			[[cell title] UTF8String]
		);
		
		
		
		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, TRUE);
		
		char *sendFtpPath;
		asprintf
		(
			 &sendFtpPath, 
			 "%s%s/%s", 
			 ftpServer, 
			 [[self fsPathCol: lastColRemote] UTF8String], 
			 [[cell title] UTF8String]
		);
		
		printf("URL: %s\n", sendFtpPath);
		
		/* specify target */
		curl_easy_setopt(curl,CURLOPT_URL, sendFtpPath);
		
		/* pass in that last of FTP commands to run after the transfer */
		//curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
		
		FILE *inputFile = fopen(fileToPush, "r");
		
		/* now specify which file to upload */
		struct multiHoldThrottle sendData;
		sendData.throttle = throttle;
		sendData.fd = inputFile;
		curl_easy_setopt(curl, CURLOPT_READDATA, &sendData);
		
		/*use this function to read the data*/
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, myFileReaderFunction);

		/* Set the size of the file to upload (optional).  If you give a *_LARGE
		option you MUST make sure that the type of the passed-in argument is a
		curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
		make sure that to pass in a type 'long' argument. */
		
		if(![fileManager fileExistsAtPath: [NSString stringWithCString: fileToPush]])
		{
			NSRunAlertPanel(@"ERROR", @"You need to select a source file or, one or more files that you selected doesn't exist.", @"Close", NULL, NULL);
			
			/*hide our progress bar*/
			[progress setHidden: YES];
			
			/*enable our controls again*/
			[files setEnabled: YES];
			[localFiles setEnabled: YES];
			[copyToServer setEnabled: YES];
			[copyToClient setEnabled: YES];
			
			[pool release];
			
			return;
		}
		
		NSDictionary *fileAttr = [fileManager fileAttributesAtPath: [NSString stringWithCString: fileToPush] traverseLink: TRUE];
		
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)[fileAttr fileSize]);
		
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressFunc);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, progress);
		
		/*we are gonna use this to make sure we can throttle the data*/
		curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, BUFFSIZE);
		
		/* Now run off and do what you've been told! */
		res = curl_easy_perform(curl);
		close(inputFile);
		
		free(fileToPush);
		free(sendFtpPath);
		[progress setDoubleValue: (double)0]; 
	}
	/*hide our progress bar*/
	[progress setHidden: YES];
	
	/*enable our controls again*/
	[files setEnabled: YES];
	[localFiles setEnabled: YES];
	[copyToServer setEnabled: YES];
	[copyToClient setEnabled: YES];
	
	
	/*this is a sneaky way of reloading the column*/
	[self singleClick: files];
	[pool release];
}

int progressFunc(NSProgressIndicator *indicator, double dlTotal, double dlNow, double ulTotal, double ulNow)
{
	double answere = ulNow * 100 / ulTotal;
	[indicator setDoubleValue: answere]; 
	return 0;
}






- (IBAction)copyToClient:(id)sender
{
	[NSThread detachNewThreadSelector: @selector(copyToClientThread:) toTarget:self withObject: sender];
}
- (void)copyToClientThread: (id)sender
{

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	/*unhide our progress bar*/
	[progressToClient setHidden: NO];
	
	/*disable all out controlls*/
	[copyToServer setEnabled: NO];
	[copyToClient setEnabled: NO];
	[localFiles setEnabled: NO];
	[files setEnabled: NO];



	NSArray *cells = [files selectedCells];
	int lastCol = [files lastColumn];
	
	int i;
	for(i = 0; i < [cells count]; i ++)
	{
		NSBrowserCell *cell = [cells objectAtIndex: i];
		char *clientPath;
		if([cells count] <= 1)
		{
			if([cell isLeaf]) asprintf
			(
				&clientPath, 
				"%s%s%s%s", 
				ftpServer, 
				[[self fsPathCol: lastCol] UTF8String], 
				(lastCol == 0) ? "" : "/", 
				[[cell stringValue] UTF8String]
			);
			else asprintf
			(
				&clientPath, 
				"%s%s/", 
				ftpServer, 
				[[self fsPathCol: lastCol] UTF8String]
			);
		}
		else
		{
			if([cell isLeaf]) asprintf
			(
				&clientPath, 
				"%s%s%s%s", 
				ftpServer, 
				[[self fsPathCol: lastCol] UTF8String], 
				(lastCol == 0) ? "" : "/", 
				[[cell stringValue] UTF8String]
			);
			else asprintf
			(
				&clientPath, 
				"%s%s%s%s/", 
				ftpServer, 
				[[self fsPathCol: lastCol] UTF8String], 
				(lastCol == 0) ? "" : "/", 
				[[cell stringValue] UTF8String]
			);
		}
		NSString *nsPath = [[NSString alloc] initWithCString: clientPath];
		[nsPath autorelease];
		
		
		/*perform Curl stuff here*/
		curl_easy_setopt(curl, CURLOPT_URL, clientPath);
		printf("Fetch: %s\n", clientPath);
		
		/*set up our data to send to the curl wirte wrapper function*/
		struct objectAndPath send;
		send.writeFile = WRITE_FILE_LOCAL;
		send.object = self;
		send.path = clientPath;
		
		/*pass something to the function - NULL at this stage*/
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &send);
		
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressFuncClient);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, progressToClient);
		

		
		/*we are gonna use this to make sure we can throttle the data*/
		curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, BUFFSIZE);
	
		/*indicate we are writing a new file*/
		newFile = TRUE;
	
		/*go get em tiger*/
		res = curl_easy_perform(curl);
		
		free(clientPath);
		
	}
	
	/*hide our progress bar*/
	[progressToClient setHidden: YES];
	
	/*enable our controls again*/
	[files setEnabled: YES];
	[localFiles setEnabled: YES];
	[copyToServer setEnabled: YES];
	[copyToClient setEnabled: YES];
		
	[localFiles reloadColumn: lastCol];
	[pool release];
}


int progressFuncClient(NSProgressIndicator *indicator, double dlTotal, double dlNow, double ulTotal, double ulNow)
{
	double answere = dlNow * 100 / dlTotal;
	[indicator setDoubleValue: answere]; 
	return 0;
}


int myExternalWriteFunction(void *buffer, size_t size, size_t nmemb, void *object)
{
	struct objectAndPath data = *(struct objectAndPath *)object;
	if(data.writeFile == WRITE_FILE_LOCAL) return [data.object fileWriteFunction:buffer size:size nmemb:nmemb path:data.path];
	else if(data.writeFile == WRITE_FILE_REMOTE) return [data.object fileWriteFunctionRemote:buffer size:size nmemb:nmemb path:data.path];
	else return [data.object myWriteFunction:buffer size:size nmemb:nmemb path:data.path];
}

- (int)fileWriteFunctionRemote: (void *)buffer size:(int)size nmemb:(int)nmemb path:(void *)dataPath
{
	int realsize = size * nmemb;
	return realsize;
}

- (int)fileWriteFunction: (void *)buffer size:(int)size nmemb:(int)nmemb path:(void *)ftpPath
{
	int realsize = size * nmemb;
	
	int lastCol = [localFiles lastColumn];
	
	NSArray *chunks = [[NSString stringWithCString: ftpPath] componentsSeparatedByString:@"/"];
	NSString *fileName = [chunks objectAtIndex: [chunks count] - 1];
	char *fileToWrite;
	asprintf(&fileToWrite, "%s/%s", [[self fsPathLocalCol: lastCol] UTF8String], [fileName UTF8String]);
	
	if([fileName compare: @""] == NSOrderedSame)
	{
		NSRunAlertPanel(@"ERROR", @"You need to select a source file!", @"Close", NULL, NULL);
		return realsize;
	}
	
	FILE *fd;
	if(newFile == TRUE)
	{
		fd = fopen(fileToWrite, "w+");
		newFile = FALSE;
	}
	else
	{
		fd = fopen(fileToWrite, "a+");
		newFile = FALSE;
	}
	if(fd)
	{
		fwrite(buffer, realsize, 1, fd);
		fclose(fd);
	}
	else
	{
		printf("failed to write data to disk: %d\n", errno);
	}
	free(fileToWrite);
	
	/*THROTTLE sleeper*/
	int throtVal = 100 - (int)[throttle floatValue];
	throtVal *= 1000;
	usleep(throtVal);
	
	return realsize;
}

- (int)myWriteFunction: (void *)buffer size:(int)size nmemb:(int)nmemb path:(void *)ftpPath
{
	int realSize = size * nmemb;
	/*bit of a nasty hack to make sure we chop off the end of the \r\n*/
	if(*((char *)buffer + (realSize - 2)) == '\r') *((char *)buffer + (realSize - 2)) = '\0';

	/*printf("DATA: %s\n", buffer);*/
	
	NSString *data = [[NSString alloc] initWithCString: buffer];
	
	NSArray *tmpArray = [data componentsSeparatedByString: @"\r\n"];
	
	NSMutableArray *lines = [[NSMutableArray alloc] init];
	//[lines autorelease];
	int i;
	for(i = 0; i < [tmpArray count]; i ++)
	{
		struct ftpparse fileData;
		if(ftpparse(&fileData, (char *)[[tmpArray objectAtIndex: i] UTF8String], strlen((char *)[[tmpArray objectAtIndex: i] UTF8String])))
		{			
		
			NSMutableArray *tempData = [[NSMutableArray alloc] init];
			[tempData insertObject: [NSString stringWithCString: fileData.name] atIndex: INDEX_FILENAME];
			[tempData insertObject: [NSNumber numberWithInt: fileData.flagtrycwd] atIndex: INDEX_FILETYPE];
			[tempData insertObject: [NSNumber numberWithUnsignedLongLong: fileData.size] atIndex: INDEX_FILESIZE];
			[tempData autorelease];
			
			[lines addObject: tempData];
		}
	}
	
	//NSArray *lines = [[NSArray alloc] initWithArray: tmpArray copyItems: YES];
	
	[data release];
	
	/*put our files array into a hash*/
	dirStore->addIndexString(dirStore, ftpPath, lines);

	/*this is quite important, otherwise curl drops the link*/
	return realSize;
}


- (IBAction)connect:(id)sender
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl)
	{
	
		/*configure our url*/
		curl_easy_setopt(curl, CURLOPT_URL, ftpServer);
		/*tell curl where to write to*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myExternalWriteFunction);
		
		/*set up our data to send to the curl wirte wrapper function*/
		struct objectAndPath send;
		send.writeFile = DONT_WRITE_FILE;
		send.object = self;
		send.path = (char *)[[self fsPathCol: 0] UTF8String];
		
		/*pass something to the function - NULL at this stage*/
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &send);
		
		/*full verbose debugging*/
		curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);
		
		/*set usename and password*/		
		asprintf(&userPass, "%s:%s", [[username stringValue] UTF8String], [[password stringValue] UTF8String]);
		curl_easy_setopt(curl, CURLOPT_USERPWD, userPass);
		
		/*try make curl keep the connection open*/
		curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 0);
		

	
		/*we are not uploading at the moment*/
		curl_easy_setopt(curl, CURLOPT_UPLOAD, FALSE);
		
		/*go get em tiger*/
		res = curl_easy_perform(curl);
		
		/*get our entry Path*/
		//curl_easy_get_info(curl, CURLINFO_FTP_ENTRY_PATH, &entryPath);
		
		/*reload the starting column*/
		[files reloadColumn: 0];
		

		char *myOwnFileData = "/tmp/.ftpClient";
		NSString *liveUsername = NSUserName();
		asprintf(&myOwnFileData, "/Users/%s/.ftpClient", [liveUsername UTF8String]);
		FILE *unFile;
		if(unFile = fopen(myOwnFileData, "w+"))
		{
			char *userPassString;
			asprintf(&userPassString, "%s:%s", [[username stringValue] UTF8String], [[password stringValue] UTF8String]);
			fwrite(userPassString, strlen(userPassString), 1, unFile);
			free(userPassString);
		}
		else
		{
			perror(NULL);
		}
		free(myOwnFileData);
		/*keep this for later*/
		if(CURLE_OK != res)
		{
			printf("CURL ERROR: %d\n", res);
		}
	}
}

- (int)browser:(NSBrowser *)sender numberOfRowsInColumn:(int)column
{
	NSMutableArray *list = (NSMutableArray *)dirStore->findIndexString(dirStore, (char *)[[self fsPathCol: column] UTF8String]);
	if(list)
	{
		return [list count];
	}
	else return 0;
}

- (void)browser:(NSBrowser *)sender willDisplayCell:(id)cell atRow:(int)row column:(int)column
{
	NSMutableArray *list = (NSMutableArray *)dirStore->findIndexString(dirStore, (char *)[[self fsPathCol: column] UTF8String]);
	if(list)
	{
		NSMutableArray *tempData = [list objectAtIndex: row];
	
		int type = [[tempData objectAtIndex: INDEX_FILETYPE] intValue];
		if(type == 0) [cell setLeaf: TRUE];
		
		[cell setTitle: [tempData objectAtIndex: INDEX_FILENAME]];
	}
}

- (void)cleanup
{
		/*clean up the curl oject*/
		curl_easy_cleanup(curl);
		
		free(userPass);
		
		if(path) free(path);

		dirStore->destruct(dirStore);
		curl_global_cleanup();
}

- (IBAction)singleClick:(id)sender
{
	if([sender isEnabled])
	{

		/*only access files if a single selection is performed*/
		NSArray *cells = [sender selectedCells];
		if([cells count] == 1)
		{

			NSBrowserCell *cell = [sender selectedCell];
			int lastCol = [sender lastColumn];
	
			if(path) free(path);
	
			//asprintf(&path, "%s%s/%s", ftpServer, [[self fsPathCol: lastCol] UTF8String], [[cell stringValue] UTF8String]);
			asprintf(&path, "%s%s/", ftpServer, [[self fsPathCol: lastCol] UTF8String]);
			NSString *nsPath = [[NSString alloc] initWithCString: path];
			[nsPath autorelease];
	
			curl_easy_setopt(curl, CURLOPT_URL, path);
		
			curl_easy_setopt(curl, CURLOPT_UPLOAD, FALSE);
		
			/*set up our data to send to the curl wirte wrapper function*/
			struct objectAndPath send;
			send.writeFile = DONT_WRITE_FILE;
			send.object = self;
			send.path = (char *)[[self fsPathCol: lastCol] UTF8String];
		
			/*pass something to the function - NULL at this stage*/
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &send);
	
			/*go get em tiger*/
			res = curl_easy_perform(curl);
	
			/*reload the particular column*/
			[files reloadColumn: lastCol];
		}
	}

}

@end
