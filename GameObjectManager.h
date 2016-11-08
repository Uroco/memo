//
//  GameObjectManager.h
//  NinjaFlight
//

#ifndef __NinjaFlight__GameObjectManager__
#define __NinjaFlight__GameObjectManager__

#import "cocos2d.h"
#import "GameScene.h"

class Object;
class EnemyController;
class Enemy;
class ItemBase;
class ScrollBG;
class Killer;
class EffectScroll;
class NFNumberLayer;
class DistanceManager;
class NFMenuItemSprite;
class NFSpriteCluster;
class GroundObjectController;
class Prison;
class GameWarpGauge;
class BossBullet;
class Cannon;
class GameContinueDialog;
class SlotController;
class GameCoinCounter;
class NinjaPowerCounter;
class GameCollectionBox;
class GameComboCounter;
class GameDebugController;
class GameHaveRollInfo;
class GuardianManager;
class GameButton;

enum BGM_State{
    BGM_STOP
    ,BGM_PLAY
    ,BGM_FEVER
    ,BGM_BOSS
    ,BGM_GAMEOVER
};

//レイヤープライオリティ
enum LAYER_PRIORITY{
    PRTY_Dialog = 10
    ,PRTY_Highest = -1
    ,PRTY_Notice = -3
    ,PRTY_ItemUseEff = -4
    ,PRTY_AddItem = -5
    ,PRTY_InfoUI = -10
    ,PRTY_InfoRecode = -15
    ,PRTY_AddScore = -25
    ,PRTY_Effect = -30 //not use
    ,PRTY_GaugeItem = -35
    ,PRTY_BGEffect = -40
    ,PRTY_EnemyBeam = -50
    ,PRTY_Player = -55
    ,PRTY_Guardian = -56
    ,PRTY_Killer = -60
    ,PRTY_Beam = -65
    ,PRTY_Enemy = -75
    ,PRTY_Frog = -85
    ,PRTY_WarpEff = -90
    ,PRTY_Prison = -93
    ,PRTY_Item = -95
    ,PRTY_Block = -100
    ,PRTY_Darken = -105
    ,PRTY_BG = -200
};

#import "BGManager.h"
#import "PlayerController.h"
#import "ItemController.h"
#import "GameBonusStageUI.h"

class GameObjectManager:public cocos2d::CCLayer{
    //ゲームオブジェクトレイヤー
    PlayerController* playerController;
    EnemyController*  enemyController;
    ItemController*   itemController;
    GroundObjectController* groundObjecController;

    NFSpriteCluster*   m_p_dialogLayer;
    NFSpriteCluster*   m_p_noticeLayer;    //優先度高めで表示したいものレイヤー
    NFSpriteCluster*   m_p_beamLayer;     // 弾を配置するレイヤー
    NFSpriteCluster*   m_p_killerLayer;    //隕石配置レイヤー
    NFSpriteCluster*  m_p_bossBeamLayer;
    NFSpriteCluster*  m_p_addItemDispLayer;//獲得したコインと緑ジェムを表示するレイヤー
    
    //状態表示レイヤー
    NFSpriteCluster*   m_p_scoreDispLayer;  //ゲーム中獲得したスコアをオブジェクトの位置に表示するレイヤー
    NFSpriteCluster*   m_p_infoLayer;      //ステータス表示などを配置するレイヤー
    NFSpriteCluster*   m_p_frendScoreLayer;
    
    //カウンタ
    NinjaPowerCounter* m_ninjaPowerCounter;//にんぢゃパワーカウンタ
    GameCoinCounter*   m_p_coinCounter;  //コインカウンタ
    GameComboCounter*   m_comboCounter; //コンボカウンタ
    
    GameWarpGauge*  m_warpGuage;    //ワープゲージ
    BGManager* m_BGManager;     //BG管理
    DistanceManager* m_distanceManager; //距離系管理クラス
    
    GuardianManager* m_guardianManager; //守護精霊くらしゅ
        
    NFSpriteCluster* buddy_help;
    SlotController* slotController;
    
    bool        m_isRental;
    
    int     m_pauseCnt;
    bool    m_executeFlg;       //実行可能フラグ
    bool    m_isExistKiller;    //隕石存在フラグ

    //ボーナスステージ
    GameBonusStageUI* m_bonusStageUI;
    
    //Item
    bool    m_isStartDash;
    bool    m_isItemUsePause;
    bool    m_isDeadPause;
    bool    m_didRecommendToChange;
    bool    m_canChange;    //変わり身が使えるか
    bool    m_canUseStartItem;
    bool    m_isTreasure;
    
    bool    m_beingProcessChangePlayer; //交代の巻物使用のプロセス中
    
    //result score
    int     m_score;
    int     m_useNum_frog;
    int     m_useNum_Continue;
    int     m_useNum_Change;
    int     m_useNum_LastRun;
    int     m_useNum_multiGold;
    int     m_useNum_gemDash;
    int     m_useNum_sushiDash;
    bool    m_isFinalBossKill;
    int     m_metalBossKillNum;
    
    //Metal Boss
    int     m_exchangeMetalBossNo;

    //relief
    bool m_canRerive;
    
    //sound
    BGM_State nowPlay;
    bool bg_play;
    bool bg_playResult;

    
    void goToPlay();
    void goToTutorial();
    
    //UI
    GameButton* m_gameButton;
    
    //makimono
    GameHaveRollInfo* m_gameHaveRollInfo;
    
    // boss result
    CCArray * bossResultArray;
    
    // final ogre cat
    bool m_isFinalOgreBossKill;
    int finalOgreBossHp;
    
    //magatama
    int m_isGetMagatama;  //まがたまゲット
    int m_jumpScore;  //まがたま用　到達スコア
    int m_jumpCombo;  //まがたま用　到達時コンボ
    int m_jumpBomb;   //まがたま用　到達時カエル数
    void roadSuperJumpData();
    
    //distance
    float m_startDistance; //スタート地点
public:
    void hitCheckAllObjects();
    void hitCheckWhenDeadWalk();
    void hitCheckCannon(Cannon*  cannon);
    
    void allObjectsUpdate(float time);
    void UIUpdate(float time);
    
    CCLayerColor* whiteLayer;
    void showWhiteOutWipe();   //始まりの白い霧消し
    void startItemUse();
    
    // v1.5.1 tutorial中か否か
    GameObjectManager();
    ~GameObjectManager();
    
    static GameObjectManager* create();
    PlayerController* getPlayerController(){ return playerController; }
    EnemyController* getEnemyController(){ return enemyController; }
    ItemController* getItemController(){ return itemController; };
    NFSpriteCluster*   getBeamLayer(){ return m_p_beamLayer;}
    DistanceManager* getDistanceManager(){ return m_distanceManager; }
    GroundObjectController* getGroundController(){ return groundObjecController; }
    
    NFSpriteCluster* getBossBeamLayer(){ return m_p_bossBeamLayer; }
    NFSpriteCluster* getAddItemDispLayer(){ return m_p_addItemDispLayer; }
    NFSpriteCluster* getNoticeLayer(){ return m_p_noticeLayer; }
    NinjaPowerCounter* getNinjaPowerCounter(){return m_ninjaPowerCounter; }
    GameComboCounter* getComboCounter(){return m_comboCounter;}
    GameHaveRollInfo* getGameHaveRollInfo(){return m_gameHaveRollInfo;}
    BGManager* getBGManager(){ return m_BGManager; }
    NFSpriteCluster* getInfoLayer(){ return m_p_infoLayer; }
    
    GameBonusStageUI* getGameBonusStageUI(){ return m_bonusStageUI; }
    
    GameCollectionBox* getCollectionBox();
    GameButton* getGameButton(){ return m_gameButton; }
    
    void useRerive();
    void rerivePlayer();    //復活
    bool canRerive(){ return m_canRerive; };
    
    void useChangePlayer();
    
    
    void init();    //生成時　初期化処理
    void initStage();
    
    void start();   //ゲーム開始時　初期化処理
    void pause();    //ゲーム一時停止処理
    void resume();  //ゲーム再開時処理
    void dispPauseLayer();
    void endPauseLayer();
    void pause_ofExceptingPlayer();
    
    bool isPause(){ return m_pauseCnt; }
    
    //Sound
    void playSound_Bg( BGM_State _state);
    
    //Distance
    float getDistance();
    float getPlayerMoveSpeed();
    float getStartDistance();

    //Scroll
    float getScrollSpeed();
    
    //coin
    void addCoin(int value);
    int getCoinNum();
    
    //score
    void    addScore(int _score, cocos2d::CCPoint _pos);
    void    addBonusScore(int _score, bool _isDash=false);
    int     getScore();
    void    dispBuddyBonus(cocos2d::CCPoint _pos);
    
    //Reccomend
    bool didRecommendToChange(){ return m_didRecommendToChange; }
    void setDidRecommendToChange( bool _st ){ m_didRecommendToChange = _st; }
    
    //item use.
    int getUseFrogNum(){ return m_useNum_frog; }
    int getUseContinueNum(){ return m_useNum_Continue; }
    int getUseChangeNum(){ return m_useNum_Change; }
    void useChange(){ m_useNum_Change++; }
    int getUseLastRunNum(){ return m_useNum_LastRun; }
    void useLastRun(){ m_useNum_LastRun++; }
    int getUseMultiGold(){ return m_useNum_multiGold; }
    int getUseGemDash(){ return m_useNum_gemDash; }
    int getUseSushiDash(){ return m_useNum_sushiDash; }
    void useMultiGold(bool isGem=true);
    void useSushiDash(bool isGem=true);
    int calcUseGem();   //ゲーム内で使ったアイテム換算
    float calcStartDashDistance();
    bool beingProcessChangePlayer();
    
    //rental
    bool isRentalStart(){ return m_isRental;}
    void finishRental();
    
    //result
    bool isFinalBossKill(){ return m_isFinalBossKill; }
    int getMetalBossKillNum(){ return m_metalBossKillNum; }
    CCArray * getResultBossArray(){ return bossResultArray; }
    
    void finalBossKill();
    //UI
    cocos2d::CCPoint getCoinGaugePos();
    cocos2d::CCPoint getWarpGaugePos();

    //カエル
    void summonFrog();
    
    //弾丸追加用
    void addBossBeam( BossBullet* _bossBullet );
    
    //メテオ
    void resetKiller();
    bool isExistKiller();
    bool isExistKillerRush();
    void addKiller(Killer* killer);
    void appearKiller();
    
    // ワープ関連
    void startIncrementFvGAnime();
    void startWarp();
    void resetWarp();
    
    //Notice
    void addNoticeLayerChild(CCNode* _s, int zOder);
    void setBuddyNotice(float _posX);
    float calcBuddyNoticeIntervalDistance();    //ノティス前の距離
    float calcBuddyNoticeIntervalPxcel();    //ノティス前のピクセル
    
    void touchBegin(cocos2d::CCPoint point);
    void touchMove(cocos2d::CCPoint point);
    void touchEnd(cocos2d::CCPoint point);
    
    //treasure
    void createTreasureGetIcon();
    bool isTreasure(){return m_isTreasure;}
    void setExistTreasure(){ m_isTreasure = true; }
    
    //bonus Lastrun.
    void createLastRunGetIcon();
    
    void lotteryMetalBossAppear();
    int  getExchangeMetalBossNo(){ return m_exchangeMetalBossNo; }
    void metalBossKill();
    
    //debug
    GameDebugController* debugContoroller;
    bool    m_debud_pause;
    void draw();
    bool isExecuteFlg(){ return m_executeFlg; };
    
    // reserve
    void reserveTargetAndShotBlock(int raidBossId , CCPoint pos);
    
    // final ogre cat
    void finalOgreBossKill(){ m_isFinalOgreBossKill = true; }
    bool isFinalOgreBossKill(){ return m_isFinalOgreBossKill; }
    void setFinalOgreBossHp(int _hp){ finalOgreBossHp = _hp; }
    int getFinalOgreBossHp(){ return finalOgreBossHp; }
    
    //bonus stage
    void showBonusStageInfo();
    
    //v1.6.3 MAGATAMA
    void createMagatamaGetIcon();
    void setPickedUpMagatama(){ m_isGetMagatama =true; };
    void recordMagatamaJumpData();
    int isGetMagatama(){ return m_isGetMagatama; }
    int getMagatamaJumpScore(){ return m_jumpScore; }
    int getMagatamaJumpCombo(){ return m_jumpCombo; }
    int getMagatamaJumpBomb(){ return m_jumpBomb; }
};


#endif /* defined(__NinjaFlight__GameObjectManager__) */
