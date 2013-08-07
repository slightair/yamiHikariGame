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
#include "CCTableView.h"
#include "GradientLayer.h"
#include "Item.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class ItemListScene : public GradientLayer, public CCTableViewDelegate, public CCTableViewDataSource
{
protected:
    vector<Item> *_items;

    Item selectedItem(unsigned int index);
public:
    virtual bool init();

    virtual void scrollViewDidScroll(CCScrollView* view){};
    virtual void scrollViewDidZoom(CCScrollView* view){};

    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);

    static CCScene* scene();
    CREATE_FUNC(ItemListScene);
};

#endif /* defined(__yamiHikariGame__ItemListScene__) */
