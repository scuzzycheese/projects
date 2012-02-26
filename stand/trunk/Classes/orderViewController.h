//
//  orderViewController.h
//  stand
//
//  Created by scuzzy on 2012/01/25.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "standsDisplayViewController.h"


@interface orderViewController : UIViewController {
	
	IBOutlet UIImageView *standPicture;
	standsDisplayViewController *standsController;
	

}
@property (nonatomic, retain) IBOutlet UIImageView *standPicture;
@property (nonatomic, retain) standsDisplayViewController *standsController;

@end
