//
//  DropItem.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/28.
//
//

#include "DropItem.h"

CCArray *DropItem::itemInfoList = NULL;

DropItem *DropItem::create()
{
    if (!DropItem::itemInfoList) {
        DropItem::itemInfoList = CCArray::createWithContentsOfFileThreadSafe("dropItems.plist");
    }

    DropItem *dropItem = new DropItem();
    if (dropItem && dropItem->init())
    {
        dropItem->autorelease();
        return dropItem;
    }
    CC_SAFE_DELETE(dropItem);
    return NULL;
}

bool DropItem::init()
{
    if (!DropItem::itemInfoList) {
        return false;
    }

    CCDictionary *itemInfo = (CCDictionary *)DropItem::itemInfoList->randomObject();
    _nameJa = ((CCString *)itemInfo->objectForKey("name_ja"))->getCString();
    _descJa = ((CCString *)itemInfo->objectForKey("desc_ja"))->getCString();
    _imageFileName = ((CCString *)itemInfo->objectForKey("image"))->getCString();
    _stamina = ((CCString *)itemInfo->objectForKey("stamina"))->intValue();
    _score = ((CCString *)itemInfo->objectForKey("score"))->intValue();

    CCSprite::initWithSpriteFrameName(_imageFileName);

    return true;
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