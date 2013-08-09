//
//  NotificationLayer.cpp
//  yamiHikariGame
//
//  Created by ichiko on 13/08/06.
//
//

#include "NotificationLayer.h"
#include "Constants.h"

#define kSpeakerMarginTop (TitleBarHeight + 50)

#define kMessageBoxMarginTop (TitleBarHeight + 140)
#define kMessageBoxMarginHorizon 48

#define kMessageBoxHeight 180

#define kMessageTextPadding 4

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})

#define kSelectionButtonMarginTop (kMessageBoxMarginTop + kMessageBoxHeight + 12)

#define kSelectionButtonWidth 90
#define kSelectionButtonHeight 36

#define kSelectionItemPadding 24

#define kSelectionButtonFillColor (ccc4(0.0, 0.0, 0.0, 0.0))

void NotificationLayer::setNoticeMessage(const char* message)
{
    _messageLabel->setString(message);
}

void NotificationLayer::setYesNoButtonAnable(bool anable)
{
    _useYesNoButton = anable;

    if (_useYesNoButton) {
        _yesNoMenu->setVisible(true);
    } else {
        _yesNoMenu->setVisible(false);
    }
}

bool NotificationLayer::init()
{
    bool result = GradientLayer::init();

    if (result)
    {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint messageBox[] = {ccp(kMessageBoxMarginHorizon, windowSize.height - kMessageBoxMarginTop),
                ccp(windowSize.width - kMessageBoxMarginHorizon, windowSize.height - kMessageBoxMarginTop),
                ccp(windowSize.width - kMessageBoxMarginHorizon, windowSize.height - kMessageBoxMarginTop - kMessageBoxHeight),
                ccp(kMessageBoxMarginHorizon, windowSize.height - kMessageBoxMarginTop - kMessageBoxHeight)};

        CCDrawNode *frameBorderNode = CCDrawNode::create();
        frameBorderNode->drawPolygon(messageBox, 4, kBoxFillColor, 1, kBoxBorderColor);
        this->addChild(frameBorderNode);

        _messageLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal, CCSize(windowSize.width - (kMessageBoxMarginHorizon + kMessageTextPadding) * 2, kMessageBoxHeight - kMessageTextPadding * 2), kCCTextAlignmentLeft);
        _messageLabel->setAnchorPoint(ccp(0, 1));
        _messageLabel->setPosition(ccp(kMessageBoxMarginHorizon + kMessageTextPadding, windowSize.height - kMessageBoxMarginTop - kMessageTextPadding));
        this->addChild(_messageLabel);

        if (_speakerImage)
        {
            _speakerImage->removeFromParentAndCleanup(true);
        }
        _speakerImage = CCSprite::createWithSpriteFrameName("brave.png");
        _speakerImage->setAnchorPoint(ccp(0.5, 1));
        _speakerImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kSpeakerMarginTop));
        this->addChild(_speakerImage);

        CCDrawNode *yesButtonNode = CCDrawNode::create();
        CCPoint buttonPoints[] = {
            ccp(0, 0),
            ccp(kSelectionButtonWidth, 0),
            ccp(kSelectionButtonWidth, kSelectionButtonHeight),
            ccp(0, kSelectionButtonHeight)
        };
        yesButtonNode->drawPolygon(buttonPoints, 4, kBoxFillColor, 1, kBoxBorderColor);

        CCLabelTTF *yesButtonLabel = CCLabelTTF::create(MessageSelectionYes, DefaultFontName, FontSizeNormal);
        yesButtonLabel->setAnchorPoint(ccp(0.5, 0.5));
        yesButtonLabel->setPosition(ccp(kSelectionButtonWidth / 2, kSelectionButtonHeight / 2));
        yesButtonNode->addChild(yesButtonLabel);

        CCLayerColor *yesButtonLayer = CCLayerColor::create(kSelectionButtonFillColor, kSelectionButtonWidth, kSelectionButtonHeight);
        yesButtonLayer->addChild(yesButtonNode);

        CCMenuItem *yesItem = CCMenuItemLabel::create(yesButtonLayer, this, menu_selector(NotificationLayer::yesButtonSelected));
        yesItem->setAnchorPoint(ccp(0.5, 1.0));

        CCDrawNode *noButtonNode = CCDrawNode::create();
        noButtonNode->drawPolygon(buttonPoints, 4, kBoxFillColor, 1, kBoxBorderColor);

        CCLabelTTF *noButtonLabel = CCLabelTTF::create(MessageSelectionNo, DefaultFontName, FontSizeNormal);
        noButtonLabel->setAnchorPoint(ccp(0.5, 0.5));
        noButtonLabel->setPosition(ccp(kSelectionButtonWidth / 2, kSelectionButtonHeight / 2));
        noButtonNode->addChild(noButtonLabel);

        CCLayerColor *noButtonLayer = CCLayerColor::create(kSelectionButtonFillColor, kSelectionButtonWidth, kSelectionButtonHeight);
        noButtonLayer->addChild(noButtonNode);

        CCMenuItem *noItem = CCMenuItemLabel::create(noButtonLayer, this, menu_selector(NotificationLayer::noButtonSelected));
        noItem->setAnchorPoint(ccp(0.5, 1.0));
        
        _yesNoMenu = CCMenu::create(yesItem, noItem, NULL);
        _yesNoMenu->setAnchorPoint(ccp(0.5, 1.0));
        _yesNoMenu->setPosition(ccp(windowSize.width / 2, windowSize.height - kSelectionButtonMarginTop));
        _yesNoMenu->alignItemsHorizontallyWithPadding(kSelectionItemPadding);
        this->addChild(_yesNoMenu);
    }
    
    return result;
}

void NotificationLayer::yesButtonSelected()
{
    CCDirector::sharedDirector()->popScene();
}

void NotificationLayer::noButtonSelected()
{
    CCDirector::sharedDirector()->popScene();
}