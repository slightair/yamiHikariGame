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

#define kItemImageMarginLeft 24
#define kItemNameLabelMarginLeft 64
#define kItemCellHeight 44
#define kItemCellSeparatorMarginHorizontal 16
#define kItemCellSeparatorRadius 0.5

CCScene* ItemListScene::scene()
{
    CCScene *scene = CCScene::create();

    ItemListScene *layer = ItemListScene::create();
    scene->addChild(layer);

    return scene;
}

void ItemListScene::onEnter()
{
    CCLayer::onEnter();

    _items = DropItem::getItems();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _underlayLayer = CCLayerGradient::create((ccColor4B){0, 0, 0, 0xff}, (ccColor4B){0x66, 0x66, 0x66, 0xff});
    CCDrawNode *lineNode = CCDrawNode::create();
    lineNode->drawSegment(ccp(TitleBarSeparatorMarginHorizontal, windowSize.height - TitleBarHeight),
                          ccp(windowSize.width - TitleBarSeparatorMarginHorizontal, windowSize.height - TitleBarHeight),
                          TitleBarSeparatorRadius, (ccColor4F){1.0, 1.0, 1.0, 1.0});
    _underlayLayer->addChild(lineNode);
    this->addChild(_underlayLayer);

    CCLabelTTF *titleLabel = CCLabelTTF::create("アイテムずかん", DefaultFontName, FontSizeNormal);
    titleLabel->setAnchorPoint(ccp(0.5, 1));
    titleLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - TitleBarTitleMarginTop));
    this->addChild(titleLabel);

    this->layoutScrollView();

    CCMenuItem *backTitleItem = CCMenuItemLabel::create(CCLabelTTF::create("《もどる", DefaultFontName, FontSizeNormal),
                                                        GameEngine::sharedEngine(),
                                                        menu_selector(GameEngine::showTitle));
    backTitleItem->setAnchorPoint(ccp(0, 1));

    CCMenu *menu = CCMenu::create(backTitleItem, NULL);
    menu->alignItemsVertically();
    menu->setPosition(ccp(TitleBarBackButtonMarginLeft, windowSize.height - TitleBarBackButtonMarginTop));
    this->addChild(menu);
}

void ItemListScene::layoutScrollView()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCDrawNode *contentLayer = CCDrawNode::create();
    float contentLayerHeight = kItemCellHeight * _items->count();
    if (contentLayerHeight < windowSize.height - TitleBarHeight) {
        contentLayerHeight = windowSize.height - TitleBarHeight;
    }
    contentLayer->setContentSize(CCSize(windowSize.width, contentLayerHeight));

    CCObject *object = NULL;
    int itemIndex = 0;
    CCARRAY_FOREACH(_items, object) {
        CCDictionary *itemInfo = (CCDictionary *)object;

        if (itemIndex > 0) {
            contentLayer->drawSegment(ccp(kItemCellSeparatorMarginHorizontal, contentLayerHeight - kItemCellHeight * itemIndex),
                                      ccp(windowSize.width - kItemCellSeparatorMarginHorizontal, contentLayerHeight - kItemCellHeight * itemIndex),
                                      kItemCellSeparatorRadius, (ccColor4F){1.0, 1.0, 1.0, 1.0});
        }

        float itemCellMidY = contentLayerHeight - kItemCellHeight * itemIndex - kItemCellHeight / 2;

        CCString *itemName = (CCString *)itemInfo->objectForKey("name_ja");
        CCString *itemImageName = (CCString *)itemInfo->objectForKey("image");

        CCSprite *itemImage = CCSprite::createWithSpriteFrameName(itemImageName->getCString());
        itemImage->setAnchorPoint(ccp(0.0, 0.5));
        itemImage->setPosition(ccp(kItemImageMarginLeft, itemCellMidY));
        contentLayer->addChild(itemImage);

        CCLabelTTF *itemNameLabel = CCLabelTTF::create(itemName->getCString(), DefaultFontName, FontSizeNormal);
        itemNameLabel->setAnchorPoint(ccp(0.0, 0.5));
        itemNameLabel->setPosition(ccp(kItemNameLabelMarginLeft, itemCellMidY));
        contentLayer->addChild(itemNameLabel);

        itemIndex++;
    }

    _itemListScrollView = CCScrollView::create(CCSize(windowSize.width, windowSize.height - TitleBarHeight), contentLayer);
    _itemListScrollView->setDirection(kCCScrollViewDirectionVertical);
    _itemListScrollView->setContentOffset(_itemListScrollView->minContainerOffset());
    _itemListScrollView->setBounceable(false);

    this->addChild(_itemListScrollView);
}