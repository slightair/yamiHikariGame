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


#define kStoryLabelMarginTop (TitleBarHeight + 74)

#define kStoryLabelWidth 278
#define kStoryLabelHeight 48

#define kSpeakLabelMarginLeft 32

#define kStoryPageMax 3

#define kStory1DungionMarginTop (TitleBarHeight + 190)
#define kStory1BraveMarginTop (kStory1DungionMarginTop + 120)

#define kStory2MonsterMarginTop (TitleBarHeight + 130)
#define kStory2StoryLabelMiddleMarginTop (TitleBarHeight + 190)
#define kStory2MarkerMarginTop (TitleBarHeight + 228)
#define kStory2BraveMarginTop (TitleBarHeight + 280)
#define kStory2BraveHeightHalf 24

#define kStory3MonsterMarginTop (TitleBarHeight + 190)
#define kStory3BraveMarginTop (TitleBarHeight + 280)
#define kStory3ObjectPaddingHorizontal 36

#define kHowtoPageMax 3

#define kHowto1DescriptionMarginTop kStoryLabelMarginTop
#define kHowto1ObjectMarginTop (kHowto1DescriptionMarginTop + 90)
#define kHowto1ArrowPaddingHorizontal 42

#define kHowto2DescriptionMarginTop kStoryLabelMarginTop
#define kHowto2ObjectMarginTop (kHowto2DescriptionMarginTop + 90)
#define kHowto2ItemPaddingHorizontal 42
#define kHowto2Description2MarginTop (kHowto2DescriptionMarginTop + 152)

#define kHowto3DescriptionMarginTop kStoryLabelMarginTop
#define kHowto3ObjectMarginTop (kHowto3DescriptionMarginTop + 90)
#define kHowto3StaminaPaddingHorizontal 24
#define kHowto3BravePaddingHorizontal 64
#define kHowto3StaminaGaugePaddingVertical 18
#define kHowto3LetsPlayMarginTop (kHowto3DescriptionMarginTop + 240)

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

    CCLabelTTF *beginingLabel = CCLabelTTF::create(MessageTutorialStory10, DefaultFontName, FontSizeNormal);
    beginingLabel->setAnchorPoint(ccp(0.5, 1.0));
    beginingLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kStoryLabelMarginTop));
    _contentLayer->addChild(beginingLabel);

    CCSprite *dungion = CCSprite::createWithSpriteFrameName("dungion.png");
    dungion->setAnchorPoint(ccp(0.5, 0.5));
    dungion->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory1DungionMarginTop));
    _contentLayer->addChild(dungion);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("braveback.png");
    brave->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory1BraveMarginTop));
    _contentLayer->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialStory10Speak, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(windowSize.width / 2 + kSpeakLabelMarginLeft, windowSize.height - kStory1BraveMarginTop));
    _contentLayer->addChild(speakLabel);
}

void TutorialScene::pageBuilderStory2()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialStoryTitle, 2, kStoryPageMax);
    setTitle(title->getCString());

    CCLabelTTF *butLabel = CCLabelTTF::create(MessageTutorialStory20, DefaultFontName, FontSizeNormal);
    butLabel->setAnchorPoint(ccp(0.5, 1.0));
    butLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kStoryLabelMarginTop));
    _contentLayer->addChild(butLabel);

    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory2MonsterMarginTop));
    _contentLayer->addChild(monster);

    CCLabelTTF *shoutLabel = CCLabelTTF::create(MessageTutorialStory20Shout, DefaultFontName, FontSizeSmall);
    shoutLabel->setAnchorPoint(ccp(0.0, 0.0));
    shoutLabel->setPosition(ccp(windowSize.width / 2 + kSpeakLabelMarginLeft, windowSize.height - kStory2MonsterMarginTop));
    _contentLayer->addChild(shoutLabel);

    CCLabelTTF *thatisLabel = CCLabelTTF::create(MessageTutorialStory21, DefaultFontName, FontSizeNormal);
    thatisLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory2StoryLabelMiddleMarginTop));
    _contentLayer->addChild(thatisLabel);

    CCSprite *exclamation = CCSprite::createWithSpriteFrameName("exclamation.png");
    exclamation->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory2MarkerMarginTop));
    _contentLayer->addChild(exclamation);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("braveback.png");
    brave->setPosition(ccp(windowSize.width / 2, windowSize.height - kStory2BraveMarginTop));
    _contentLayer->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialStory21Speak, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(windowSize.width / 2 + kSpeakLabelMarginLeft, windowSize.height - kStory2BraveMarginTop));
    _contentLayer->addChild(speakLabel);
}

void TutorialScene::pageBuilderStory3()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialStoryTitle, 3, kStoryPageMax);
    setTitle(title->getCString());

    CCLabelTTF *storyLabel = CCLabelTTF::create(MessageTutorialStory30, DefaultFontName, FontSizeNormal);
    storyLabel->setAnchorPoint(ccp(0.5, 1.0));
    storyLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kStoryLabelMarginTop));
    _contentLayer->addChild(storyLabel);

    CCSprite *monster = CCSprite::createWithSpriteFrameName("monster.png");
    monster->setPosition(ccp(windowSize.width / 2 - kStory3ObjectPaddingHorizontal, windowSize.height - kStory3MonsterMarginTop));
    _contentLayer->addChild(monster);

    CCLabelTTF *shoutLabel = CCLabelTTF::create(MessageTutorialStory30Shout, DefaultFontName, FontSizeSmall);
    shoutLabel->setAnchorPoint(ccp(0.0, 0.0));
    shoutLabel->setPosition(ccp(windowSize.width / 2 - kStory3ObjectPaddingHorizontal + kSpeakLabelMarginLeft, windowSize.height - kStory3MonsterMarginTop));
    _contentLayer->addChild(shoutLabel);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(windowSize.width / 2 + kStory3ObjectPaddingHorizontal, windowSize.height - kStory3BraveMarginTop));
    _contentLayer->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialStory30Speak, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(windowSize.width / 2 + kStory3ObjectPaddingHorizontal + kSpeakLabelMarginLeft, windowSize.height - kStory3BraveMarginTop));
    _contentLayer->addChild(speakLabel);
}

void TutorialScene::pageBuilderHowToPlay()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 1, kHowtoPageMax);
    setTitle(title->getCString());

    CCLabelTTF *howtoLabel1 = CCLabelTTF::create(MessageTutorialHowToMoveText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentLeft);
    howtoLabel1->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel1->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto1DescriptionMarginTop));
    _contentLayer->addChild(howtoLabel1);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto1ObjectMarginTop));
    _contentLayer->addChild(brave);

    CCSprite *left = CCSprite::createWithSpriteFrameName("arrowleft.png");
    left->setPosition(ccp(windowSize.width / 2 - kHowto1ArrowPaddingHorizontal, windowSize.height - kHowto1ObjectMarginTop));
    _contentLayer->addChild(left);

    CCSprite *right = CCSprite::createWithSpriteFrameName("arrowright.png");
    right->setPosition(ccp(windowSize.width / 2 + kHowto1ArrowPaddingHorizontal, windowSize.height - kHowto1ObjectMarginTop));
    _contentLayer->addChild(right);
}

void TutorialScene::pageBuilderHowToPlay2()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 2, kHowtoPageMax);
    setTitle(title->getCString());

    CCLabelTTF *howtoLabel1 = CCLabelTTF::create(MessageTutorialItemEffectText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentLeft);
    howtoLabel1->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel1->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto2DescriptionMarginTop));
    _contentLayer->addChild(howtoLabel1);

    CCSprite *item1 = CCSprite::createWithSpriteFrameName("mushroom01.png");
    item1->setPosition(ccp(windowSize.width / 2 - kHowto2ItemPaddingHorizontal, windowSize.height - kHowto2ObjectMarginTop));
    _contentLayer->addChild(item1);

    CCSprite *item2 = CCSprite::createWithSpriteFrameName("treasurebox01.png");
    item2->setPosition(ccp(windowSize.width / 2 + kHowto2ItemPaddingHorizontal, windowSize.height - kHowto2ObjectMarginTop));
    _contentLayer->addChild(item2);

    CCSprite *item3 = CCSprite::createWithSpriteFrameName("snake01.png");
    item3->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto2ObjectMarginTop));
    _contentLayer->addChild(item3);

    CCLabelTTF *howtoLabel2 = CCLabelTTF::create(MessageTutorialItemListText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentLeft);
    howtoLabel2->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel2->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto2Description2MarginTop));
    _contentLayer->addChild(howtoLabel2);
}

void TutorialScene::pageBuilderHowToPlay3()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *title = CCString::createWithFormat(MessageTutorialHowtoTitle, 3, kHowtoPageMax);
    setTitle(title->getCString());

    CCLabelTTF *howtoLabel3 = CCLabelTTF::create(MessageTutorialGameOverText, DefaultFontName, FontSizeNormal, CCSize(kStoryLabelWidth, kStoryLabelHeight), kCCTextAlignmentLeft);
    howtoLabel3->setAnchorPoint(ccp(0.5, 1.0));
    howtoLabel3->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto3DescriptionMarginTop));
    _contentLayer->addChild(howtoLabel3);

    CCSprite *staminaGaugeBackground1 = CCSprite::createWithSpriteFrameName("staminaGaugeBackground.png");
    staminaGaugeBackground1->setAnchorPoint(ccp(0.0, 0.5));
    staminaGaugeBackground1->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal, windowSize.height - (kHowto3ObjectMarginTop - kHowto3StaminaGaugePaddingVertical)));
    staminaGaugeBackground1->setOpacity(StaminaGaugeBackgroundAlpha);
    _contentLayer->addChild(staminaGaugeBackground1);

    CCSprite *staminaGauge = CCSprite::createWithSpriteFrameName("staminaGauge.png");
    staminaGauge->setAnchorPoint(ccp(0.0, 0.5));
    staminaGauge->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal, windowSize.height - (kHowto3ObjectMarginTop - kHowto3StaminaGaugePaddingVertical)));
    staminaGauge->setOpacity(StaminaGaugeAlpha);
    staminaGauge->setScaleX(0.8);
    _contentLayer->addChild(staminaGauge);

    CCLabelTTF *staminaLabel1 = CCLabelTTF::create(MessageStaminaText, DefaultFontName, FontSizeSmall);
    staminaLabel1->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal + StaminaGaugeWidth / 2, windowSize.height - (kHowto3ObjectMarginTop - kHowto3StaminaGaugePaddingVertical)));
    _contentLayer->addChild(staminaLabel1);

    CCSprite *downArrow = CCSprite::createWithSpriteFrameName("arrowdown.png");
    downArrow->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal + StaminaGaugeWidth / 2, windowSize.height - kHowto3ObjectMarginTop));
    _contentLayer->addChild(downArrow);

    CCSprite *staminaGaugeBackground2 = CCSprite::createWithSpriteFrameName("staminaGaugeBackground.png");
    staminaGaugeBackground2->setAnchorPoint(ccp(0.0, 0.5));
    staminaGaugeBackground2->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal, windowSize.height - (kHowto3ObjectMarginTop + kHowto3StaminaGaugePaddingVertical)));
    staminaGaugeBackground2->setOpacity(StaminaGaugeBackgroundAlpha);
    _contentLayer->addChild(staminaGaugeBackground2);

    CCLabelTTF *staminaLabel2 = CCLabelTTF::create(MessageStaminaText, DefaultFontName, FontSizeSmall);
    staminaLabel2->setPosition(ccp(windowSize.width / 2 + kHowto3StaminaPaddingHorizontal + StaminaGaugeWidth / 2, windowSize.height - (kHowto3ObjectMarginTop + kHowto3StaminaGaugePaddingVertical)));
    _contentLayer->addChild(staminaLabel2);

    CCSprite *brave = CCSprite::createWithSpriteFrameName("brave.png");
    brave->setRotation(90);
    brave->setPosition(ccp(windowSize.width / 2 - kHowto3BravePaddingHorizontal, windowSize.height - kHowto3ObjectMarginTop));
    _contentLayer->addChild(brave);

    CCLabelTTF *speakLabel = CCLabelTTF::create(MessageTutorialGameOverMonologueText, DefaultFontName, FontSizeSmall);
    speakLabel->setAnchorPoint(ccp(0.0, 0.0));
    speakLabel->setPosition(ccp(windowSize.width / 2 - kHowto3BravePaddingHorizontal + kSpeakLabelMarginLeft, windowSize.height - kHowto3ObjectMarginTop));
    _contentLayer->addChild(speakLabel);

    CCLabelTTF *letsPlayLabel = CCLabelTTF::create(MessageTutorialLetsPlayText, DefaultFontName, FontSizeNormal);
    letsPlayLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kHowto3LetsPlayMarginTop));
    _contentLayer->addChild(letsPlayLabel);
}