//
//  GameStateManager.h
//  NinjaFlight
//
//  Created by Kubo Ayami on 2014/06/23.
//
//

#ifndef __NinjaFlight__GameStateManager__
#define __NinjaFlight__GameStateManager__

typedef enum{
    GMS_WAIT,
    GMS_PROLOGE,
    GMS_ENTRY,
    GMS_RECOMMEND,
    GMS_TUTORIAL,
    GMS_BONUSSTARTINFO,
    GMS_RUN,
    GMS_DEAD,
    GMS_TIMEOUT,
    GMS_CONTINUE, //救済処置ステート
    GMS_LASTRUN,
    GMS_GAMEOVER,
    GMS_NEUTRAL //なんでもない
}GameState;

#import "cocos2d.h"
class GameStateAbstract:public cocos2d::CCNode{
protected:
    GameState m_state;
    GameStateAbstract();
public:
    virtual void begin()=0;
    virtual GameStateAbstract* excute(float dt)=0;
    virtual void end()=0;
    GameState getState(){ return m_state; }
};

//test用state
class GameState_Wait :public GameStateAbstract{
public:
    virtual void begin(){};
    virtual GameStateAbstract* excute(float dt);
    virtual void end(){};
};

class GameState_Prologe :public GameStateAbstract{  //オニネコボスが仲間を連れ去るアニメ再生
public:
    GameState_Prologe();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_Entry :public GameStateAbstract{    //プレイヤーが画面下から迫り上がってくる演出
public:
    GameState_Entry();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameRecommendDialog;
class GameState_Recommend :public GameStateAbstract{    //練金、すしダッシュなどのレコメンド
    GameRecommendDialog* dialog;
public:
    GameState_Recommend();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameTutorialManager;
class GameState_Tutorial :public GameStateAbstract{ //チュートリアル
    int prvFrogNum;
    GameTutorialManager* tutorial;
public:
    GameState_Tutorial();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_BonusStartInfo :public GameStateAbstract{   //ボーナスステージ初めのタイトルと制限時間表示
public:
    GameState_BonusStartInfo();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_Run :public GameStateAbstract{  //通常ゲームプレイ
    bool m_isBonusStage;
public:
    GameState_Run();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_Dead :public GameStateAbstract{ //プレイヤー死亡時の演出
    bool    m_isLeft;
    float   m_gameOverTimer;
    
public:
    GameState_Dead();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_TimeOut :public GameStateAbstract{  //ボーナスステージのタイムアウト演出
public:
    GameState_TimeOut();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameContinueDialog;
class GameState_Continue :public GameStateAbstract{ //コンティニューレコメンドダイアログ表示
    GameStateAbstract* nextState;
    void checkUseContinueItem(GameContinueDialog* _dialog);
public:
    GameState_Continue();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class NFNumberLayer;
class GameState_LastRun :public GameStateAbstract{  //ラストラン状態
//    int runDistance;
    int goalDistance;
    int speedDownPunc;
    int plusDistance;
    
    //debugs
    cocos2d::CCSprite* debug_layer;
public:
    GameState_LastRun();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

class GameState_GameOver :public GameStateAbstract{ //プレイヤーが下に落ちていく演出
public:
    GameState_GameOver();
    virtual void begin();
    virtual GameStateAbstract* excute(float dt);
    virtual void end();
};

/*
 *  GameStateManager
 */
class GameStateManager : public cocos2d::CCNode{
    static GameStateManager* instance;
    GameStateAbstract* m_nowState;
    float m_gamePlayTime;
    
    GameStateManager();
    ~GameStateManager();
    void update(float dt);
public:
    bool finish();
    void restart();
    GameState getState();
    void replaseState(GameStateAbstract* _newState);
    
    static void launch();
    static GameStateManager* getInstance(){ return instance; }
    float getGamePlayTime(){ return m_gamePlayTime; }
};

#endif /* defined(__NinjaFlight__GameStateManager__) */
