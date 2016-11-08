//
//  GameStateManager.cpp
//  NinjaFlight
//
//  Created by Kubo Ayami on 2014/06/23.
//
//

#import "GameStateManager.h"
#import "GameObjectManager.h"
#import "GameScene.h"
#import "FixedValue.h"
#import "User.h"

#import "EnemyController.h"
#import "DistanceManager.h"
#import "GuardianManager.h"
#import "GameButton.h"
#import "Frog.h"
/*----------------------
 *  GameStateManager
 -----------------------*/
GameStateManager* GameStateManager::instance =NULL;

GameStateManager::GameStateManager(){
    m_nowState=NULL;
    m_gamePlayTime=0;
}
GameStateManager::~GameStateManager(){
    if( m_nowState ){
        m_nowState->release();
        delete m_nowState;
    }
    m_gamePlayTime=0;
    instance=NULL;
}

void GameStateManager::launch(){
    if( !instance ){
        instance = new GameStateManager();
        GameScene::sharedInstance()->addChild(instance);
        
        instance->scheduleUpdate();
        instance->restart();
    }
}

bool GameStateManager::finish(){
    instance->autorelease();
    instance->unscheduleUpdate();
    instance->removeFromParentAndCleanup(true);
    instance=NULL;
    return true;
}

void GameStateManager::update(float dt){
    m_gamePlayTime += dt;
    if(!gameObjectManager || !gameObjectManager->isExecuteFlg()){
        return;
    }
    
    dt = MIN( 0.05, dt);
    GameStateAbstract* nextState = m_nowState->excute(dt);
    if( nextState ){
        replaseState(nextState);
    }
}

void GameStateManager::restart(){
    if( GameScene::sharedInstance()->isBonusStage() ){
        replaseState( new GameState_Entry());
    }else if( GameScene::sharedInstance()->getGameStartArgs()->isUseSuperJump ){
        replaseState(new GameState_Entry());
    }else{
        replaseState(new GameState_Prologe());
    }
}

void GameStateManager::replaseState(GameStateAbstract *_newState){
    if( m_nowState ){
        m_nowState->end();
        m_nowState->release();
        delete m_nowState;
    }
    
    if( _newState ){
        _newState->begin();
        m_nowState = _newState;
        m_nowState->retain();
    }
}

GameState GameStateManager::getState(){
    return m_nowState->getState();
}

/*----------------------
 *  GameStates
 -----------------------*/
GameStateAbstract::GameStateAbstract()
:m_state(GMS_NEUTRAL)
{
}

GameStateAbstract* GameState_Wait::excute(float dt){
    return NULL;
}

//-----------------------
//  GameState_Prologe
//-----------------------
#import "GameProloge.h"
GameState_Prologe::GameState_Prologe()
{
    m_state =GMS_PROLOGE;
}
void GameState_Prologe::begin(){
    GameProloge* prologe = GameProloge::create();
    gameObjectManager->addChild(prologe);
    
    gameObjectManager->getPlayerController()->pause();
    gameObjectManager->getInfoLayer()->setVisible(false);
    gameObjectManager->showWhiteOutWipe();

    gameObjectManager->getPlayerController()->setVisible(false); //クサナギの剣のエフェクトが見えるので消す
    gameObjectManager->getGameButton()->setPauseButtonEnabled(false);//ポーズボタンは押せない
    gameObjectManager->getBGManager()->loadingBGTexture();  //背景テクスチャ残りのステージをロード（先頭のステージは抽選時に読み込み済み）
}

GameStateAbstract* GameState_Prologe::excute(float dt){
    if( !GameProloge::getInstance() || GameProloge::getInstance()->isEnd ){
        return new GameState_Entry();
    }
    return NULL;
}
void GameState_Prologe::end(){
    gameObjectManager->getPlayerController()->setVisible(true);
    gameObjectManager->getGameButton()->setPauseButtonEnabled(true);//ポーズボタン解禁
}

//-----------------------
//  GameState_Entry
//-----------------------
GameState_Entry::GameState_Entry()
{
    m_state =GMS_ENTRY;
}
void GameState_Entry::begin(){
    gameObjectManager->getPlayerController()->resume();
    gameObjectManager->showWhiteOutWipe();
    
    //sound BG
    gameObjectManager->playSound_Bg(BGM_STOP);
    gameObjectManager->playSound_Bg(BGM_PLAY);
    gameObjectManager->getGameButton()->setPauseButtonEnabled(false); //ポーズボタンは押せない
}
GameStateAbstract* GameState_Entry::excute(float dt){
    PlayerController* playerController = gameObjectManager->getPlayerController();
    float posY = playerController->getPositionY();
    posY += 8.0f;
    posY = MIN(0, posY);
    playerController->setPositionY(posY);
    GuardianManager::getInstance()->updateAnimationPos(0);
    
    
    if( playerController->getPositionY() >= 0 ){
        return new GameState_Recommend();
    }
    return NULL;
}
void GameState_Entry::end(){
    gameObjectManager->getPlayerController()->setPositionY(0);
    GuardianManager::getInstance()->updateAnimationPos(0);
    gameObjectManager->getGameButton()->setPauseButtonEnabled(true);//ポーズボタン解禁
}
//-----------------------
//  GameState_Recommend
//-----------------------
#import "GameContinueDialog.h"
GameState_Recommend::GameState_Recommend()
{
    m_state =GMS_RECOMMEND;
}
void GameState_Recommend::begin(){
    dialog = GameRecommendDialog::create();
    if( dialog ){
        gameObjectManager->getNoticeLayer()->addChild(dialog);
    }
}
GameStateAbstract* GameState_Recommend::excute(float dt){
    gameObjectManager->getBGManager()->update(dt);
    
    if( !dialog || dialog->isEnd() ){
        bool tFlag = User::getInstance()->getIsTutorial();
        if(tFlag && !g_d_loopGame){
            User::getInstance()->setIsTutorial(false);
            return new GameState_Tutorial();
        }else{
            if( GameScene::sharedInstance()->isBonusStage() ){
                return new GameState_BonusStartInfo();
            }
            return new GameState_Run();
        }
    }
    return NULL;
}
void GameState_Recommend::end(){
    if( dialog ){
        dialog->removeFromParentAndCleanup(true);
        dialog=NULL;
    }
}

//-----------------------
//  GameState_Tutorial
//-----------------------
#import "GameTutorialManager.h"
GameState_Tutorial::GameState_Tutorial()
{
    m_state =GMS_TUTORIAL;
}
void GameState_Tutorial::begin(){
    tutorial = new GameTutorialManager();
    gameObjectManager->addChild(tutorial, PRTY_Highest+10);
    gameObjectManager->getGameButton()->setPauseButtonEnabled(false);//ポーズボタンは押せない

    prvFrogNum = gameObjectManager->getGameButton()->getFrogNum();
    gameObjectManager->getGameButton()->setFrogNum(1);//お試し用に一個
    gameObjectManager->getInfoLayer()->setVisible(true);
}
GameStateAbstract* GameState_Tutorial::excute(float dt){
    
    if(tutorial->isEnd()){
        return new GameState_Run();
    }
    
    //プレイヤー更新
    gameObjectManager->getPlayerController()->update(dt);
    
    GuardianManager::getInstance()->update(dt);
    
    // 背景スクロール
    gameObjectManager->getBGManager()->update(dt);
    
    return NULL;
}
void GameState_Tutorial::end(){
    tutorial->removeFromParentAndCleanup(true);
    
    //レイガンの数を元に戻す
    gameObjectManager->getGameButton()->setFrogNum(prvFrogNum);
    Frog::cancel();
    
    ItemUseController::getInstance()->cansel();
    gameObjectManager->getBeamLayer()->removeAllChildrenWithCleanup(true);
    gameObjectManager->getGameButton()->setPauseButtonEnabled(true);
    
    gameObjectManager->resume();
    gameObjectManager->getPlayerController()->start();
}

//-----------------------
//  GameState_BonusStartInfo
//-----------------------
GameState_BonusStartInfo::GameState_BonusStartInfo()
{
    m_state =GMS_BONUSSTARTINFO;
}
void GameState_BonusStartInfo::begin(){
    gameObjectManager->showBonusStageInfo();
}
GameStateAbstract* GameState_BonusStartInfo::excute(float dt){
    if( gameObjectManager->getGameBonusStageUI()->canStart() ){
        return new GameState_Run();
    }
    //プレイヤー更新
    gameObjectManager->getPlayerController()->update(dt);
    
    GuardianManager::getInstance()->update(dt);
    
    // 背景スクロール
    gameObjectManager->getBGManager()->update(dt);
    return NULL;
}
void GameState_BonusStartInfo::end(){
}

//-----------------------
//  GameState_Run
//-----------------------
GameState_Run::GameState_Run()
{
    m_state =GMS_RUN;
}
void GameState_Run::begin(){
    gameObjectManager->resume();
    gameObjectManager->getInfoLayer()->setVisible(true);
    
    m_isBonusStage = GameScene::sharedInstance()->isBonusStage();
    GuardianManager::getInstance()->start();
    
    gameObjectManager->startItemUse();
}
GameStateAbstract* GameState_Run::excute(float dt){
    
    gameObjectManager->allObjectsUpdate(dt);
    
    //当たり判定
    gameObjectManager->hitCheckAllObjects();
    
    gameObjectManager->UIUpdate(dt);
    
    
    //死亡確認
    if(gameObjectManager->getPlayerController()->isLeaderDead()){
        return new GameState_Dead();
    }
    
    if( m_isBonusStage ){
        gameObjectManager->getGameBonusStageUI()->update(dt);
        if( gameObjectManager->getGameBonusStageUI()->isTimeUp() ){
            return new GameState_TimeOut();
        }
    }
    return NULL;
}
void GameState_Run::end(){
}

//-----------------------
//  GameState_Dead
//-----------------------
GameState_Dead::GameState_Dead()
{
    m_state =GMS_DEAD;
}
void GameState_Dead::begin(){
    gameObjectManager->playSound_Bg(BGM_STOP);
    playSoundEffect(g_SEName_player_death);
    gameObjectManager->pause_ofExceptingPlayer();
    m_isLeft = false;
    m_gameOverTimer = 0;
}
GameStateAbstract* GameState_Dead::excute(float dt){
    if( (m_gameOverTimer >= GAMEOVER_WAIT_TIME)){
        return new GameState_Continue();
    }
    
    if( m_isLeft ){
        gameObjectManager->setPositionX(-10);
    }else{
        gameObjectManager->setPositionX(10);
    }
    
    m_isLeft = !m_isLeft;
    m_gameOverTimer += dt;
    
    return NULL;
}
void GameState_Dead::end(){
    gameObjectManager->setPositionX(0);
}

//-----------------------
//  GameState_TimeOut
//-----------------------
GameState_TimeOut::GameState_TimeOut()
{
    m_state =GMS_TIMEOUT;
}
void GameState_TimeOut::begin(){
    gameObjectManager->pause();
    gameObjectManager->getGameBonusStageUI()->resume();
}
GameStateAbstract* GameState_TimeOut::excute(float dt){
    if( gameObjectManager->getGameBonusStageUI()->canEnd()){
        return new GameState_Continue();
    }
    
    return NULL;
}
void GameState_TimeOut::end(){
    gameObjectManager->getPlayerController()->warpEnd();
    Frog::cancel();
}
//-----------------------
//  GameState_Continue
//-----------------------
GameState_Continue::GameState_Continue()
{
    m_state =GMS_CONTINUE;
}
void GameState_Continue::begin(){
    nextState=NULL;
    int _no = GCD_TAKEOVER;
    if( GameScene::sharedInstance()->isBonusStage() ){
        _no = GCD_RERIVE;
        if( gameObjectManager->getGameBonusStageUI()->isTimeUp() ){
            _no = GCD_LASTRUN;
        }
    }
    GameContinueDialog::show(this, callfuncN_selector(GameState_Continue::checkUseContinueItem), (GCD_STATE_NO)_no);
}
GameStateAbstract* GameState_Continue::excute(float dt){
    return nextState;
}
void GameState_Continue::end(){
}
void GameState_Continue::checkUseContinueItem(GameContinueDialog *_dialog){
    switch (_dialog->getUseItemNo()) {
        case GCD_TAKEOVER:
            gameObjectManager->useChange();
            ItemUseController::getInstance()->reserveItemUse(kSkillItemType_TAKEOVER);
            break;
            
        case GCD_RERIVE:
            ItemUseController::getInstance()->reserveItemUse(kSkillItemType_CONTINU);
            break;
            
        case GCD_LASTRUN:
            if( gameObjectManager )gameObjectManager->useLastRun();
            nextState = new GameState_LastRun();
            break;
            
        default:
            nextState = new GameState_GameOver();
            break;
    }
}

//-----------------------
//  GameState_LastRun
//-----------------------
GameState_LastRun::GameState_LastRun()
{
    m_state =GMS_LASTRUN;
}
void GameState_LastRun::begin(){
    gameObjectManager->resetKiller(); //出ている隕石を消す
    ItemUseController::getInstance()->reserveItemUse(kSkillItemType_LASTRUN);
    
    DistanceManager* distanceManager = gameObjectManager->getDistanceManager();
    goalDistance = distanceManager->getDistance() * 1.1;
    
    //精霊のご加護
    plusDistance = MAX( 0, GuardianManager::getInstance()->getSpecialSkillValue(kGdSpSkill_AddDis_LastRun));
    
    int residueDistance = goalDistance- distanceManager->getDistance();
    distanceManager->setPlayerMoveSpeedRate(DEADWALK_SPEED_RATE_MAX);
    distanceManager->setAccel(false);   //加速を止める
    speedDownPunc = residueDistance*0.1;
    
    #ifdef DEBUG
    if( g_isDispParams ){
        debug_layer = CCSprite::create();
        gameObjectManager->addChild(debug_layer);
    }
    #endif
    
    gameObjectManager->getGameButton()->setFrogBtnEnabled(false);
    gameObjectManager->resume();
}

GameStateAbstract* GameState_LastRun::excute(float dt){
    gameObjectManager->allObjectsUpdate(dt);
    gameObjectManager->UIUpdate(dt);
    
    //当たり判定
    gameObjectManager->hitCheckWhenDeadWalk();
    
    DistanceManager* distanceManager = gameObjectManager->getDistanceManager();
    //残りの距離
    int residueDistance = (goalDistance + plusDistance)-(int)distanceManager->getDistance();
    
    if(residueDistance % speedDownPunc == 0 ){
        float rate = distanceManager->getPlayerMoveSpeedRate();
        if( distanceManager->getPlayerMoveSpeed() > 1.0f ){
            distanceManager->setPlayerMoveSpeedRate(MAX( 1.5, rate*0.9f));
        }
    }
#ifdef DEBUG
    if( g_isDispParams ){
        debug_layer->removeAllChildrenWithCleanup(true);
        
        char str[128];
        sprintf(str, "Last Run:goal %dm + %dm", goalDistance, plusDistance);
        NFLabelTTF* tex1 = NFLabelTTF::create(str, FONT_W6, 30);
        debug_layer->addChild(tex1);
        tex1->setColor(ccBLACK);
        tex1->setPosition(ccp(winSize.width*0.5, winSize.height*0.75));
        
        sprintf(str, "now:%dm rest:%dm", (int)distanceManager->getDistance(), residueDistance);
        NFLabelTTF* tex2 = NFLabelTTF::create(str, FONT_W6, 30);
        debug_layer->addChild(tex2);
        tex2->setColor(ccBLACK);
        tex2->setPosition(ccp(tex1->getPositionX(), tex1->getPositionY()-30));
    }
#endif
    
    if(residueDistance <= 0 ){     //退場処理
        return new GameState_GameOver();
    }
    return NULL;
}

void GameState_LastRun::end(){
    gameObjectManager->getPlayerController()->deadWalkEnd();
#ifdef DEBUG
    if( g_isDispParams ){
        debug_layer->removeFromParentAndCleanup(true);
    }
#endif
}

//-----------------------
//  GameState_GameOver
//-----------------------
GameState_GameOver::GameState_GameOver()
{
    m_state =GMS_GAMEOVER;
}
void GameState_GameOver::begin(){
    gameObjectManager->getPlayerController()->deadConfirm(); //死亡確定
    gameObjectManager->getEnemyController()->resultNextBoss();
    gameObjectManager->playSound_Bg(BGM_GAMEOVER);
    gameObjectManager->resume();
    gameObjectManager->getGameButton()->setPauseButtonEnabled(false);//ポーズボタン押せない
}
GameStateAbstract* GameState_GameOver::excute(float dt){
    if(gameObjectManager->getPlayerController()->isLeaderDeadFinish()){
        return new GameState_Wait();
    }
    
    gameObjectManager->allObjectsUpdate(dt);
    gameObjectManager->UIUpdate(dt);
    return NULL;
}
void GameState_GameOver::end(){
    NFLog("game over.-----");
    GameScene::sharedInstance()->gameover();
}



//void GameState_Entry::begin(){
//}
//GameStateAbstract* GameState_Entry::excute(float dt){
//    return NULL;
//}
//void GameState_Entry::end(){
//}

