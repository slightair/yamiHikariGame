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
    const char *_title;
    CCLayerGradient *_underlayLayer;
public:
    virtual void onEnter();
    void setTitle(const char *);

    CREATE_FUNC(GradientLayer);
};

#endif /* defined(__yamiHikariGame__GradientLayer__) */
