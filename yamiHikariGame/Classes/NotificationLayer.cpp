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
#define kMessageBoxMarginHorizontal 16

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})

#define kMessageLabelMarginHorizontal 22
#define kMessageLabelMarginVertical 6

#define kActionButtonFillColor (ccc4(0.0, 0.0, 0.0, 0.0))

#define kCommandAreaHeight 40
#define kCommandAreaMarginTop 4
#define kCommandAreaMarginBottom 24
#define kCommandButtonWidth 88
#define kCommandButtonHeight 44
#define kCommandButtonPadding 32

void NotificationLayer::setNoticeMessage(const char* message)
{
    _messageLabel->setString(message);
}

void NotificationLayer::setNotificationType(NotificationType t)
{
    _currentNotificationType = t;
    updateMenuState();
}

void NotificationLayer::updateMenuState()
{
    switch (_currentNotificationType) {
        case NOTIFICATION_LAYER_OK_ONLY:
            _okMenu->setVisible(true);
            _yesNoMenu->setVisible(false);
            break;
        case NOTIFICATION_LAYER_YES_NO:
            _okMenu->setVisible(false);
            _yesNoMenu->setVisible(true);
            break;
    }
}

void NotificationLayer::setActionTarget(NotificationActionType actionType, CCObject *rec, SEL_MenuHandler selector)
{
    switch (actionType) {
        case NOTIFICATION_LAYER_ACTION_OK:
            _okMenuItem->setTarget(rec, selector);
            break;
        case NOTIFICATION_LAYER_ACTION_YES:
            _yesMenuItem->setTarget(rec, selector);
            break;
        case NOTIFICATION_LAYER_ACTION_NO:
            _noMenuItem->setTarget(rec, selector);
            break;
    }
}

bool NotificationLayer::init()
{
    bool result = GradientLayer::init();

    if (result)
    {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        float messageBoxBottom = kCommandAreaHeight + kCommandAreaMarginTop + kCommandAreaMarginBottom;

        CCDrawNode *frameBorderNode = CCDrawNode::create();
        CCPoint messageBox[] = {ccp(kMessageBoxMarginHorizontal, windowSize.height - kMessageBoxMarginTop),
            ccp(windowSize.width - kMessageBoxMarginHorizontal, windowSize.height - kMessageBoxMarginTop),
            ccp(windowSize.width - kMessageBoxMarginHorizontal, messageBoxBottom),
            ccp(kMessageBoxMarginHorizontal, messageBoxBottom)};
        frameBorderNode->drawPolygon(messageBox, 4, kBoxFillColor, 1, kBoxBorderColor);
        this->addChild(frameBorderNode);

        _messageLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal, CCSize(windowSize.width - kMessageBoxMarginHorizontal * 2, (windowSize.height - kMessageBoxMarginTop) - messageBoxBottom - kMessageLabelMarginVertical * 2), kCCTextAlignmentLeft);
        _messageLabel->setAnchorPoint(ccp(0, 1));
        _messageLabel->setPosition(ccp(kMessageLabelMarginHorizontal, windowSize.height - kMessageBoxMarginTop - kMessageLabelMarginVertical));
        this->addChild(_messageLabel);

        if (_speakerImage)
        {
            _speakerImage->removeFromParentAndCleanup(true);
        }
        _speakerImage = CCSprite::createWithSpriteFrameName("brave.png");
        _speakerImage->setAnchorPoint(ccp(0.5, 1.0));
        _speakerImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kSpeakerMarginTop));
        this->addChild(_speakerImage);

        CCLabelTTF *okButtonLabel = CCLabelTTF::create(MessageSelectionOK, DefaultFontName, FontSizeNormal);
        okButtonLabel->setAnchorPoint(ccp(0.5, 0.5));
        okButtonLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));

        CCLayerColor *okButtonLayer = CCLayerColor::create(kActionButtonFillColor, kCommandButtonWidth, kCommandButtonHeight);
        okButtonLayer->addChild(okButtonLabel);

        _okMenuItem = CCMenuItemLabel::create(okButtonLayer);
        _okMenuItem->setAnchorPoint(ccp(0.5, 0.5));

        _okMenu = CCMenu::create(_okMenuItem, NULL);
        _okMenu->setAnchorPoint(ccp(0.5, 1.0));
        _okMenu->setPosition(ccp(windowSize.width / 2, kCommandAreaMarginBottom + kCommandAreaHeight / 2));
        _okMenu->alignItemsHorizontallyWithPadding(kCommandButtonPadding);
        this->addChild(_okMenu);

        CCLabelTTF *yesButtonLabel = CCLabelTTF::create(MessageSelectionYes, DefaultFontName, FontSizeNormal);
        yesButtonLabel->setAnchorPoint(ccp(0.5, 0.5));
        yesButtonLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));

        CCLayerColor *yesButtonLayer = CCLayerColor::create(kActionButtonFillColor, kCommandButtonWidth, kCommandButtonHeight);
        yesButtonLayer->addChild(yesButtonLabel);

        _yesMenuItem = CCMenuItemLabel::create(yesButtonLayer);
        _yesMenuItem->setAnchorPoint(ccp(0.5, 0.5));

        CCLabelTTF *noButtonLabel = CCLabelTTF::create(MessageSelectionNo, DefaultFontName, FontSizeNormal);
        noButtonLabel->setAnchorPoint(ccp(0.5, 0.5));
        noButtonLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));

        CCLayerColor *noButtonLayer = CCLayerColor::create(kActionButtonFillColor, kCommandButtonWidth, kCommandButtonHeight);
        noButtonLayer->addChild(noButtonLabel);

        _noMenuItem = CCMenuItemLabel::create(noButtonLayer);
        _noMenuItem->setAnchorPoint(ccp(0.5, 0.5));

        _yesNoMenu = CCMenu::create(_yesMenuItem, _noMenuItem, NULL);
        _yesNoMenu->setAnchorPoint(ccp(0.5, 1.0));
        _yesNoMenu->setPosition(ccp(windowSize.width / 2, kCommandAreaMarginBottom + kCommandAreaHeight / 2));
        _yesNoMenu->alignItemsHorizontallyWithPadding(kCommandButtonPadding);
        this->addChild(_yesNoMenu);

        updateMenuState();
    }
    
    return result;
}
