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

Brave *Brave::create(const char *pszFileName)
{
    Brave *brave = new Brave();
    if (brave && brave->init(pszFileName))
    {
        brave->autorelease();
        return brave;
    }
    CC_SAFE_DELETE(brave);
    return NULL;
}

bool Brave::init(const char *pszFileName)
{
    _dustParticleSystem = CCParticleSystemQuad::create("dust.plist");
    _dustParticleSystem->setPosition(ccp(0, 0));
    this->addChild(_dustParticleSystem);

    _characterSprite = CCSprite::create(pszFileName);
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