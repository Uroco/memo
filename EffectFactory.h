//
//  EffectFactory.h
//  NinjaFlight
//


#ifndef __NinjaFlight__EffectFactory__
#define __NinjaFlight__EffectFactory__

#import "cocos2d.h"
class NFSpriteCluster;
class EffectFactory: public cocos2d::CCNode{
public:
    
    //ランダムな座標を返す
    static cocos2d::CCPoint getRandomInterval(cocos2d::CCSize _range);
    
    //ポイズナーの弾に初期被弾エフェクト
    static void createPoison(cocos2d::CCNode* parent,
                             cocos2d::CCPoint _pos,
                             int zOrder=0);
    
    //サンダーの被弾エフェクト
    static void createShock(cocos2d::CCNode* parent,
                             cocos2d::CCPoint _pos,
                             int zOrder=0);
    
    //錬金の術のゲーム開始時に出るオレンジ色のわっか
    static void createMultiGold(cocos2d::CCNode* parent,
                            cocos2d::CCPoint _pos,
                            int zOrder=0);
    
    //仲間救出時の星エフェクト
    static void createStar(cocos2d::CCNode* parent,
                                cocos2d::CCPoint _pos,
                                int zOrder=0,
                           cocos2d::ccColor3B _col = cocos2d::ccWHITE);
    
    //宝箱・コレクション獲得時のキラキラエフェクト
    static void createShine(cocos2d::CCNode* parent,
                                cocos2d::CCPoint _pos,
                                int zOrder=0);
    
    //スコア獲得時のエフェクト
    static void createAddScore(int _score, cocos2d::CCNode* parent,
                            cocos2d::CCPoint _pos,
                            int zOrder=0);

    //ダメージ表示
    static void debugShowDamage(int _dmg,
                                cocos2d::CCNode* parent,
                                cocos2d::CCPoint _pos,
                                int zOrder=0);
    
    //味方が一定数以上のスコアボーナス発生時のエフェクト
    static void createBuddyBonus(cocos2d::CCNode* parent,
                               cocos2d::CCPoint _pos,
                               int zOrder=0);
    
    //桜吹雪
    static void createDeadWalkSakura(cocos2d::CCNode* parent,
                                 cocos2d::CCPoint _pos,
                                 int zOrder=0);
    //敵死に爆破
    static void createNormalEnemyDeathEffect(cocos2d::CCNode* parent,
                                     int zOrder=0);
    static void createBomEnemyDeathEffect(cocos2d::CCNode* parent,
                                             int zOrder=0);
    
    //かえるボタン
    static void createFrogBtnEffect(cocos2d::CCNode* eff_bomb_front, cocos2d::CCNode* eff_bomb_back);
    
    //fire beam effect
    static void createExplosionAnimation(cocos2d::CCNode* parent,
                                         cocos2d::CCNode* target,
                                         cocos2d::SEL_CallFunc _exitFunc);
    static void createExplosion2Animation(cocos2d::CCNode* parent,
                                         cocos2d::CCNode* target,
                                         cocos2d::SEL_CallFunc _exitFunc);
    static void createExplosionFireFlowerAnimation(cocos2d::CCNode* parent,
                                          cocos2d::CCNode* target,
                                          cocos2d::SEL_CallFunc _exitFunc);
    
    //player beam effect
    static void createSlashEffectAnimation_Assult(cocos2d::CCNode* parent);
    static void createSlashEffectAnimation_Normal(cocos2d::CCNode* parent);
    static void createSlashEffectAnimation_Kunoichi(cocos2d::CCNode* parent);
    static void createSlashEffectAnimation_Musasabi(cocos2d::CCNode* parent);
    static void createSlashEffectAnimation_Revive(cocos2d::CCNode* parent);
    static void createSlashEffectAnimation_Brown(cocos2d::CCNode* parent);
    
    //rental info.
    static void createRentalInfoEffect(cocos2d::CCNode* parent,
                                       int zOrder=0);
    
    //disp speed up timing.
    static void createSpeedUpInfo(cocos2d::CCNode* parent,
                                  int zOrder=0);
    
    //boss name
    static void createNearBossInfo( int bossNo,
                                     cocos2d::CCNode* parent,
                                  int zOrder=0);
    static void createNearRaidBossInfo( int bossNo,
                                   cocos2d::CCNode* parent,
                                   int zOrder=0);
    static void createRaidBossWeak(int attr,
                                   cocos2d::CCNode* parent,
                                   int zOrder=0);
    
    //bonus score add
    static void createAddBonusScore(int _score, bool isDash, cocos2d::CCNode* parent,
                               int zOrder=0);
    
    //bonus at luck zone of mile stone line
    static void createLuckZoneBonus(bool isExcellent, cocos2d::CCNode* parent,
                                    int zOrder=0);
    
    //hien wing
    static void createHienWing(cocos2d::CCNode* parent,
                                     cocos2d::CCPoint _pos,
                                     int zOrder=0);
    //new recode
    static void createNewRecode(cocos2d::CCNode* parent,
                               int zOrder=0);
    void setNewRecodeRepeat(cocos2d::CCNode* sender, void* data);//createNewRecodeが呼ぶ
    
    //block break eff
    static void createBlockBreak(cocos2d::CCNode* parent,
                                 int zOrder=0);
    // block target anim
    static void createFallBlockTargetAnim(int raidBossId , cocos2d::CCPoint pos , cocos2d::CCNode *parent, int zOrder);
    
///////////////////
    //raid 4
    static void createBeginHauntEffect(cocos2d::CCPoint pos , cocos2d::CCNode *parent, int zOrder, int tag);
    static void createEndHauntEffect(cocos2d::CCPoint pos , cocos2d::CCNode *parent, int zOrder);
    static void createBuddySealedDefenceEffect(cocos2d::CCPoint pos , cocos2d::CCNode *parent, int zOrder);
};

#endif /* defined(__NinjaFlight__EffectFactory__) */
