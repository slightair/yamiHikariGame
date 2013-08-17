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

void (TutorialScene::*TutorialScene::__pageBuilder[])() = {
    &TutorialScene::hoge,
    &TutorialScene::fuga,
    &TutorialScene::piyo,
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

    void (TutorialScene::*pageBuilder)() = TutorialScene::__pageBuilder[_page];
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

void TutorialScene::hoge()
{
    CCLog("hoge");
}

void TutorialScene::fuga()
{
    CCLog("fuga");
}

void TutorialScene::piyo()
{
    CCLog("piyo");
}