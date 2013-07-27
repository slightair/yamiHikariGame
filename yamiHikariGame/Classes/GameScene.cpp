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
#define kSpriteSheetImageFileName "spriteSheet.pvr.ccz"

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

    _worldNode = CCNode::create();

    _backgroundMainNode = CCLayerColor::create();

    _backgroundNode1 = this->createBackgroundNode();
    _backgroundMainNode->addChild(_backgroundNode1);

    _backgroundNode2 = this->createBackgroundNode();
    _backgroundNode2->setPosition(ccp(0, windowSize.height));
    _backgroundMainNode->addChild(_backgroundNode2);

    _monster = Monster::createWithSpriteFrameName("monster.png");
    _monster->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height));
    _worldNode->addChild(_monster);

    _brave = Brave::createWithSpriteFrameName("brave.png");
    _brave->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height * 2 - _brave->getContentSize().height / 2));
    _worldNode->addChild(_brave);

    _darknessNode = Darkness::create(_brave->getPosition());

    _monster->startAnimation();
    _brave->startAnimation();

    this->addChild(_backgroundMainNode);
    this->addChild(_worldNode);
    this->addChild(_darknessNode);

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

    _monster->followBrave(_brave->getPosition(), delta);
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
    _darknessNode->setLightPosition(_brave->getPosition());

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
    CCSpriteBatchNode *backgroundNode = CCSpriteBatchNode::create(kSpriteSheetImageFileName);

    for (int y = 0; y < windowSize.height * 1.0 / kChipSize; y++) {
        for (int x = 0; x < windowSize.width * 1.0 / kChipSize; x++) {
            CCSprite *tile = CCSprite::createWithSpriteFrameName("chip.png");
            GLubyte chipColorOffset = 0xff - rand() % kChipColorLevel;
            tile->setColor((ccColor3B){chipColorOffset, chipColorOffset, chipColorOffset});
            tile->setAnchorPoint(ccp(0, 0));
            tile->setPosition(ccp(x * kChipSize, y * kChipSize));
            backgroundNode->addChild(tile);
        }
    }

    return backgroundNode;
}