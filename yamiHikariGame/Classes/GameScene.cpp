//
//  GameScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//
//

#include "GameScene.h"

#define chipSize 16

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

    backgroundNode = CCSpriteBatchNode::create("chip.png");
    this->addChild(backgroundNode);

    for (int y = 0; y < windowSize.height * 1.0 / chipSize; y++) {
        for (int x = 0; x < windowSize.width * 1.0 / chipSize; x++) {
            CCSprite *tile = CCSprite::createWithTexture(backgroundNode->getTexture());
            tile->setAnchorPoint(ccp(0, 0));
            tile->setPosition(ccp(x * chipSize, y *chipSize));
            backgroundNode->addChild(tile);
        }
    }

    CCSprite *sprite = CCSprite::create("monster.png");
    sprite->setPosition( ccp(windowSize.width / 2, windowSize.height / 2) );
    this->addChild(sprite);

    return true;
}