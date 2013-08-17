//
//  TutorialScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/14.
//
//

#ifndef __yamiHikariGame__TutorialScene__
#define __yamiHikariGame__TutorialScene__

#include "cocos2d.h"
#include "GradientLayer.h"

using namespace cocos2d;

class TutorialScene : public GradientLayer
{
protected:
    static void (TutorialScene::*__pageBuilder[])();

    int _page;
    bool _isPageEnd;
    CCNode *_contentLayer;

    void nextPage();
    void finishTutorial();

public:
    void hoge();
    void fuga();
    void piyo();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

    static CCScene* scene();
    CREATE_FUNC(TutorialScene);
};

#endif /* defined(__yamiHikariGame__TutorialScene__) */
