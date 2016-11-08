#ifndef __ANOTHERWORLD_SCENE_H__
#define __ANOTHERWORLD_SCENE_H__

#import "cocos2d.h"
#import "BuddyData.h"
using namespace cocos2d;

class BGManager;
class NormalEnemy;
class NFNumberLayer;
class Boss;
class Buddy;
class Player;
class NFSpriteCluster;
class Cannon;

enum AnotherModeState{
    AMS_PLAYER =0
    ,AMS_BUDDY
    ,AMS_BOSS
    ,AMS_ENEMY
};

class AnotherWorld : public CCScene
{
    BGManager*  m_BGManager;
    
    CCLayer* testLayer;
    CCLayer* parLayer;
    cocos2d::CCPoint m_charaPos;
    
    NFNumberLayer*  noDisp;
    AnotherModeState m_state;
    NFSpriteCluster* m_effect;
    
    void test();
    void test2(CCObject* sender);

    //Player
    NFNumberLayer*  dy_rankDisp;    //player:shotType buddy:rankNo
    NFNumberLayer*  dy_costumeDisp; //player:evo buddy:costume
    
    CCMenuItemFont* btn_actionControl;
    bool     m_canUpdate;
    void    controllUpdate();
    
    Player*      player;
    int shotType;
    int playerNo;
    int evolutionType;
    void playerMode();
    void p_create();
//    void p_shot();
    void p_run();
    void p_damage();
    void p_next();
    void p_clone();
    void p_reset();
    void p_shotLvCng();
    void p_shotEff();
//    void p_shottEff2();
    void p_cngEvolution();
    void p_fly();
    
    //Buddy
    Buddy*      buddy;
//    Cannon* clone;
    NFSpriteCluster* m_shotLayer;
    NFNumberLayer*  dy_LvDisp;
    int buddyAttr;
    int buddyRank;
    int buddyConsumeType;
    int buddyLevel;
    int kakudaiRitu;
    void buddyMode();
    void dy_create();
    void dy_shot();
    void dy_run();
    void dy_damage();
    void dy_next();
    void dy_cangeRank();
    void dy_clone();
    void dy_cangeCostume();
    void dy_kakudai();
    void dy_shotLvCng();
    
    //boss
//    Boss*          boss;
//    int bossNo;
    NFSpriteCluster*    b_shotLayer;
    void bossMode();
    void b_create();
    void b_wait();
    void b_damage();
    void b_attack();
    void b_back();
    void b_next();
    void b_death();
    void b_reset();
    void b_shot();
    void b_action();
    void b_exit();
    
    
    //enemy
	NormalEnemy*          enemy;
    int enemyNo;
    int enemyType;
    void enemyMode();
    void e_create();
    void e_damage();
    void e_next();
    void e_death();
    void e_freeze();
    void e_thunder();
    void e_fire();
    void e_cangeType();
    
    void e_reset();
    
    void exit();
//    void resetScroll();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
	
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    CREATE_FUNC(AnotherWorld);
    
    void update(float dt);
    
    void draw();
};
#endif // __ANOTHERWORLD_SCENE_H__
