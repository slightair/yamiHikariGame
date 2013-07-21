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
#define kSwingDuration 0.5f
#define kSwingWidth 40
#define kEasingRate 1.2

using namespace cocos2d;

void Monster::startAnimation()
{
    this->setScale(kExpandScale);
    this->setOpacity(kWeakOpacity);

    this->runSwingSequence();
}

void Monster::runSwingSequence()
{
    CCScaleTo *expandAction1   = CCScaleTo::create(kSwingDuration, kExpandScale);
    CCScaleTo *contractAction1 = CCScaleTo::create(kSwingDuration, kDefaultScale);
    CCScaleTo *expandAction2   = CCScaleTo::create(kSwingDuration, kExpandScale);
    CCScaleTo *contractAction2 = CCScaleTo::create(kSwingDuration, kDefaultScale);

    CCFadeTo *fadeToWeak1   = CCFadeTo::create(kSwingDuration, kWeakOpacity);
    CCFadeTo *fadeToStrong1 = CCFadeTo::create(kSwingDuration, kDefaultOpacity);
    CCFadeTo *fadeToWeak2   = CCFadeTo::create(kSwingDuration, kWeakOpacity);
    CCFadeTo *fadeToStrong2 = CCFadeTo::create(kSwingDuration, kDefaultOpacity);

    CCMoveBy *toRight   = CCMoveBy::create(kSwingDuration, ccp( kSwingWidth / 2, 0));
    CCMoveBy *toCenter1 = CCMoveBy::create(kSwingDuration, ccp(-kSwingWidth / 2, 0));
    CCMoveBy *toLeft    = CCMoveBy::create(kSwingDuration, ccp(-kSwingWidth / 2, 0));
    CCMoveBy *toCenter2 = CCMoveBy::create(kSwingDuration, ccp( kSwingWidth / 2, 0));

    CCCallFuncN *callNextSequence = CCCallFuncN::create(this, callfuncN_selector(Monster::runSwingSequence));

    CCSequence *action = CCSequence::create(
                                            CCSpawn::create(contractAction1, fadeToStrong1, CCEaseIn::create(toRight, kEasingRate),    NULL),
                                            CCSpawn::create(expandAction1,   fadeToWeak1,   CCEaseOut::create(toCenter1, kEasingRate), NULL),
                                            CCSpawn::create(contractAction2, fadeToStrong2, CCEaseIn::create(toLeft, kEasingRate),     NULL),
                                            CCSpawn::create(expandAction2,   fadeToWeak2,   CCEaseOut::create(toCenter2, kEasingRate), NULL),
                                            callNextSequence,
                                            NULL);
    this->runAction(action);
}
