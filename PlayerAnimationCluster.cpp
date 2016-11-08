//
//  PlayerAnimationCluster.cpp
//  NinjaFlight
//

#import "PlayerAnimationCluster.h"
#import "NormalPlayerAnimation.h"
#import "MagnetPlayerAnimation.h"
#import "AwakenPlayerAnimation.h"
#import "RevivePlayerAnimation.h"
#import "AssaultPlayerAnimation.h"
#import "BrownPlayerAnimation.h"
#import "Charactor.h"
#import "CommonDefine.h"

PlayerAnimationCluster* PlayerAnimationCluster::create(int typeNo, int _evolutionType){
    
    PlayerAnimationCluster* instance = NULL;
    switch (typeNo) {
        case CharactorType_Normal:
            instance = NormalPlayerAnimation::create(_evolutionType);
            break;
        case CharactorType_Kunoichi:
            instance = MagnetPlayerAnimation::create();
            break;
        case CharactorType_Musasabi:
            instance = AwakenPlayerAnimation::create();
            break;
        case CharactorType_Revive:
            instance = RevivePlayerAnimation::create();
            break;
        case CharactorType_Assault:
            instance = AssaultPlayerAnimation::create();
            break;
        case CharactorType_Brown:
            instance = BrownPlayerAnimation::create(_evolutionType);
            break;
        default:
            NFLog("PlayerAnimationCluster create Error!! TypeNo[%d]",typeNo);
            return NULL;
    }
    instance->m_animeState = PAS_MAX;
    return instance;
}

bool PlayerAnimationCluster::init(){
    NFSpriteCluster::init();
    
    p_shadow = NFSpriteCluster::create("p_shadow.png");
    p_shadow->setAnchorPoint(ccp(0.5, 0.5));
    p_shadow->setPosition(ccp(0.0, -50.0));
    p_shadow->setOpacity(getOpacity());
    this->addChild(p_shadow, -10);

    aura = NFSpriteCluster::create();
    this->addChild(aura);
    setAuraAnimation();

    normal = NFSpriteCluster::create();
    this->addChild(normal);
    
    damage = NFSpriteCluster::create();
    this->addChild(damage);
    initClashEff();
    

    return true;
}

void PlayerAnimationCluster::stopPrvAnimation(){
    if( normal != NULL ) normal->stopAction();
    if( damage != NULL ) damage->stopAction();
}

void PlayerAnimationCluster::resetAnimation(){
    normal->setVisible(false);
    damage->setVisible(false);
}

void PlayerAnimationCluster::setShotAnimation(){
    setAnimation(PAS_RUN);
}

void PlayerAnimationCluster::setAnimation(PLAYER_ANIME_STATE state){
    resetRotateAndScale();
    stopPrvAnimation();
    resetAnimation();
    
    switch (state) {
        case PAS_SHOT:
            setShotAnimation();
            break;
        case PAS_RUN:
            setRunAnimation();
            break;
        case PAS_DAMAGE:
            clashEffAnimation();
            setDamageAnimation();
            break;
        case PAS_FRYING:
            setFlyingAnimation();
            break;
        default:
            NFLog("Animation State erroer. [%d]",state);
            return;
    }
    
    m_animeState = state;
}

void PlayerAnimationCluster::initClashEff(){
    eff_clash = NFSpriteCluster::create("eff_clash.png");
    eff_clash->setAnchorPoint(ccp(0.5, 0.5));
    eff_clash->setPosition(ccp(50.0, 80.0));
    eff_clash->setScale(0.6);
    eff_clash->setOpacity(0.0);
    damage->addChild(eff_clash, 10);
}

void PlayerAnimationCluster::clashEffAnimation(){
    eff_clash->setScale(0.8);
    eff_clash->setOpacity(0.0);
    eff_clash->setPosition(ccp(0.0, 0.0));
    eff_clash->setRotation(0);
    
    
    eff_clash->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCScaleTo::create(3.0 / 30.0, 1.3),
       CCScaleTo::create(2.0 / 30.0, 1.7),
       CCScaleTo::create(4.0 / 30.0, 2.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(3.0 / 30.0, getOpacity()),
       CCDelayTime::create(2.0 / 30.0),
       CCFadeTo::create(4.0 / 30.0, 0.0),
       NULL),
      NULL));
}