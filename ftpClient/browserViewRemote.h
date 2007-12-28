/* browserViewRemote */

#import <Cocoa/Cocoa.h>

#include <curl/types.h>
#include <curl/curl.h>


#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#include <CoreServices/CoreServices.h>

#include "libhash.h"
#include "ftpparse.h"
#include "browserEventHandler.h"

#define INDEX_FILENAME 0
#define INDEX_FILETYPE 1
#define INDEX_FILESIZE 2

#define DONT_WRITE_FILE 0
#define WRITE_FILE_LOCAL 1
#define WRITE_FILE_REMOTE 2

#define BUFFSIZE 10000

#define KEYCHAIN_NAME "ftpClient"
#define KEYCHAIN_NAME_LEN 9

@interface browserViewRemote : NSObject
{
	IBOutlet NSButton *copyToClient;
	IBOutlet NSButton *copyToServer;
	IBOutlet NSSlider *throttle;
	IBOutlet NSProgressIndicator *progress;
	IBOutlet NSProgressIndicator *progressToClient;
    IBOutlet browserEventHandler *files;
	IBOutlet browserEventHandler *localFiles;
    IBOutlet NSTextField *password;
    IBOutlet NSTextField *username;
		
	/*curl members*/
	CURL *curl;
	CURLcode res;
	
	char *path;

	/*to store column data*/
	hshObj dirStore;
	
	char *ftpServer;
	char *userPass;
	char *entryPath;
	
	/*this is a bit crazy*/
	int newFile;
	
	NSFileManager *fileManager;
	
}

struct objectAndPath
{
	int writeFile;
	browserViewRemote *object;
	char *path;
};

struct multiHoldThrottle
{
	FILE *fd;
	NSSlider *throttle;
};

- (NSString *)fsPathCol:(int)column;

/*keychain stuff*/
OSStatus ChangePasswordKeychain(char *newPassword, SecKeychainItemRef itemRef);
OSStatus GetPasswordKeychain(char *username, char *password, int *passwordLen, SecKeychainItemRef *itemRef);
OSStatus StorePasswordKeychain(char *username, char *password);


- (int)fileWriteFunctionRemote: (void *)buffer size:(int)size nmemb:(int)nmemb path:(void *)dataPath;
- (int)fileWriteFunction: (void *)buffer size:(int)size nmemb:(int)nmemb path:(void *)ftpPath;
- (int)myWriteFunction: (void *)buffer size: (int)size nmemb: (int)nmemb path: (void *)path;

/*write progress indicator*/
int progressFunc(NSProgressIndicator *indicator, double dlTotal, double dlNow, double ulTotal, double ulNow);
int progressFuncClient(NSProgressIndicator *indicator, double dlTotal, double dlNow, double ulTotal, double ulNow);

/*call wrapper for curl*/
int myExternalWriteFunction(void *buffer, size_t size, size_t nmemb, void *object);

- (IBAction)copyToServer:(id)sender;
- (void)copyToServerThread:(id)sender;

- (IBAction)copyToClient:(id)sender;
- (void)copyToClientThread: (id)sender;

- (NSString *)fsPathCol:(int)column;
- (NSString *)fsPathLocalCol:(int)column;
- (IBAction)connect:(id)sender;
- (IBAction)singleClick:(id)sender;
@end
