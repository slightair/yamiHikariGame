//
//  GameScene.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/07/16.
//
//

#include "GameScene.h"
#include "Constants.h"
#include "GameEngine.h"
#include "SimpleAudioEngine.h"

#include "DropItem.h"

#define kDropItemInterval 0.2
#define kEmergedAreaHorizontalMarginRate 0.1
#define kCollisionAreaPadding 8
#define kSEItemGet "SE001.mp3"
#define kSoundEffectVolume 0.15

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();

    GameScene *layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

void GameScene::update(float delta)
{
    _monster->followBrave(_brave->getPosition(), delta);

    CCSize braveSize = _brave->getContentSize();
    _braveRect = CCRectMake(_brave->getPosition().x - braveSize.width / 2 + kCollisionAreaPadding,
                            _brave->getPosition().y - braveSize.height / 2 + kCollisionAreaPadding,
                            braveSize.width - kCollisionAreaPadding * 2,
                            braveSize.height - kCollisionAreaPadding * 2);
    collisionCheck();
}

void GameScene::onEnter()
{
    CCLayer::onEnter();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    _worldNode = CCNode::create();
    _groundNode = Ground::create();
    _itemsNode = CCSpriteBatchNode::create(SpriteSheetImageFileName);
    _scoreBoardNode = ScoreBoard::create();

    _worldNode->addChild(_groundNode);
    _worldNode->addChild(_itemsNode);

    _monster = Monster::createWithSpriteFrameName("monster.png");
    _monster->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height));
    _worldNode->addChild(_monster);

    _brave = Brave::createWithSpriteFrameName("brave.png");
    _brave->setPosition(ccp(windowSize.width / 2, windowSize.height - _monster->getContentSize().height * 2 - _brave->getContentSize().height / 2));
    _worldNode->addChild(_brave);

    _darknessNode = Darkness::create(_brave->getPosition());

    this->addChild(_worldNode);
    this->addChild(_darknessNode);
    this->addChild(_scoreBoardNode);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(kSoundEffectVolume);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(kSEItemGet);

    this->scheduleUpdate();
}

void GameScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();

    _monster->startAnimation();
    _brave->startAnimation();

    this->schedule(schedule_selector(GameScene::dropItem), kDropItemInterval);
}

void GameScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect(kSEItemGet);

    CCLayer::onExit();
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    _touchedLocation = pTouch->getLocationInView();

    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = pTouch->getLocationInView();
    float distance = location.x - _touchedLocation.x;

#warning debug
    CCLog("%f, %f", location.x, location.y);
    CCLog("dist => %f", distance);

    _brave->moveX(distance);
    _darknessNode->setLightPosition(_brave->getPosition());

    _touchedLocation = location;
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScene::dropItem()
{
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    float horizontalMargin = windowSize.width * kEmergedAreaHorizontalMarginRate;
    int emergedAreaWidth = windowSize.width - horizontalMargin * 2;
    float positionX = arc4random() % emergedAreaWidth + horizontalMargin;

    DropItem *item = DropItem::create();
    item->setPosition(ccp(positionX, -item->getContentSize().height / 2));
    _itemsNode->addChild(item);
    item->drop();
}

void GameScene::collisionCheck()
{
    GameEngine *engine = GameEngine::sharedEngine();
    DropItem *dropItem = NULL;
    CCObject *child = NULL;
    CCARRAY_FOREACH(_itemsNode->getChildren(), child) {
        dropItem = (DropItem *)child;
        if (_braveRect.intersectsRect(dropItem->boundingBox())) {
            CCParticleSystem *starParticle = CCParticleSystemQuad::create("stars.plist");
            starParticle->setPosition(dropItem->getPosition());
            starParticle->setAutoRemoveOnFinish(true);
            this->addChild(starParticle);
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(kSEItemGet);

            engine->addScore(dropItem->getScore());

            dropItem->stopAllActions();
            dropItem->removeFromParentAndCleanup(true);
        }
    }
}