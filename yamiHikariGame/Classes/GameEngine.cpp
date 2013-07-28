//
//  GameEngine.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "GameEngine.h"
#include "Constants.h"
#include "GameScene.h"

#define kTransitionDuration 1.0
#define kGameTickInterval 0.1

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
    _stamina = StaminaMax;

    CCDirector *director = CCDirector::sharedDirector();
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, GameScene::scene());
    director->replaceScene(transition);

    director->getScheduler()->scheduleSelector(schedule_selector(GameEngine::tick), this, kGameTickInterval, false);
}

void GameEngine::finishGame()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(GameEngine::tick), this);
}

void GameEngine::tick()
{
    _stamina -= 1;
    _score += 1;

    if (_stamina <= 0) {
        this->finishGame();
    }
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
    if (_stamina + stamina > StaminaMax) {
        _stamina = StaminaMax;
    }
    else {
        _stamina += stamina;
    }
}