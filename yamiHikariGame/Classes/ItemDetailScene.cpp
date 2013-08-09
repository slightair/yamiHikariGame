//
//  ItemDetailScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#include "ItemDetailScene.h"
#include "Constants.h"
#include "GameEngine.h"

#define kItemImageMarginTop (TitleBarHeight + 68)

#define kItemNameLabelMarginLeft 16
#define kItemNameLabelMarginTop (TitleBarHeight + 14)

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})
#define kBoxMarginHorizontal 16

#define kScoreBoxMarginTop (TitleBarHeight + 160)
#define kScoreBoxHeight 32
#define kScoreLabelMarginLeft 22
#define kScoreLabelMarginTop (TitleBarHeight + 166)

#define kDescriptionBoxMarginTop (TitleBarHeight + 200)
#define kDescriptionLabelMarginHorizontal 22
#define kDescriptionLabelMarginTop (TitleBarHeight + 206)

#define kPageSelectorHeight 64
#define kPageSelectorMarginHorizontal 16
#define kPageSelectorMarginVertical 8

CCScene* ItemDetailScene::sceneWithItem(Item item)
{
    CCScene *scene = CCScene::create();

    ItemDetailScene *layer = ItemDetailScene::create();
    layer->setItem(item);
    scene->addChild(layer);

    return scene;
}

void ItemDetailScene::setItem(Item item)
{
    _item = item;

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCString *itemName = CCString::createWithFormat("%02lld %s", _item.get_id(), _item->name.c_str());
    CCString *itemScore = CCString::createWithFormat("%s:%d %s:%+d", MessageScoreText, _item->score, MessageStaminaText, _item->stamina);

    if (_itemImage) {
        _itemImage->removeFromParentAndCleanup(true);
    }
    _itemImage = CCSprite::createWithSpriteFrameName(_item->image.c_str());
    _itemImage->setAnchorPoint(ccp(0.5, 1.0));
    _itemImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kItemImageMarginTop));
    _itemImage->setScale(2.0);
    this->addChild(_itemImage);

    _itemNameLabel->setString(itemName->getCString());
    _scoreLabel->setString(itemScore->getCString());
    _descriptionLabel->setString(_item->desc.c_str());

    updatePageSelector();
}

bool ItemDetailScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        setTitle(MessageItemBookTitle);

        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        float descriptionBoxBottom = kPageSelectorHeight + kPageSelectorMarginVertical * 2;
        CCDrawNode *frameBorderNode = CCDrawNode::create();
        CCPoint scoreBox[] = {ccp(kBoxMarginHorizontal, windowSize.height - kScoreBoxMarginTop),
                              ccp(windowSize.width - kBoxMarginHorizontal, windowSize.height - kScoreBoxMarginTop),
                              ccp(windowSize.width - kBoxMarginHorizontal, windowSize.height - kScoreBoxMarginTop - kScoreBoxHeight),
                              ccp(kBoxMarginHorizontal, windowSize.height - kScoreBoxMarginTop - kScoreBoxHeight)};

        CCPoint descriptionBox[] = {ccp(kBoxMarginHorizontal, windowSize.height - kDescriptionBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, windowSize.height - kDescriptionBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, descriptionBoxBottom),
            ccp(kBoxMarginHorizontal, descriptionBoxBottom)};

        frameBorderNode->drawPolygon(scoreBox, 4, kBoxFillColor, 1, kBoxBorderColor);
        frameBorderNode->drawPolygon(descriptionBox, 4, kBoxFillColor, 1, kBoxBorderColor);

        this->addChild(frameBorderNode);

        _itemNameLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        _itemNameLabel->setAnchorPoint(ccp(0.0, 1.0));
        _itemNameLabel->setPosition(ccp(kItemNameLabelMarginLeft, windowSize.height - kItemNameLabelMarginTop));
        this->addChild(_itemNameLabel);

        _scoreLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal);
        _scoreLabel->setAnchorPoint(ccp(0.0, 1.0));
        _scoreLabel->setPosition(ccp(kScoreLabelMarginLeft, windowSize.height - kScoreLabelMarginTop));
        this->addChild(_scoreLabel);

        _descriptionLabel = CCLabelTTF::create("", DefaultFontName, FontSizeNormal, CCSize(windowSize.width - kDescriptionLabelMarginHorizontal * 2, windowSize.height - kDescriptionLabelMarginTop - descriptionBoxBottom), kCCTextAlignmentLeft);
        _descriptionLabel->setAnchorPoint(ccp(0.0, 1.0));
        _descriptionLabel->setPosition(ccp(kDescriptionLabelMarginHorizontal, windowSize.height - kDescriptionLabelMarginTop));
        this->addChild(_descriptionLabel);

        setTitleBarLeftButton(MessageBackButtonTitle, CCDirector::sharedDirector(), menu_selector(CCDirector::popScene));

        CCMenuItem *prevItem = CCMenuItemLabel::create(CCLabelTTF::create(MessagePrevButtonTitle, DefaultFontName, FontSizeNormal),
                                                       this,
                                                       menu_selector(ItemDetailScene::showPrevItem));
        prevItem->setAnchorPoint(ccp(0.0, 1.0));

        CCMenuItem *nextItem = CCMenuItemLabel::create(CCLabelTTF::create(MessageNextButtonTitle, DefaultFontName, FontSizeNormal),
                                                       this,
                                                       menu_selector(ItemDetailScene::showNextItem));
        nextItem->setAnchorPoint(ccp(1.0, 1.0));

        _pageSelectorPrev = CCMenu::create(prevItem, NULL);
        _pageSelectorPrev->setPosition(ccp(kPageSelectorMarginHorizontal, kPageSelectorHeight + kPageSelectorMarginVertical));
        this->addChild(_pageSelectorPrev);

        _pageSelectorNext = CCMenu::create(nextItem, NULL);
        _pageSelectorNext->setPosition(ccp(windowSize.width - kPageSelectorMarginHorizontal, kPageSelectorHeight + kPageSelectorMarginVertical));
        this->addChild(_pageSelectorNext);
    }

    return result;
}

void ItemDetailScene::updatePageSelector()
{
    vector<Item> *items = GameEngine::sharedEngine()->getItems();

    if (_item.get_id() == 1) {
        _pageSelectorPrev->setEnabled(false);
        _pageSelectorPrev->setOpacity(0);

        _pageSelectorNext->setEnabled(true);
        _pageSelectorNext->setOpacity(0xff);
    }
    else if (_item.get_id() == items->size()) {
        _pageSelectorPrev->setEnabled(true);
        _pageSelectorPrev->setOpacity(0xff);

        _pageSelectorNext->setEnabled(false);
        _pageSelectorNext->setOpacity(0);
    }
    else {
        _pageSelectorPrev->setEnabled(true);
        _pageSelectorPrev->setOpacity(0xff);

        _pageSelectorNext->setEnabled(true);
        _pageSelectorNext->setOpacity(0xff);
    }
}

void ItemDetailScene::showPrevItem()
{
    vector<Item> *items = GameEngine::sharedEngine()->getItems();

    Item prevItem = items->at(_item.get_id() - 2);
    setItem(prevItem);
}

void ItemDetailScene::showNextItem()
{
    vector<Item> *items = GameEngine::sharedEngine()->getItems();

    Item nextItem = items->at(_item.get_id());
    setItem(nextItem);
}