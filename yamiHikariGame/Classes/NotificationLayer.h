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

enum NotificationType {
    NOTIFICATION_LAYER_OK_ONLY, // DEFAULT
    NOTIFICATION_LAYER_YES_NO
};

enum NotificationActionType {
    NOTIFICATION_LAYER_ACTION_OK,
    NOTIFICATION_LAYER_ACTION_YES,
    NOTIFICATION_LAYER_ACTION_NO
};

class NotificationLayer : public GradientLayer
{
private:
    void updateMenuState();

protected:
    CCSprite *_speakerImage;
    CCLabelTTF *_messageLabel;

    CCMenuItem *_okMenuItem;
    CCMenu *_okMenu;

    CCMenuItem *_yesMenuItem;
    CCMenuItem *_noMenuItem;
    CCMenu *_yesNoMenu;

    NotificationType _currentNotificationType;

public:
    void setNoticeMessage(const char*);
    void setNotificationType(NotificationType t);
    void setActionTarget(NotificationActionType actionType, CCObject *rec, SEL_MenuHandler selector);

    virtual bool init();

    CREATE_FUNC(NotificationLayer);
};

#endif 
