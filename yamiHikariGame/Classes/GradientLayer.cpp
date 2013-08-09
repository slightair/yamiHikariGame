//
//  GradientLayer.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#include "GradientLayer.h"
#include "Constants.h"

#define kButtonLabelTag 100

bool GradientLayer::init()
{
    bool result = CCLayer::init();
    if (result) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        _underlayLayer = CCLayerGradient::create((ccColor4B){0, 0, 0, 0xff}, (ccColor4B){0x66, 0x66, 0x66, 0xff});
        CCDrawNode *lineNode = CCDrawNode::create();
        lineNode->drawSegment(ccp(TitleBarSeparatorMarginHorizontal, windowSize.height - TitleBarHeight),
                              ccp(windowSize.width - TitleBarSeparatorMarginHorizontal, windowSize.height - TitleBarHeight),
                              TitleBarSeparatorRadius, (ccColor4F){1.0, 1.0, 1.0, 1.0});
        _underlayLayer->addChild(lineNode);
        this->addChild(_underlayLayer);

        _titleLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        _titleLabel->setAnchorPoint(ccp(0.5, 1.0));
        _titleLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - TitleBarTitleMarginTop));
        this->addChild(_titleLabel);

        CCLayerColor *leftButtonLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, TitleBarButtonWidth, TitleBarButtonHeight);
        CCLabelTTF *leftButtonLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        leftButtonLabel->setPosition(ccp(TitleBarButtonWidth / 2, TitleBarButtonHeight / 2));
        _titleBarLeftButton = CCMenuItemLabel::create(leftButtonLayer);
        _titleBarLeftButton->addChild(leftButtonLabel, 0, kButtonLabelTag);

        CCMenu *leftMenu = CCMenu::create(_titleBarLeftButton, NULL);
        leftMenu->setPosition(ccp(TitleBarLeftButtonMarginLeft + TitleBarButtonWidth / 2, windowSize.height - TitleBarLeftButtonMarginTop - TitleBarButtonHeight / 2));
        leftMenu->setVisible(false);

        this->addChild(leftMenu);
    }

    return result;
}

void GradientLayer::setTitle(const char *title)
{
    _titleLabel->setString(title);
}

void GradientLayer::setTitleBarLeftButton(const char *string, CCObject *target, SEL_MenuHandler selector)
{
    CCLabelTTF *label = (CCLabelTTF *)_titleBarLeftButton->getChildByTag(kButtonLabelTag);
    label->setString(string);

    _titleBarLeftButton->setTarget(target, selector);
    _titleBarLeftButton->getParent()->setVisible(true);
}