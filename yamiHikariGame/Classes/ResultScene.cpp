//
//  ResultScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/10.
//
//

#include "ResultScene.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Item.h"

#define kItemCountMax 999

#define kBraveImageMarginTop (TitleBarHeight + 48)

#define kBraveMessageMarginTop (TitleBarHeight + 72)
#define kBraveMessageAdjustX 32

#define kBoxFillColor ((ccColor4F){0.0, 0.0, 0.0, 0.0})
#define kBoxBorderColor ((ccColor4F){1.0, 1.0, 1.0, 1.0})
#define kBoxMarginHorizontal 16
#define kBoxMarginTop (TitleBarHeight + 160)

#define kScoreLabelMarginTop (TitleBarHeight + 140)

#define kItemCountLabelMarginTop (TitleBarHeight + 184)

#define kItemImageAreaMarginTop (TitleBarHeight + 234)
#define kNumberOfLineItems 8
#define kItemImageSize 24
#define kItemImageMarginHorizontal 8
#define kItemImageMarginVertical 16
#define kItemImageCountLabelAdjustY 6

#define kCommandAreaHeight 32
#define kCommandAreaMarginTop 14
#define kCommandAreaMarginBottom 18
#define kCommandButtonWidth 88
#define kCommandButtonHeight 64
#define kCommandButtonPadding 32

CCScene* ResultScene::scene()
{
    CCScene *scene = CCScene::create();

    ResultScene *layer = ResultScene::create();
    scene->addChild(layer);

    return scene;
}

bool ResultScene::init()
{
    bool result = GradientLayer::init();

    if (result) {
        setTitle(MessageResultTitle);

        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        GameEngine *engine = GameEngine::sharedEngine();

        CCSprite *braveImage = CCSprite::createWithSpriteFrameName("brave.png");
        braveImage->setRotation(90);
        braveImage->setPosition(ccp(windowSize.width / 2, windowSize.height - kBraveImageMarginTop - braveImage->getContentSize().height / 2));
        this->addChild(braveImage);

        CCLabelTTF *messageLabel = CCLabelTTF::create(engine->getResultMessage(), DefaultFontName, FontSizeSmall);
        messageLabel->setPosition(ccp(windowSize.width / 2 + kBraveMessageAdjustX, windowSize.height - kBraveMessageMarginTop));
        messageLabel->setAnchorPoint(ccp(0.0, 0.0));
        this->addChild(messageLabel);

        float boxBottom = kCommandAreaHeight + kCommandAreaMarginTop + kCommandAreaMarginBottom;
        CCDrawNode *boxNode = CCDrawNode::create();
        CCPoint contentBox[] = {ccp(kBoxMarginHorizontal, windowSize.height - kBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, windowSize.height - kBoxMarginTop),
            ccp(windowSize.width - kBoxMarginHorizontal, boxBottom),
            ccp(kBoxMarginHorizontal, boxBottom)};

        boxNode->drawPolygon(contentBox, 4, kBoxFillColor, 1, kBoxBorderColor);
        this->addChild(boxNode);

        CCString *scoreText = CCString::createWithFormat("%s:%d", MessageScoreText, engine->getScore());
        CCLabelTTF *scoreLabel = CCLabelTTF::create(scoreText->getCString(), DefaultFontName, FontSizeNormal);
        scoreLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kScoreLabelMarginTop));
        this->addChild(scoreLabel);

        map<hiberlite::sqlid_t, int> *foundItems = engine->getFoundItems();
        map<hiberlite::sqlid_t, int>::iterator foundItemsIterator = foundItems->begin();
        vector<Item> *items = engine->getItems();

        float itemImageAreaMarginLeft = windowSize.width / 2 - ((kNumberOfLineItems / 2 - 1) * (kItemImageSize + kItemImageMarginHorizontal)) - kItemImageMarginHorizontal / 2 - kItemImageSize / 2;

        int sumFoundItems = 0;
        int index = 0;
        while (foundItemsIterator != foundItems->end()) {
            hiberlite::sqlid_t itemID = (*foundItemsIterator).first;
            Item item = items->at(itemID - 1);
            int count = (*foundItemsIterator).second;

            const char *imageFileName = item->image.c_str();

            int posX = index % kNumberOfLineItems;
            int posY = index / kNumberOfLineItems;

            CCPoint imagePosition = ccp(itemImageAreaMarginLeft + (kItemImageSize + kItemImageMarginHorizontal) * posX,
                                        windowSize.height - kItemImageAreaMarginTop - (kItemImageSize + kItemImageMarginVertical) * posY);
            CCSprite *itemImage = CCSprite::createWithSpriteFrameName(imageFileName);
            itemImage->setPosition(imagePosition);
            this->addChild(itemImage);

            sumFoundItems += count;
            if (count > kItemCountMax) {
                count = kItemCountMax;
            }

            CCString *countText = CCString::createWithFormat("%d", count);
            CCLabelTTF *countLabel = CCLabelTTF::create(countText->getCString(), DefaultFontName, FontSizeSmall);
            countLabel->setPosition(ccpAdd(imagePosition, ccp(0, -kItemImageSize / 2 - kItemImageCountLabelAdjustY)));
            this->addChild(countLabel);

            foundItemsIterator++;
            index++;
        }

        CCString *itemCountText = CCString::createWithFormat("%s:%d", MessageNumberOfFoundItemsText, sumFoundItems);
        CCLabelTTF *itemCountLabel = CCLabelTTF::create(itemCountText->getCString(), DefaultFontName, FontSizeNormal);
        itemCountLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - kItemCountLabelMarginTop));
        this->addChild(itemCountLabel);

        CCLayerColor *retryLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kCommandButtonWidth, kCommandButtonHeight);
        CCLabelTTF *retryLabel = CCLabelTTF::create(MessageRetryButtonTitle, DefaultFontName, FontSizeNormal);
        retryLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));
        retryLayer->addChild(retryLabel);
        CCMenuItem *retryItem = CCMenuItemLabel::create(retryLayer,
                                                        GameEngine::sharedEngine(),
                                                        menu_selector(GameEngine::startNewGame));

        CCLayerColor *backTitleLayer = CCLayerColor::create((ccColor4B){0x00, 0x00, 0x00, 0x00}, kCommandButtonWidth, kCommandButtonHeight);
        CCLabelTTF *backTitleLabel = CCLabelTTF::create(MessageBackTitleButtonTitle, DefaultFontName, FontSizeNormal);
        backTitleLabel->setPosition(ccp(kCommandButtonWidth / 2, kCommandButtonHeight / 2));
        backTitleLayer->addChild(backTitleLabel);
        CCMenuItem *backTitleItem = CCMenuItemLabel::create(backTitleLayer,
                                                            GameEngine::sharedEngine(),
                                                            menu_selector(GameEngine::showTitle));

        CCMenu *menu = CCMenu::create(retryItem, backTitleItem, NULL);
        menu->alignItemsHorizontallyWithPadding(kCommandButtonPadding);
        menu->setPosition(ccp(windowSize.width / 2, kCommandAreaMarginBottom + kCommandAreaHeight / 2));
        this->addChild(menu);
    }

    return result;
}