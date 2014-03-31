//
//  yamiHikariGameAppController.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import <Everyplay/Everyplay.h>

@class RootViewController;

@interface AppController : NSObject
<UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate, EveryplayDelegate>
{
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

