//
//  ScoreBoard.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "ScoreBoard.h"
#include "Constants.h"
#include "GameEngine.h"

#define kScoreLabelMarginLeft 6
#define kScoreLabelMarginTop 12

#define kStaminaGaugeMarginRight 6
#define kStaminaGaugeMarginTop 12

ScoreBoard *ScoreBoard::create()
{
    ScoreBoard *board = new ScoreBoard();
    if (board && board->init())
    {
        board->autorelease();
        return board;
    }
    CC_SAFE_DELETE(board);
    return NULL;
}

void ScoreBoard::update(float delta)
{
    GameEngine *engine = GameEngine::sharedEngine();

    this->setScore(engine->getScore());
    this->setStamina(engine->getStamina());
}

void ScoreBoard::onEnter()
{
    CCNodeRGBA::onEnter();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _staminaGaugeBackground = CCSprite::createWithSpriteFrameName("staminaGaugeBackground.png");
    _staminaGaugeBackground->setAnchorPoint(ccp(1.0, 0.5));
    _staminaGaugeBackground->setPosition(ccp(windowSize.width - kStaminaGaugeMarginRight, windowSize.height - kStaminaGaugeMarginTop));
    _staminaGaugeBackground->setOpacity(StaminaGaugeBackgroundAlpha);
    this->addChild(_staminaGaugeBackground);

    _staminaGauge = CCSprite::createWithSpriteFrameName("staminaGauge.png");
    _staminaGauge->setAnchorPoint(ccp(0.0, 0.5));
    _staminaGauge->setPosition(ccp(windowSize.width - kStaminaGaugeMarginRight - StaminaGaugeWidth, windowSize.height - kStaminaGaugeMarginTop));
    _staminaGauge->setOpacity(StaminaGaugeAlpha);
    this->addChild(_staminaGauge);

    _staminaLabel = CCLabelTTF::create(MessageStaminaText, DefaultFontName, FontSizeSmall);
    _staminaLabel->setPosition(ccp(windowSize.width - kStaminaGaugeMarginRight - StaminaGaugeWidth / 2, windowSize.height - kScoreLabelMarginTop));
    this->addChild(_staminaLabel);

    _scoreLabel = CCLabelTTF::create(MessageScoreText, DefaultFontName, FontSizeSmall);
    _scoreLabel->setAnchorPoint(ccp(0.0, 0.5));
    _scoreLabel->setPosition(ccp(kScoreLabelMarginLeft, windowSize.height - kScoreLabelMarginTop));
    this->addChild(_scoreLabel);

    this->scheduleUpdate();
}

void ScoreBoard::setScore(int score)
{
    CCString *scoreText = CCString::createWithFormat("%s %d", MessageScoreText, score);

    _scoreLabel->setString(scoreText->getCString());
}

void ScoreBoard::setStamina(int stamina)
{
    float rate = stamina * 1.0 / StaminaMax;
    if (rate < 0) {
        rate = 0;
    }
    _staminaGauge->setScaleX(rate);
}