//
//  ScoreBoard.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#ifndef __yamiHikariGame__ScoreBoard__
#define __yamiHikariGame__ScoreBoard__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreBoard : public CCNodeRGBA
{
protected:
    CCLabelTTF *_scoreLabel;
public:
    virtual void update(float delta);
    virtual void onEnter();
    static ScoreBoard *create();
    void setScore(int score);
};

#endif /* defined(__yamiHikariGame__ScoreBoard__) */
