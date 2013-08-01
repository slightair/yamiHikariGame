//
//  DropItem.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#ifndef __yamiHikariGame__DropItem__
#define __yamiHikariGame__DropItem__

#include "cocos2d.h"

using namespace cocos2d;

class DropItem : public CCSprite
{
protected:
    bool init();
    static void loadDropItemsInfo();

    const char *_nameJa;
    const char *_descJa;
    const char *_imageFileName;
    int _stamina;
    int _score;
public:
    static DropItem *create();
    const char *getName();
    const char *getDesc();
    const char *getImageFileName();
    int getStamina();
    int getScore();
    void drop();

#warning tentative
    static CCArray *getItems();
};

#endif /* defined(__yamiHikariGame__DropItem__) */
