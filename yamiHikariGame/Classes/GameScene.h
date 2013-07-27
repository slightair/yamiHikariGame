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
#include "Darkness.h"

using namespace cocos2d;

class GameScene : public CCLayer
{
protected:
    Darkness *_darknessNode;
    CCNode *_worldNode;

    CCLayerColor *_backgroundMainNode;
    CCSpriteBatchNode *_backgroundNode1;
    CCSpriteBatchNode *_backgroundNode2;

    Monster *_monster;
    Brave *_brave;

    CCPoint _touchedLocation;

    CCSpriteBatchNode *createBackgroundNode();
public:
    virtual bool init();
    virtual void update(float delta);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    static CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__yamiHikariGame__GameScene__) */
