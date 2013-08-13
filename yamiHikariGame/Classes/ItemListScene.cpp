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
#include "ItemDetailScene.h"

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
    scene->addChild(layer);

    return scene;
}

bool ItemListScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        setTitle(MessageItemBookTitle);

        _items = GameEngine::sharedEngine()->getItems();

        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        CCTableView *tableView = CCTableView::create(this, CCSize(windowSize.width, windowSize.height - TitleBarHeight));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setDelegate(this);
        tableView->setBounceable(false);
        tableView->reloadData();
        this->addChild(tableView);

        setTitleBarLeftButton(MessageBackButtonTitle, GameEngine::sharedEngine(), menu_selector(GameEngine::showTitle));
    }

    return result;
}

Item ItemListScene::selectedItem(unsigned int index)
{
    return _items->at(_items->size() - index - 1);
}

void ItemListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    Item item = selectedItem(cell->getIdx());
    CCScene *scene = ItemDetailScene::sceneWithItem(item);

    CCDirector::sharedDirector()->pushScene(scene);
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

    Item item = selectedItem(idx);

    cell->removeChildByTag(kItemCellTagImage);

    itemNumberLabel = (CCLabelTTF *)cell->getChildByTag(kItemCellTagNumberLabel);
    itemNumberLabel->setString(CCString::createWithFormat("%02lld", item.get_id())->getCString());

    CCSprite *itemImage = NULL;
    itemNameLabel = (CCLabelTTF *)cell->getChildByTag(kItemCellTagNameLabel);

    if (item->count > 0) {
        itemImage = CCSprite::createWithSpriteFrameName(item->image.c_str());
        itemNameLabel->setString(item->name.c_str());
    } else {
        itemImage = CCSprite::createWithSpriteFrameName(NotFoundItemImage);
        itemNameLabel->setString(MessageNotFoundItemNameText);
    }

    itemImage->setAnchorPoint(ccp(0.0, 0.5));
    itemImage->setPosition(ccp(kItemImageMarginLeft, kItemCellHeight / 2));
    itemImage->setTag(kItemCellTagImage);
    cell->addChild(itemImage);

    return cell;
}

unsigned int ItemListScene::numberOfCellsInTableView(CCTableView *table)
{
    return _items->size();
}
