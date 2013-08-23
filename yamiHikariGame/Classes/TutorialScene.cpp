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


#define kContentBoxFillColor (ccc4(0x00, 0x00, 0x00, 0x00))
#define kContentBoxWidth 320
#define kContentBoxHeight (480 - TitleBarHeight)

#define kStoryLabelMarginVertical 74

#define kStoryLabelWidth 278
#define kStoryLabelHeight 48

#define kSpeakLabelMarginLeft 32

#define kStoryPageMax 3
#define kHowtoPageMax 3

#define kStoryDungionMarginLeftShift 8
#define kStoryWalkingBraveMarginTop 96
#define kStoryExclamationMarginTop 64
#define kStoryFearedBraveMarginTop 48

#define kHowto1ArrowPaddingHorizontal 42

#define kHowto2ItemPaddingHorizontal 42

#define kHowto3StaminaGaugePaddingVertical 18

void (TutorialScene::*TutorialScene::__pageBuilders[])() = {
    &TutorialScene::pageBuilderStory,
    &TutorialScene::pageBuilderStory2,
    &TutorialScene::pageBuilderStory3,
    &TutorialScene::pageBuilderHowToPlay,
    &TutorialScene::pageBuilderHowToPlay2,
    &TutorialScene::pageBuilderHowToPlay3,
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

    CCString *title = CCString::createWithFormat(MessageTutorialStoryTitle, 1, kStoryPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *beginingLabel = CCLabelTTF::create(MessageTutorialStory10, DefaultFontName, FontSizeNormal);
    beginingLabel->setAnchorPoint(ccp(0.5, 1.0));
    beginingLabel->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(beginingLabel);

    CCSprite *dungion = CCSprite::createWithSpriteFrameName("dungion.png");
    dungion->setPosition(ccp(kContentBoxWidth / 2 - kStoryDungionMarginLeftShift, kContentBoxHeight / 2));
    contentBox->addChild(dungion);

    int braveTop = kContentBoxHeight / 2 - kStoryWalkingBraveMarginTop;
    CCSprite *brave = CCSprite::createWithSpriteFrameName("braveback.png");
    brave->setPosition(ccp(kContentBoxWidth / 2, braveTop));
    contentBox->addChild(brave);

    CCLabelTTF *braveSpeakLabel = CCLabelTTF::create(MessageTutorialStory10Speak, DefaultFontName, FontSizeSmall);
    braveSpeakLabel->setAnchorPoint(ccp(0.0, 0.0));
    braveSpeakLabel->setPosition(ccp(kContentBoxWidth / 2 + kSpeakLabelMarginLeft, braveTop));
    contentBox->addChild(braveSpeakLabel);
}

void TutorialScene::pageBuilderStory2()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialStoryTitle, 2, kStoryPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *butLabel = CCLabelTTF::create(MessageTutorialStory20, DefaultFontName, FontSizeNormal);
    butLabel->setAnchorPoint(ccp(0.5, 1.0));
    butLabel->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(butLabel);

    int monsterTop = kContentBoxHeight / 2 + 64;
    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(kContentBoxWidth / 2, monsterTop));
    contentBox->addChild(monster);

    CCLabelTTF *monsterSpeakLabel = CCLabelTTF::create(MessageTutorialStory20Shout, DefaultFontName, FontSizeSmall);
    monsterSpeakLabel->setAnchorPoint(ccp(0.0, 0.0));
    monsterSpeakLabel->setPosition(ccp(kContentBoxWidth / 2 + kSpeakLabelMarginLeft, monsterTop));
    contentBox->addChild(monsterSpeakLabel);

    CCLabelTTF *thatisLabel = CCLabelTTF::create(MessageTutorialStory21, DefaultFontName, FontSizeNormal);
    thatisLabel->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight / 2));
    contentBox->addChild(thatisLabel);

    int exmarkTop = kContentBoxHeight / 2 - kStoryExclamationMarginTop;
    CCSprite *exclamation = CCSprite::createWithSpriteFrameName("exclamation.png");
    exclamation->setPosition(ccp(kContentBoxWidth / 2, exmarkTop));
    contentBox->addChild(exclamation);

    int braveTop = exmarkTop - kStoryFearedBraveMarginTop;
    CCSprite *brave = CCSprite::createWithSpriteFrameName("braveback.png");
    brave->setPosition(ccp(kContentBoxWidth / 2, braveTop));
    contentBox->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialStory21Speak, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(kContentBoxWidth / 2 + kSpeakLabelMarginLeft, braveTop));
    contentBox->addChild(speakLabel);
}

void TutorialScene::pageBuilderStory3()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialStoryTitle, 3, kStoryPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *storyLabel = CCLabelTTF::create(MessageTutorialStory30, DefaultFontName, FontSizeNormal);
    storyLabel->setAnchorPoint(ccp(0.5, 1.0));
    storyLabel->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(storyLabel);

    int monsterTop = kContentBoxHeight / 2;
    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(kContentBoxWidth / 2, monsterTop));
    contentBox->addChild(monster);

    CCLabelTTF *monsterSpeakLabel = CCLabelTTF::create(MessageTutorialStory30Shout, DefaultFontName, FontSizeSmall);
    monsterSpeakLabel->setAnchorPoint(ccp(0.0, 0.0));
    monsterSpeakLabel->setPosition(ccp(kContentBoxWidth / 2 + kSpeakLabelMarginLeft, monsterTop));
    contentBox->addChild(monsterSpeakLabel);

    int braveTop = kContentBoxHeight / 2 - kStoryExclamationMarginTop - kStoryFearedBraveMarginTop;
    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(kContentBoxWidth / 2, braveTop));
    contentBox->addChild(brave);

    CCLabelTTF *braveSpeakLabel = CCLabelTTF::create(MessageTutorialStory30Speak, DefaultFontName, FontSizeSmall);
    braveSpeakLabel->setAnchorPoint(ccp(0.0, 0.0));
    braveSpeakLabel->setPosition(ccp(kContentBoxWidth / 2 + kSpeakLabelMarginLeft, braveTop));
    contentBox->addChild(braveSpeakLabel);
}

void TutorialScene::pageBuilderHowToPlay()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 1, kHowtoPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *howtoLabel1 = CCLabelTTF::create(MessageTutorialHowToMoveText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentCenter);
    howtoLabel1->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel1->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(howtoLabel1);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight / 2));
    contentBox->addChild(brave);

    CCSprite *left = CCSprite::createWithSpriteFrameName("arrowleft.png");
    left->setPosition(ccp(kContentBoxWidth / 2 - kHowto1ArrowPaddingHorizontal, kContentBoxHeight / 2));
    contentBox->addChild(left);

    CCSprite *right = CCSprite::createWithSpriteFrameName("arrowright.png");
    right->setPosition(ccp(kContentBoxWidth / 2 + kHowto1ArrowPaddingHorizontal, kContentBoxHeight / 2));
    contentBox->addChild(right);
}

void TutorialScene::pageBuilderHowToPlay2()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 2, kHowtoPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *howtoLabel1 = CCLabelTTF::create(MessageTutorialItemEffectText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentCenter);
    howtoLabel1->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel1->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(howtoLabel1);

    CCSprite *item1 = CCSprite::createWithSpriteFrameName("mushroom01.png");
    item1->setPosition(ccp(kContentBoxWidth / 2 - kHowto2ItemPaddingHorizontal, kContentBoxHeight / 2));
    contentBox->addChild(item1);

    CCSprite *item2 = CCSprite::createWithSpriteFrameName("treasurebox01.png");
    item2->setPosition(ccp(kContentBoxWidth / 2 + kHowto2ItemPaddingHorizontal, kContentBoxHeight / 2));
    contentBox->addChild(item2);

    CCSprite *item3 = CCSprite::createWithSpriteFrameName("snake01.png");
    item3->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight / 2));
    contentBox->addChild(item3);

    CCLabelTTF *howtoLabel2 = CCLabelTTF::create(MessageTutorialItemListText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentCenter);
    howtoLabel2->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel2->setPosition(ccp(kContentBoxWidth / 2, kStoryLabelMarginVertical + kStoryLabelHeight));
    contentBox->addChild(howtoLabel2);
}

void TutorialScene::pageBuilderHowToPlay3()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 3, kHowtoPageMax);
    setTitle(title->getCString());

    CCLayerColor *contentBox = CCLayerColor::create(kContentBoxFillColor, kContentBoxWidth, kContentBoxHeight);
    contentBox->setPosition(ccp(windowSize.width / 2 - kContentBoxWidth / 2, windowSize.height -  TitleBarHeight - kContentBoxHeight));
    _contentLayer->addChild(contentBox);

    CCLabelTTF *howtoLabel3 = CCLabelTTF::create(MessageTutorialGameOverText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentCenter);
    howtoLabel3->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel3->setPosition(ccp(kContentBoxWidth / 2, kContentBoxHeight - kStoryLabelMarginVertical));
    contentBox->addChild(howtoLabel3);

    int staminaLeft = kContentBoxWidth * 0.75;

    CCSprite *staminaGaugeBackground1 = CCSprite::createWithSpriteFrameName("staminaGaugeBackground.png");
    staminaGaugeBackground1->setAnchorPoint(ccp(0.0, 0.5));
    staminaGaugeBackground1->setPosition(ccp(staminaLeft - StaminaGaugeWidth / 2, kContentBoxHeight / 2 + kHowto3StaminaGaugePaddingVertical));
    staminaGaugeBackground1->setOpacity(StaminaGaugeBackgroundAlpha);
    contentBox->addChild(staminaGaugeBackground1);

    CCSprite *staminaGauge = CCSprite::createWithSpriteFrameName("staminaGauge.png");
    staminaGauge->setAnchorPoint(ccp(0.0, 0.5));
    staminaGauge->setPosition(ccp(staminaLeft - StaminaGaugeWidth / 2, kContentBoxHeight / 2 + kHowto3StaminaGaugePaddingVertical));
    staminaGauge->setOpacity(StaminaGaugeAlpha);
    staminaGauge->setScaleX(0.8);
    contentBox->addChild(staminaGauge);

    CCLabelTTF *staminaLabel1 = CCLabelTTF::create(MessageStaminaText, DefaultFontName, FontSizeSmall);
    staminaLabel1->setPosition(ccp(staminaLeft, kContentBoxHeight / 2 + kHowto3StaminaGaugePaddingVertical));
    contentBox->addChild(staminaLabel1);

    CCSprite *downArrow = CCSprite::createWithSpriteFrameName("arrowdown.png");
    downArrow->setPosition(ccp(staminaLeft, kContentBoxHeight / 2));
    contentBox->addChild(downArrow);

    CCSprite *staminaGaugeBackground2 = CCSprite::createWithSpriteFrameName("staminaGaugeBackground.png");
    staminaGaugeBackground2->setAnchorPoint(ccp(0.0, 0.5));
    staminaGaugeBackground2->setPosition(ccp(staminaLeft - StaminaGaugeWidth / 2, kContentBoxHeight / 2 - kHowto3StaminaGaugePaddingVertical));
    staminaGaugeBackground2->setOpacity(StaminaGaugeBackgroundAlpha);
    contentBox->addChild(staminaGaugeBackground2);

    CCLabelTTF *staminaLabel2 = CCLabelTTF::create(MessageStaminaText, DefaultFontName, FontSizeSmall);
    staminaLabel2->setPosition(ccp(staminaLeft, kContentBoxHeight / 2 + kHowto3StaminaGaugePaddingVertical));
    contentBox->addChild(staminaLabel2);

    int braveLeft = kContentBoxWidth / 4;
    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setRotation(90);
    brave->setPosition(ccp(braveLeft, kContentBoxHeight / 2));
    contentBox->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialGameOverMonologueText, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(braveLeft + kSpeakLabelMarginLeft, kContentBoxHeight / 2));
    contentBox->addChild(speakLabel);

    CCLabelTTF *letsPlayLabel = CCLabelTTF::create(MessageTutorialLetsPlayText, DefaultFontName, FontSizeNormal);
    letsPlayLabel->setAnchorPoint(ccp(0.5, 0.0));
    letsPlayLabel->setPosition(ccp(kContentBoxWidth / 2, kStoryLabelMarginVertical));
    contentBox->addChild(letsPlayLabel);
}