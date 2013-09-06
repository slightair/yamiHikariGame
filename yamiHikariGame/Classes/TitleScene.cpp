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

#define kMainMenuItemPaddingVertical 12
#define kSubMenuItemPaddingHorizontal 72
#define kSubMenuMarginBottom 32
#define kResetMenuMarginTop 16
#define kResetMenuPaddingHorizontal 144

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
        titleLogo->setPosition(ccp(windowSize.width / 2, windowSize.height * 0.83));
        this->addChild(titleLogo);

        CCSprite *bomb = CCSprite::createWithSpriteFrameName("bomb.png");
        CCSprite *bombPressed = CCSprite::createWithSpriteFrameName("bombfire.png");
        CCMenuItemSprite *resetSaveDataItem = CCMenuItemSprite::create(bomb, bombPressed,
                                                                       GameEngine::sharedEngine(),
                                                                       menu_selector(GameEngine::confirmResetSaveData));

        CCMenu *resetMenu = CCMenu::create(resetSaveDataItem, NULL);
        resetMenu->setPosition(ccp(windowSize.width / 2 - kResetMenuPaddingHorizontal , windowSize.height - kResetMenuMarginTop));
        this->addChild(resetMenu);

        CCMenuItem *startGameItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageGameStartText, DefaultFontName, FontSizeBig),
                                                            this,
                                                            menu_selector(TitleScene::startGame));

        CCMenuItem *startTutorialItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageShowTutorialText, DefaultFontName, FontSizeBig), this, menu_selector(TitleScene::startTutorial));

        CCMenu *startMenu = CCMenu::create(startGameItem, startTutorialItem, NULL);
        startMenu->setPosition(ccp(windowSize.width / 2, windowSize.height * 0.25));
        startMenu->alignItemsVerticallyWithPadding(kMainMenuItemPaddingVertical);
        this->addChild(startMenu);

        CCMenuItem *showItemListItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageShowItemListText, DefaultFontName, FontSizeBig),
                                                               GameEngine::sharedEngine(),
                                                               menu_selector(GameEngine::showItemList));

        CCMenuItem *showRankingItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageShowRankingText, DefaultFontName, FontSizeBig),
                                                              GameEngine::sharedEngine(),
                                                              menu_selector(GameEngine::showRanking));

        CCMenu *subMenu = CCMenu::create(showRankingItem, showItemListItem, NULL);
        subMenu->alignItemsHorizontallyWithPadding(kSubMenuItemPaddingHorizontal);
        subMenu->setPosition(ccp(windowSize.width / 2, showItemListItem->getContentSize().height / 2 + kSubMenuMarginBottom));
        this->addChild(subMenu);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        CCMenuItem *signInMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("ログイン", DefaultFontName, FontSizeBig),
                                                            GameEngine::sharedEngine(), menu_selector(GameEngine::signInGoogle));
        CCMenuItem *signOutMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("ログアウト", DefaultFontName, FontSizeBig),
                                                              GameEngine::sharedEngine(), menu_selector(GameEngine::signOutGoogle));

        CCMenu *androidMenu = CCMenu::create(signInMenuItem, signOutMenuItem, NULL);
        androidMenu->setPosition(ccp(windowSize.width / 4, windowSize.height / 2));
        androidMenu->alignItemsVertically();
        this->addChild(androidMenu);
#endif
    }

    return result;
}

void TitleScene::update(float delta)
{
    _darknessNode->setLightPosition(_brave->getPosition());
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