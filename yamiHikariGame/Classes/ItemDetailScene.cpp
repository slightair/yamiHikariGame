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
#define kPageSelectorMarginHorizontal 0
#define kPageSelectorMarginVertical 8
#define kPageSelectorButtonWidth 88
#define kPageSelectorButtonHeight 44

#define kItemNameLabelFormat "%02lld %s"

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

    CCString *itemName = NULL;
    CCString *itemScore = NULL;
    CCString *itemDesc = NULL;
    CCString *itemImage = NULL;

    if (_item->count > 0){
        itemName = CCString::createWithFormat(kItemNameLabelFormat, _item.get_id(), _item->name.c_str());
        itemScore = CCString::createWithFormat("%s:%d %s:%+d", MessageScoreText, _item->score, MessageStaminaText, _item->stamina);
        itemDesc = CCString::create(_item->desc);
        itemImage = CCString::create(_item->image);
    }
    else {
        itemName = CCString::createWithFormat(kItemNameLabelFormat, _item.get_id(), MessageNotFoundItemNameText);
        itemScore = CCString::createWithFormat("%s:%s %s:%s", MessageScoreText, MessageNotFoundItemScoreText, MessageStaminaText, MessageNotFoundItemStaminaText);
        itemDesc = CCString::create(MessageNotFoundItemDescText);
        itemImage = CCString::create(NotFoundItemImage);
    }

    if (_itemImage) {
        _itemImage->removeFromParentAndCleanup(true);
    }
    _itemImage = CCSprite::createWithSpriteFrameName(itemImage->getCString());
    _itemImage->setAnchorPoint(ccp(0.5, 1.0));
    _itemImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kItemImageMarginTop));
    _itemImage->setScale(2.0);
    this->addChild(_itemImage);

    _itemNameLabel->setString(itemName->getCString());
    _scoreLabel->setString(itemScore->getCString());
    _descriptionLabel->setString(itemDesc->getCString());

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

        CCLayerColor *prevLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kPageSelectorButtonWidth, kPageSelectorButtonHeight);
        CCLabelTTF *prevLabel = CCLabelTTF::create(MessagePrevButtonTitle, DefaultFontName, FontSizeNormal);
        prevLabel->setPosition(ccp(kPageSelectorButtonWidth / 2, kPageSelectorButtonHeight / 2));
        prevLayer->addChild(prevLabel);
        CCMenuItem *prevItem = CCMenuItemLabel::create(prevLayer,
                                                       this,
                                                       menu_selector(ItemDetailScene::showPrevItem));
        prevItem->setAnchorPoint(ccp(0.0, 1.0));

        CCLayerColor *nextLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kPageSelectorButtonWidth, kPageSelectorButtonHeight);
        CCLabelTTF *nextLabel = CCLabelTTF::create(MessageNextButtonTitle, DefaultFontName, FontSizeNormal);
        nextLabel->setPosition(ccp(kPageSelectorButtonWidth / 2, kPageSelectorButtonHeight / 2));
        nextLayer->addChild(nextLabel);
        CCMenuItem *nextItem = CCMenuItemLabel::create(nextLayer,
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
        _pageSelectorPrev->setVisible(false);
        _pageSelectorNext->setVisible(true);
    }
    else if (_item.get_id() == items->size()) {
        _pageSelectorPrev->setVisible(true);
        _pageSelectorNext->setVisible(false);
    }
    else {
        _pageSelectorPrev->setVisible(true);
        _pageSelectorNext->setVisible(true);
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