//
//  EnemyAnimationCluster.cpp
//  NinjaFlight
//

#import "EnemyAnimationCluster.h"

bool EnemyAnimationCluster::init(void){
    NFSpriteCluster::init();
    m_animeState = EAS_MAX;
    return true;
}

void EnemyAnimationCluster::setFunc(cocos2d::CCObject *pSelectorTarget,
                                cocos2d::SEL_CallFunc end_selector){
    m_endDamageCallFunc = end_selector;
    m_target = pSelectorTarget;
}

void EnemyAnimationCluster::setAnimation(ENEMY_ANIME_STATE state){
    
    if( state == m_animeState ) return;
    stopAction();
    resetAnimation();
    
    switch (state) {
        case EAS_ATTACK:
            setAttackAnimation();
            break;
        case EAS_DAMAGE:
            setDamageAnimation();
            break;
        default:
            return;
    }

    m_animeState = state;
}

void EnemyAnimationCluster::finishDamageAnimation(){
    (m_target->*m_endDamageCallFunc)();
}

//------------------------
//  BossAnimationSetting
//------------------------
#import "BossAnimation01.h"
#import "BossAnimation02.h"
#import "BossAnimation03.h"
#import "BossAnimation04.h"
#import "BossAnimation05.h"
#import "BossAnimation06.h"
#import "Boss.h"

#import "RaidBossAnimation01.h"
#import "RaidBossAnimation02.h"
#import "RaidBossAnimation03.h"
#import "RaidBossAnimation04.h"
#import "RaidBossAnimation05.h"


BossAnimationCluster* BossAnimationCluster::create(int typeNo,
                                                   cocos2d::CCObject* pSelectorTarget, cocos2d::SEL_CallFunc end_selector){
    
    BossAnimationCluster* instance = NULL;
    switch (typeNo) {
        case kBossTypes1:
            instance = BossAnimation01::create();
            break;
        case kBossTypes2:
            instance = BossAnimation02::create();
            break;
        case kBossTypes3:
            instance = BossAnimation03::create();
            break;
        case kBossTypes4:
            instance = BossAnimation04::create();
            break;
        case kBossTypes5:
            instance = BossAnimation05::create();
            break;
        case kBossTypes6:
            instance = BossAnimation06::create();
            break;
        case kBossTypesGold:
            instance = BossAnimation01::createMetal();
            break;
        case kBossTypes8:
            instance = BossAnimation05::createFinalOgre();
            break;
            
        //raid
        case kRBossType1_ThunderDragon:
        case kRBossType1_FireDragon:
        case kRBossType1_PoisonDragon:
            instance = RaidBossAnimation01::create(typeNo);
            break;
        case kRBossType2_ThunderRobo:
        case kRBossType2_FireRobo:
        case KRBossType2_PoisonRobo:
            instance = RaidBossAnimation02::create(typeNo);
            break;
            
        case kRBossType3_SpikeKraken:
        case kRBossType3_PoisonKraken:
        case kRBossType3_FireKraken:
        case kRBossType3_ThunderKraken:
            instance = RaidBossAnimation03::create(typeNo);
            break;
            
        case kRBossType4_SpikeGhost:
        case kRBossType4_FireGhost:
        case kRBossType4_PoisonGhost:
        case kRBossType4_ThunderGhost:
            instance = RaidBossAnimation04::create(typeNo);
            break;
        case kRBossType5_MechaEgypt:
            instance = RaidBossAnimation05_Ra::create(typeNo);
            break;
        case kRBossType5_CosmoEgypt:
            instance = RaidBossAnimation05_Anubis::create(typeNo);
            break;
    }
    
    instance->setFunc(pSelectorTarget, end_selector);
    instance->autorelease();
    return instance;
}

bool BossAnimationCluster::init(void){
    NFSpriteCluster::init();
    m_animeState = EAS_MAX;
    return true;
}

void BossAnimationCluster::setAnimation(ENEMY_ANIME_STATE state){
    
    if( state == m_animeState ) return;
    
    stopAction();
    resetAnimation();
    
    switch (state) {
        case EAS_ATTACK:
            setAttackAnimation();
            break;
        case EAS_DAMAGE:
            setDamageAnimation();
            break;
        case EAS_WAIT:
            setWaitAnimation();
            break;
        case EAS_BACK:
            setBackAnimation();
            break;
        case EAS_SHOT:
            setShotAnimation();
            break;
            
        default:
            break;
    }
    m_animeState = state;
}