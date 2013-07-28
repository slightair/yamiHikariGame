//
//  Ground.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "Ground.h"
#include "Constants.h"

#define kChipSize 16
#define kChipColorLevel 32

Ground *Ground::create()
{
    Ground *ground = new Ground();
    if (ground && ground->init())
    {
        ground->autorelease();
        return ground;
    }
    CC_SAFE_DELETE(ground);
    return NULL;
}

bool Ground::init()
{
    CCLayerColor::initWithColor((ccColor4B){141, 112, 90, 255});

    return true;
}

void Ground::update(float delta)
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint backgroundScrollVert = ccp(0, windowSize.height / 2);
    float yPosition;

    _backgroundNode1->setPosition(ccpAdd(_backgroundNode1->getPosition(), ccpMult(backgroundScrollVert, delta)));
    _backgroundNode2->setPosition(ccpAdd(_backgroundNode2->getPosition(), ccpMult(backgroundScrollVert, delta)));

    yPosition = this->convertToWorldSpace(_backgroundNode1->getPosition()).y;
    if (yPosition > windowSize.height) {
        _backgroundNode1->setPosition(ccpAdd(_backgroundNode1->getPosition(), ccp(0, -windowSize.height * 2)));
    }

    yPosition = this->convertToWorldSpace(_backgroundNode2->getPosition()).y;
    if (yPosition > windowSize.height) {
        _backgroundNode2->setPosition(ccpAdd(_backgroundNode2->getPosition(), ccp(0, -windowSize.height * 2)));
    }
}

void Ground::onEnter()
{
    CCLayerColor::onEnter();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _backgroundNode1 = this->createBackgroundNode();
    this->addChild(_backgroundNode1);

    _backgroundNode2 = this->createBackgroundNode();
    _backgroundNode2->setPosition(ccp(0, windowSize.height));
    this->addChild(_backgroundNode2);

    this->scheduleUpdate();
}

CCSpriteBatchNode *Ground::createBackgroundNode()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode *backgroundNode = CCSpriteBatchNode::create(SpriteSheetImageFileName);

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