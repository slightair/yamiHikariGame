//
//  GradientLayer.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#ifndef __yamiHikariGame__GradientLayer__
#define __yamiHikariGame__GradientLayer__

#include "cocos2d.h"

using namespace cocos2d;

class GradientLayer : public CCLayer
{
protected:
    CCLabelTTF *_titleLabel;
    CCLayerGradient *_underlayLayer;
    CCMenuItem *_titleBarLeftButton;
public:
    virtual bool init();
    void setTitle(const char *);
    void setTitleBarLeftButton(const char *string, CCObject *target, SEL_MenuHandler selector);

    CREATE_FUNC(GradientLayer);
};

#endif /* defined(__yamiHikariGame__GradientLayer__) */
