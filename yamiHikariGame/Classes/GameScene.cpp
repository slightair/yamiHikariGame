//
//  GameScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//
//

#include "GameScene.h"

using namespace cocos2d;

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();

    GameScene *layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::create("HelloWorld.png");
    sprite->setPosition( ccp(windowSize.width / 2, windowSize.height / 2) );
    this->addChild(sprite);

    return true;
}