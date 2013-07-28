//
//  GameEngine.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "GameEngine.h"
#include "GameScene.h"

#define kTransitionDuration 1.0

static GameEngine *__sharedEngine = NULL;

GameEngine *GameEngine::sharedEngine()
{
    if (!__sharedEngine) {
        __sharedEngine = new GameEngine();
        __sharedEngine->init();
    }

    return __sharedEngine;
}

bool GameEngine::init()
{
    return true;
}

void GameEngine::startNewGame()
{
    _score = 0;
    _stamina = 0;

    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, GameScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

int GameEngine::getScore()
{
    return _score;
}

int GameEngine::getStamina()
{
    return _stamina;
}

void GameEngine::addScore(int score)
{
    _score += score;
}

void GameEngine::addStamina(int stamina)
{
    _stamina += stamina;
}