//
//  ResultScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/10.
//
//

#include "ResultScene.h"
#include "Constants.h"
#include "GameEngine.h"

#define kBraveImageMarginTop (TitleBarHeight + 48)

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})
#define kBoxMarginHorizontal 16
#define kBoxMarginTop (TitleBarHeight + 140)

#define kCommandAreaHeight 40
#define kCommandAreaMarginTop 4
#define kCommandAreaMarginBottom 24
#define kCommandButtonWidth 88
#define kCommandButtonHeight 44
#define kCommandButtonPadding 32

CCScene* ResultScene::scene()
{
    CCScene *scene = CCScene::create();

    ResultScene *layer = ResultScene::create();
    scene->addChild(layer);

    return scene;
}

bool ResultScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        setTitle(MessageResultTitle);

        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        CCSprite *braveImage = CCSprite::createWithSpriteFrameName("brave.png");
        braveImage->setRotation(90);
        braveImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kBraveImageMarginTop - braveImage->getContentSize().height / 2));
        this->addChild(braveImage);

        float boxBottom = kCommandAreaHeight + kCommandAreaMarginTop + kCommandAreaMarginBottom;
        CCDrawNode *boxNode = CCDrawNode::create();
        CCPoint contentBox[] = {ccp(kBoxMarginHorizontal, windowSize.height - kBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, windowSize.height - kBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, boxBottom),
            ccp(kBoxMarginHorizontal, boxBottom)};

        boxNode->drawPolygon(contentBox, 4, kBoxFillColor, 1, kBoxBorderColor);
        this->addChild(boxNode);

        CCLayerColor *retryLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kCommandButtonWidth, kCommandButtonHeight);
        CCLabelTTF *retryLabel = CCLabelTTF::create(MessageRetryButtonTitle, DefaultFontName, FontSizeNormal);
        retryLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));
        retryLayer->addChild(retryLabel);
        CCMenuItem *retryItem = CCMenuItemLabel::create(retryLayer,
                                                        GameEngine::sharedEngine(),
                                                        menu_selector(GameEngine::startNewGame));

        CCLayerColor *backTitleLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kCommandButtonWidth, kCommandButtonHeight);
        CCLabelTTF *backTitleLabel = CCLabelTTF::create(MessageBackTitleButtonTitle, DefaultFontName, FontSizeNormal);
        backTitleLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));
        backTitleLayer->addChild(backTitleLabel);
        CCMenuItem *backTitleItem = CCMenuItemLabel::create(backTitleLayer,
                                                            GameEngine::sharedEngine(),
                                                            menu_selector(GameEngine::showTitle));

        CCMenu *menu = CCMenu::create(retryItem, backTitleItem, NULL);
        menu->alignItemsHorizontallyWithPadding(kCommandButtonPadding);
        menu->setPosition(ccp(windowSize.width / 2, kCommandAreaMarginBottom + kCommandAreaHeight / 2));
        this->addChild(menu);
    }

    return result;
}