//
//  Monster.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/21.
//
//

#ifndef __yamiHikariGame__Monster__
#define __yamiHikariGame__Monster__

#include "cocos2d.h"

using namespace cocos2d;

class Monster : public CCNodeRGBA
{
protected:
    CCSprite *_characterSprite;

    bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    void runEffectSequence();
public:
    static Monster *createWithSpriteFrameName(const char *pszSpriteFrameName);
    void startAnimation();
    void followBrave(CCPoint bravePosition, float delta);
    void finishAnimation();
};

#endif /* defined(__yamiHikariGame__Monster__) */
