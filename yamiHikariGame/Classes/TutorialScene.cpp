//
//  TutorialScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/14.
//
//

#include "TutorialScene.h"
#include "Constants.h"
#include "GameEngine.h"

#define kBraveMarginTop (TitleBarHeight + 74)

void (TutorialScene::*TutorialScene::__pageBuilders[])() = {
    &TutorialScene::pageBuilderStory,
    &TutorialScene::pageBuilderHowToPlay,
    NULL};

CCScene* TutorialScene::scene()
{
    CCScene *scene = CCScene::create();

    TutorialScene *layer = TutorialScene::create();
    scene->addChild(layer);

    return scene;
}

bool TutorialScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        setTitle(MessageTutorialTitle);

        _page = -1;
        _isPageEnd = false;

        _contentLayer = CCNode::create();
        this->addChild(_contentLayer);

        nextPage();
    }

    return result;
}

void TutorialScene::nextPage()
{
    _page++;

    void (TutorialScene::*pageBuilder)() = TutorialScene::__pageBuilders[_page];
    if (pageBuilder) {
        _contentLayer->removeAllChildren();
        (this->*pageBuilder)();
    }
    else {
        _isPageEnd = true;
        finishTutorial();
    }
}

void TutorialScene::finishTutorial()
{
    GameEngine::sharedEngine()->finishTutorial();
}

void TutorialScene::onEnter()
{
    GradientLayer::onEnter();

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void TutorialScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    GradientLayer::onExit();
}

void TutorialScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!_isPageEnd) {
        nextPage();
    }
}

void TutorialScene::pageBuilderStory()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(windowSize.width / 2, windowSize.height - (TitleBarHeight + 24)));
    _contentLayer->addChild(monster);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(windowSize.width / 2, windowSize.height - kBraveMarginTop));
    _contentLayer->addChild(brave);

    CCLabelTTF *speakLabel1 = CCLabelTTF::create("なんかおいかけられてる", DefaultFontName, FontSizeSmall);
    speakLabel1->setAnchorPoint(ccp(0.0, 0.5));
    speakLabel1->setPosition(ccp(windowSize.width / 2 + 24, windowSize.height - kBraveMarginTop + 8));
    _contentLayer->addChild(speakLabel1);

    CCLabelTTF *speakLabel2 = CCLabelTTF::create("こわい、にげよう", DefaultFontName, FontSizeSmall);
    speakLabel2->setAnchorPoint(ccp(0.0, 0.5));
    speakLabel2->setPosition(ccp(windowSize.width / 2 + 24, windowSize.height - kBraveMarginTop - 8));
    _contentLayer->addChild(speakLabel2);
}

void TutorialScene::pageBuilderHowToPlay()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(windowSize.width / 2, windowSize.height - kBraveMarginTop));
    _contentLayer->addChild(brave);
}