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

class Monster : public cocos2d::CCSprite
{
protected:
    void runSwingSequence();
public:
    void startAnimation();
};

#endif /* defined(__yamiHikariGame__Monster__) */
