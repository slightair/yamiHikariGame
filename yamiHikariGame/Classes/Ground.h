//
//  Ground.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#ifndef __yamiHikariGame__Ground__
#define __yamiHikariGame__Ground__

#include "cocos2d.h"

using namespace cocos2d;

class Ground : public CCLayerColor
{
protected:
    CCSpriteBatchNode *_backgroundNode1;
    CCSpriteBatchNode *_backgroundNode2;

    bool init();
    CCSpriteBatchNode *createBackgroundNode();
public:
    virtual void update(float delta);
    virtual void onEnter();
    static Ground *create();
};

#endif /* defined(__yamiHikariGame__Ground__) */
