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

class Monster : public CCSprite
{
protected:
    void runSwingSequence();
public:
    void startAnimation();
};

#endif /* defined(__yamiHikariGame__Monster__) */
