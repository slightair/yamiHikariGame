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

#define kScoreLabelFontSize 8
#define kScoreLabelMarginX 6
#define kScoreLabelMarginY 24

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
}

void ScoreBoard::onEnter()
{
    CCNodeRGBA::onEnter();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _scoreLabel = CCLabelTTF::create("Score: 0", DefaultFontName, kScoreLabelFontSize);
    _scoreLabel->setAnchorPoint(ccp(0, 0.5));
    _scoreLabel->setPosition(ccp(kScoreLabelMarginX, windowSize.height - kScoreLabelMarginY));
    this->addChild(_scoreLabel);

    this->scheduleUpdate();
}

void ScoreBoard::setScore(int score)
{
    CCString *scoreText = CCString::createWithFormat("Score:%d", score);

    _scoreLabel->setString(scoreText->getCString());
}