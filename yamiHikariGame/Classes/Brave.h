//
//  Brave.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/22.
//
//

#ifndef __yamiHikariGame__Brave__
#define __yamiHikariGame__Brave__

#include "cocos2d.h"

using namespace cocos2d;

class Brave : public CCNodeRGBA
{
protected:
    CCSprite *_characterSprite;
    CCParticleSystem *_dustParticleSystem;

    bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    void runRunningSequence();
public:
    static Brave *createWithSpriteFrameName(const char *pszSpriteFrameName);
    void startAnimation();
    void moveX(float delta);
};

#endif /* defined(__yamiHikariGame__Brave__) */
