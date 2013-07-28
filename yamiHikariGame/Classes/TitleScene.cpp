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

CCScene* TitleScene::scene()
{
    CCScene *scene = CCScene::create();

    TitleScene *layer = TitleScene::create();
    scene->addChild(layer);

    return scene;
}

void TitleScene::onEnter()
{
    CCLayer::onEnter();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _groundNode = Ground::create();
    this->addChild(_groundNode);

    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
    this->addChild(monster);

    CCMenuItem *startGameItem = CCMenuItemLabel::create(CCLabelTTF::create("スタート", DefaultFontName, DefaultFontSize),
                                                        GameEngine::sharedEngine(),
                                                        menu_selector(GameEngine::startNewGame));

    CCMenu *menu = CCMenu::create(startGameItem, NULL);
    menu->alignItemsVertically();
    menu->setPosition(ccp(windowSize.width / 2, windowSize.height * 0.2));
    this->addChild(menu);
}
