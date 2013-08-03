//
//  ItemDetailScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#include "ItemDetailScene.h"
#include "Constants.h"

CCScene* ItemDetailScene::sceneWithItemInfo(CCDictionary *itemInfo)
{
    CCScene *scene = CCScene::create();

    ItemDetailScene *layer = ItemDetailScene::create();
    layer->setItemInfo(itemInfo);
    scene->addChild(layer);

    return scene;
}

void ItemDetailScene::setItemInfo(CCDictionary *itemInfo)
{
    _itemInfo = itemInfo;

    setTitle(((CCString *)itemInfo->objectForKey("name_ja"))->getCString());
}

bool ItemDetailScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        CCMenuItem *backTitleItem = CCMenuItemLabel::create(CCLabelTTF::create("《もどる", DefaultFontName, FontSizeNormal),
                                                            CCDirector::sharedDirector(),
                                                            menu_selector(CCDirector::popScene));
        backTitleItem->setAnchorPoint(ccp(0, 1));

        CCMenu *menu = CCMenu::create(backTitleItem, NULL);
        menu->alignItemsVertically();
        menu->setPosition(ccp(TitleBarBackButtonMarginLeft, windowSize.height - TitleBarBackButtonMarginTop));
        this->addChild(menu);
    }

    return result;
}