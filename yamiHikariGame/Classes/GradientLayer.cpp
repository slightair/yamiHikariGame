//
//  GradientLayer.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#include "GradientLayer.h"
#include "Constants.h"

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
        _titleLabel->setAnchorPoint(ccp(0.5, 1));
        _titleLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - TitleBarTitleMarginTop));
        this->addChild(_titleLabel);
    }

    return result;
}

void GradientLayer::setTitle(const char *title)
{
    _titleLabel->setString(title);
}