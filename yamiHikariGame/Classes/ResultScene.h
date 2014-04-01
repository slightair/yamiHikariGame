//
//  ResultScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/10.
//
//

#ifndef __yamiHikariGame__ResultScene__
#define __yamiHikariGame__ResultScene__

#include "cocos2d.h"
#include "GradientLayer.h"

using namespace std;
using namespace cocos2d;

class ResultScene : public GradientLayer
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    static CCScene* scene();
    CREATE_FUNC(ResultScene);
};

#endif /* defined(__yamiHikariGame__ResultScene__) */
