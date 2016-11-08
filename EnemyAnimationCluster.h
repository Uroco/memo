//
//  EnemyAnimationCluster.h
//  NinjaFlight
//

#ifndef __NinjaFlight__EnemyAnimationCluster__
#define __NinjaFlight__EnemyAnimationCluster__

#import "GameObjectAnimationCluster.h"

enum ENEMY_ANIME_STATE{
    EAS_ATTACK=0
    ,EAS_DAMAGE
    ,EAS_WAIT
    ,EAS_BACK
    ,EAS_SHOT
    ,EAS_MAX
};

class EnemyAnimationCluster : public GameObjectAnimationCluster{
protected:
    ENEMY_ANIME_STATE m_animeState;
    cocos2d::SEL_CallFunc    m_endDamageCallFunc;
    cocos2d::CCObject*      m_target;
    
    virtual void setAttackAnimation(){}
    virtual void setDamageAnimation(){}
    bool init(void);
    
    void finishDamageAnimation();
public:
    virtual void setAnimation(ENEMY_ANIME_STATE state);
    ENEMY_ANIME_STATE getState(){return m_animeState;}
    void setFunc(cocos2d::CCObject* pSelectorTarget, cocos2d::SEL_CallFunc end_selector);
};


//------------------------
//  BossAnimationSetting
//------------------------
class BossAnimationCluster : public EnemyAnimationCluster{
protected:
    virtual void initAnimation(){};
    virtual void setWaitAnimation(){}
    virtual void setBackAnimation(){}
    virtual void setShotAnimation(){}
    bool init(void);
public:
    static BossAnimationCluster* create(int typeNo,cocos2d::CCObject* pSelectorTarget, cocos2d::SEL_CallFunc end_selector);
    virtual void setAnimation(ENEMY_ANIME_STATE state);
};


#endif /* defined(__NinjaFlight__BossAnimationSetting__) */
