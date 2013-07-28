//
//  GameEngine.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#ifndef __yamiHikariGame__GameEngine__
#define __yamiHikariGame__GameEngine__

#include "cocos2d.h"

using namespace cocos2d;

class GameEngine
{
protected:
    bool init();
    GameEngine(){};
    GameEngine(const GameEngine& rhs);
    GameEngine& operator=(const GameEngine& rhs);

public:
    static GameEngine *sharedEngine();
};

#endif /* defined(__yamiHikariGame__GameEngine__) */
