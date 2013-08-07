//
//  MessageScene.h
//  yamiHikariGame
//
//  Created by ichiko on 13/08/06.
//
//

#ifndef yamiHikariGame_MessageScene_h
#define yamiHikariGame_MessageScene_h

#include "cocos2d.h"
#include "GradientLayer.h"

using namespace std;
using namespace cocos2d;

class MessageScene : public GradientLayer
{
protected:
    CCSprite *_speakerImage;
    CCLabelTTF *_messageLabel;
    
public:
    void setNoticeMessage(const char*);
    virtual bool init();
    
    static CCScene* scene();
    CREATE_FUNC(MessageScene);
};

#endif
