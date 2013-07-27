//
//  Darkness.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/25.
//
//

#include "Darkness.h"

#define kDarknessAlpha 0xaa
#define kLightSize 80

Darkness *Darkness::create(CCPoint initialLightPosition)
{
    Darkness *darkness = new Darkness();
    if (darkness && darkness->init(initialLightPosition))
    {
        darkness->autorelease();
        return darkness;
    }
    CC_SAFE_DELETE(darkness);
    return NULL;
}

bool Darkness::init(CCPoint initialLightPosition)
{
    CCLayerColor::initWithColor((ccColor4B){0x00, 0x00, 0x00, kDarknessAlpha});

    _lightNode = CCDrawNode::create();
    _lightNode->drawDot(ccp(0, 0), kLightSize, (ccColor4F){1.0, 1.0, 1.0, 1.0});
    _lightNode->setBlendFunc((ccBlendFunc){GL_DST_COLOR, GL_ONE});
    _lightNode->setPosition(initialLightPosition);

    this->addChild(_lightNode);

    return true;
}

void Darkness::setLightPosition(CCPoint position)
{
    _lightNode->setPosition(position);
}