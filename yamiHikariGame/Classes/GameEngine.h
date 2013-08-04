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
#include "hiberlite.h"

using namespace std;
using namespace cocos2d;

class GameEngine : public CCObject
{
protected:
    hiberlite::Database _db;

    int _score;
    int _stamina;

    bool init();
    GameEngine(){};
    GameEngine(const GameEngine& rhs);
    GameEngine& operator=(const GameEngine& rhs);

    void tick();

public:
    static GameEngine *sharedEngine();
    void validateSaveData();
    void startNewGame();
    void finishGame();
    void showResult();
    void showItemList();
    void showTitle();
    int getScore();
    int getStamina();
    void addScore(int score);
    void addStamina(int stamina);

    hiberlite::Database *savedataDB();
};

#endif /* defined(__yamiHikariGame__GameEngine__) */
