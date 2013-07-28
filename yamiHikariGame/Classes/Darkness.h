//
//  Darkness.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/25.
//
//

#ifndef __yamiHikariGame__Darkness__
#define __yamiHikariGame__Darkness__

#include "cocos2d.h"

using namespace cocos2d;

class Darkness : public CCLayerColor
{
protected:
    CCDrawNode *_lightNode;

    bool init(CCPoint initialLightPosition);
public:
    static Darkness *create(CCPoint initialLightPosition);
    void setLightPosition(CCPoint position);
};

#endif /* defined(__yamiHikariGame__Darkness__) */
