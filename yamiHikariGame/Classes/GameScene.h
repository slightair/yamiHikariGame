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

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__yamiHikariGame__GameScene__) */
