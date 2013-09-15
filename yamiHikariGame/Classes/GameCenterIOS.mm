//
//  GameCenterIOS.mm
//  yamiHikariGame
//
//  Created by slightair on 2013/08/30.
//
//

#include "GameCenter.h"
#include <GameKit/GameKit.h>
#include "Constants.h"
#include "AppController.h"
#include "RootViewController.h"

void GameCenter::configure()
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    localPlayer.authenticateHandler = ^(UIViewController *viewController, NSError *error) {
        if (localPlayer.authenticated) {
            [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error){
                if (error) {
                    return;
                }
                for(GKAchievement *achievement in achievements) {
                    if (achievement.completed) {
                        _completedAchievementIDs.push_back([achievement.identifier UTF8String]);
                    }
                }
             }];
        }
        else {

        }
    };
}

bool getAuthenticated()
{
    return [GKLocalPlayer localPlayer].authenticated;
}

void GameCenter::showRanking()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;

    GKLeaderboardViewController *leaderboardViewController = [[GKLeaderboardViewController alloc] init];
    leaderboardViewController.timeScope = GKLeaderboardTimeScopeAllTime;
    leaderboardViewController.leaderboardDelegate = appController.viewController;

    [appController.viewController presentViewController:leaderboardViewController animated:YES completion:NULL];
}

void GameCenter::showAchievements()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;

    GKAchievementViewController *achievementViewController = [[GKAchievementViewController alloc] init];
    achievementViewController.achievementDelegate = appController.viewController;

    [appController.viewController presentViewController:achievementViewController animated:YES completion:NULL];
}

void GameCenter::registerHighScore(int score)
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if (localPlayer.authenticated) {
        GKScore *highScore = [[GKScore alloc] initWithCategory:[NSString stringWithUTF8String:LeaderboardIDHighScoreIOS]];
        highScore.value = score;
        [highScore reportScoreWithCompletionHandler:NULL];
    }
}

void GameCenter::registerAchievements(vector<Achievement> *achievements)
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if (localPlayer.authenticated) {
        vector<Achievement>::iterator achievementsIterator = achievements->begin();

        while (achievementsIterator != achievements->end()) {
            Achievement achievementInfo = *achievementsIterator;
            string achievementID = achievementInfo.getIOSAchievementID();

            vector<string>::iterator pos = find(_completedAchievementIDs.begin(), _completedAchievementIDs.end(), achievementID);
            if (pos == _completedAchievementIDs.end()) {
                GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:[NSString stringWithUTF8String:achievementID.c_str()]];
                achievement.percentComplete = achievementInfo.getProcess() * 100.0 / achievementInfo.getGoal();
                achievement.showsCompletionBanner = YES;
                [achievement reportAchievementWithCompletionHandler:^(NSError *error){
                    if (!error) {
                        _completedAchievementIDs.push_back(achievementID);
                    }
                }];
            }

            achievementsIterator++;
        }
    }
}

void GameCenter::signIn()
{
    // nop
}

void GameCenter::signOut()
{
    // nop
}