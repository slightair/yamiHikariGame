//
//  Brave.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/22.
//
//

#include "Brave.h"

#define kShakeDuration 0.05
#define kShakeAngle 5
#define kEffectDuration 0.1

Brave *Brave::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    Brave *brave = new Brave();
    if (brave && brave->initWithSpriteFrameName(pszSpriteFrameName))
    {
        brave->autorelease();
        return brave;
    }
    CC_SAFE_DELETE(brave);
    return NULL;
}

bool Brave::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    _dustParticleSystem = CCParticleSystemQuad::create("dust.plist");
    _dustParticleSystem->setPosition(ccp(0, 0));
    this->addChild(_dustParticleSystem);

    _characterSprite = CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    this->setContentSize(_characterSprite->getContentSize());

    this->addChild(_characterSprite);

    return true;
}

void Brave::startAnimation()
{
    this->runRunningSequence();
}

void Brave::runRunningSequence()
{
    CCRotateBy *rotateToLeft      = CCRotateBy::create(kShakeDuration, kShakeAngle);
    CCRotateBy *rotateToRightBack = CCRotateBy::create(kShakeDuration, -kShakeAngle);
    CCRotateBy *rotateToRight     = CCRotateBy::create(kShakeDuration, -kShakeAngle);
    CCRotateBy *rotateToLeftBack  = CCRotateBy::create(kShakeDuration, kShakeAngle);
    CCCallFuncN *callNextSequence = CCCallFuncN::create(this, callfuncN_selector(Brave::runRunningSequence));

    CCSequence *action = CCSequence::create(
                                            rotateToLeft,
                                            rotateToRightBack,
                                            rotateToRight,
                                            rotateToLeftBack,
                                            callNextSequence,
                                            NULL);
    _characterSprite->runAction(action);
}

void Brave::moveX(float delta)
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint nextPosition = ccpAdd(this->getPosition(), ccp(delta, 0));

    if (nextPosition.x < 0) {
        nextPosition.x = 0;
    }
    else if (nextPosition.x > windowSize.width) {
        nextPosition.x = windowSize.width;
    }

    this->setPosition(nextPosition);
}

void Brave::finishAnimation()
{
    _dustParticleSystem->stopSystem();
    _characterSprite->stopAllActions();

    _characterSprite->runAction(CCRotateTo::create(0.0, 90));
}

void Brave::recoverEffect()
{
    CCSequence *action = CCSequence::create(
                                            CCTintTo::create(kEffectDuration, 0x66, 0xff, 0x66),
                                            CCTintTo::create(kEffectDuration, 0xff, 0xff, 0xff),
                                            NULL);
    _characterSprite->runAction(action);
}

void Brave::damageEffect()
{
    CCSequence *action = CCSequence::create(
                                            CCTintTo::create(kEffectDuration, 0xff, 0x66, 0x66),
                                            CCTintTo::create(kEffectDuration, 0xff, 0xff, 0xff),
                                            NULL);
    _characterSprite->runAction(action);
}