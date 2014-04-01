//
//  GameEngine.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "GameEngine.h"
#include "SimpleAudioEngine.h"
#include "sha1.h"
#include "Constants.h"
#include "GameCenter.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ItemListScene.h"
#include "Item.h"
#include "NotificationLayer.h"
#include "EveryplayManager.h"

#define kTransitionDuration 1.0
#define kGameTickInterval 0.1
#define kSurvivePoint 1
#define kStaminaConsumption 3
#define kWaitForResultDuration 3

#define kSavefileName "savedata.db"
#define kAchievementsFileName "achievements.plist"
#define kResultMessagesFileName "resultMessages.plist"

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
    _achievements = CCArray::createWithContentsOfFile(kAchievementsFileName);
    _achievements->retain();
    _resultMessages = CCArray::createWithContentsOfFile(kResultMessagesFileName);
    _resultMessages->retain();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _authenticated = false;
#endif

    return true;
}

void GameEngine::startTutorial(bool startGame)
{
    _startWithTutorial = startGame;
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, TutorialScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::finishTutorial()
{
    if (_startWithTutorial) {
        startNewGame();
    }
    else {
        CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, TitleScene::scene());
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}

void GameEngine::startNewGame()
{
    _score = 0;
    _stamina = StaminaMax;
    _foundItems.clear();

    CCDirector *director = CCDirector::sharedDirector();
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, GameScene::scene());
    director->replaceScene(transition);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EveryplayManager *everyplayManager = EveryplayManager::sharedManager();
    everyplayManager->startRecording();
#endif

    director->getScheduler()->scheduleSelector(schedule_selector(GameEngine::tick), this, kGameTickInterval, false);
}

void GameEngine::finishGame()
{
    CCDirector *director = CCDirector::sharedDirector();

    director->getScheduler()->unscheduleSelector(schedule_selector(GameEngine::tick), this);

    GameScene *gameScene = (GameScene *)director->getRunningScene()->getChildren()->objectAtIndex(0);
    gameScene->finishAnimations();

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SEGameOver);

    registerFoundItemCount();

    director->getScheduler()->scheduleSelector(schedule_selector(GameEngine::showResult), this, 0, 0, kWaitForResultDuration, false);

    registerActivities();
}

void GameEngine::tick()
{
    _stamina -= kStaminaConsumption;
    _score += kSurvivePoint;

    if (_stamina <= 0) {
        this->finishGame();
    }
}

void GameEngine::registerFoundItemCount()
{
    map<hiberlite::sqlid_t, int>::iterator iterator = _foundItems.begin();

    while (iterator != _foundItems.end()) {
        hiberlite::sqlid_t itemID = (*iterator).first;
        Item item = _items.at(itemID - 1);
        int count = (*iterator).second;

        item->updateCount(item->count + count);
        item.save();

        iterator++;
    }
}

void GameEngine::registerActivities()
{
    GameCenter *gameCenter = GameCenter::sharedCenter();

    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    int currentHighScore = userDefault->getIntegerForKey(HighScoreKey, 0);
    string currentHighScoreChecksum = userDefault->getStringForKey(HighScoreChecksumKey, "");

    if (currentHighScoreChecksum != generateScoreChecksum(currentHighScore)) {
        currentHighScore = 0;
    }

    int highScore = _score;
    if (_score > currentHighScore) {
        userDefault->setIntegerForKey(HighScoreKey, _score);
        userDefault->setStringForKey(HighScoreChecksumKey, generateScoreChecksum(_score));
        userDefault->flush();
    }
    else {
        highScore = currentHighScore;
    }
    gameCenter->registerHighScore(highScore);

    vector<Achievement> completedAchievements;

    Achievement firstPlayAchievement;
    firstPlayAchievement.setName(AchievementFirstPlayName);
    firstPlayAchievement.setIOSAchievementID(AchievementFirstPlayAchievementIDIOS);
    firstPlayAchievement.setAndroidAchievementID(AchievementFirstPlayAchievementIDAndroid);
    firstPlayAchievement.setProcess(1);
    firstPlayAchievement.setGoal(1);
    completedAchievements.push_back(firstPlayAchievement);

    CCObject *object = NULL;
    CCARRAY_FOREACH(_achievements, object) {
        CCDictionary *achievementInfo = (CCDictionary *)object;

        int count = ((CCString *)achievementInfo->objectForKey("count"))->intValue();
        CCArray *itemIDs = (CCArray *)achievementInfo->objectForKey("item_ids");

        int sum = 0;
        CCObject *itemID = NULL;
        CCARRAY_FOREACH(itemIDs, itemID) {
            int id = ((CCString *)itemID)->intValue();
            if (id <= _items.size()) {
                Item item = _items.at(id - 1);
                sum += item->count;
            }
        }

        Achievement achievement;
        achievement.setName(((CCString *)achievementInfo->objectForKey("name"))->getCString());
        achievement.setIOSAchievementID(((CCString *)achievementInfo->objectForKey("ios_achievement_id"))->getCString());
        const char* androidId = ((CCString *)achievementInfo->objectForKey("android_achievement_id"))->getCString();
        achievement.setAndroidAchievementID(string(androidId));
        achievement.setProcess(sum);
        achievement.setGoal(count);

        completedAchievements.push_back(achievement);
    }

    gameCenter->registerAchievements(&completedAchievements);
}

void GameEngine::showResult()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, ResultScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::showItemList()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, ItemListScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::showRanking()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (!getAuthenticatedIndirectly()) {
        CCMessageBox(MessageAlertShowRankingAchievementsAndroid, MessageAlertTitleAndroid);
    }
#endif
    GameCenter::sharedCenter()->showRanking();
}

void GameEngine::showAchievements()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (!getAuthenticatedIndirectly()) {
        CCMessageBox(MessageAlertShowRankingAchievementsAndroid, MessageAlertTitleAndroid);
    }
#endif
    GameCenter::sharedCenter()->showAchievements();
}

void GameEngine::showTitle()
{
    CCTransitionFade *transition = CCTransitionFade::create(kTransitionDuration, TitleScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameEngine::shareReplay()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EveryplayManager *manager = EveryplayManager::sharedManager();
    manager->playLastRecording();
#endif
}

void GameEngine::confirmResetSaveData()
{
    NotificationLayer *confirmLayer = NotificationLayer::create();
    confirmLayer->setTitle(MessageConfirmResetSaveDataTitle);
    confirmLayer->setNoticeMessage(MessageConfirmResetSaveDataText);
    confirmLayer->setNotificationType(NOTIFICATION_LAYER_YES_NO);
    confirmLayer->setActionTarget(NOTIFICATION_LAYER_ACTION_NO, CCDirector::sharedDirector(), menu_selector(CCDirector::popScene));
    confirmLayer->setActionTarget(NOTIFICATION_LAYER_ACTION_YES, this, menu_selector(GameEngine::resetSaveData));

    CCScene *scene = CCScene::create();
    scene->addChild(confirmLayer);
    CCDirector::sharedDirector()->pushScene(scene);
}

void GameEngine::resetSaveData()
{
    rebuildSaveData();

    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    userDefault->setBoolForKey(TutorialStateKey, false);
    userDefault->setIntegerForKey(HighScoreKey, 0);
    userDefault->setStringForKey(HighScoreChecksumKey, "");
    userDefault->flush();

    NotificationLayer *noticeLayer = NotificationLayer::create();
    noticeLayer->setTitle(MessageConfirmResetSaveDataTitle);
    noticeLayer->setNoticeMessage(MessageCompleteResetSaveDataText);
    noticeLayer->setNotificationType(NOTIFICATION_LAYER_OK_ONLY);
    noticeLayer->setActionTarget(NOTIFICATION_LAYER_ACTION_OK, CCDirector::sharedDirector(), menu_selector(CCDirector::popScene));

    CCScene *scene = CCScene::create();
    scene->addChild(noticeLayer);
    CCDirector::sharedDirector()->replaceScene(scene);
}

bool GameEngine::needsTutorial()
{
    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    bool tutorialDone = userDefault->getBoolForKey(TutorialStateKey, false);
    if (!tutorialDone) {
        userDefault->setBoolForKey(TutorialStateKey, true);
        userDefault->flush();
        return true;
    }
    return false;
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
        copyInitialData(saveFilePath);
    }

    _db.open(saveFilePath);

    _items = _db.getAllBeans<_Item>();
    for (int i=0; i<_items.size(); i++) {
        if (!_items.at(i)->validate()) {
            CCLog("validation error!!");

            rebuildSaveData();

            NotificationLayer *noticeLayer = NotificationLayer::create();
            noticeLayer->setTitle(MessageInvalidDataTitle);
            noticeLayer->setNoticeMessage(MessageInvalidDataText);
            noticeLayer->setNotificationType(NOTIFICATION_LAYER_OK_ONLY);
            noticeLayer->setActionTarget(NOTIFICATION_LAYER_ACTION_OK, CCDirector::sharedDirector(), menu_selector(CCDirector::popScene));

            CCScene *scene = CCScene::create();
            scene->addChild(noticeLayer);
            CCDirector::sharedDirector()->pushScene(scene);

            return;
        }
    }
}

void GameEngine::rebuildSaveData()
{
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();

    _db.close();
    _items.clear();

    string saveFilePath = fileUtils->getWritablePath().append(kSavefileName);
    copyInitialData(saveFilePath);

    _db.open(saveFilePath);
    _items = _db.getAllBeans<_Item>();
}

void GameEngine::copyInitialData(string saveFilePath)
{
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();

    string initDBFilePath = fileUtils->fullPathForFilename("init.db");

    unsigned long nSize = 0;
    unsigned char* buffer = fileUtils->getFileData(initDBFilePath.c_str(), "rb", &nSize);

    if (buffer != NULL && nSize > 0) {
        FILE *dest = fopen(saveFilePath.c_str(), "wb");
        unsigned long result = fwrite(buffer, sizeof(char), nSize, dest);
        if (result < nSize) {
            CCLog("copy savedata failed. %ld", result);
        }
        fclose(dest);
    }
    CC_SAFE_DELETE_ARRAY(buffer);
}

void GameEngine::foundItem(hiberlite::sqlid_t itemID)
{
    Item item = _items.at(itemID - 1);

    addScore(item->score);
    addStamina(item->stamina);

    if (_foundItems.find(itemID) == _foundItems.end()) {
        _foundItems[itemID] = 1;
    }
    else {
        _foundItems[itemID] += 1;
    }
}

const char *GameEngine::getResultMessage()
{
    return ((CCString *)_resultMessages->randomObject())->getCString();
}

void GameEngine::onResultTransitionDidFinish()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EveryplayManager *everyplayManager = EveryplayManager::sharedManager();
    everyplayManager->stopRecording();
    everyplayManager->mergeScore(_score);
#endif
}

string GameEngine::generateScoreChecksum(int score)
{
    char input[64];
    unsigned char digest[SHA1DigestLength];
    char buf[ChecksumLength];

    sprintf(input, "%d:%s", score, ScoreChecksumSalt);

    SHA1 sha1;
    sha1.addBytes((unsigned char *)input, strlen(input));
    sha1.getDigest(digest, SHA1DigestLength);
    sprintf(buf, "%02x%02x%02x%02x", digest[0], digest[1], digest[2], digest[3]);

    return string(buf);
}

vector<Item> *GameEngine::getItems()
{
    return &_items;
}

map<hiberlite::sqlid_t, int> *GameEngine::getFoundItems()
{
    return &_foundItems;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void GameEngine::signInGoogle()
{
    GameCenter::sharedCenter()->signIn();
}

void GameEngine::signOutGoogle()
{
    GameCenter::sharedCenter()->signOut();
}

void GameEngine::singInStateChanged(bool isSignedIn) {
    _authenticated = isSignedIn;
}

bool GameEngine::getAuthenticatedIndirectly() {
    return _authenticated;
}

#endif
