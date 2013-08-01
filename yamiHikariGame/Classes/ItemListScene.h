//
//  ItemListScene.h
//  yamiHikariGame
//
//  Created by slightair on 2013/07/31.
//
//

#ifndef __yamiHikariGame__ItemListScene__
#define __yamiHikariGame__ItemListScene__

#include "cocos2d.h"
#include "CCScrollView.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ItemListScene : public CCLayer
{
protected:
    CCArray *_items;

    CCLayerGradient *_underlayLayer;
    CCScrollView *_itemListScrollView;

    void layoutScrollView();
public:
    virtual void onEnter();

    static CCScene* scene();
    CREATE_FUNC(ItemListScene);
};

#endif /* defined(__yamiHikariGame__ItemListScene__) */
