//
//  ItemDetailScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#ifndef __yamiHikariGame__ItemDetailScene__
#define __yamiHikariGame__ItemDetailScene__

#include "cocos2d.h"
#include "GradientLayer.h"

using namespace cocos2d;

class ItemDetailScene : public GradientLayer
{
protected:
    CCDictionary *_itemInfo;

    CCSprite *_itemImage;
    CCLabelTTF *_itemNameLabel;
    CCLabelTTF *_scoreLabel;
    CCLabelTTF *_descriptionLabel;

public:
    void setItemInfo(CCDictionary *itemInfo);

    virtual bool init();

    static CCScene* sceneWithItemInfo(CCDictionary *itemInfo);
    CREATE_FUNC(ItemDetailScene);
};

#endif /* defined(__yamiHikariGame__ItemDetailScene__) */