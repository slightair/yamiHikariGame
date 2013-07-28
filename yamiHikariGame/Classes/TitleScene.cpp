//
//  TitleScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "TitleScene.h"

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
}
