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
#include "Ground.h"
#include "ScoreBoard.h"

using namespace cocos2d;

class GameScene : public CCLayer
{
protected:
    CCNode *_worldNode;
    Ground *_groundNode;
    CCSpriteBatchNode *_itemsNode;
    Darkness *_darknessNode;
    ScoreBoard *_scoreBoardNode;

    Monster *_monster;
    Brave *_brave;

    CCPoint _touchedLocation;
    CCRect _braveRect;

    bool _finished;

    void collisionCheck();
    void dropItem();
    void showObtainedScore(int score);
    void showObtainedStamina(int stamina);
public:
    virtual void update(float delta);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    static CCScene* scene();
    CREATE_FUNC(GameScene);

    void finishAnimations();
};

#endif /* defined(__yamiHikariGame__GameScene__) */
