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
#include "Item.h"

using namespace std;
using namespace cocos2d;

class GameEngine : public CCObject
{
protected:
    hiberlite::Database _db;
    vector<Item> _items;
    int _score;
    int _stamina;

    bool init();
    GameEngine(){};
    GameEngine(const GameEngine& rhs);
    GameEngine& operator=(const GameEngine& rhs);

    void tick();

public:
    static GameEngine *sharedEngine();
    void loadSaveData();
    void startNewGame();
    void finishGame();
    void showResult();
    void showItemList();
    void showTitle();
    int getScore();
    int getStamina();
    void addScore(int score);
    void addStamina(int stamina);

    vector<Item> *getItems();
};

#endif /* defined(__yamiHikariGame__GameEngine__) */
