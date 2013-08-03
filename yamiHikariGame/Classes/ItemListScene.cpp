//
//  ItemListScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/31.
//
//

#include "ItemListScene.h"
#include "Constants.h"
#include "GameEngine.h"

#include "DropItem.h"

#define kItemNumberLabelMarginLeft 16
#define kItemImageMarginLeft 60
#define kItemNameLabelMarginLeft 100

#define kItemCellHeight 44
#define kItemCellSeparatorMarginHorizontal 16
#define kItemCellSeparatorRadius 0.5

enum ItemCellTag {
    kItemCellTagNumberLabel = 100,
    kItemCellTagImage,
    kItemCellTagNameLabel,
};

CCScene* ItemListScene::scene()
{
    CCScene *scene = CCScene::create();

    ItemListScene *layer = ItemListScene::create();
    layer->setTitle("アイテムずかん");
    scene->addChild(layer);

    return scene;
}

void ItemListScene::onEnter()
{
    GradientLayer::onEnter();

    _items = DropItem::getItems();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCTableView *tableView = CCTableView::create(this, CCSize(windowSize.width, windowSize.height - TitleBarHeight));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setDelegate(this);
    tableView->setBounceable(false);
    tableView->reloadData();
    this->addChild(tableView);


    CCMenuItem *backTitleItem = CCMenuItemLabel::create(CCLabelTTF::create("《もどる", DefaultFontName, FontSizeNormal),
                                                        GameEngine::sharedEngine(),
                                                        menu_selector(GameEngine::showTitle));
    backTitleItem->setAnchorPoint(ccp(0, 1));

    CCMenu *menu = CCMenu::create(backTitleItem, NULL);
    menu->alignItemsVertically();
    menu->setPosition(ccp(TitleBarBackButtonMarginLeft, windowSize.height - TitleBarBackButtonMarginTop));
    this->addChild(menu);
}

void ItemListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int selectedItemIndex = cell->getIdx();

    CCDictionary *itemInfo = (CCDictionary *)_items->objectAtIndex(selectedItemIndex);
    CCLog("%s", ((CCString *)itemInfo->objectForKey("name_ja"))->getCString());
}

CCSize ItemListScene::cellSizeForTable(CCTableView *table)
{
    return CCSize(CCDirector::sharedDirector()->getWinSize().width, kItemCellHeight);
}

CCTableViewCell* ItemListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();

    CCLabelTTF *itemNumberLabel = NULL;
    CCLabelTTF *itemNameLabel = NULL;

    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();

        itemNumberLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        itemNumberLabel->setAnchorPoint(ccp(0.0, 0.5));
        itemNumberLabel->setPosition(ccp(kItemNumberLabelMarginLeft, kItemCellHeight / 2));
        itemNumberLabel->setTag(kItemCellTagNumberLabel);
        cell->addChild(itemNumberLabel);

        itemNameLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        itemNameLabel->setAnchorPoint(ccp(0.0, 0.5));
        itemNameLabel->setPosition(ccp(kItemNameLabelMarginLeft, kItemCellHeight / 2));
        itemNameLabel->setTag(kItemCellTagNameLabel);
        cell->addChild(itemNameLabel);
    }

    CCDictionary *itemInfo = (CCDictionary *)_items->objectAtIndex(idx);
    CCString *itemName = (CCString *)itemInfo->objectForKey("name_ja");
    CCString *itemImageName = (CCString *)itemInfo->objectForKey("image");

    cell->removeChildByTag(kItemCellTagImage);

    itemNumberLabel = (CCLabelTTF *)cell->getChildByTag(kItemCellTagNumberLabel);
    itemNumberLabel->setString(CCString::createWithFormat("%02d", idx + 1)->getCString());

    CCSprite *itemImage = CCSprite::createWithSpriteFrameName(itemImageName->getCString());
    itemImage->setAnchorPoint(ccp(0.0, 0.5));
    itemImage->setPosition(ccp(kItemImageMarginLeft, kItemCellHeight / 2));
    itemImage->setTag(kItemCellTagImage);
    cell->addChild(itemImage);

    itemNameLabel = (CCLabelTTF *)cell->getChildByTag(kItemCellTagNameLabel);
    itemNameLabel->setString(itemName->getCString());

    return cell;
}

unsigned int ItemListScene::numberOfCellsInTableView(CCTableView *table)
{
    return _items->count();
}