//
//  EveryplayManager.mm
//  yamiHikariGame
//
//  Created by slightair on 2014/03/31.
//
//

#include "EveryplayManager.h"
#include <Everyplay/Everyplay.h>

void EveryplayManager::startRecording()
{
    [[[Everyplay sharedInstance] capture] startRecording];
}

void EveryplayManager::stopRecording()
{
    [[[Everyplay sharedInstance] capture] stopRecording];
}

void EveryplayManager::mergeScore(int score)
{
    [[Everyplay sharedInstance] mergeSessionDeveloperData:@{@"score" : @(score)}];
}

void EveryplayManager::playLastRecording()
{
    [[Everyplay sharedInstance] playLastRecording];
}