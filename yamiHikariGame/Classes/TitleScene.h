//
//  TitleScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#ifndef __yamiHikariGame__TitleScene__
#define __yamiHikariGame__TitleScene__

#include "cocos2d.h"
#include "Monster.h"
#include "Brave.h"
#include "Darkness.h"
#include "Ground.h"

using namespace cocos2d;

class TitleScene : CCLayer
{
protected:
    Ground *_groundNode;
    Darkness *_darknessNode;
    Monster *_monster;
    Brave *_brave;

    void runEscapeSequence(CCNode *object);
    void startGame();
    void resetSaveData();

public:
    virtual bool init();
    virtual void update(float delta);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();

    static CCScene* scene();
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__yamiHikariGame__TitleScene__) */
