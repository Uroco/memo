//
//  EffectFactory.cpp
//  NinjaFlight
//

#import "EffectFactory.h"
#import "NFSpriteCluster.h"
#import "CCNodeUtil.h"
#import "NFLabelTTF.h"
#import "CommonDefine.h"

using namespace cocos2d;

CCPoint EffectFactory::getRandomInterval(cocos2d::CCSize _range){
    CCPoint pos = ccp(0,0);
    int addX = rand()%(int)(_range.width/2);
    if( addX % 2 ) addX *= -1;
    pos.x += addX;
    int addY = rand()%(int)(_range.height/2);
    if( addY % 2 ) addY *= -1;
    pos.y += addY;
    
    return pos;
}

void EffectFactory::createPoison(cocos2d::CCNode *parent, cocos2d::CCPoint _pos,
                                 int zOrder){
    if( parent == NULL ) return;
    
    NFSpriteCluster* eff_poison1 = NFSpriteCluster::create("eff_poison1.png");
    eff_poison1->setAnchorPoint(ccp(0.5, 0.5));
    eff_poison1->setPosition(_pos);
    eff_poison1->setOpacity(168.3);
    parent->addChild(eff_poison1);
    
    NFSpriteCluster* eff_poison2 = NFSpriteCluster::create("eff_poison2.png");
    eff_poison2->setAnchorPoint(ccp(0.5, 0.5));
    eff_poison2->setPosition(_pos);
    eff_poison2->setScale(0.5);
    eff_poison2->setOpacity(0.0);
    parent->addChild(eff_poison2);

    eff_poison1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.2),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.1),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.2),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.1),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.2),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.1),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 81.7),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(6.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 204.2),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 153.4),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 50.8),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_poison2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(5.0 / 30.0, 1.0),
       CCScaleTo::create(12.0 / 30.0, 1.6),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(12.0 / 30.0, 0.0),
       NULL),
      NULL));

}


void EffectFactory::createShock(cocos2d::CCNode *parent, cocos2d::CCPoint _pos,
                                 int zOrder){
    if( parent == NULL ) return;
  
    NFSpriteCluster* eff_shock1 = NFSpriteCluster::create("eff_shock1.png");
    parent->addChild(eff_shock1);
    eff_shock1->setAnchorPoint(ccp(0.5, 0.5));
    eff_shock1->setPosition(_pos);
    eff_shock1->setScale(0.3);
    
    NFSpriteCluster* eff_shock2 = NFSpriteCluster::create("eff_shock2.png");
    parent->addChild(eff_shock2);
    eff_shock2->setAnchorPoint(ccp(0.5, 0.5));
    eff_shock2->setPosition(ccpAdd(_pos, ccp(-47.0, 40.0)));
    eff_shock2->setScaleX(0.684);
    eff_shock2->setScaleY(0.934);
    eff_shock2->setRotation(231.7);
    eff_shock2->setOpacity(0.0);
    eff_shock2->setAloneProperty(true);

    eff_shock1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(3.0 / 30.0, 1.2),
       CCScaleTo::create(3.0 / 30.0, 1.4),
       CCScaleTo::create(7.0 / 30.0, 2.0),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(6.0 / 30.0),
       CCFadeTo::create(7.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_shock2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(6.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(20.0, -37.0)),
       CCDelayTime::create(2.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(60.4, -28.9)),
       CCDelayTime::create(2.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(6.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 1.0),
       CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 0.724, 0.747),
       CCDelayTime::create(2.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(6.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 128.3),
       CCDelayTime::create(2.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 149.2),
       CCDelayTime::create(2.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));

}

void EffectFactory::createMultiGold(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    if( parent == NULL ) return;

    NFSpriteCluster* eff_gold1 = NFSpriteCluster::create("eff_gold1.png");
    parent->addChild(eff_gold1);
    eff_gold1->setAnchorPoint(ccp(0.5, 0.5));
    eff_gold1->setPosition(_pos);
    eff_gold1->setScale(0.5);
    eff_gold1->setOpacity(76.7);
    
    NFSpriteCluster* eff_gold2 = NFSpriteCluster::create();
    parent->addChild(eff_gold2);
    eff_gold2->setAnchorPoint(ccp(0.0, 0.0));
    eff_gold2->setPosition(_pos);
    eff_gold2->setScale(0.5);
    eff_gold2->setOpacity(76.7);
    eff_gold2->setHandsOffChildProperty(true);
    
    NFSpriteCluster* eff_gold22 = NFSpriteCluster::create("eff_gold2.png");
    eff_gold2->addChild(eff_gold22);
    eff_gold22->setAnchorPoint(ccp(0.5, 0.5));
    eff_gold22->setPosition(ccp(0.0, 0.0));
    eff_gold22->setOpacity(76.7);

    eff_gold1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(9.0 / 30.0, 1.621),
       CCScaleTo::create(20.0 / 30.0, 4.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCRotateBy::create(20.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(9.0 / 30.0, 255.0),
       CCFadeTo::create(20.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_gold22->runAction(CCRotateBy::create(30.0 / 30.0, -90.0 * 30));
    eff_gold2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(9.0 / 30.0, 1.62),
       CCScaleTo::create(20.0 / 30.0, 4.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCRotateBy::create(9.0 / 30.0, 30.0),
       CCRotateBy::create(20.0 / 30.0, 60.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(9.0 / 30.0, 255.0),
       CCFadeTo::create(20.0 / 30.0, 0.0),
       NULL),
      NULL));

}

void EffectFactory::createStar(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder,cocos2d::ccColor3B _col ){
    if( parent == NULL ) return;
    
    NFSpriteCluster* eff_star = NFSpriteCluster::create("eff_star.png");
    eff_star->setAnchorPoint(ccp(0.5, 0.5));
    eff_star->setPosition(_pos);
    eff_star->setScale(0.3);
    eff_star->setRotation(-60.0);
    eff_star->setOpacity(73.7);
    eff_star->setBlendFunc((ccBlendFunc) {GL_SRC_ALPHA, GL_ONE});//加算合成
    parent->addChild(eff_star);
    
    eff_star->setColor(_col);

    eff_star->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(7.0 / 30.0, 1.0),
       CCScaleTo::create(12.0 / 30.0, 0.75),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCRotateBy::create(7.0 / 30.0, 60.0),
       CCRotateBy::create(12.0 / 30.0, 10.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(7.0 / 30.0, 255.0),
       CCFadeTo::create(12.0 / 30.0, 0.0),
       NULL),
      NULL));
}

void EffectFactory::createShine(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    NFSpriteCluster* eff_revive1 = NFSpriteCluster::create("eff_revive1.png");
    eff_revive1->setAnchorPoint(ccp(0.5, 0.5));
    eff_revive1->setPosition(_pos);
    eff_revive1->setScale(0.2);
    eff_revive1->setBlendFunc((ccBlendFunc) {GL_SRC_ALPHA, GL_ONE});//加算合成
    parent->addChild(eff_revive1);

    eff_revive1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(5.0 / 30.0, 1.6),
       CCDelayTime::create(4.0 / 30.0),
       CCScaleTo::create(10.0 / 30.0, 0.6),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCRotateBy::create(10.0 / 30.0, 90.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      NULL));    
}
#import "FixedValue.h"
void EffectFactory::createAddScore(int _score, cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    
    NFNumberLayer* score = NFNumberLayer::create(_score, "num_score_01.png", 46.0, 60.0, -8, 28, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0);
    score->setPosition(_pos);
    score->setOpacity(0.0);
    parent->addChild(score);
    
//    CCPoint pos = ccp(598.0, 924.0);
//    score->runAction(
//        CCSequence::create(
//                           CCSpawn::create
//                           (CCSequence::create
//                            (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 48.3)),
//                             CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.3)),
//                             CCMoveBy::create(10.0 / 30.0, ccp(0.0, 34.5)),
//                             NULL),
//                            CCDelayTime::create(29.0 / 30.0),
//                            NULL)
//        ,CCMoveTo::create(0.5, pos)
//    ,CCNodeUtil::createRemoveAction()
//                     ,NULL));
    
    score->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 48.3)),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.3)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 34.5)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      CCDelayTime::create(29.0 / 30.0),
      NULL));
}


void EffectFactory::debugShowDamage(int _dmg, cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    char str[16];
    sprintf(str, "DMG %d",_dmg);
    NFLabelTTF* dmg = NFLabelTTF::create(str, FONT_W6, 24);
    parent->addChild(dmg, 100);
    dmg->setPosition(_pos);
    dmg->setPositionY(_pos.y - 50);
    dmg->setOpacity(0.0);
    dmg->setScale(0.8);
    dmg->setColor(ccRED);

    
    dmg->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 48.3)),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.3)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 34.5)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      CCDelayTime::create(29.0 / 30.0),
      NULL));
}

void EffectFactory::createBuddyBonus(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    
    NFSpriteCluster* buddy_bonus1 = NFSpriteCluster::create("buddy_bonus1.png");
    buddy_bonus1->setAnchorPoint(ccp(0.5, 0.5));
    buddy_bonus1->setPosition(ccpAdd(_pos, ccp(10.0, 10.0)));
    buddy_bonus1->setOpacity(0.0);
    parent->addChild(buddy_bonus1);
    
    NFSpriteCluster* buddy_bonus2 = NFSpriteCluster::create("buddy_bonus2.png");
    buddy_bonus2->setAnchorPoint(ccp(0.5, 0.5));
    buddy_bonus2->setPosition(ccpAdd(_pos,ccp(10.0, 60.0)));
    buddy_bonus2->setOpacity(0.0);
    parent->addChild(buddy_bonus2);
    
    buddy_bonus1->runAction
    (CCSequence::create
     (CCSpawn::create
      (CCSequence::create
       (CCScaleTo::create(4.0 / 30.0, 1.3),
        CCScaleTo::create(4.0 / 30.0, 1.6),
        CCScaleTo::create(6.0 / 30.0, 1.8),
        NULL),
       CCSequence::create
       (CCFadeTo::create(4.0 / 30.0, 255.0),
        CCDelayTime::create(4.0 / 30.0),
        CCFadeTo::create(6.0 / 30.0, 0.0),
        NULL),
       NULL)
      ,CCNodeUtil::createRemoveAction()
      ,NULL));
    
    buddy_bonus2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCMoveBy::create(6.0 / 30.0, ccp(0.0, 25.0)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 10.0)),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(6.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      NULL));

}

void EffectFactory::createDeadWalkSakura(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    
    NFSpriteCluster* eff_sakura3 = NFSpriteCluster::create("eff_sakura3.png");
    eff_sakura3->setAnchorPoint(ccp(0.5, 0.0));
    eff_sakura3->setPosition(ccp(320.0, -80.0));
    eff_sakura3->setScale(2.0);
    eff_sakura3->setOpacity(0.0);
    parent->addChild(eff_sakura3);
    
    NFSpriteCluster* eff_sakura2 = NFSpriteCluster::create("eff_sakura2.png");
    eff_sakura2->setAnchorPoint(ccp(0.5, 0.0));
    eff_sakura2->setPosition(ccp(320.0, -380.0));
    eff_sakura2->setScale(2.0);
    parent->addChild(eff_sakura2);
    
    NFSpriteCluster* eff_sakura1 = NFSpriteCluster::create("eff_sakura1.png");
    eff_sakura1->setAnchorPoint(ccp(0.5, 0.0));
    eff_sakura1->setPosition(ccp(320.0, -640.0));
    eff_sakura1->setScale(2.0);
    parent->addChild(eff_sakura1);
    
    eff_sakura3->runAction
    (CCSequence::create
     (CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(0.4, ccp(0.0, 52.4)),
        CCMoveBy::create(0.33, ccp(0.0, 16.9)),
        CCMoveBy::create(0.27, ccp(0.0, 10.8)),
        CCDelayTime::create(0.03),
        NULL),
       CCSequence::create
       (CCScaleTo::create(0.4, 2.0, 2.3),
        CCScaleTo::create(0.33, 2.0, 2.8),
        CCScaleTo::create(0.27, 2.0, 3.0),
        CCDelayTime::create(0.03),
        NULL),
       CCSequence::create
       (CCFadeTo::create(0.4, 255.0),
        CCDelayTime::create(0.33),
        CCFadeTo::create(0.27, 0.0),
        CCDelayTime::create(0.03),
        NULL),
       NULL),
      CCNodeUtil::createRemoveAction(),
      NULL));
    eff_sakura2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(0.53, ccp(0.0, 290.0)),
       CCMoveBy::create(0.53, ccp(0.0, 90.0)),
       CCDelayTime::create(0.03),
       NULL),
      CCDelayTime::create(1.1),
      CCSequence::create
      (CCDelayTime::create(0.53),
       CCFadeTo::create(0.53, 0.0),
       CCDelayTime::create(0.03),
       CCNodeUtil::createRemoveAction(),
       NULL),
      NULL));
    eff_sakura1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(0.67, ccp(0.0, 580.0)),
       CCMoveBy::create(0.53, ccp(0.0, 60.0)),
       NULL),
      CCDelayTime::create(1.2),
      CCSequence::create
      (CCDelayTime::create(0.67),
       CCFadeTo::create(0.53, 0.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      NULL));
}

void EffectFactory::createNormalEnemyDeathEffect(cocos2d::CCNode *parent,
                                                 int zOrder){
    NFSpriteCluster* eff_bakuhatsu2 = NFSpriteCluster::create("eff_bakuhatsu2.png");
    eff_bakuhatsu2->setAnchorPoint(ccp(0.5, 0.5));
    eff_bakuhatsu2->setScale(0.7);
    parent->addChild(eff_bakuhatsu2);
    
    NFSpriteCluster* eff_bakuhatsu = NFSpriteCluster::create("eff_bakuhatsu.png");
    eff_bakuhatsu->setAnchorPoint(ccp(0.5, 0.5));
    eff_bakuhatsu->setScale(0.3);
    parent->addChild(eff_bakuhatsu);
    
    eff_bakuhatsu2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(8.0 / 30.0, 2.0),
       CCScaleTo::create(4.0 / 30.0, 2.4),
       NULL),
      CCSequence::create
      (CCRotateBy::create(8.0 / 30.0, 30.0),
       CCRotateBy::create(4.0 / 30.0, 10.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(8.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_bakuhatsu->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(5.0 / 30.0, 2.2),
       CCScaleTo::create(5.0 / 30.0, 2.8),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
}

void EffectFactory::createBomEnemyDeathEffect(cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* eff_yubaku3 = NFSpriteCluster::create("eff_yubaku3.png");
    eff_yubaku3->setAnchorPoint(ccp(0.5, 0.5));
    eff_yubaku3->setPosition(ccp(0.0, 0.0));
    eff_yubaku3->setScale(2.0);
    eff_yubaku3->setOpacity(0.0);
    parent->addChild(eff_yubaku3);
    
    NFSpriteCluster* eff_yubaku2 = NFSpriteCluster::create("eff_yubaku2.png");
    eff_yubaku2->setAnchorPoint(ccp(0.5, 0.5));
    eff_yubaku2->setPosition(ccp(0.0, 0.0));
    eff_yubaku2->setScale(0.7);
    eff_yubaku2->setOpacity(0.0);
    parent->addChild(eff_yubaku2);
    
    NFSpriteCluster* eff_yubaku1 = NFSpriteCluster::create("eff_yubaku1.png");
    eff_yubaku1->setAnchorPoint(ccp(0.5, 0.5));
    eff_yubaku1->setPosition(ccp(0.0, 0.0));
    eff_yubaku1->setScale(0.6);
    eff_yubaku1->setOpacity(50.8);
    parent->addChild(eff_yubaku1);
    
    eff_yubaku3->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 4.0),
       CCScaleTo::create(5.0 / 30.0, 5.2),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_yubaku2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(2.0 / 30.0, 1.0),
       CCScaleTo::create(6.0 / 30.0, 1.5),
       CCScaleTo::create(5.0 / 30.0, 1.6),
       NULL),
      CCSequence::create
      (CCFadeTo::create(2.0 / 30.0, 255.0),
       CCDelayTime::create(6.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_yubaku1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(5.0 / 30.0, ccp(0.05, -0.05)),
       CCMoveBy::create(8.0 / 30.0, ccp(-0.05, 0.05)),
       NULL),
      CCSequence::create
      (CCScaleTo::create(5.0 / 30.0, 1.6),
       CCScaleTo::create(8.0 / 30.0, 2.0),
       NULL),
      CCSequence::create
      (CCRotateBy::create(5.0 / 30.0, 0.0),
       CCRotateBy::create(8.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(5.0 / 30.0, 255.0),
       CCFadeTo::create(8.0 / 30.0, 0.0),
       NULL),
      NULL));
}

void EffectFactory::createFrogBtnEffect(cocos2d::CCNode* eff_bomb_front, cocos2d::CCNode* eff_bomb_back){
    NFSpriteCluster* ico_frog_02 = NFSpriteCluster::create("ico_flog_02.png");
    ico_frog_02->setAnchorPoint(ccp(0.5, 0.5));
    ico_frog_02->setPosition(ccp(65.6, 63.8));
    ico_frog_02->setScale(1.4);
    ico_frog_02->setOpacity(0.0);
    eff_bomb_front->addChild(ico_frog_02);
    
    NFSpriteCluster* ico_frog_03 = NFSpriteCluster::create("ico_flog_03.png");
    ico_frog_03->setAnchorPoint(ccp(0.5, 0.5));
    ico_frog_03->setPosition(ccp(65.6, 63.8));
    ico_frog_03->setScale(1.4);
    ico_frog_03->setOpacity(0.0);
    eff_bomb_front->addChild(ico_frog_03);
    
    NFSpriteCluster* eff_bomb_03 = NFSpriteCluster::create("eff_bomb_03.png");
    eff_bomb_03->setAnchorPoint(ccp(0.5, 0.497));
    eff_bomb_03->setPosition(ccp(79.4, 76.1));
    eff_bomb_03->setScale(1.4);
    eff_bomb_03->setRotation(20.0);
    eff_bomb_03->setOpacity(0.0);
    eff_bomb_03->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    eff_bomb_front->addChild(eff_bomb_03);
    
    NFSpriteCluster* eff_bomb_021 = NFSpriteCluster::create("eff_bomb_02.png");
    eff_bomb_021->setAnchorPoint(ccp(0.5, 0.5));
    eff_bomb_021->setPosition(ccp(79.6, 76.5));
    eff_bomb_021->setScale(1.4);
    eff_bomb_021->setRotation(34.0);
    eff_bomb_021->setOpacity(0.0);
    eff_bomb_021->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    eff_bomb_front->addChild(eff_bomb_021);
    
    NFSpriteCluster* eff_bomb_022 = NFSpriteCluster::create("eff_bomb_02.png");
    eff_bomb_022->setAnchorPoint(ccp(0.5, 0.5));
    eff_bomb_022->setPosition(ccp(79.6, 76.5));
    eff_bomb_022->setScale(1.4);
    eff_bomb_022->setRotation(34.0);
    eff_bomb_022->setOpacity(0.0);
    eff_bomb_022->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    eff_bomb_front->addChild(eff_bomb_022);
    
    NFSpriteCluster* eff_bomb_01 = NFSpriteCluster::create("eff_bomb_01.png");
    eff_bomb_01->setAnchorPoint(ccp(0.501, 0.5));
    eff_bomb_01->setPosition(ccp(116.0, 40.0));
    eff_bomb_01->setScale(0.84);
    eff_bomb_01->setOpacity(0.0);
    eff_bomb_01->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    eff_bomb_front->addChild(eff_bomb_01);
    
    NFSpriteCluster* eff_bomb_05 = NFSpriteCluster::create("eff_bomb_05.png");
    eff_bomb_05->setAnchorPoint(ccp(0.5, 0.5));
    eff_bomb_05->setPosition(ccp(81.0, 75.0));
    eff_bomb_05->setScale(1.4);
    eff_bomb_05->setOpacity(0.0);
    eff_bomb_05->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    eff_bomb_front->addChild(eff_bomb_05);
    
    eff_bomb_back->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCDelayTime::create(19.0 / 30.0),
        CCMoveBy::create(10.0 / 30.0, ccp(0.00938, 0.0406)),
        CCMoveBy::create(10.0 / 30.0, ccp(-0.0392, -0.01084)),
        CCDelayTime::create(21.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(0.02979, -0.02979)),
        NULL),
       CCSequence::create
       (CCDelayTime::create(19.0 / 30.0),
        CCScaleTo::create(10.0 / 30.0, 2.66),
        CCScaleTo::create(10.0 / 30.0, 3.64),
        CCDelayTime::create(21.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 1.68),
        NULL),
       CCSequence::create
       (CCDelayTime::create(19.0 / 30.0),
        CCFadeTo::create(10.0 / 30.0, 101.6),
        CCFadeTo::create(10.0 / 30.0, 0.0),
        CCDelayTime::create(21.0 / 30.0),
        NULL),
       NULL)));
    ico_frog_02->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCDelayTime::create(23.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       CCDelayTime::create(12.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       CCDelayTime::create(20.0 / 30.0),
       NULL)
      ));
    ico_frog_03->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCDelayTime::create(26.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(12.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       CCDelayTime::create(22.0 / 30.0),
       NULL)
      ));
    eff_bomb_03->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCMoveBy::create(15.0 / 30.0, ccp(0.469, 0.095)),
        CCMoveBy::create(14.0 / 30.0, ccp(-0.442, 0.2753)),
        CCDelayTime::create(29.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(-0.02768, -0.37)),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCScaleTo::create(15.0 / 30.0, 1.398),
        CCScaleTo::create(14.0 / 30.0, 1.398),
        CCDelayTime::create(29.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 1.4),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCRotateBy::create(15.0 / 30.0, -116.5),
        CCRotateBy::create(14.0 / 30.0, -129.6),
        CCDelayTime::create(29.0 / 30.0),
        CCRotateBy::create(0.0 / 30.0, -113.9),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCFadeTo::create(15.0 / 30.0, 101.6),
        CCFadeTo::create(14.0 / 30.0, 0.0),
        CCDelayTime::create(29.0 / 30.0),
        NULL),
       NULL)));
    eff_bomb_021->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(15.0 / 30.0, ccp(0.445, 0.0551)),
        CCMoveBy::create(14.0 / 30.0, ccp(-0.001659, -0.397)),
        CCDelayTime::create(31.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(-0.443, 0.342)),
        NULL),
       CCSequence::create
       (CCScaleTo::create(15.0 / 30.0, 1.4),
        CCScaleTo::create(14.0 / 30.0, 1.4),
        CCDelayTime::create(31.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 1.4),
        NULL),
       CCSequence::create
       (CCRotateBy::create(15.0 / 30.0, -119.7),
        CCRotateBy::create(14.0 / 30.0, -134.3),
        CCDelayTime::create(31.0 / 30.0),
        CCRotateBy::create(0.0 / 30.0, -106.0),
        NULL),
       CCSequence::create
       (CCFadeTo::create(15.0 / 30.0, 178.3),
        CCFadeTo::create(14.0 / 30.0, 0.0),
        CCDelayTime::create(31.0 / 30.0),
        NULL),
       NULL)));
    eff_bomb_022->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCMoveBy::create(15.0 / 30.0, ccp(0.541, 0.399)),
        CCMoveBy::create(14.0 / 30.0, ccp(-0.0977, -0.741)),
        CCDelayTime::create(29.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(-0.443, 0.342)),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCScaleTo::create(15.0 / 30.0, 1.4),
        CCScaleTo::create(14.0 / 30.0, 1.4),
        CCDelayTime::create(29.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 1.4),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCRotateBy::create(15.0 / 30.0, -119.7),
        CCRotateBy::create(14.0 / 30.0, -134.3),
        CCDelayTime::create(29.0 / 30.0),
        CCRotateBy::create(0.0 / 30.0, -106.0),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCFadeTo::create(15.0 / 30.0, 50.8),
        CCFadeTo::create(14.0 / 30.0, 0.0),
        CCDelayTime::create(29.0 / 30.0),
        NULL),
       NULL)));
    eff_bomb_01->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCMoveBy::create(11.0 / 30.0, ccp(-0.1994, 0.0597)),
        CCMoveBy::create(10.0 / 30.0, ccp(0.1907, -0.345)),
        CCDelayTime::create(21.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(0.00873, 0.2851)),
        NULL),
       CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCScaleTo::create(11.0 / 30.0, 1.258),
        CCScaleTo::create(10.0 / 30.0, 1.678),
        CCDelayTime::create(21.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 0.84),
        NULL),
       CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCRotateBy::create(11.0 / 30.0, 15.0),
        CCRotateBy::create(10.0 / 30.0, 15.0),
        CCDelayTime::create(21.0 / 30.0),
        CCRotateBy::create(0.0 / 30.0, -30.0),
        NULL),
       CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCFadeTo::create(11.0 / 30.0, 255.0),
        CCFadeTo::create(10.0 / 30.0, 0.0),
        CCDelayTime::create(21.0 / 30.0),
        NULL),
       NULL)));
    eff_bomb_05->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCMoveBy::create(11.0 / 30.0, ccp(0.0636, 0.00768)),
        CCMoveBy::create(10.0 / 30.0, ccp(-0.0546, -0.01671)),
        CCDelayTime::create(21.0 / 30.0),
        CCMoveBy::create(0.0 / 30.0, ccp(-0.00902, 0.00902)),
        NULL),
       CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCScaleTo::create(11.0 / 30.0, 2.427),
        CCScaleTo::create(10.0 / 30.0, 3.36),
        CCDelayTime::create(21.0 / 30.0),
        CCScaleTo::create(0.0 / 30.0, 1.4),
        NULL),
       CCSequence::create
       (CCDelayTime::create(18.0 / 30.0),
        CCFadeTo::create(11.0 / 30.0, 73.7),
        CCFadeTo::create(10.0 / 30.0, 0.0),
        CCDelayTime::create(21.0 / 30.0),
        NULL),
       NULL)));    
}

void EffectFactory::createExplosionAnimation(cocos2d::CCNode *parent, cocos2d::CCNode* target, cocos2d::SEL_CallFunc _exitFunc){
    
    CCSprite* eff_explosion3 = CCSprite::create("eff_explosion3.png");
    eff_explosion3->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion3->setPosition(ccp(50.0, 60.0));
    eff_explosion3->setScale(0.5);
    eff_explosion3->setOpacity(0.0);
    parent->addChild(eff_explosion3);
    
    CCSprite* eff_explosion4 = CCSprite::create("eff_explosion4.png");
    eff_explosion4->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion4->setPosition(ccp(50.0, 60.0));
    eff_explosion4->setScale(2.0);
    eff_explosion4->setOpacity(0.0);
    parent->addChild(eff_explosion4);
    
    CCSprite* eff_explosion1 = CCSprite::create("eff_explosion1.png");
    eff_explosion1->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion1->setPosition(ccp(50.0, 60.0));
    eff_explosion1->setScale(0.6);
    parent->addChild(eff_explosion1);
    
    CCSprite* eff_explosion2 = CCSprite::create("eff_explosion2.png");
    eff_explosion2->setAnchorPoint(ccp(0.5, 0.0471));
    eff_explosion2->setPosition(ccp(50.0, 60.0));
    eff_explosion2->setScaleX(0.15);
    eff_explosion2->setScaleY(0.5);
    parent->addChild(eff_explosion2);

    eff_explosion3->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 2.3),
       CCScaleTo::create(3.0 / 30.0, 2.0),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 50.8),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_explosion4->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCScaleTo::create(8.0 / 30.0, 4.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCFadeTo::create(8.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_explosion1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(4.0 / 30.0, ccp(-0.05, 0.0)),
       CCDelayTime::create(3.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.05, 0.0)),
       CCCallFunc::create(target,_exitFunc),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 2.0),
       CCScaleTo::create(3.0 / 30.0, 1.8),
       CCScaleTo::create(5.0 / 30.0, 1.6),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCRotateBy::create(3.0 / 30.0, 0.0),
       CCRotateBy::create(5.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_explosion2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(3.0 / 30.0, 1.4, 2.0),
       CCScaleTo::create(4.0 / 30.0, 2.0, 1.8),
       CCScaleTo::create(4.0 / 30.0, 1.6, 0.6),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 127.5),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));

    
//    
//    eff_explosion3->runAction
//    (CCSpawn::create
//     (CCSequence::create
//      (CCDelayTime::create(0.07),
//       CCMoveBy::create(0.13, ccp(0.0, 10.0)),
//       CCDelayTime::create(0.13),
//       NULL),
//      CCSequence::create
//      (CCDelayTime::create(0.07),
//       CCScaleTo::create(0.13, 1.8),
//       CCScaleTo::create(0.1, 2.0),
//       CCDelayTime::create(0.03),
//       NULL),
//      CCSequence::create
//      (CCDelayTime::create(0.07),
//       CCFadeTo::create(0.0, 255.0),
//       CCDelayTime::create(0.13),
//       CCFadeTo::create(0.1, 50.8),
//       CCDelayTime::create(0.03),
//       CCFadeTo::create(0.0, 0.0),
//       NULL),
//      NULL));
//    eff_explosion4->runAction
//    (CCSpawn::create
//     (CCSequence::create
//      (CCDelayTime::create(4.0 / 30.0),
//       CCScaleTo::create(8.0 / 30.0, 4.0),
//       NULL),
//      CCSequence::create
//      (CCDelayTime::create(4.0 / 30.0),
//       CCFadeTo::create(0.0 / 30.0, 255.0),
//       CCFadeTo::create(8.0 / 30.0, 0.0),
//       NULL),
//      NULL));
//    
//    eff_explosion1->runAction
//    (CCSequence::create
//     (CCSpawn::create
//      (CCSequence::create
//       (CCMoveBy::create(0.13, ccp(-0.1, 0.0)),
//        CCDelayTime::create(0.13),
//        CCMoveBy::create(0.13, ccp(0.1, 0.0)),
//        NULL),
//       CCSequence::create
//       (CCScaleTo::create(0.13, 2.0),
//        CCScaleTo::create(0.13, 1.8),
//        CCScaleTo::create(0.13, 1.6),
//        NULL),
//       CCSequence::create
//       (CCDelayTime::create(0.27),
//        CCFadeTo::create(0.13, 0.0),
//        NULL),
//       NULL),
//      CCCallFunc::create(target,_exitFunc),
//      NULL));
//    
//    eff_explosion2->runAction
//    (CCSpawn::create
//     (CCSequence::create
//      (CCScaleTo::create(0.1, 1.4, 2.0),
//       CCScaleTo::create(0.13, 2.0, 1.8),
//       CCScaleTo::create(0.13, 1.6, 0.6),
//       CCDelayTime::create(0.03),
//       NULL),
//      CCSequence::create
//      (CCDelayTime::create(0.1),
//       CCFadeTo::create(0.13, 127.5),
//       CCFadeTo::create(0.13, 0.0),
//       CCDelayTime::create(0.03),
//       NULL),
//      NULL));
}

void EffectFactory::createExplosion2Animation(cocos2d::CCNode* parent,
                               cocos2d::CCNode* target,
                               cocos2d::SEL_CallFunc _exitFunc)
{    
    CCSprite* eff_explosion4 = CCSprite::create("eff_explosion4.png");
    eff_explosion4->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion4->setPosition(ccp(40.0, 40.0));
    eff_explosion4->setScaleX(2.2);
    eff_explosion4->setScaleY(2.0);
    eff_explosion4->setOpacity(0.0);
    parent->addChild(eff_explosion4);
    
    CCSprite* eff_explosion5 = CCSprite::create("eff_explosion5.png");
    eff_explosion5->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion5->setPosition(ccp(40.0, 40.0));
    eff_explosion5->setScale(2.0);
    eff_explosion5->setOpacity(0.0);
    parent->addChild(eff_explosion5);
    
    CCSprite* eff_explosion1 = CCSprite::create("eff_explosion1.png");
    eff_explosion1->setAnchorPoint(ccp(0.5, 0.5));
    eff_explosion1->setPosition(ccp(40.0, 40.0));
    eff_explosion1->setScale(0.4);
    parent->addChild(eff_explosion1);
    
    eff_explosion4->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCMoveBy::create(9.0 / 30.0, ccp(0.05, 0.05)),
       CCMoveBy::create(8.0 / 30.0, ccp(-0.05, -0.05)),
       CCCallFunc::create(target,_exitFunc),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(9.0 / 30.0, 5.6, 5.04),
       CCScaleTo::create(8.0 / 30.0, 7.0, 6.3),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCFadeTo::create(9.0 / 30.0, 127.5),
       CCFadeTo::create(8.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_explosion5->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.05, -0.05)),
       CCDelayTime::create(3.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.05, -0.05)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(-0.1, 0.1)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.0, 0.05)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.0, 0.05)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.05, 0.0)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(-0.05, 0.0)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(-0.1, 0.0)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.05, 0.0)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.0, -0.05)),
       CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(0.0 / 30.0, ccp(0.05, -0.05)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -2.437, 2.437),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 2.75),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -2.937, 2.937),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -3.14, 3.14),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 3.28),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -3.42, 3.42),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 3.56),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -3.7, 3.7),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 3.76),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -3.82, 3.82),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 3.89),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -3.95, 3.95),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 4.01),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -4.08, 4.08),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, 4.14),
       CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(0.0 / 30.0, -4.2, 4.2),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 81.7),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 158.4),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 211.2),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 245.0),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(10.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 199.2),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 140.4),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 83.7),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 25.9),
       NULL),
      NULL));
    eff_explosion1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(3.0 / 30.0, ccp(-0.05, 0.0)),
       CCDelayTime::create(5.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.05, 0.0)),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(3.0 / 30.0, 2.0),
       CCScaleTo::create(5.0 / 30.0, 2.1),
       CCScaleTo::create(4.0 / 30.0, 2.2),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 191.3),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
}

void EffectFactory::createExplosionFireFlowerAnimation(cocos2d::CCNode *parent,
                                                       cocos2d::CCNode *target,
                                                       cocos2d::SEL_CallFunc _exitFunc){
    NFSpriteCluster* eff_bd43_06_bomb_02 = NFSpriteCluster::create("eff_bd43_06_bomb_02.png");
    parent->addChild(eff_bd43_06_bomb_02);
    eff_bd43_06_bomb_02->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_02->setPosition(ccp(-1.1, 0.5));
    eff_bd43_06_bomb_02->setScale(0.6);
    eff_bd43_06_bomb_02->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_04 = NFSpriteCluster::create("eff_bd43_06_bomb_04.png");
    parent->addChild(eff_bd43_06_bomb_04);
    eff_bd43_06_bomb_04->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_04->setPosition(ccp(-0.6, -0.4));
    eff_bd43_06_bomb_04->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_03 = NFSpriteCluster::create("eff_bd43_06_bomb_03.png");
    parent->addChild(eff_bd43_06_bomb_03);
    eff_bd43_06_bomb_03->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_03->setPosition(ccp(-1.0, 0.0));
    eff_bd43_06_bomb_03->setScale(0.84);
    eff_bd43_06_bomb_03->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_05 = NFSpriteCluster::create("eff_bd43_06_bomb_05.png");
    eff_bd43_06_bomb_05->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_05->setPosition(ccp(-1.0, 0.0));
    eff_bd43_06_bomb_05->setScale(0.67);
    eff_bd43_06_bomb_05->setOpacity(0.0);
    parent->addChild(eff_bd43_06_bomb_05);
    
    NFSpriteCluster* eff_bd43_06_bomb_08 = NFSpriteCluster::create("eff_bd43_06_bomb_08.png");
    parent->addChild(eff_bd43_06_bomb_08);
    eff_bd43_06_bomb_08->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_08->setPosition(ccp(-1.7, -0.3));
    eff_bd43_06_bomb_08->setScale(0.5);
    eff_bd43_06_bomb_08->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_09 = NFSpriteCluster::create("eff_bd43_06_bomb_09.png");
    parent->addChild(eff_bd43_06_bomb_09);
    eff_bd43_06_bomb_09->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_09->setPosition(ccp(-0.7, -1.4));
    eff_bd43_06_bomb_09->setScale(0.44);
    eff_bd43_06_bomb_09->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_01 = NFSpriteCluster::create("eff_bd43_06_bomb_01.png");
    parent->addChild(eff_bd43_06_bomb_01);
    eff_bd43_06_bomb_01->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_01->setPosition(ccp(-0.5, 0.0));
    eff_bd43_06_bomb_01->setScale(0.64);
    
    NFSpriteCluster* eff_bd43_06_bomb_10 = NFSpriteCluster::create("eff_bd43_06_bomb_10.png");
    parent->addChild(eff_bd43_06_bomb_10);
    eff_bd43_06_bomb_10->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_10->setPosition(ccp(-1.0, 0.0));
    eff_bd43_06_bomb_10->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_061 = NFSpriteCluster::create("eff_bd43_06_bomb_06.png");
    parent->addChild(eff_bd43_06_bomb_061);
    eff_bd43_06_bomb_061->setAnchorPoint(ccp(0.501, 0.497));
    eff_bd43_06_bomb_061->setPosition(ccp(-3.5, 106.6));
    eff_bd43_06_bomb_061->setScale(0.8);
    eff_bd43_06_bomb_061->setRotation(90.0);
    eff_bd43_06_bomb_061->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_062 = NFSpriteCluster::create("eff_bd43_06_bomb_06.png");
    parent->addChild(eff_bd43_06_bomb_062);
    eff_bd43_06_bomb_062->setAnchorPoint(ccp(0.5, 0.499));
    eff_bd43_06_bomb_062->setPosition(ccp(1.3, -94.8));
    eff_bd43_06_bomb_062->setScale(0.8);
    eff_bd43_06_bomb_062->setRotation(-88.0);
    eff_bd43_06_bomb_062->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_063 = NFSpriteCluster::create("eff_bd43_06_bomb_06.png");
    parent->addChild(eff_bd43_06_bomb_063);
    eff_bd43_06_bomb_063->setAnchorPoint(ccp(0.501, 0.501));
    eff_bd43_06_bomb_063->setPosition(ccp(108.2, 1.8));
    eff_bd43_06_bomb_063->setScale(0.8);
    eff_bd43_06_bomb_063->setRotation(180.0);
    eff_bd43_06_bomb_063->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_064 = NFSpriteCluster::create("eff_bd43_06_bomb_06.png");
    parent->addChild(eff_bd43_06_bomb_064);
    eff_bd43_06_bomb_064->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_064->setPosition(ccp(-106.1, -1.8));
    eff_bd43_06_bomb_064->setScale(0.8);
    eff_bd43_06_bomb_064->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_071 = NFSpriteCluster::create("eff_bd43_06_bomb_07.png");
    parent->addChild(eff_bd43_06_bomb_071);
    eff_bd43_06_bomb_071->setAnchorPoint(ccp(0.5, 0.5));
    eff_bd43_06_bomb_071->setPosition(ccp(-93.6, -70.3));
    eff_bd43_06_bomb_071->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_072 = NFSpriteCluster::create("eff_bd43_06_bomb_07.png");
    parent->addChild(eff_bd43_06_bomb_072);
    eff_bd43_06_bomb_072->setAnchorPoint(ccp(0.5, 0.499));
    eff_bd43_06_bomb_072->setPosition(ccp(98.3, 84.9));
    eff_bd43_06_bomb_072->setScale(1.0);
    eff_bd43_06_bomb_072->setRotation(188.0);
    eff_bd43_06_bomb_072->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_073 = NFSpriteCluster::create("eff_bd43_06_bomb_07.png");
    parent->addChild(eff_bd43_06_bomb_073);
    eff_bd43_06_bomb_073->setAnchorPoint(ccp(0.499, 0.5));
    eff_bd43_06_bomb_073->setPosition(ccp(-90.6, 85.7));
    eff_bd43_06_bomb_073->setScale(1.0);
    eff_bd43_06_bomb_073->setRotation(95.0);
    eff_bd43_06_bomb_073->setOpacity(0.0);
    
    NFSpriteCluster* eff_bd43_06_bomb_074 = NFSpriteCluster::create("eff_bd43_06_bomb_07.png");
    parent->addChild(eff_bd43_06_bomb_074);
    eff_bd43_06_bomb_074->setAnchorPoint(ccp(0.5, 0.501));
    eff_bd43_06_bomb_074->setPosition(ccp(88.8, -68.9));
    eff_bd43_06_bomb_074->setScale(1.0);
    eff_bd43_06_bomb_074->setRotation(-90.0);
    eff_bd43_06_bomb_074->setOpacity(0.0);
    
    eff_bd43_06_bomb_02->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(8.0 / 30.0, ccp(0.0499, -0.5)),
       CCDelayTime::create(5.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(9.77E-4, -9.77E-4)),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       CCCallFunc::create(target,_exitFunc),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(8.0 / 30.0, 1.24),
       CCDelayTime::create(5.0 / 30.0),
       CCScaleTo::create(5.0 / 30.0, 1.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(8.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 78.7),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_04->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.071, 0.001025)),
       CCDelayTime::create(11.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.44),
       CCDelayTime::create(11.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 214.2),
       CCFadeTo::create(1.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 68.7),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_03->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(-6.84E-4, 6.84E-4)),
       CCMoveBy::create(3.0 / 30.0, ccp(9.77E-4, -9.77E-4)),
       CCDelayTime::create(15.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(1.0 / 30.0, 0.55),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCDelayTime::create(15.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(1.0 / 30.0, 255.0),
       CCDelayTime::create(11.0 / 30.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_05->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCMoveBy::create(3.0 / 30.0, ccp(9.16E-5, 2.0)),
       CCDelayTime::create(15.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCDelayTime::create(15.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(7.0 / 30.0, 30.9),
       CCFadeTo::create(7.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_08->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(7.86E-4, -7.86E-4)),
       CCMoveBy::create(7.0 / 30.0, ccp(0.00824, 0.0418)),
       CCMoveBy::create(4.0 / 30.0, ccp(-0.0784, 0.02841)),
       CCDelayTime::create(4.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.0),
       CCScaleTo::create(7.0 / 30.0, 1.84),
       CCScaleTo::create(4.0 / 30.0, 2.16),
       CCDelayTime::create(4.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(7.0 / 30.0, 142.4),
       CCFadeTo::create(4.0 / 30.0, 30.9),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_09->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCMoveBy::create(9.0 / 30.0, ccp(-0.001044, 0.001044)),
       CCMoveBy::create(6.0 / 30.0, ccp(-0.1586, 0.01059)),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCScaleTo::create(9.0 / 30.0, 1.0),
       CCScaleTo::create(6.0 / 30.0, 1.32),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(6.0 / 30.0, 27.9),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(13.0 / 30.0, ccp(-0.5, -1.221E-5)),
       CCDelayTime::create(7.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(13.0 / 30.0, 1.0),
       CCDelayTime::create(7.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(13.0 / 30.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_10->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCMoveBy::create(2.0 / 30.0, ccp(-8.7E-5, 8.7E-5)),
       CCMoveBy::create(6.0 / 30.0, ccp(0.0613, -0.01729)),
       CCMoveBy::create(7.0 / 30.0, ccp(-0.0718, 0.02783)),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCScaleTo::create(2.0 / 30.0, 1.2),
       CCScaleTo::create(6.0 / 30.0, 1.44),
       CCScaleTo::create(7.0 / 30.0, 1.54),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCFadeTo::create(2.0 / 30.0, 173.3),
       CCFadeTo::create(6.0 / 30.0, 78.7),
       CCFadeTo::create(7.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_bd43_06_bomb_061->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(0.62, 24.05)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.39, 6.15)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCScaleTo::create(1.0 / 30.0, 0.8),
       CCScaleTo::create(10.0 / 30.0, 0.8),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCRotateBy::create(1.0 / 30.0, 0.0),
       CCRotateBy::create(10.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCFadeTo::create(1.0 / 30.0, 181.3),
       CCFadeTo::create(10.0 / 30.0, 27.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_062->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(0.1274, -28.39)),
       CCMoveBy::create(10.0 / 30.0, ccp(-0.692, -6.99)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCScaleTo::create(1.0 / 30.0, 0.8),
       CCScaleTo::create(10.0 / 30.0, 0.8),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCRotateBy::create(1.0 / 30.0, 0.0),
       CCRotateBy::create(10.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCFadeTo::create(1.0 / 30.0, 181.3),
       CCFadeTo::create(10.0 / 30.0, 30.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_063->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(23.08, 0.1396)),
       CCMoveBy::create(10.0 / 30.0, ccp(5.92, -0.409)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCScaleTo::create(1.0 / 30.0, 0.8),
       CCScaleTo::create(10.0 / 30.0, 0.8),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCRotateBy::create(1.0 / 30.0, 0.0),
       CCDelayTime::create(10.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCFadeTo::create(1.0 / 30.0, 181.3),
       CCFadeTo::create(10.0 / 30.0, 30.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_064->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(-21.62, -0.5)),
       CCMoveBy::create(10.0 / 30.0, ccp(-15.75, 0.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCFadeTo::create(1.0 / 30.0, 181.3),
       CCFadeTo::create(10.0 / 30.0, 30.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_071->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCMoveBy::create(3.0 / 30.0, ccp(-9.0, -12.0)),
       CCMoveBy::create(7.0 / 30.0, ccp(-2.3, -2.1)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(1.0 / 30.0, 183.3),
       CCFadeTo::create(3.0 / 30.0, 158.4),
       CCFadeTo::create(7.0 / 30.0, 12.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_072->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCMoveBy::create(3.0 / 30.0, ccp(8.75, 9.43)),
       CCMoveBy::create(7.0 / 30.0, ccp(2.247, 4.24)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCScaleTo::create(7.0 / 30.0, 0.999),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCRotateBy::create(3.0 / 30.0, 0.0),
       CCRotateBy::create(7.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(1.0 / 30.0, 183.3),
       CCFadeTo::create(3.0 / 30.0, 158.4),
       CCFadeTo::create(7.0 / 30.0, 12.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_073->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCMoveBy::create(3.0 / 30.0, ccp(-14.79, 10.66)),
       CCMoveBy::create(7.0 / 30.0, ccp(-1.792, 3.21)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCScaleTo::create(7.0 / 30.0, 1.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCRotateBy::create(3.0 / 30.0, 0.0),
       CCRotateBy::create(7.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(1.0 / 30.0, 183.3),
       CCFadeTo::create(3.0 / 30.0, 158.4),
       CCFadeTo::create(7.0 / 30.0, 12.9),
       NULL),
      NULL));
    eff_bd43_06_bomb_074->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCMoveBy::create(3.0 / 30.0, ccp(13.75, -8.4)),
       CCMoveBy::create(7.0 / 30.0, ccp(6.0, -3.75)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCScaleTo::create(7.0 / 30.0, 1.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCRotateBy::create(3.0 / 30.0, 0.0),
       CCRotateBy::create(7.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(1.0 / 30.0, 183.3),
       CCFadeTo::create(3.0 / 30.0, 158.4),
       CCFadeTo::create(7.0 / 30.0, 12.9),
       NULL),
      NULL));

}
void EffectFactory::createSlashEffectAnimation_Assult(cocos2d::CCNode *parent){
    
    NFSpriteCluster* eff_slash_e11 = NFSpriteCluster::create("eff_slash_e1.png");
    eff_slash_e11->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_e11->setPosition(ccp(60.0, 60.0));
    eff_slash_e11->setScaleX(0.599);
    eff_slash_e11->setScaleY(0.598);
    eff_slash_e11->setRotation(60.2);
    parent->addChild(eff_slash_e11);
    
    NFSpriteCluster* eff_slash_e12 = NFSpriteCluster::create("eff_slash_e1.png");
    eff_slash_e12->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_e12->setPosition(ccp(60.0, 60.0));
    eff_slash_e12->setScaleX(0.599);
    eff_slash_e12->setScaleY(0.598);
    eff_slash_e12->setRotation(29.8);
    eff_slash_e12->setOpacity(0.0);
    parent->addChild(eff_slash_e12);
    
    NFSpriteCluster* eff_slash_e2 = NFSpriteCluster::create("eff_slash_e2.png");
    eff_slash_e2->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_e2->setPosition(ccp(60.0, 60.0));
    eff_slash_e2->setScaleY(0.9);
    eff_slash_e2->setOpacity(0.0);
    parent->addChild(eff_slash_e2);

    eff_slash_e11->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(5.0 / 30.0, 1.8, 0.901),
       CCScaleTo::create(3.0 / 30.0, 0.916, 0.55),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCRotateBy::create(5.0 / 30.0, 13.8),
       CCRotateBy::create(3.0 / 30.0, -3.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_e12->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(5.0 / 30.0, 1.317, 0.659),
       CCScaleTo::create(3.0 / 30.0, 0.719, 1.199),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(5.0 / 30.0, 19.1),
       CCRotateBy::create(3.0 / 30.0, -5.1),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_e2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(5.0 / 30.0, 1.5, 1.35),
       CCScaleTo::create(3.0 / 30.0, 1.6, 1.44),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       NULL),
      NULL));
}
void EffectFactory::createSlashEffectAnimation_Normal(cocos2d::CCNode *parent){
    NFSpriteCluster* eff_slash_a2 = NFSpriteCluster::create("eff_slash_a2.png");
    eff_slash_a2->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_a2->setPosition(ccp(30.0, 30.0));
    eff_slash_a2->setScaleX(0.7);
    eff_slash_a2->setScaleY(0.47);
    eff_slash_a2->setOpacity(0.0);
    parent->addChild(eff_slash_a2);
    
    NFSpriteCluster* eff_slash_a11 = NFSpriteCluster::create("eff_slash_a1.png");
    eff_slash_a11->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_a11->setPosition(ccp(30.0, 30.0));
    eff_slash_a11->setScaleX(0.6);
    eff_slash_a11->setScaleY(0.6);
    eff_slash_a11->setRotation(70.0);
    parent->addChild(eff_slash_a11);
    
    NFSpriteCluster* eff_slash_a12 = NFSpriteCluster::create("eff_slash_a1.png");
    eff_slash_a12->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_a12->setPosition(ccp(30.0, 30.0));
    eff_slash_a12->setScaleX(0.598);
    eff_slash_a12->setScaleY(0.599);
    eff_slash_a12->setRotation(100.0);
    eff_slash_a12->setOpacity(0.0);
    parent->addChild(eff_slash_a12);

    eff_slash_a2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCScaleTo::create(5.0 / 30.0, 1.8, 1.5),
       CCScaleTo::create(3.0 / 30.0, 1.92, 1.6),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCRotateBy::create(5.0 / 30.0, 0.0),
       CCRotateBy::create(3.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 101.6),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_slash_a11->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.194, 0.597),
       CCScaleTo::create(3.0 / 30.0, 0.79, 0.474),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCRotateBy::create(4.0 / 30.0, 19.1),
       CCRotateBy::create(3.0 / 30.0, -4.7),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_a12->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.44, 0.721),
       CCScaleTo::create(3.0 / 30.0, 0.915, 0.549),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(4.0 / 30.0, -13.9),
       CCRotateBy::create(3.0 / 30.0, 3.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
}
void EffectFactory::createSlashEffectAnimation_Kunoichi(cocos2d::CCNode *parent){
    NFSpriteCluster* eff_slash_b2 = NFSpriteCluster::create("eff_slash_b2.png");
    eff_slash_b2->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_b2->setPosition(ccp(30.0, 30.0));
    eff_slash_b2->setScaleX(0.8);
    eff_slash_b2->setScaleY(0.6);
    eff_slash_b2->setOpacity(0.0);
    parent->addChild(eff_slash_b2);
    
    NFSpriteCluster* eff_slash_b1 = NFSpriteCluster::create("eff_slash_b1.png");
    eff_slash_b1->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_b1->setPosition(ccp(30.0, 30.0));
    eff_slash_b1->setScaleX(1.0);
    eff_slash_b1->setScaleY(1.0);
    eff_slash_b1->setRotation(10.0);
    eff_slash_b1->setOpacity(0.0);
    parent->addChild(eff_slash_b1);

    eff_slash_b2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.6, 1.2),
       CCScaleTo::create(6.0 / 30.0, 2.0, 1.5),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_b1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, -20.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.8),
       CCScaleTo::create(5.0 / 30.0, 1.8),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCRotateBy::create(4.0 / 30.0, -10.0),
       CCRotateBy::create(5.0 / 30.0, -10.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(5.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 76.7),
       CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(5.0 / 30.0, 0.0),
       NULL),
      NULL));
}
void EffectFactory::createSlashEffectAnimation_Musasabi(cocos2d::CCNode *parent){
    NFSpriteCluster* eff_slash_c2 = NFSpriteCluster::create("eff_slash_c2.png");
    eff_slash_c2->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_c2->setPosition(ccp(30.0, 30.0));
    eff_slash_c2->setScaleY(0.75);
    eff_slash_c2->setOpacity(0.0);
    parent->addChild(eff_slash_c2);
    
    NFSpriteCluster* eff_slash_c1 = NFSpriteCluster::create("eff_slash_c1.png");
    eff_slash_c1->setAnchorPoint(ccp(0.5, 0.871));
    eff_slash_c1->setPosition(ccp(30.0, 30.0));
    eff_slash_c1->setScale(0.6);
    eff_slash_c1->setOpacity(63.8);
    parent->addChild(eff_slash_c1);

    eff_slash_c2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCScaleTo::create(3.0 / 30.0, 1.3, 0.975),
       CCScaleTo::create(3.0 / 30.0, 1.5, 1.125),
       CCScaleTo::create(3.0 / 30.0, 1.6, 1.2),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(3.0 / 30.0, 255.0),
       CCFadeTo::create(3.0 / 30.0, 191.3),
       CCFadeTo::create(3.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_slash_c1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.164, 1.6),
       CCScaleTo::create(2.0 / 30.0, 1.164, 1.6),
       CCScaleTo::create(2.0 / 30.0, 0.6, 1.2),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCRotateBy::create(4.0 / 30.0, 0.0),
       CCRotateBy::create(2.0 / 30.0, 0.0),
       CCRotateBy::create(2.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(4.0 / 30.0, 255.0),
       CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(2.0 / 30.0, 63.8),
       CCDelayTime::create(1.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 0.0),
       NULL),
      NULL));

}
void EffectFactory::createSlashEffectAnimation_Revive(cocos2d::CCNode *parent){
    NFSpriteCluster* eff_slash_d2 = NFSpriteCluster::create("eff_slash_d2.png");
    eff_slash_d2->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_d2->setPosition(ccp(30.0, 30.0));
    eff_slash_d2->setScaleX(0.8);
    eff_slash_d2->setScaleY(0.6);
    eff_slash_d2->setOpacity(0.0);
    parent->addChild(eff_slash_d2);
    
    NFSpriteCluster* eff_slash_d1 = NFSpriteCluster::create("eff_slash_d1.png");
    eff_slash_d1->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_d1->setPosition(ccp(30.0, 30.0));
    eff_slash_d1->setScaleY(0.9);
    eff_slash_d1->setOpacity(0.0);
    parent->addChild(eff_slash_d1);

    eff_slash_d2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 2.0, 1.5),
       CCScaleTo::create(6.0 / 30.0, 2.3, 1.725),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_d1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 2.0, 1.8),
       CCScaleTo::create(5.0 / 30.0, 2.2, 1.98),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCRotateBy::create(5.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 76.7),
       CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(5.0 / 30.0, 76.7),
       NULL),
      NULL));
}

void EffectFactory::createSlashEffectAnimation_Brown(cocos2d::CCNode *parent){
    NFSpriteCluster* eff_slash_100b = NFSpriteCluster::create("eff_slash_100b.png");
    eff_slash_100b->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_100b->setPosition(ccp(0.0, 0.0));
    eff_slash_100b->setScale(0.8);
    eff_slash_100b->setOpacity(0.0);
    parent->addChild(eff_slash_100b);
    
    NFSpriteCluster* eff_slash_100a = NFSpriteCluster::create("eff_slash_100a.png");
    eff_slash_100a->setAnchorPoint(ccp(0.5, 0.5));
    eff_slash_100a->setPosition(ccp(0.0, 0.0));
    eff_slash_100a->setScaleX(1.0);
    eff_slash_100a->setScaleY(1.0);
    eff_slash_100a->setRotation(10.0);
    eff_slash_100a->setOpacity(0.0);
    parent->addChild(eff_slash_100a);

    eff_slash_100b->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.6),
       CCScaleTo::create(4.0 / 30.0, 2.0),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_slash_100a->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.6),
       CCScaleTo::create(6.0 / 30.0, 2.199),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCRotateBy::create(4.0 / 30.0, -10.0),
       CCRotateBy::create(6.0 / 30.0, -10.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 76.7),
       CCFadeTo::create(4.0 / 30.0, 255.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       NULL),
      NULL));

}

#import "NFLabelTTF.h"
#import "User.h"
void EffectFactory::createRentalInfoEffect(cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* game_hire_bg_03 = NFSpriteCluster::create("game_hire_bg_03.png");
    game_hire_bg_03->setAnchorPoint(ccp(0.5, 0.5));
    game_hire_bg_03->setPosition(ccp(320.0, 20.0));
    game_hire_bg_03->setOpacity(0.0);
    parent->addChild(game_hire_bg_03,zOrder);
    
    NFSpriteCluster* game_hire_bg_02_02 = NFSpriteCluster::create("game_hire_bg_02_02.png");
    game_hire_bg_02_02->setAnchorPoint(ccp(0.5, 0.5));
    game_hire_bg_02_02->setPosition(ccp(632.0, 206.0));
    game_hire_bg_02_02->setScaleY(83.0);
    game_hire_bg_02_02->setOpacity(0.0);
    parent->addChild(game_hire_bg_02_02,zOrder);
    
    NFSpriteCluster* game_hire_bg_02_01 = NFSpriteCluster::create("game_hire_bg_02_01.png");
    game_hire_bg_02_01->setAnchorPoint(ccp(0.5, 0.5));
    game_hire_bg_02_01->setPosition(ccp(8.0, 206.0));
    game_hire_bg_02_01->setScaleY(83.0);
    game_hire_bg_02_01->setOpacity(0.0);
    parent->addChild(game_hire_bg_02_01,zOrder);
    
    NFSpriteCluster* game_hire_bg_01 = NFSpriteCluster::create("game_hire_bg_01.png");
    game_hire_bg_01->setAnchorPoint(ccp(0.5, 0.5));
    game_hire_bg_01->setPosition(ccp(320.0, 394.0));
    game_hire_bg_01->setOpacity(0.0);
    parent->addChild(game_hire_bg_01,zOrder);
    
    NFSpriteCluster* logo_shop_hire_01 = NFSpriteCluster::create("logo_shop_hire_01.png");
    logo_shop_hire_01->setAnchorPoint(ccp(0.5, 0.5));
    logo_shop_hire_01->setPosition(ccp(85.0, 393.0));
    logo_shop_hire_01->setOpacity(0.0);
    parent->addChild(logo_shop_hire_01,zOrder);
    
    NFSpriteCluster* game_record_id_bg_01 = NFSpriteCluster::create("game_record_id_bg_01.png");
    game_record_id_bg_01->setAnchorPoint(ccp(0.5, 0.5));
    game_record_id_bg_01->setPosition(ccp(222.0, 320.0));
    parent->addChild(game_record_id_bg_01,zOrder);
    
    User* user = User::getInstance();
    CCString* name = user->getRentalFriendName();
    NFLabelTTF* txt_id_game_record_01_t00001 = NFLabelTTF::create(name->getCString(), FONT_W6, 20, CCSizeMake(392.0, 18.0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    txt_id_game_record_01_t00001->setColor(ccc3(0xff, 0xff, 0xff));
    txt_id_game_record_01_t00001->setAnchorPoint(ccp(0.0, 1.0));
    txt_id_game_record_01_t00001->setPosition(ccp(124.0, 328.0));
    parent->addChild(txt_id_game_record_01_t00001,zOrder);
    
    NFSpriteCluster* ico_profile_bg_03 = NFSpriteCluster::create("ico_profile_bg_03.png");
    ico_profile_bg_03->setAnchorPoint(ccp(0.5, 0.5));
    ico_profile_bg_03->setPosition(ccp(69.0, 319.0));
    parent->addChild(ico_profile_bg_03,zOrder);
    
    CCSprite* icon = NULL;
    const char* photoUrl = user->getRentalFriendPhotoURL().c_str();
    if(::strcmp(photoUrl, "list_rank_ico_master_01.png") == 0){
        icon = CCSprite::create(photoUrl);
    }else{
        icon = CCSprite::create();
        if(::strcmp(photoUrl , "") != 0){
            CCNodeUtil::setImageFromURL(icon, user->getRentalFriendPhotoURL().c_str() , 88, 88 ,true);
        }
    }
    
    
//    CCSprite* icon = CCSprite::create();
//    CCNodeUtil::setImageFromURL(icon, user->getRentalFriendPhotoURL().c_str() , 88, 88 , true);
//    
    
    //CCSprite* ico_profile_non_s_01 = CCSprite::createWithTexture(user->getRentalFriendIcon()->getTexture());
    CCSprite* ico_profile_non_s_01 = icon;
    ico_profile_non_s_01->setAnchorPoint(ccp(0.5, 0.5));
    ico_profile_non_s_01->setScale(66/ico_profile_non_s_01->getContentSize().width);
    ico_profile_non_s_01->setPosition(ccp(69.0, 319.0));
    parent->addChild(ico_profile_non_s_01,zOrder);
    
    NFSpriteCluster* ico_profile_bg_01 = NFSpriteCluster::create("ico_profile_bg_01.png");
    ico_profile_bg_01->setAnchorPoint(ccp(0.5, 0.5));
    ico_profile_bg_01->setPosition(ccp(69.0, 319.0));
    parent->addChild(ico_profile_bg_01,zOrder);
    
    ico_profile_non_s_01->runAction(
                            CCSequence::create(
                                CCDelayTime::create(4.0),
                                CCNodeUtil::createRemoveAction(),
                                NULL));
    
    ico_profile_bg_01->runAction(CCSequence::create(
                                CCDelayTime::create(4.0),
                                CCNodeUtil::createRemoveAction(),
                                NULL));
    
    txt_id_game_record_01_t00001->runAction(CCSequence::create(
                                CCDelayTime::create(4.0),
                                CCNodeUtil::createRemoveAction(),
                                NULL));
    
    game_record_id_bg_01->runAction(CCSequence::create(
                                                               CCDelayTime::create(4.0),
                                                               CCNodeUtil::createRemoveAction(),
                                                               NULL));
    ico_profile_bg_03->runAction(CCSequence::create(
                                                    CCDelayTime::create(4.0),
                                                    CCNodeUtil::createRemoveAction(),
                                                    NULL));
    
    game_hire_bg_03->runAction
    (CCSequence::create
     (CCFadeTo::create(14.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 0.0),
      CCNodeUtil::createRemoveAction(),
      NULL)
     );
    game_hire_bg_02_02->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(119.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 0.0),
       NULL),
      NULL));
    game_hire_bg_02_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(119.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 76.7),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCFadeTo::create(15.0 / 30.0, 0.0),
       NULL),
      NULL));
    game_hire_bg_01->runAction
    (CCSequence::create
     (CCFadeTo::create(14.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 0.0),
      CCNodeUtil::createRemoveAction(),
      NULL)
     );
    logo_shop_hire_01->runAction
    (CCSequence::create
     (CCFadeTo::create(14.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 76.7),
      CCFadeTo::create(15.0 / 30.0, 255.0),
      CCFadeTo::create(15.0 / 30.0, 0.0),
      CCNodeUtil::createRemoveAction(),
      NULL)
     );

    
}

void EffectFactory::createSpeedUpInfo(cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* speed_up = NFSpriteCluster::create("speed_up.png");
    speed_up->setAnchorPoint(ccp(0.5, 0.5));
    speed_up->setPosition(ccp(320.0, 820.0));
    speed_up->setOpacity(0.0);
    parent->addChild(speed_up,zOrder);
    
    speed_up->runAction(CCSequence::create(
                            CCFadeIn::create(0.3),
                            CCDelayTime::create(0.85),
                            CCSpawn::create(
                                CCFadeOut::create(0.3)
                                ,CCMoveBy::create(0.3, ccp(0, -30))
                                ,NULL)
                            ,CCNodeUtil::createRemoveAction()
                                ,NULL));
}

#import "Event.h"
void EffectFactory::createNearBossInfo( int bossNo, cocos2d::CCNode *parent, int zOrder){
    CCPoint pos = ccp( 320, 615);
    
    CCSprite* bs_name_p2 = CCSprite::create("bs_name_p2.png");
    bs_name_p2->setAnchorPoint(ccp(0.5, 0.5));
    bs_name_p2->setPosition(ccpAdd(pos, ccp(440.0, -10.0)));
    bs_name_p2->setScale(2.0);
    bs_name_p2->setOpacity(0.0);
    parent->addChild(bs_name_p2);
    
    CCSprite* bs_name_p1 = CCSprite::create("bs_name_p1.png");
    bs_name_p1->setAnchorPoint(ccp(0.5, 0.5));
    bs_name_p1->setPosition(ccpAdd(pos, ccp(-440.0, -10.0)));
    bs_name_p1->setScale(2.0);
    bs_name_p1->setOpacity(0.0);
    parent->addChild(bs_name_p1);
    
    char filiname[128];
    sprintf(filiname, "bs_name_%02d.png", bossNo);
    CCSprite* bs_name_01 = CCSprite::create(filiname);
    bs_name_01->setAnchorPoint(ccp(0.5, 0.5));
    bs_name_01->setPosition(ccpAdd(pos, ccp(0.0, 0.0)));
    bs_name_01->setScale(2.0);
    bs_name_01->setOpacity(0.0);
    parent->addChild(bs_name_01);

    bs_name_p2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(6.0 / 30.0, ccp(-444.0, 0.0)),
       CCMoveBy::create(5.0 / 30.0, ccp(4.0, 0.0)),
       CCDelayTime::create(50.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(6.0 / 30.0, 2.0),
       CCScaleTo::create(5.0 / 30.0, 2.0),
       CCDelayTime::create(50.0 / 30.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(6.0 / 30.0, 255.0),
       CCDelayTime::create(50.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    bs_name_p1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(6.0 / 30.0, ccp(444.0, 0.0)),
       CCMoveBy::create(5.0 / 30.0, ccp(-4.0, 0.0)),
       CCDelayTime::create(50.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(6.0 / 30.0, 2.0),
       CCScaleTo::create(5.0 / 30.0, 2.0),
       CCDelayTime::create(50.0 / 30.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(6.0 / 30.0, 255.0),
       CCDelayTime::create(50.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    bs_name_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(64.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(10.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCDelayTime::create(45.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
}

void EffectFactory::createNearRaidBossInfo(int bossNo, cocos2d::CCNode *parent, int zOrder){
    CCPoint pos = ccp( 320, 615);//ccp( winSize.width/2, winSize.height/2);
    
    char filiname[128];
    
    if(bossNo >= 117){
        bossNo = 116;
    }
    
    sprintf(filiname, "bs_name_%02d.png", bossNo);
    CCSprite* bs_name_101 = CCSprite::create(filiname);
    bs_name_101->setAnchorPoint(ccp(0.5, 0.5));
    bs_name_101->setPosition(ccpAdd(pos, ccp(0.0, 30.0)));
    bs_name_101->setScale(2.0);
    bs_name_101->setOpacity(0.0);
    parent->addChild(bs_name_101);
    
    int level = User::getInstance()->getRaidInfo()->lv;
    NFNumberLayer* num_distance_m_01 = NFNumberLayer::create(level, "num_distance_m_01.png", 36.0, 44.0, 0, 22, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0);
    num_distance_m_01->setPosition(ccpAdd(pos, ccp(48.0, -12.0)));
    num_distance_m_01->setOpacity(0.0);
    parent->addChild(num_distance_m_01);

    bs_name_101->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, -30.0)),
       CCDelayTime::create(71.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 2.0),
       CCScaleTo::create(5.0 / 30.0, 2.0),
       CCDelayTime::create(75.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCDelayTime::create(71.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
    num_distance_m_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, -30.0)),
       CCDelayTime::create(71.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCDelayTime::create(71.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
}

void EffectFactory::createRaidBossWeak(int attr, cocos2d::CCNode *parent, int zOrder){
    
    NFSpriteCluster* bg_weak_point_01 = NFSpriteCluster::create("bg_weak_point_01.png");
    parent->addChild(bg_weak_point_01);
    bg_weak_point_01->setAnchorPoint(ccp(0.5, 0.5));
    bg_weak_point_01->setPosition(ccp(320.0, 538.0));
    bg_weak_point_01->setScale(2.0);
    bg_weak_point_01->setOpacity(0.0);
    
    char elementFilename[128];
    getBuddyElementIconFilename(elementFilename, attr, kCostumBasic, false);
    NFSpriteCluster* ico_element_001 = NFSpriteCluster::create(elementFilename);
    parent->addChild(ico_element_001);
    ico_element_001->setAnchorPoint(ccp(0.5, 0.5));
    ico_element_001->setPosition(ccp(486.4, 509.6));
    ico_element_001->setScaleX(3.0);
    ico_element_001->setScaleY(3.0);
    ico_element_001->setOpacity(0.0);
    
    NFSpriteCluster* ico_element_002 = NFSpriteCluster::create(elementFilename);
    parent->addChild(ico_element_002);
    ico_element_002->setAnchorPoint(ccp(0.5, 0.5));
    ico_element_002->setPosition(ccp(486.4, 509.6));
    ico_element_002->setScaleX(1.2);
    ico_element_002->setScaleY(1.2);
    ico_element_002->setOpacity(0.0);
    ico_element_002->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    bg_weak_point_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, -30.0)),
       CCDelayTime::create(71.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCDelayTime::create(71.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
    ico_element_001->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(14.0 / 30.0),
       CCMoveBy::create(9.0 / 30.0, ccp(-0.3041, 0.547)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.302, -0.548)),
       CCDelayTime::create(56.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(14.0 / 30.0),
       CCScaleTo::create(9.0 / 30.0, 1.218),
       CCScaleTo::create(1.0 / 30.0, 1.2),
       CCDelayTime::create(60.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCFadeTo::create(5.0 / 30.0, 255.0),
       CCDelayTime::create(66.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
    ico_element_002->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(36.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(24.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCFadeTo::create(11.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(35.0 / 30.0),
       CCNodeUtil::createSetBlendFuncAction(ico_element_002, CC_BLEND_SRC, CC_BLEND_DST),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
}

void EffectFactory::createAddBonusScore(int _score, bool isDash, cocos2d::CCNode *parent, int zOrder){
    
//    NFSpriteCluster* socre_bonus_bg_01 = NFSpriteCluster::create("socre_bonus_bg_01.png");
//    socre_bonus_bg_01->setAnchorPoint(ccp(0.5, 0.5));
//    socre_bonus_bg_01->setPosition(ccp(320.0, 462.0));
//    socre_bonus_bg_01->setOpacity(0.0);
//    parent->addChild(socre_bonus_bg_01);
//    
//    NFNumberLayer* num_score_l_01 = NFNumberLayer::create(_score, "num_score_l_01.png", 62.0, 80.0, -10, 32, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0, "sign_plus", 62, 0, 0, 0);
//    num_score_l_01->setPosition(ccp(319.0, 429.7));
//    num_score_l_01->setOpacity(0.0);
//    parent->addChild(num_score_l_01);
    
    CCSprite* socre_bonus_bg_01 = CCSprite::create("socre_bonus_bg_01.png");
    socre_bonus_bg_01->setAnchorPoint(ccp(0.5, 0.5));
    socre_bonus_bg_01->setPosition(ccp(320.0, 430.0));
    socre_bonus_bg_01->setOpacity(0.0);
    parent->addChild(socre_bonus_bg_01);
    
    CCSprite* logo_socre_bonus_01;
    if(isDash){
        logo_socre_bonus_01 = CCSprite::create("logo_socre_bonus_02.png");
    }else{
        logo_socre_bonus_01 = CCSprite::create("logo_socre_bonus_01.png");
    }
    logo_socre_bonus_01->setAnchorPoint(ccp(0.5, 0.5));
    logo_socre_bonus_01->setPosition(ccp(320.0, 496.0));
    logo_socre_bonus_01->setOpacity(0.0);
    parent->addChild(logo_socre_bonus_01);
    
    NFNumberLayer* num_score_l_01 = NFNumberLayer::create(_score, "num_score_l_01.png", 62.0, 80.0, -10, 32, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0, "sign_plus", 62, 0, 0, 0);
    num_score_l_01->setPosition(ccp(319.0, 430.0));
    num_score_l_01->setOpacity(0.0);
    parent->addChild(num_score_l_01);
    
    socre_bonus_bg_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 50.0)),
       CCDelayTime::create(30.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.0)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 33.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(35.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      NULL));
    logo_socre_bonus_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 50.0)),
       CCDelayTime::create(30.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.0)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 33.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(35.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      NULL));
    num_score_l_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 50.0)),
       CCDelayTime::create(30.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 17.0)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 33.0)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(35.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      NULL));
    
 }

void EffectFactory::createLuckZoneBonus(bool isExcellent, cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* Logo_turn_point_good_02;
    
    if( isExcellent ){
        Logo_turn_point_good_02 = NFSpriteCluster::create("Logo_turn_point_good_02.png");
    }else{
        Logo_turn_point_good_02 = NFSpriteCluster::create("Logo_turn_point_good_01.png");
    }
    
    Logo_turn_point_good_02->setAnchorPoint(ccp(0.5, 0.5));
    Logo_turn_point_good_02->setPosition(ccp(321.0, 341.0));
    Logo_turn_point_good_02->setOpacity(0.0);
    parent->addChild(Logo_turn_point_good_02);
    
    Logo_turn_point_good_02->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(14.0 / 30.0, ccp(0.0, 50.0)),
       CCDelayTime::create(30.0 / 30.0),
       CCMoveBy::create(5.0 / 30.0, ccp(0.0, 16.65)),
       CCMoveBy::create(10.0 / 30.0, ccp(0.0, 33.4)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 255.0),
       CCDelayTime::create(35.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       NULL),
      NULL));
}

void EffectFactory::createHienWing(cocos2d::CCNode *parent, cocos2d::CCPoint _pos, int zOrder){
    CCSprite* p11_wsfx1 = CCSprite::create("p11_wsfx1.png");
    p11_wsfx1->setAnchorPoint(ccp(1.0, 0.5));
    p11_wsfx1->setPosition(_pos);
    p11_wsfx1->setOpacity(0.0);
    parent->addChild(p11_wsfx1);
    
    CCSprite* p11_wsfx2 = CCSprite::create("p11_wsfx2.png");
    p11_wsfx2->setAnchorPoint(ccp(0.0, 0.5));
    p11_wsfx2->setPosition(_pos);
    p11_wsfx2->setOpacity(0.0);
    parent->addChild(p11_wsfx2);
    
    CCSprite* eff_jjj04 = CCSprite::create("eff_jjj04.png");
    eff_jjj04->setAnchorPoint(ccp(0.5, 0.5));
    eff_jjj04->setPosition(_pos);
    eff_jjj04->setOpacity(0.0);
    parent->addChild(eff_jjj04);
    
    CCSprite* eff_jjj03 = CCSprite::create("eff_jjj03.png");
    eff_jjj03->setAnchorPoint(ccp(0.5, 0.5));
    eff_jjj03->setPosition(_pos);
    eff_jjj03->setOpacity(0.0);
    parent->addChild(eff_jjj03);

    p11_wsfx1->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCMoveBy::create(7.0 / 30.0, ccp(40.0, 0.0)),
       CCDelayTime::create(18.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCScaleTo::create(7.0 / 30.0, 3.0),
       CCScaleTo::create(10.0 / 30.0, 3.35),
       CCScaleTo::create(7.0 / 30.0, 3.6),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(17.0 / 30.0),
       CCFadeTo::create(7.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    p11_wsfx2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCMoveBy::create(7.0 / 30.0, ccp(-40.0, 0.0)),
       CCDelayTime::create(18.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCScaleTo::create(7.0 / 30.0, 3.0),
       CCScaleTo::create(10.0 / 30.0, 3.35),
       CCScaleTo::create(7.0 / 30.0, 3.6),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(7.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(17.0 / 30.0),
       CCFadeTo::create(7.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_jjj04->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(7.0 / 30.0, 3.6),
       CCScaleTo::create(22.0 / 30.0, 2.4),
       CCScaleTo::create(8.0 / 30.0, 1.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCFadeTo::create(7.0 / 30.0, 255.0),
       CCDelayTime::create(22.0 / 30.0),
       CCFadeTo::create(8.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_jjj03->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCScaleTo::create(10.0 / 30.0, 3.6),
       CCScaleTo::create(10.0 / 30.0, 4.0),
       CCDelayTime::create(1.0 / 30.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(0.0 / 30.0, 255.0),
       CCDelayTime::create(10.0 / 30.0),
       CCFadeTo::create(10.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
 }

void EffectFactory::createNewRecode(cocos2d::CCNode *parent, int zOrder){
    
    NFSpriteCluster* logo_new_record_01 = NFSpriteCluster::create("logo_new_record_s_01.png");
    parent->addChild(logo_new_record_01);
    logo_new_record_01->setAnchorPoint(ccp(0.5, 0.5));
    logo_new_record_01->setPosition(ccp(536.0, 878.0));
    logo_new_record_01->setOpacity(0.0);
    
    NFSpriteCluster* eff_new_record_011 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_011);
    eff_new_record_011->setAnchorPoint(ccp(0.5, 0.5));
    eff_new_record_011->setPosition(ccp(602.5, 892.9));
    eff_new_record_011->setOpacity(0.0);
    eff_new_record_011->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    NFSpriteCluster* eff_new_record_012 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_012);
    eff_new_record_012->setAnchorPoint(ccp(0.5, 0.498));
    eff_new_record_012->setPosition(ccp(514.3, 890.3));
    eff_new_record_012->setScale(1.088);
    eff_new_record_012->setOpacity(0.0);
    eff_new_record_012->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    NFSpriteCluster* eff_new_record_013 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_013);
    eff_new_record_013->setAnchorPoint(ccp(0.5, 0.5));
    eff_new_record_013->setPosition(ccp(465.0, 904.4));
    eff_new_record_013->setScale(0.912);
    eff_new_record_013->setOpacity(0.0);
    eff_new_record_013->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    NFSpriteCluster* eff_new_record_014 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_014);
    eff_new_record_014->setAnchorPoint(ccp(0.498, 0.502));
    eff_new_record_014->setPosition(ccp(575.0, 903.7));
    eff_new_record_014->setScale(0.794);
    eff_new_record_014->setOpacity(0.0);
    eff_new_record_014->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    NFSpriteCluster* eff_new_record_015 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_015);
    eff_new_record_015->setAnchorPoint(ccp(0.502, 0.502));
    eff_new_record_015->setPosition(ccp(499.7, 890.7));
    eff_new_record_015->setScale(0.89);
    eff_new_record_015->setOpacity(0.0);
    eff_new_record_015->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    NFSpriteCluster* eff_new_record_016 = NFSpriteCluster::create("eff_new_record_01.png");
    parent->addChild(eff_new_record_016);
    eff_new_record_016->setAnchorPoint(ccp(0.5, 0.494));
    eff_new_record_016->setPosition(ccp(610.0, 902.2));
    eff_new_record_016->setScale(0.912);
    eff_new_record_016->setOpacity(0.0);
    eff_new_record_016->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    
    EffectFactory* caller = new EffectFactory();
    parent->addChild(caller);
    
    {
        logo_new_record_01->runAction
        (CCSequence::create
         (CCSpawn::create
          (CCSequence::create
           (CCMoveBy::create(6.0 / 30.0, ccp(0.0, 22.35)),
            CCMoveBy::create(2.0 / 30.0, ccp(0.0, -3.55)),
            CCMoveBy::create(1.0 / 30.0, ccp(0.0, 1.2)),
            CCDelayTime::create(30.0 / 30.0),
            NULL),
           CCSequence::create
           (CCFadeTo::create(6.0 / 30.0, 171.3),
            CCFadeTo::create(2.0 / 30.0, 227.1),
            CCFadeTo::create(1.0 / 30.0, 255.0),
            CCDelayTime::create(30.0 / 30.0),
            NULL),
           NULL)
          ,CCCallFuncND::create(caller,callfuncND_selector(EffectFactory::setNewRecodeRepeat),(void*)logo_new_record_01)
          ,NULL));
        
        eff_new_record_011->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(9.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(1.221E-4, -1.221E-4)),
           CCMoveBy::create(5.0 / 30.0, ccp(-6.1E-5, 6.1E-5)),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(9.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 1.208),
           CCScaleTo::create(5.0 / 30.0, 1.417),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(9.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        eff_new_record_012->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(13.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(0.02058, 0.0338)),
           CCMoveBy::create(5.0 / 30.0, ccp(-0.02924, -0.02076)),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(13.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 1.315),
           CCScaleTo::create(5.0 / 30.0, 1.542),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(13.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        eff_new_record_013->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(17.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(-0.0756, 0.1358)),
           CCMoveBy::create(5.0 / 30.0, ccp(0.0844, -0.1446)),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(17.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 1.102),
           CCScaleTo::create(5.0 / 30.0, 1.292),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(17.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        eff_new_record_014->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(21.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(-0.02488, 0.1668)),
           CCMoveBy::create(5.0 / 30.0, ccp(0.0352, -0.1771)),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(21.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 0.96),
           CCScaleTo::create(5.0 / 30.0, 1.125),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(21.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        eff_new_record_015->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(25.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(-0.0739, -0.01885)),
           CCMoveBy::create(5.0 / 30.0, ccp(0.02794, -0.02418)),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(25.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 1.075),
           CCScaleTo::create(5.0 / 30.0, 1.26),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(25.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        eff_new_record_016->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCDelayTime::create(29.0 / 30.0),
           CCMoveBy::create(5.0 / 30.0, ccp(0.02948, 0.1073)),
           CCMoveBy::create(5.0 / 30.0, ccp(-0.0207, 0.0207)),
           NULL),
          CCSequence::create
          (CCDelayTime::create(29.0 / 30.0),
           CCScaleTo::create(5.0 / 30.0, 1.102),
           CCScaleTo::create(5.0 / 30.0, 1.292),
           NULL),
          CCSequence::create
          (CCDelayTime::create(29.0 / 30.0),
           CCFadeTo::create(5.0 / 30.0, 204.2),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
    }
}

void EffectFactory::setNewRecodeRepeat(cocos2d::CCNode *sender, void* data){
    NFSpriteCluster* obj = (NFSpriteCluster*)data;
    
    obj->setOpacity(255);
    obj->setPosition(ccp(536.0, 898.0));
    obj->setScale(1);
    obj->setRotation(0);
    
    obj->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCFadeTo::create(14.0 / 30.0, 0.0),
       CCFadeTo::create(15.0 / 30.0, 255.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL)
      ));
    
    this->removeFromParentAndCleanup(true);
    this->release();
}

void EffectFactory::createBlockBreak(cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* eff_boxbomb2 = NFSpriteCluster::create("eff_boxbomb2.png");
    eff_boxbomb2->setAnchorPoint(ccp(0.5, 0.5));
    eff_boxbomb2->setPosition(ccp(0.0, 0.0));
    eff_boxbomb2->setOpacity(127.5);
    parent->addChild(eff_boxbomb2);
    
    NFSpriteCluster* eff_boxbomb11 = NFSpriteCluster::create("eff_boxbomb1.png");
    eff_boxbomb11->setAnchorPoint(ccp(0.5, 0.4));
    eff_boxbomb11->setPosition(ccp(0.0, 0.0));
    eff_boxbomb11->setScaleX(0.915);
    eff_boxbomb11->setScaleY(0.549);
    eff_boxbomb11->setRotation(19.1);
    parent->addChild(eff_boxbomb11);
    
    NFSpriteCluster* eff_boxbomb12 = NFSpriteCluster::create("eff_boxbomb1.png");
    eff_boxbomb12->setAnchorPoint(ccp(0.5, 0.4));
    eff_boxbomb12->setPosition(ccp( 0.0, 0.0));
    eff_boxbomb12->setScaleX(0.655);
    eff_boxbomb12->setScaleY(0.873);
    eff_boxbomb12->setRotation(-52.4);
    parent->addChild(eff_boxbomb12);
    
    eff_boxbomb2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(8.0 / 30.0, 1.599),
       CCScaleTo::create(6.0 / 30.0, 1.799),
       NULL),
      CCSequence::create
      (CCRotateBy::create(8.0 / 30.0, 9.8),
       CCRotateBy::create(6.0 / 30.0, 4.2),
       NULL),
      CCSequence::create
      (CCFadeTo::create(8.0 / 30.0, 255.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       NULL),
      NULL));
    eff_boxbomb11->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(6.0 / 30.0, 1.756, 1.364),
       CCScaleTo::create(6.0 / 30.0, 2.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCRotateBy::create(6.0 / 30.0, -3.3),
       CCRotateBy::create(6.0 / 30.0, -5.8),
       CCDelayTime::create(1.0 / 30.0),
       CCRotateBy::create(0.0 / 30.0, 0.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(6.0 / 30.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
    eff_boxbomb12->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.4),
       CCScaleTo::create(8.0 / 30.0, 2.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCRotateBy::create(4.0 / 30.0, 2.4),
       CCRotateBy::create(8.0 / 30.0, 10.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      CCSequence::create
      (CCDelayTime::create(4.0 / 30.0),
       CCFadeTo::create(8.0 / 30.0, 0.0),
       CCDelayTime::create(1.0 / 30.0),
       NULL),
      NULL));
}

/**
 * レイドボスがブロックを落とすチカチカ
 */
void EffectFactory::createFallBlockTargetAnim(int raidBossId , CCPoint pos , cocos2d::CCNode *parent, int zOrder){
    
    char imgStr[32];
    
    sprintf(imgStr, "bs%d_b1.png" , raidBossId);
    NFSpriteCluster* bs104_b11 = NFSpriteCluster::create(imgStr);
    bs104_b11->setAnchorPoint(ccp(0.5, 0.5));
    bs104_b11->setPosition(pos);
    bs104_b11->setOpacity(0.0);
    bs104_b11->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    parent->addChild(bs104_b11);
    
    sprintf(imgStr, "bs%d_b1.png" , raidBossId);
    NFSpriteCluster* bs104_b12 = NFSpriteCluster::create(imgStr);
    bs104_b12->setAnchorPoint(ccp(0.5, 0.5));
    bs104_b12->setPosition(pos);
    bs104_b12->setScale(2.0);
    bs104_b12->setOpacity(0.0);
    bs104_b12->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    parent->addChild(bs104_b12);
    

    // レイドボスがエジプトのメカだったら専用アニメーション
    if(raidBossId == 115){
        bs104_b11->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCScaleTo::create(5.0 / 30.0, 2.0),
           CCScaleTo::create(5.0 / 30.0, 1.0),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCFadeTo::create(5.0 / 30.0, 101.6),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          NULL));
        bs104_b12->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCScaleTo::create(10.0 / 30.0, 1.0),
           CCDelayTime::create(53.0 / 30.0),
           CCScaleTo::create(6.0 / 30.0, 3.0),
           NULL),
          CCSequence::create
          (CCFadeTo::create(10.0 / 30.0, 255.0),
           CCDelayTime::create(53.0 / 30.0),
           CCFadeTo::create(6.0 / 30.0, 0.0),
           NULL),
          CCSequence::create
          (CCDelayTime::create(23.0 / 30.0),
           CCRotateBy::create(20.0 / 30.0 , 180.0f),
           CCRotateBy::create(20.0 / 30.0 , 180.0f),
           CCDelayTime::create(6.0 / 30.0),
           NULL),
          NULL));
    }else{
        bs104_b11->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCScaleTo::create(5.0 / 30.0, 2.0),
           CCScaleTo::create(5.0 / 30.0, 1.0),
           CCDelayTime::create(1.0 / 30.0),
           NULL),
          CCSequence::create
          (CCFadeTo::create(5.0 / 30.0, 101.6),
           CCFadeTo::create(5.0 / 30.0, 0.0),
           CCDelayTime::create(1.0 / 30.0),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
        bs104_b12->runAction
        (CCSpawn::create
         (CCSequence::create
          (CCScaleTo::create(10.0 / 30.0, 1.0),
           CCDelayTime::create(60.0 / 30.0),
           NULL),
          CCSequence::create
          (CCFadeTo::create(10.0 / 30.0, 255.0),
           CCDelayTime::create(14.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(4.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(4.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(4.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(4.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(4.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 255.0),
           CCDelayTime::create(2.0 / 30.0),
           CCFadeTo::create(0.0 / 30.0, 0.0),
           //CCCallFuncO::create(this, callfuncO_selector(GroundObjectController::fallBlock), targetPos),
           CCNodeUtil::createRemoveAction(),
           NULL),
          NULL));
    }
}

void EffectFactory::createBeginHauntEffect(cocos2d::CCPoint pos, cocos2d::CCNode *parent, int zOrder, int tag){
    NFSpriteCluster* base = NFSpriteCluster::create();
    base->setAnchorPoint(ccp(0.5, 0.5));
    base->setPosition(pos);
    parent->addChild(base, zOrder, tag);
    
    NFSpriteCluster* eff_haunt_begin_04 = NFSpriteCluster::create("eff_haunt_begin_04.png");
    eff_haunt_begin_04->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_04->setPosition(ccp(-1.0, -1.0));
    base->addChild(eff_haunt_begin_04);
    
    NFSpriteCluster* eff_haunt_begin_03 = NFSpriteCluster::create("eff_haunt_begin_03.png");
    eff_haunt_begin_03->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_03->setPosition(ccp(-3.0, 13.0));
    eff_haunt_begin_03->setOpacity(178.3);
    base->addChild(eff_haunt_begin_03);
    
    NFSpriteCluster* eff_haunt_begin_02 = NFSpriteCluster::create("eff_haunt_begin_02.png");
    eff_haunt_begin_02->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_02->setPosition(ccp(-1.0, -20.0));
    base->addChild(eff_haunt_begin_02);
    
    NFSpriteCluster* eff_haunt_begin_01 = NFSpriteCluster::create("eff_haunt_begin_01.png");
    eff_haunt_begin_01->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_01->setPosition(ccp(-2.0, 11.0));
    base->addChild(eff_haunt_begin_01);
    
    eff_haunt_begin_04->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(1.0 / 30.0, ccp(-0.0883, -0.1368)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.1383, 0.1868)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.1248, -0.2212)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.1252, 0.2212)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.03125, -0.2858)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.2313, 0.2358)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.0748, -0.1712)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.1252, 0.2212)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.0843, -0.3096)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.113, 0.0586)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.1193, -0.2187)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.1953, 0.403)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.428, -0.2434)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.113, 0.0586)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.1685, -0.2102)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.01576, 0.3111)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.02478, -0.01744)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.02478, 0.01744)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.01795, 0.001017)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.1679, 0.099)),
        NULL),
       CCSequence::create
       (CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        CCScaleTo::create(1.0 / 30.0, 0.999),
        CCScaleTo::create(1.0 / 30.0, 1.0),
        NULL),
       CCSequence::create
       (CCRotateBy::create(1.0 / 30.0, 10.0),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, 10.0),
        CCRotateBy::create(1.0 / 30.0, 9.8),
        CCRotateBy::create(1.0 / 30.0, -9.8),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, 10.0),
        CCRotateBy::create(1.0 / 30.0, 10.0),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, -9.8),
        CCRotateBy::create(1.0 / 30.0, 14.6),
        CCRotateBy::create(1.0 / 30.0, 5.2),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, -9.8),
        CCRotateBy::create(1.0 / 30.0, 9.8),
        CCRotateBy::create(1.0 / 30.0, 10.0),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, -10.0),
        CCRotateBy::create(1.0 / 30.0, 10.0),
        NULL),
       CCSequence::create
       (CCDelayTime::create(2.0 / 30.0),
        CCNodeUtil::createSetBlendFuncAction(eff_haunt_begin_04, CC_BLEND_SRC, CC_BLEND_DST),
        CCDelayTime::create(4.0 / 30.0),
        CCNodeUtil::createSetBlendFuncAction(eff_haunt_begin_04, CC_BLEND_SRC, CC_BLEND_DST),
        CCDelayTime::create(1.0 / 30.0),
        CCNodeUtil::createSetBlendFuncAction(eff_haunt_begin_04, CC_BLEND_SRC, CC_BLEND_DST),
        CCDelayTime::create(13.0 / 30.0),
        CCNodeUtil::createSetBlendFuncAction(eff_haunt_begin_04, CC_BLEND_SRC, CC_BLEND_DST),
        NULL),
       NULL)));
    eff_haunt_begin_03->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(8.0 / 30.0, ccp(-0.001571, 0.00561)),
        CCMoveBy::create(11.0 / 30.0, ccp(0.001571, -0.00561)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.0, 0.0)),
        NULL),
       CCSequence::create
       (CCScaleTo::create(8.0 / 30.0, 1.1),
        CCScaleTo::create(11.0 / 30.0, 1.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       CCSequence::create
       (CCRotateBy::create(8.0 / 30.0, 0.0),
        CCRotateBy::create(11.0 / 30.0, 0.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       CCSequence::create
       (CCFadeTo::create(8.0 / 30.0, 76.7),
        CCFadeTo::create(11.0 / 30.0, 178.3),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       NULL)));
    eff_haunt_begin_02->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(5.0 / 30.0, ccp(0.0, -4.5)),
        CCMoveBy::create(5.0 / 30.0, ccp(0.0, 7.5)),
        CCMoveBy::create(4.0 / 30.0, ccp(0.0, -7.5)),
        CCMoveBy::create(5.0 / 30.0, ccp(0.0, 4.5)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.0, 0.0)),
        NULL),
       CCSequence::create
       (CCFadeTo::create(5.0 / 30.0, 229.1),
        CCFadeTo::create(5.0 / 30.0, 204.2),
        CCFadeTo::create(4.0 / 30.0, 229.1),
        CCFadeTo::create(5.0 / 30.0, 255.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       NULL)));
    eff_haunt_begin_01->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(8.0 / 30.0, ccp(-7.19E-4, 1.899)),
        CCMoveBy::create(5.0 / 30.0, ccp(-0.0039, -0.992)),
        CCMoveBy::create(6.0 / 30.0, ccp(0.00462, -0.908)),
        CCMoveBy::create(1.0 / 30.0, ccp(0.0, 0.0)),
        NULL),
       CCSequence::create
       (CCScaleTo::create(8.0 / 30.0, 1.0),
        CCScaleTo::create(5.0 / 30.0, 1.0),
        CCScaleTo::create(6.0 / 30.0, 1.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       CCSequence::create
       (CCRotateBy::create(8.0 / 30.0, 0.0),
        CCRotateBy::create(5.0 / 30.0, 0.0),
        CCRotateBy::create(6.0 / 30.0, 0.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       CCSequence::create
       (CCFadeTo::create(8.0 / 30.0, 204.2),
        CCFadeTo::create(5.0 / 30.0, 232.1),
        CCFadeTo::create(6.0 / 30.0, 255.0),
        CCDelayTime::create(1.0 / 30.0),
        NULL),
       NULL)));

}
void EffectFactory::createEndHauntEffect(cocos2d::CCPoint pos, cocos2d::CCNode *parent, int zOrder){
    NFSpriteCluster* eff_haunt_begin_04 = NFSpriteCluster::create("eff_haunt_begin_04.png");
    eff_haunt_begin_04->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_04->setPosition(ccp(-1.0, -1.0));
    parent->addChild(eff_haunt_begin_04);
    
    NFSpriteCluster* eff_haunt_begin_03 = NFSpriteCluster::create("eff_haunt_begin_03.png");
    eff_haunt_begin_03->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_03->setPosition(ccp(-3.0, 13.0));
    eff_haunt_begin_03->setOpacity(127.5);
    parent->addChild(eff_haunt_begin_03);
    
    NFSpriteCluster* eff_haunt_begin_02 = NFSpriteCluster::create("eff_haunt_begin_02.png");
    eff_haunt_begin_02->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_02->setPosition(ccp(-1.0, -20.0));
    parent->addChild(eff_haunt_begin_02);
    
    NFSpriteCluster* eff_haunt_begin_01 = NFSpriteCluster::create("eff_haunt_begin_01.png");
    eff_haunt_begin_01->setAnchorPoint(ccp(0.5, 0.5));
    eff_haunt_begin_01->setPosition(ccp(-2.0, 11.0));
    parent->addChild(eff_haunt_begin_01);

    eff_haunt_begin_04->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(9.0 / 30.0, ccp(0.0585, 0.0615)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCScaleTo::create(9.0 / 30.0, 1.1),
      CCFadeTo::create(9.0 / 30.0, 0.0),
      CCSequence::create
      (CCDelayTime::create(9.0 / 30.0),
       CCNodeUtil::createSetBlendFuncAction(eff_haunt_begin_04, CC_BLEND_SRC, CC_BLEND_DST),
       NULL),
      NULL));
    eff_haunt_begin_03->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(9.0 / 30.0, ccp(-8.54E-4, 0.001147)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCScaleTo::create(9.0 / 30.0, 1.1),
      CCFadeTo::create(9.0 / 30.0, 0.0),
      NULL));
    eff_haunt_begin_02->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(9.0 / 30.0, ccp(-5.37E-4, -12.5)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCScaleTo::create(9.0 / 30.0, 1.1),
      CCFadeTo::create(9.0 / 30.0, 0.0),
      NULL));
    eff_haunt_begin_01->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(9.0 / 30.0, ccp(-8.54E-4, 0.001147)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCScaleTo::create(9.0 / 30.0, 1.1),
      CCFadeTo::create(9.0 / 30.0, 0.0),
      NULL));

}
void EffectFactory::createBuddySealedDefenceEffect(cocos2d::CCPoint pos, cocos2d::CCNode *parent, int zOrder){
    CCSprite* bd_shield11 = CCSprite::create("bd_shield1.png");
    bd_shield11->setAnchorPoint(ccp(0.5, 0.5));
    bd_shield11->setPosition(ccpAdd(pos,ccp(1.0, 0.0)));
    bd_shield11->setScale(0.0562);
    bd_shield11->setOpacity(0.0);
    parent->addChild(bd_shield11);
    
    CCSprite* bd_shield12 = CCSprite::create("bd_shield1.png");
    bd_shield12->setAnchorPoint(ccp(0.5, 0.5));
    bd_shield12->setPosition(ccpAdd(pos,ccp(1.0, 0.0)));
    bd_shield12->setRotation(90.0);
    bd_shield12->setOpacity(0.0);
    bd_shield12->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE});
    parent->addChild(bd_shield12);
    
    CCSprite* bd_shield2 = CCSprite::create("bd_shield2.png");
    bd_shield2->setAnchorPoint(ccp(0.5, 0.5));
    bd_shield2->setPosition(ccpAdd(pos,ccp(-1.0, -2.0)));
    bd_shield2->setScale(1.09);
    bd_shield2->setOpacity(0.0);
    parent->addChild(bd_shield2);

    bd_shield11->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(10.0 / 20.0, ccp(0.00787, -0.00787)),
       CCDelayTime::create(8.0 / 20.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCScaleTo::create(10.0 / 20.0, 1.0),
       CCDelayTime::create(8.0 / 20.0),
       NULL),
      CCSequence::create
      (CCRotateBy::create(10.0 / 20.0, 90.0),
       CCDelayTime::create(8.0 / 20.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(10.0 / 20.0, 255.0),
       CCDelayTime::create(8.0 / 20.0),
       CCFadeTo::create(0.0 / 20.0, 0.0),
       NULL),
      NULL));
    bd_shield12->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(20.0 / 20.0),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(13.0 / 20.0),
       CCFadeTo::create(5.0 / 20.0, 255.0),
       CCFadeTo::create(1.0 / 20.0, 194.2),
       CCDelayTime::create(1.0 / 20.0),
       CCFadeTo::create(0.0 / 20.0, 0.0),
       NULL),
      NULL));
    bd_shield2->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(20.0 / 20.0),
       CCMoveBy::create(9.0 / 20.0, ccp(-3.149, 3.149)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(20.0 / 20.0),
       CCScaleTo::create(9.0 / 20.0, 2.425),
       NULL),
      CCSequence::create
      (CCDelayTime::create(20.0 / 20.0),
       CCFadeTo::create(0.0 / 20.0, 255.0),
       CCFadeTo::create(9.0 / 20.0, 0.0),
       NULL),
      NULL));
    
    //ボスの攻撃がはじけるエフェクト
    NFSpriteCluster* eff_anti_haunt = NFSpriteCluster::create("eff_anti_haunt.png");
    eff_anti_haunt->setAnchorPoint(ccp(0.5, 0.5));
    eff_anti_haunt->setPosition(ccpAdd(pos, ccp(0.0, 3.0)));
    parent->addChild(eff_anti_haunt);

    eff_anti_haunt->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCMoveBy::create(4.0 / 30.0, ccp(-3.2E-4, 4.3E-4)),
       CCNodeUtil::createRemoveAction(),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.1),
       NULL),
      CCSequence::create
      (CCDelayTime::create(3.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));

}