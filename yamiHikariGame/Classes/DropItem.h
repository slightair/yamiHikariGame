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
#include "Item.h"

using namespace cocos2d;

class DropItem : public CCSprite
{
protected:
    Item _item;

    bool init();
    Item selectItem();
public:
    static DropItem *create();
    void drop();

    int getItemID();
    int getStamina();
};

#endif /* defined(__yamiHikariGame__DropItem__) */
