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

#define kMenuItemPadding 8
#define kCharacterDistance 80

#define kMonsterDelay 0.2
#define kEscapeDuration 4.0
#define kMoveWidth 180

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

        CCLabelTTF *titleLabel = CCLabelTTF::create("ヤミからのトウソウ", DefaultFontName, FontSizeBig);
        titleLabel->setPosition(ccp(windowSize.width / 2, windowSize.height * 0.8));
        this->addChild(titleLabel);

        CCMenuItem *startGameItem = CCMenuItemLabel::create(CCLabelTTF::create("スタート", DefaultFontName, FontSizeBig),
                                                            GameEngine::sharedEngine(),
                                                            menu_selector(GameEngine::startNewGame));

        CCMenuItem *showItemListItem = CCMenuItemLabel::create(CCLabelTTF::create("アイテムずかん", DefaultFontName, FontSizeBig),
                                                               GameEngine::sharedEngine(),
                                                               menu_selector(GameEngine::showItemList));

        CCMenu *menu = CCMenu::create(startGameItem, showItemListItem, NULL);
        menu->alignItemsVerticallyWithPadding(kMenuItemPadding);
        menu->setPosition(ccp(windowSize.width / 2, windowSize.height * 0.2));
        this->addChild(menu);
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