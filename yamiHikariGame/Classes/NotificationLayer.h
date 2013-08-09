//
// NotificationLayer.h
//  yamiHikariGame
//
//  Created by ichiko on 13/08/06.
//
//

#ifndef yamiHikariGame_NotificationLayer_h
#define yamiHikariGame_NotificationLayer_h

#include "cocos2d.h"
#include "GradientLayer.h"

using namespace std;
using namespace cocos2d;

class NotificationLayer : public GradientLayer
{
protected:
    CCSprite *_speakerImage;
    CCLabelTTF *_messageLabel;
    CCMenu *_yesNoMenu;

    bool _useYesNoButton;
    
public:
    void setNoticeMessage(const char*);
    void setYesNoButtonAnable(bool);

    virtual bool init();
    virtual void yesButtonSelected();
    virtual void noButtonSelected();
};

#endif 
