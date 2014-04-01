//
//  EveryplayManager.cpp
//  yamiHikariGame
//
//  Created by slightair on 2014/03/31.
//
//

#include "EveryplayManager.h"

static EveryplayManager *__sharedManager = NULL;

EveryplayManager *EveryplayManager::sharedManager()
{
    if (!__sharedManager) {
        __sharedManager = new EveryplayManager();
        __sharedManager->init();
    }

    return __sharedManager;
}

bool EveryplayManager::init()
{
    return true;
}