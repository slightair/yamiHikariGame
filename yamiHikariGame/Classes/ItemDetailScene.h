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
#include "Item.h"

using namespace std;
using namespace cocos2d;
using namespace hiberlite;

class ItemDetailScene : public GradientLayer
{
protected:
    bean_ptr<Item> _item;

    CCSprite *_itemImage;
    CCLabelTTF *_itemNameLabel;
    CCLabelTTF *_scoreLabel;
    CCLabelTTF *_descriptionLabel;

public:
    void setItem(bean_ptr<Item> item);

    virtual bool init();

    static CCScene* sceneWithItem(bean_ptr<Item> item);
    CREATE_FUNC(ItemDetailScene);
};

#endif /* defined(__yamiHikariGame__ItemDetailScene__) */
