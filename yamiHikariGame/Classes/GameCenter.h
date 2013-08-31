//
//  GameCenter.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/27.
//
//

#ifndef __yamiHikariGame__GameCenter__
#define __yamiHikariGame__GameCenter__

#include <vector>
#include "Achievement.h"

using namespace std;

class GameCenter
{
protected:
    vector<string> _completedAchievementIDs;

    bool init();
    GameCenter(){};
    GameCenter(const GameCenter& rhs);
    GameCenter& operator=(const GameCenter& rhs);

public:
    static GameCenter *sharedCenter();

    void configure();
    bool getAuthenticated();
    void showRanking();
    void showAchievements();
    void registerHighScore(int score);
    void registerAchievements(vector<Achievement> *achievements);
};

#endif /* defined(__yamiHikariGame__GameCenter__) */
