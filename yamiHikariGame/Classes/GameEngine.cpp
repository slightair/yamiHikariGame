//
//  GameEngine.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "GameEngine.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ItemListScene.h"
#include "Item.h"

#define kTransitionDuration 1.0
#define kGameTickInterval 0.1
#define kSurvivePoint 1
#define kStaminaConsumption 3
#define kWaitForResultDuration 3

#define kSavefileName "savedata.db"

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
    CCDirector *director = CCDirector::sharedDirector();

    director->getScheduler()->unscheduleSelector(schedule_selector(GameEngine::tick), this);

    GameScene *gameScene = (GameScene *)director->getRunningScene()->getChildren()->objectAtIndex(0);
    gameScene->finishAnimations();

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SEGameOver);

    director->getScheduler()->scheduleSelector(schedule_selector(GameEngine::showResult), this, 0, 0, kWaitForResultDuration, false);
}

void GameEngine::tick()
{
    _stamina -= kStaminaConsumption;
    _score += kSurvivePoint;

    if (_stamina <= 0) {
        this->finishGame();
    }
}

void GameEngine::showResult()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, TitleScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::showItemList()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, ItemListScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::showTitle()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, TitleScene::scene());
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
    if (_stamina + stamina > StaminaMax) {
        _stamina = StaminaMax;
    }
    else {
        _stamina += stamina;
    }
}

void GameEngine::loadSaveData()
{
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
    bool forceRebuildSaveData = false;

    string saveFilePath = fileUtils->getWritablePath().append(kSavefileName);
    if (forceRebuildSaveData || !fileUtils->isFileExist(saveFilePath)) {
        CCLog("rebuild save data!");
        string initDBFilePath = fileUtils->fullPathForFilename("init.db");

        FILE *src, *dest;
        char buffer[128];
        src = fopen(initDBFilePath.c_str(), "rb");
        dest = fopen(saveFilePath.c_str(), "wb");

        while (feof(src) == 0) {
            int read = fread(buffer, sizeof(char), 128, src);
            fwrite(buffer, sizeof(char), read, dest);
        }

        fclose(src);
        fclose(dest);
    }

    _db.open(saveFilePath);

    _items = _db.getAllBeans<_Item>();
    for (int i=0; i<_items.size(); i++) {
        if (!_items.at(i)->validate()) {
#warning not implemented
            return;
        }
    }
}

vector<Item> *GameEngine::getItems()
{
    return &_items;
}