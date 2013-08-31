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

}