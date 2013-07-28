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
#include "Ground.h"

using namespace cocos2d;

class TitleScene : CCLayer
{
protected:
    Ground *_groundNode;
public:
    virtual void onEnter();
//    virtual void onEnterTransitionDidFinish();

    static CCScene* scene();
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__yamiHikariGame__TitleScene__) */
