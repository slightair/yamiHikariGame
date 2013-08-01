//
//  ItemDetailScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/01.
//
//

#include "ItemDetailScene.h"
#include "Constants.h"

CCScene* ItemDetailScene::scene()
{
    CCScene *scene = CCScene::create();

    ItemDetailScene *layer = ItemDetailScene::create();
    scene->addChild(layer);

    return scene;
}

void ItemDetailScene::onEnter()
{
    GradientLayer::onEnter();
}