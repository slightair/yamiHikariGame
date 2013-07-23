//
//  GameScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//
//

#ifndef __yamiHikariGame__GameScene__
#define __yamiHikariGame__GameScene__

#include "cocos2d.h"
#include "Monster.h"
#include "Brave.h"

using namespace cocos2d;

class GameScene : public CCLayer
{
protected:
    CCNode *_backgroundMainNode;
    CCSpriteBatchNode *_backgroundNode1;
    CCSpriteBatchNode *_backgroundNode2;
    Monster *_monster;
    Brave *_brave;

    CCSpriteBatchNode *createBackgroundNode();
public:
    virtual bool init();
    virtual void update(float delta);
    static CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__yamiHikariGame__GameScene__) */
