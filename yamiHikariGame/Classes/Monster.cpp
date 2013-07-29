//
//  Monster.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/21.
//
//

#include "Monster.h"

#define kExpandScale 2.0
#define kDefaultScale 1.0
#define kWeakOpacity 0x99
#define kDefaultOpacity 0xff
#define kEffectDuration 0.5f

Monster *Monster::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    Monster *monster = new Monster();
    if (monster && monster->initWithSpriteFrameName(pszSpriteFrameName))
    {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Monster::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    _characterSprite = CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    this->setContentSize(_characterSprite->getContentSize());
    this->addChild(_characterSprite);

    return true;
}

void Monster::startAnimation()
{
    _characterSprite->setScale(kExpandScale);
    _characterSprite->setOpacity(kWeakOpacity);

    this->runEffectSequence();
}

void Monster::runEffectSequence()
{
    CCScaleTo *expandAction1   = CCScaleTo::create(kEffectDuration, kExpandScale);
    CCScaleTo *contractAction1 = CCScaleTo::create(kEffectDuration, kDefaultScale);
    CCScaleTo *expandAction2   = CCScaleTo::create(kEffectDuration, kExpandScale);
    CCScaleTo *contractAction2 = CCScaleTo::create(kEffectDuration, kDefaultScale);

    CCFadeTo *fadeToWeak1   = CCFadeTo::create(kEffectDuration, kWeakOpacity);
    CCFadeTo *fadeToStrong1 = CCFadeTo::create(kEffectDuration, kDefaultOpacity);
    CCFadeTo *fadeToWeak2   = CCFadeTo::create(kEffectDuration, kWeakOpacity);
    CCFadeTo *fadeToStrong2 = CCFadeTo::create(kEffectDuration, kDefaultOpacity);

    CCCallFuncN *callNextSequence = CCCallFuncN::create(this, callfuncN_selector(Monster::runEffectSequence));

    CCSequence *action = CCSequence::create(
                                            CCSpawn::create(contractAction1, fadeToStrong1, NULL),
                                            CCSpawn::create(expandAction1,   fadeToWeak1,   NULL),
                                            CCSpawn::create(contractAction2, fadeToStrong2, NULL),
                                            CCSpawn::create(expandAction2,   fadeToWeak2,   NULL),
                                            callNextSequence,
                                            NULL);
    _characterSprite->runAction(action);
}

void Monster::followBrave(CCPoint bravePosition, float delta)
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    float monsterSpeedHorizontal = windowSize.width / 2 * (bravePosition.x < this->getPosition().x ? -1 : 1);
    CCPoint nextPosition = ccpAdd(this->getPosition(), ccpMult(ccp(monsterSpeedHorizontal, 0), delta));

    if (monsterSpeedHorizontal < 0 && nextPosition.x < bravePosition.x) {
        nextPosition.x = bravePosition.x;
    }
    else if (monsterSpeedHorizontal > 0 && nextPosition.x > bravePosition.x) {
        nextPosition.x = bravePosition.x;
    }

    this->setPosition(nextPosition);
}

void Monster::finishAnimation()
{
    _characterSprite->stopAllActions();
}