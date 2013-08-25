//
//  DropItem.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "DropItem.h"
#include "GameEngine.h"

DropItem *DropItem::create(Item item)
{
    DropItem *dropItem = new DropItem();
    if (dropItem && dropItem->init(item))
    {
        dropItem->autorelease();
        return dropItem;
    }
    CC_SAFE_DELETE(dropItem);
    return NULL;
}

bool DropItem::init(Item item)
{
    _item = item;
    return CCSprite::initWithSpriteFrameName(_item->image.c_str());
}

void DropItem::drop()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    float scrollSpeed = windowSize.height / 2;
    float duration = windowSize.height / scrollSpeed;

    CCSequence *action = CCSequence::create(
                                            CCMoveBy::create(duration, ccp(0, windowSize.height + this->getContentSize().height)),
                                            CCCallFuncND::create(this, callfuncND_selector(CCSprite::removeFromParentAndCleanup), (void *)true),
                                            NULL);

    this->runAction(action);
}

int DropItem::getItemID()
{
    return _item.get_id();
}

int DropItem::getStamina()
{
    return _item->stamina;
}

int DropItem::getScore()
{
    return _item->score;
}