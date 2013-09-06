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
    map<hiberlite::sqlid_t, int> _foundItems;
    int _score;
    int _stamina;
    bool _startWithTutorial;
    CCArray *_achievements;

    bool init();
    GameEngine(){};
    GameEngine(const GameEngine& rhs);
    GameEngine& operator=(const GameEngine& rhs);

    void tick();
    void addScore(int score);
    void addStamina(int stamina);
    void registerFoundItemCount();
    void registerActivities();
    void copyInitialData(string saveFilePath);
    void rebuildSaveData();
    void resetSaveData();
    string generateScoreChecksum(int score);

public:
    static GameEngine *sharedEngine();
    void loadSaveData();
    void startTutorial(bool startGame);
    void finishTutorial();
    void startNewGame();
    void finishGame();
    void showResult();
    void showRanking();
    void showItemList();
    void showTitle();
    void confirmResetSaveData();
    bool needsTutorial();
    int getScore();
    int getStamina();
    void foundItem(hiberlite::sqlid_t itemID);

    vector<Item> *getItems();
    map<hiberlite::sqlid_t, int> *getFoundItems();
};

#endif /* defined(__yamiHikariGame__GameEngine__) */
