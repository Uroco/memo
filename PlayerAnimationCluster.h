//
//  PlayerAnimationCluster.h
//  NinjaFlight
//

#ifndef __NinjaFlight__PlayerAnimationCluster__
#define __NinjaFlight__PlayerAnimationCluster__

#import "cocos2d.h"
#import "GameObjectAnimationCluster.h"

enum PLAYER_ANIME_STATE{
    PAS_SHOT,
    PAS_RUN,
    PAS_DAMAGE,
    PAS_FRYING,
    PAS_MAX
};


class PlayerAnimationCluster : public GameObjectAnimationCluster{
protected:
    PlayerAnimationCluster(){}
    
    PLAYER_ANIME_STATE m_animeState;
    NFSpriteCluster* normal;
    NFSpriteCluster* damage;
    NFSpriteCluster* aura;
    NFSpriteCluster* eff_clash;
    NFSpriteCluster* p_shadow;

    virtual void initAnimation()=0;
    virtual void setShotAnimation();
    virtual void setRunAnimation(){}
    virtual void setDamageAnimation(){}
    virtual void setFlyingAnimation(){}
    virtual void setAuraAnimation()=0;
    
    virtual void stopPrvAnimation();
    virtual void resetAnimation();
    
    void initClashEff();
    void clashEffAnimation();
    
    virtual bool init();
public:
    static PlayerAnimationCluster* create(int _typeNo, int _evolutionType);
    void setAnimation(PLAYER_ANIME_STATE state);
    PLAYER_ANIME_STATE getState(){return m_animeState;}
    
};
#endif /* defined(__NinjaFlight__PlayerAnimationCluster__) */
