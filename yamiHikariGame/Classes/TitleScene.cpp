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
