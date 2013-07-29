//
//  yamiHikariGameAppDelegate.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "TitleScene.h"

#define kDefaultDesignResolutionWidth 320
#define kDefaultDesignResolutionHeight 480
#define kIPadDesignResolutionWidth 768
#define kIPadDesignResolutionHeight 1024

#define kIPhone4inchHeight 568
#define kIPhone3_5inchHeight 480
#define kIPadHeight 1024

#define kIPhone4inchScreenHeight 1136

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *openGLView = CCEGLView::sharedOpenGLView();
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();

    std::vector<std::string> searchResolutionsOrder;

    pDirector->setOpenGLView(openGLView);

    // turn on display FPS
    pDirector->setDisplayStats(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCSize screenSize = openGLView->getFrameSize();

    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone) {
        if (screenSize.height == kIPhone4inchScreenHeight) {
            openGLView->setDesignResolutionSize(kDefaultDesignResolutionWidth, kIPhone4inchHeight, kResolutionExactFit);
        }
        else {
            openGLView->setDesignResolutionSize(kDefaultDesignResolutionWidth, kDefaultDesignResolutionHeight, kResolutionExactFit);
        }
    }
    else {
        openGLView->setDesignResolutionSize(kIPadDesignResolutionWidth, kIPadDesignResolutionHeight, kResolutionExactFit);
    }

    float retinaThreshold = platform == kTargetIphone ? kIPhone3_5inchHeight : kIPadHeight;
    if (screenSize.height > retinaThreshold) {
        searchResolutionsOrder.push_back("ios-hd");
        pDirector->setContentScaleFactor(2.0f);
    }
    else {
        searchResolutionsOrder.push_back("default");
    }
#else
    // Android, etc...
    openGLView->setDesignResolutionSize(defaultDesignResolutionSize.width, defaultDesignResolutionSize.height, kResolutionExactFit);
    searchResolutionsOrder.push_back("default");
#endif

    fileUtils->setSearchResolutionsOrder(searchResolutionsOrder);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spriteSheet.plist");

    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(SoundEffectVolume);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SEItemGet);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SEBadItemGet);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SEGameOver);

    // create a scene. it's an autorelease object
    CCScene *pScene = TitleScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
