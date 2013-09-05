//
//  GameCenterAndroid.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/30.
//
//

#include "GameCenter.h"

#include "Constants.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* _CLASS_NAME = "cc/clv/yamiHikariGame/gamecenter/GameCenter";

namespace helper {
    void callStaticVoidMethod(const char* methodName) {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, _CLASS_NAME, methodName, "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    bool callStaticBoolMethod(const char* methodName) {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, _CLASS_NAME, methodName, "()Z")) {
            bool result = (t.env->CallStaticBooleanMethod(t.classID, t.methodID) == JNI_TRUE);
            t.env->DeleteLocalRef(t.classID);
            return result;
        }
        return false;
    }

    bool callStaticBoolMethodWithString(const char* methodName, const char* strArg) {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, _CLASS_NAME, methodName, "(Ljava/lang/String;)Z")) {
            jstring jstrArg = t.env->NewStringUTF(strArg);
            bool result = (t.env->CallStaticBooleanMethod(t.classID, t.methodID, jstrArg) == JNI_TRUE);
            t.env->DeleteLocalRef(jstrArg);
            t.env->DeleteLocalRef(t.classID);
            return result;
        }
        return false;
    }

    bool callStaticBoolMethodWithStringAndInt(const char* methodName, const char* strArg1, int intArg2) {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, _CLASS_NAME, methodName, "(Ljava/lang/String;I)Z")) {
            jstring jstrArg1 = t.env->NewStringUTF(strArg1);
            bool result = (t.env->CallStaticBooleanMethod(t.classID, t.methodID, jstrArg1, intArg2) == JNI_TRUE);
            t.env->DeleteLocalRef(jstrArg1);
            t.env->DeleteLocalRef(t.classID);
            return result;
        }
        return false;
    }
}

void GameCenter::configure()
{
    // nop
}

void GameCenter::signIn()
{
    helper::callStaticVoidMethod("signIn");
}

void GameCenter::signOut()
{
    helper::callStaticVoidMethod("signOut");
}

bool GameCenter::getAuthenticated()
{
    return helper::callStaticBoolMethod("isSignedIn");
}

void GameCenter::showRanking()
{
    helper::callStaticBoolMethod("showLeaderboard");
}

void GameCenter::showAchievements()
{
    helper::callStaticBoolMethod("showAchievements");
}

void GameCenter::registerHighScore(int score)
{
    helper::callStaticBoolMethodWithStringAndInt("registerScore", LeaderboardIDHighScoreAndroid, score);
}

void GameCenter::registerAchievements(vector<Achievement> *achievements)
{
    if (getAuthenticated()) {
        vector<Achievement>::iterator achievementsIterator = achievements->begin();

        while (achievementsIterator != achievements->end()) {
            Achievement achievementInfo = *achievementsIterator;

            // _completedAchievementIDsを更新する必要があるのか?

            const char* achievementId = achievementInfo.getAndroidAchievementID().c_str();
            int goal = achievementInfo.getGoal();
            int process = achievementInfo.getProcess();
            if (process >= goal) {
                helper::callStaticBoolMethodWithString("unlockAchievement", achievementId);
            } else {
                helper::callStaticBoolMethodWithStringAndInt("incrementAchievementDiffWithServerData", achievementId, process);
            }

            achievementsIterator++;
        }
    }
}
