//
//  MessageScene.cpp
//  yamiHikariGame
//
//  Created by ichiko on 13/08/06.
//
//

#include "MessageScene.h"
#include "Constants.h"

#define kMessageBoxMarginTop 180
#define kMessageBoxMarginHorizon 48

#define kMessageBoxHeight 180

#define kMessageTextPadding 4

#define kSpeakerMarginTop 100

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})

CCScene* MessageScene::scene()
{
    CCScene *scene = CCScene::create();
    MessageScene *layer = MessageScene::create();
    scene->addChild(layer);
    
    return scene;
}

void MessageScene::setNoticeMessage(const char* message)
{
    _messageLabel->setString(message);
}

bool MessageScene::init()
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
        
        setNoticeMessage("テストのめっせーじデスヨー\nはい、いいえとかいる?");
    }
    
    return result;
}