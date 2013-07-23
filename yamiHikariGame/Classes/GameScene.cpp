//
//  GameScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//
//

#include "GameScene.h"

#define kChipSize 16
#define kChipColorLevel 32

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

    _backgroundMainNode = CCNode::create();
    this->addChild(_backgroundMainNode);

    _backgroundNode1 = this->createBackgroundNode();
    _backgroundMainNode->addChild(_backgroundNode1);

    _backgroundNode2 = this->createBackgroundNode();
    _backgroundNode2->setPosition(ccp(0, windowSize.height));
    _backgroundMainNode->addChild(_backgroundNode2);

    _monster = (Monster *)Monster::create("monster.png");
    _monster->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height));
    this->addChild(_monster);

    _brave = Brave::create("brave.png");
    _brave->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height * 2 - _brave->getContentSize().height / 2));
    this->addChild(_brave);

    _monster->startAnimation();
    _brave->startAnimation();

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float delta)
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint backgroundScrollVert = ccp(0, windowSize.height / 2);
    float yPosition;

    _backgroundNode1->setPosition(ccpAdd(_backgroundNode1->getPosition(), ccpMult(backgroundScrollVert, delta)));
    _backgroundNode2->setPosition(ccpAdd(_backgroundNode2->getPosition(), ccpMult(backgroundScrollVert, delta)));

    yPosition = _backgroundMainNode->convertToWorldSpace(_backgroundNode1->getPosition()).y;
    if (yPosition > windowSize.height) {
        _backgroundNode1->setPosition(ccpAdd(_backgroundNode1->getPosition(), ccp(0, -windowSize.height * 2)));
    }

    yPosition = _backgroundMainNode->convertToWorldSpace(_backgroundNode2->getPosition()).y;
    if (yPosition > windowSize.height) {
        _backgroundNode2->setPosition(ccpAdd(_backgroundNode2->getPosition(), ccp(0, -windowSize.height * 2)));
    }
}

void GameScene::onEnter()
{
    CCLayer::onEnter();

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    _touchedLocation = pTouch->getLocationInView();

    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = pTouch->getLocationInView();
    float distance = location.x - _touchedLocation.x;

#warning debug
    CCLog("%f, %f", location.x, location.y);
    CCLog("dist => %f", distance);

    _brave->moveX(distance);

    _touchedLocation = location;
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

CCSpriteBatchNode *GameScene::createBackgroundNode()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode *backgroundNode = CCSpriteBatchNode::create("chip.png");

    for (int y = 0; y < windowSize.height * 1.0 / kChipSize; y++) {
        for (int x = 0; x < windowSize.width * 1.0 / kChipSize; x++) {
            CCSprite *tile = CCSprite::createWithTexture(backgroundNode->getTexture());
            GLubyte chipColorOffset = 255 - rand() % kChipColorLevel;
            tile->setColor((ccColor3B){chipColorOffset, chipColorOffset, chipColorOffset});
            tile->setAnchorPoint(ccp(0, 0));
            tile->setPosition(ccp(x * kChipSize, y * kChipSize));
            backgroundNode->addChild(tile);
        }
    }

    return backgroundNode;
}