//
//  GameCenter.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/27.
//
//

#include "GameCenter.h"

static GameCenter *__sharedCenter = NULL;

GameCenter *GameCenter::sharedCenter()
{
    if (!__sharedCenter) {
        __sharedCenter = new GameCenter();
        __sharedCenter->init();
    }

    return __sharedCenter;
}

bool GameCenter::init()
{
    return true;
}

bool GameCenter::configure()
{
    return false;
}

void GameCenter::showRanking()
{

}

void GameCenter::showAchievements()
{

}

void GameCenter::registerHighScore(int score)
{

}

void GameCenter::registerAchievements(vector<Achievement> *achievements)
{

}