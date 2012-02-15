//
//  standAppDelegate.m
//  stand
//
//  Created by scuzzy on 2012/01/24.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "standAppDelegate.h"



@implementation standAppDelegate

@synthesize window;
@synthesize tabBarController;
@synthesize XMLParser;

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after app launch.
    
	// Set the tab bar controller as the window's root view controller and display.
    self.window.rootViewController = self.tabBarController;
    [self.window makeKeyAndVisible];
	
	
	NSThread *myThread = [[NSThread alloc] initWithTarget:self selector:@selector(workerThread) object:nil];
	[myThread start];

    return YES;
}




- (void) workerThread
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	//NSString *appFolderPath = [[NSBundle mainBundle] resourceURL];
	
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolderPath = [documentPaths objectAtIndex:0];
	
	
	updateZipFile = [documentsFolderPath stringByAppendingString:@"/update.zip"];
	//NSLog(@"File to download:%@", fileToDownload);
	
	ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:[NSURL URLWithString:@"http://192.168.0.2/downloads/update.zip"]];
	[request setDownloadDestinationPath:updateZipFile];
	[request setDelegate:self];
	[request startAsynchronous];
	
	while(1)
	{
		//Implement updates for new conent here
		sleep(10);
	}
	[pool release];
}

- (void)requestFinished:(ASIHTTPRequest *)request
{
	NSLog(@"Successfully downloaded the update file.\n");
	[self initialiseXML];
}

- (void)requestFailed:(ASIHTTPRequest *)request
{
	NSError *error = [request error];
	NSLog(@"Failed to download the update file: %@\n", [error description]);
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Download failed" 
													message:[error localizedDescription]
												   delegate:nil 
										  cancelButtonTitle:@"OK"
										  otherButtonTitles:nil];
	[alert show];
	[alert release];
	
	//Try initialise XML even if we couldn't download an update
	//NOTE: This all needs work.
	[self initialiseXML];
}


- (void)initialiseXML
{	
	ZipArchive *ziper = [[ZipArchive alloc] init];
	
	[ziper UnzipOpenFile:updateZipFile];
	[ziper UnzipFileTo:documentsFolderPath overWrite:YES];
	
	[ziper release];
	
	NSString *standsXMLFile = [documentsFolderPath stringByAppendingString:@"/stands.xml"];
	
	self.XMLParser = [[XMLParser alloc] initWithFilename:standsXMLFile];
}

//Have to test this still
- (void)ErrorMessage:(NSString *)msg
{
	NSLog(@"Error unziping file: %@\n", msg);
}





- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive.
     */
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     */
}


#pragma mark -
#pragma mark UITabBarControllerDelegate methods

/*
 // Optional UITabBarControllerDelegate method
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController {
}
 */

/*
 // Optional UITabBarControllerDelegate method
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed {
}
 */

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [tabBarController release];
    [window release];

    [super dealloc];
}
	 

@end

