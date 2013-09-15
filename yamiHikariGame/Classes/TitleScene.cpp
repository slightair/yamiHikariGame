//
//  TitleScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "TitleScene.h"
#include "Constants.h"
#include "GameEngine.h"

#define kImageButtonSize 48

#define kSubImageButtonSize 32
#define kSubImageButtonOpacity 96

#define kResetMenuMarginTop 4
#define kResetMenuMarginLeft 4

#define kShowTutorialMenuMarginTop 4
#define kShowTutorialMenuMarginRight 4

#define kTitleLogoMarginTop 32

#define kStartGameMenuMarginBottom 96

#define kShowItemListMenuMarginBottom 16
#define kShowItemListMenuMarginRight 16

#define kGameCenterMenuItemPaddingVertical 8
#define kGameCenterMenuItemMarginBottom 16
#define kGameCenterMenuItemMarginLeft 16

#define kGoogleMenuItemMarginBottom 16

#define kCharacterDistance 80
#define kMonsterDelay 0.2
#define kEscapeDuration 4.0
#define kMoveWidth 100

CCScene* TitleScene::scene()
{
    CCScene *scene = CCScene::create();

    TitleScene *layer = TitleScene::create();
    scene->addChild(layer);

    return scene;
}

bool TitleScene::init()
{
    bool result = CCLayer::init();
    if (result) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        _groundNode = Ground::create();
        this->addChild(_groundNode);

        _monster = Monster::createWithSpriteFrameName("monster.png");
        _monster->setPosition(ccp(windowSize.width / 2, windowSize.height / 2 + kCharacterDistance));
        this->addChild(_monster);

        _brave = Brave::createWithSpriteFrameName("brave.png");
        _brave->setPosition(ccp(windowSize.width / 2, _monster->getPosition().y - kCharacterDistance));
        this->addChild(_brave);

        this->runEscapeSequence(_brave);
        _monster->runAction(CCSequence::create(CCDelayTime::create(kMonsterDelay),
                                               CCCallFuncND::create(this, callfuncND_selector(TitleScene::runEscapeSequence), _monster),
                                               NULL));

        _darknessNode = Darkness::create(_brave->getPosition());
        this->addChild(_darknessNode);

        CCSprite *titleLogo = CCSprite::createWithSpriteFrameName("titlelogo.png");
        titleLogo->setAnchorPoint(ccp(0.5, 1.0));
        titleLogo->setPosition(ccp(windowSize.width / 2, windowSize.height - kTitleLogoMarginTop));
        this->addChild(titleLogo);

        CCSprite *bombNormal = CCSprite::createWithSpriteFrameName("bomb.png");
        CCSprite *bombPressed = CCSprite::createWithSpriteFrameName("bombfire.png");

        CCMenuItemSprite *resetSaveDataItem = this->createSubImageMenuItem(bombNormal, bombPressed,
                                                                        GameEngine::sharedEngine(),
                                                                        menu_selector(GameEngine::confirmResetSaveData));

        CCMenu *resetMenu = CCMenu::create(resetSaveDataItem, NULL);
        resetMenu->setPosition(ccp(kSubImageButtonSize / 2 + kResetMenuMarginLeft,
                                   windowSize.height - kSubImageButtonSize / 2 - kResetMenuMarginTop));
        this->addChild(resetMenu);

        CCSprite *scrollNormal = CCSprite::createWithSpriteFrameName("scroll.png");
        CCSprite *scrollPressed = CCSprite::createWithSpriteFrameName("scroll.png");

        CCMenuItemSprite *showTutorialItem = this->createSubImageMenuItem(scrollNormal, scrollPressed,
                                                                       this,
                                                                       menu_selector(TitleScene::startTutorial));

        CCMenu *showTutorialMenu = CCMenu::create(showTutorialItem, NULL);
        showTutorialMenu->setPosition(ccp(windowSize.width - kSubImageButtonSize / 2 - kShowTutorialMenuMarginRight,
                                          windowSize.height - kSubImageButtonSize / 2 - kShowTutorialMenuMarginTop));
        this->addChild(showTutorialMenu);

        CCMenuItem *startGameItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageGameStartText, DefaultFontName, FontSizeBig),
                                                            this,
                                                            menu_selector(TitleScene::startGame));

        CCMenu *startMenu = CCMenu::create(startGameItem, NULL);
        startMenu->setPosition(ccp(windowSize.width / 2, startGameItem->getContentSize().height / 2 + kStartGameMenuMarginBottom));
        this->addChild(startMenu);

        CCSprite *referenceNormal = CCSprite::createWithSpriteFrameName("referenceButtonNormal.png");
        CCSprite *referencePressed = CCSprite::createWithSpriteFrameName("referenceButtonPressed.png");

        CCMenuItemSprite *showItemListItem = CCMenuItemSprite::create(referenceNormal, referencePressed,
                                                               GameEngine::sharedEngine(),
                                                               menu_selector(GameEngine::showItemList));

        CCMenu *showItemListMenu = CCMenu::create(showItemListItem, NULL);
        showItemListMenu->setPosition(ccp(windowSize.width - kImageButtonSize / 2 - kShowItemListMenuMarginRight,
                                          kImageButtonSize / 2 + kShowItemListMenuMarginBottom));
        this->addChild(showItemListMenu);

        CCSprite *rankingNormal = CCSprite::createWithSpriteFrameName("rankingButtonNormal.png");
        CCSprite *rankingPressed = CCSprite::createWithSpriteFrameName("rankingButtonPressed.png");

        CCMenuItemSprite *showRankingItem = CCMenuItemSprite::create(rankingNormal, rankingPressed,
                                                              GameEngine::sharedEngine(),
                                                              menu_selector(GameEngine::showRanking));

        CCSprite *achievementNormal = CCSprite::createWithSpriteFrameName("achievementButtonNormal.png");
        CCSprite *achievementPressed = CCSprite::createWithSpriteFrameName("achievementButtonPressed.png");

        CCMenuItemSprite *showAchievementItem = CCMenuItemSprite::create(achievementNormal, achievementPressed,
                                                              GameEngine::sharedEngine(),
                                                              menu_selector(GameEngine::showAchievements));

        CCMenu *gameCenterMenu = CCMenu::create(showRankingItem, showAchievementItem, NULL);
        gameCenterMenu->alignItemsVerticallyWithPadding(kGameCenterMenuItemPaddingVertical);
        gameCenterMenu->setPosition(ccp(kImageButtonSize / 2 + kGameCenterMenuItemMarginLeft,
                                         (kImageButtonSize + kGameCenterMenuItemPaddingVertical + kImageButtonSize ) / 2 + kGameCenterMenuItemMarginBottom));

        this->addChild(gameCenterMenu);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCSprite *signInNormal = CCSprite::createWithSpriteFrameName("btn_g+signin_normal.png");
        CCSprite *signInPressed = CCSprite::createWithSpriteFrameName("btn_g+signin_pressed.png");

        CCMenuItemSprite *signInItem = CCMenuItemSprite::create(signInNormal, signInPressed,
                                                                GameEngine::sharedEngine(),
                                                                menu_selector(GameEngine::signInGoogle));

        _signInMenu = CCMenu::create(signInItem, NULL);
        _signInMenu->setPosition(ccp(windowSize.width / 2, signInNormal->getContentSize().height / 2 + kGoogleMenuItemMarginBottom));

        this->addChild(_signInMenu);

        CCSprite *signOutNormal = CCSprite::createWithSpriteFrameName("btn_g+signout_normal.png");
        CCSprite *signOutPressed = CCSprite::createWithSpriteFrameName("btn_g+signout_pressed.png");

        CCMenuItemSprite *signOutItem = CCMenuItemSprite::create(signOutNormal, signOutPressed,
                                                                 GameEngine::sharedEngine(),
                                                                 menu_selector(GameEngine::signOutGoogle));

        _signOutMenu = CCMenu::create(signOutItem, NULL);
        _signOutMenu->setPosition(ccp(windowSize.width / 2, signOutNormal->getContentSize().height / 2 + kGoogleMenuItemMarginBottom));
        _signOutMenu->setVisible(false);

        this->addChild(_signOutMenu);
#endif
    }

    return result;
}

void TitleScene::update(float delta)
{
    _darknessNode->setLightPosition(_brave->getPosition());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (GameEngine::sharedEngine()->getAuthenticatedIndirectly()) {
        _signInMenu->setVisible(false);
        _signOutMenu->setVisible(true);
    } else {
        _signInMenu->setVisible(true);
        _signOutMenu->setVisible(false);
    }
#endif
}

void TitleScene::onEnter()
{
    CCLayer::onEnter();

    this->scheduleUpdate();
}

void TitleScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();

    _monster->startAnimation();
    _brave->startAnimation();
}

void TitleScene::onExit()
{
    this->unscheduleUpdate();

    _monster->finishAnimation();
    _brave->finishAnimation();

    CCLayer::onExit();
}

void TitleScene::runEscapeSequence(CCNode *object)
{
    CCMoveBy *moveToRight  = CCMoveBy::create(kEscapeDuration / 4, ccp(kMoveWidth / 2, 0));
    CCMoveBy *moveToLeft   = CCMoveBy::create(kEscapeDuration / 2, ccp(-kMoveWidth, 0));
    CCMoveBy *moveToCenter = CCMoveBy::create(kEscapeDuration / 4, ccp(kMoveWidth / 2, 0));

    CCCallFuncND *callNextSequence = CCCallFuncND::create(this, callfuncND_selector(TitleScene::runEscapeSequence), object);

    CCSequence *action = CCSequence::create(moveToRight,
                                            moveToLeft,
                                            moveToCenter,
                                            callNextSequence,
                                            NULL);
    object->runAction(action);
}

void TitleScene::startGame()
{
    GameEngine *engine = GameEngine::sharedEngine();
    if (engine->needsTutorial()) {
        engine->startTutorial(true);
    }
    else {
        engine->startNewGame();
    }
}

void TitleScene::startTutorial()
{
    GameEngine::sharedEngine()->startTutorial(false);
}

CCMenuItemSprite *TitleScene::createSubImageMenuItem(CCSprite *normalImage, CCSprite *pressedImage, CCObject *target, SEL_MenuHandler selector)
{
    normalImage->setPosition(ccp(kSubImageButtonSize / 2, kSubImageButtonSize / 2));
    normalImage->setOpacity(kSubImageButtonOpacity);
    pressedImage->setPosition(ccp(kSubImageButtonSize / 2, kSubImageButtonSize / 2));

    CCLayerColor *normalImageLayer = CCLayerColor::create(ccc4(0, 0, 0, 0), kSubImageButtonSize, kSubImageButtonSize);
    normalImageLayer->addChild(normalImage);

    CCLayerColor *pressedImageLayer = CCLayerColor::create(ccc4(0, 0, 0, 0), kSubImageButtonSize, kSubImageButtonSize);
    pressedImageLayer->addChild(pressedImage);

    return CCMenuItemSprite::create(normalImageLayer, pressedImageLayer, target, selector);
}