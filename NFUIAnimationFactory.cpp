//
//  NFUIAnimationFactory.cpp
//  NinjaFlight
//
#define NF_UI_ANIMATIN_DEFINE
#import "NFUIAnimationFactory.h"

/**
 * EVENTロゴを生成します。生成すると自動的にアニメーションを開始します。
 * 一番左の座標を始点に相対的に生成するので、一番左の座標を指定してください。
 */
void NFUIAnimationFactory::createAnimation_EventLogo(float x , float y, CCNode* parent)
{
    CCSprite* logo_event_011 = CCSprite::create("logo_event_01.png");
    logo_event_011->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_011->setPosition(ccp(x, y));
    parent->addChild(logo_event_011);
    
    CCSprite* logo_event_02 = CCSprite::create("logo_event_02.png");
    logo_event_02->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_02->setPosition(ccp(x + 19 , y - 0.5));
    parent->addChild(logo_event_02);
    
    CCSprite* logo_event_012 = CCSprite::create("logo_event_01.png");
    logo_event_012->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_012->setPosition(ccp(x + 40 , y - 0.5));
    parent->addChild(logo_event_012);
    
    CCSprite* logo_event_03 = CCSprite::create("logo_event_03.png");
    logo_event_03->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_03->setPosition(ccp(x + 58 , y - 0.5));
    parent->addChild(logo_event_03);
    
    CCSprite* logo_event_04 = CCSprite::create("logo_event_04.png");
    logo_event_04->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_04->setPosition(ccp(x + 78 , y - 0.5));
    parent->addChild(logo_event_04);
    
    CCSprite* logo_event_05 = CCSprite::create("logo_event_05.png");
    logo_event_05->setAnchorPoint(ccp(0.5, 0.5));
    logo_event_05->setPosition(ccp(x + 92, y - 0.5));
    parent->addChild(logo_event_05);
    
    logo_event_011->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCDelayTime::create(48.0 / 30.0),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 0.55)),
       NULL)
      ));
    logo_event_02->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(4.0 / 30.0, ccp(0.0, 0.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCMoveBy::create(45.0 / 30.0, ccp(0.0, 0.0)),
       NULL)
      ));
    logo_event_012->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(8.0 / 30.0, ccp(0.0, 0.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCMoveBy::create(41.0 / 30.0, ccp(0.0, 0.0)),
       NULL)
      ));
    logo_event_03->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(12.0 / 30.0, ccp(0.0, 0.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCMoveBy::create(37.0 / 30.0, ccp(0.0, 0.0)),
       NULL)
      ));
    logo_event_04->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(16.0 / 30.0, ccp(0.0, 0.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCMoveBy::create(33.0 / 30.0, ccp(0.0, 0.0)),
       NULL)
      ));
    logo_event_05->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSequence::create
      (CCMoveBy::create(20.0 / 30.0, ccp(0.0, 0.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.55)),
       CCMoveBy::create(4.0 / 30.0, ccp(0.0, 14.0)),
       CCMoveBy::create(2.0 / 30.0, ccp(0.0, -6.0)),
       CCMoveBy::create(1.0 / 30.0, ccp(0.0, 2.0)),
       CCMoveBy::create(29.0 / 30.0, ccp(0.0, 0.0)),
       NULL)
      ));
}

/**
 * Newロゴを指定した位置に作成します。なお、作成後、自動的にアニメーションします。
 */
CCSprite* NFUIAnimationFactory::createAnimation_NewLogo(float x , float y, CCNode* parent, int zOrder)
{
    CCSprite* ico_new_01 = CCSprite::create("ico_new_01.png");
    ico_new_01->setAnchorPoint(ccp(0.5, 0.5));
    ico_new_01->setPosition(ccp(x , y));
    parent->addChild(ico_new_01, zOrder);
    
    ico_new_01->runAction
    (CCRepeatForever::create
     ((CCActionInterval*)CCSpawn::create
      (CCSequence::create
       (CCMoveBy::create(6.0 / 30.0, ccp(0.0495, -0.0498)),
        CCMoveBy::create(8.0 / 30.0, ccp(4.76E-4, -2.319E-4)),
        CCDelayTime::create(15.0 / 30.0),
        CCMoveBy::create(6.0 / 30.0, ccp(0.0495, -0.0498)),
        CCMoveBy::create(8.0 / 30.0, ccp(4.76E-4, -2.319E-4)),
        CCMoveBy::create(16.0 / 30.0, ccp(-0.05, 0.05)),
        CCMoveBy::create(1.0 / 30.0, ccp(-0.05, 0.05)),
        NULL),
       CCSequence::create
       (CCScaleTo::create(6.0 / 30.0, 1.3),
        CCScaleTo::create(8.0 / 30.0, 1.0),
        CCDelayTime::create(15.0 / 30.0),
        CCScaleTo::create(6.0 / 30.0, 1.3),
        CCScaleTo::create(8.0 / 30.0, 1.0),
        CCDelayTime::create(17.0 / 30.0),
        NULL),
       NULL)));
    
    return ico_new_01;
}
