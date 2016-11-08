
//  GameObjectManager.cpp
//  NinjaFlight
//

#import "CommonDefine.h"

#import "GameObjectManager.h"
#import "EnemyController.h"
#import "ItemController.h"
#import "GroundObjectController.h"

#import "Enemy.h"
#import "Player.h"
#import "Beam.h"
#import "ItemBase.h"
#import "Killer.h"
#import "ScrollBG.h"
#import "User.h"
#import "Frog.h"
#import "SoundManager.h"
#import "NFNumberLayer.h"
#import "BGManager.h"
#import "DistanceManager.h"
#import "GameContinueDialog.h"
#import "GameWarpGauge.h"
#import "GameCounter.h"
#import "GameCollectionBox.h"
#import "EffectFactory.h"
#import "QuestManager.h"
#import "GameStateManager.h"
#import "GuardianManager.h"
#import "GameButton.h"
#ifdef DEBUG
#import "GameDebugController.h"
#endif

using namespace cocos2d;


GameObjectManager::GameObjectManager()
{
    m_executeFlg = false;
    m_BGManager = NULL;
    m_distanceManager = NULL;
    debugContoroller= NULL;
}

GameObjectManager::~GameObjectManager(){
    this->unscheduleUpdate();
}

GameObjectManager* GameObjectManager::create(){
    GameObjectManager* g = new GameObjectManager();
	g->autorelease();
    
    return g;
}
#import "GameBonusStageUI.h"
void GameObjectManager::initStage(){
    m_bonusStageUI = NULL;
    
    if( GameScene::sharedInstance()->isBonusStage() ){
        m_BGManager = new BGManager(BGSet_Bonus);
    }else{
        m_BGManager = new BGManager(BGSet_Normal);
    }
    this->addChild(m_BGManager->getBGStageSet()->getBG(), PRTY_BG);
    this->addChild(m_BGManager->getBGStageSet()->getBGEffect(), PRTY_BGEffect);
    this->addChild(m_distanceManager->m_eff_warp, PRTY_WarpEff);
    this->addChild(m_BGManager);
}

void GameObjectManager::init(){
    if( m_BGManager != NULL ){
        delete m_BGManager;
    }
    if( m_distanceManager != NULL ){
        delete m_distanceManager;
    }
    buddy_help = NULL;
    
#ifdef DEBUG
    debugContoroller = GameDebugController::create();
    debugContoroller->setVisible(false);
    GameScene::sharedInstance()->addChild(debugContoroller, 100);
#endif
    
    //あいてむ数を獲得ちゃん
//    m_raygunNum = RAYGUN_MAX_NUM;
    m_useNum_frog = 0;
    m_useNum_Continue = 0;
    m_useNum_Change = 0;
    m_useNum_LastRun = 0;
    m_useNum_multiGold = 0;
    m_useNum_gemDash=0;
    m_useNum_sushiDash = 0;
    
    m_score = 0;
    m_isFinalBossKill = false;
    m_metalBossKillNum = 0;
    m_didRecommendToChange = false;
    m_canUseStartItem = true;
    m_isTreasure = User::getInstance()->isTreasureAppear();
    m_isFinalOgreBossKill = false;
    finalOgreBossHp = BOSS_FINAL_OGRE_HP;
    // ボス履歴配列の初期化
    bossResultArray = CCArray::create();
    bossResultArray->retain();
    
    const GameStartArgs* gameStartArgs = GameScene::sharedInstance()->getGameStartArgs();
    
    //magatama
    m_isGetMagatama = 0;
    m_jumpScore=0;
    m_jumpCombo=0;
    m_jumpBomb=0;
    
    m_p_frendScoreLayer = NFSpriteCluster::create();
    this->addChild(m_p_frendScoreLayer);
    
    //距離
    m_startDistance = g_initDistance;
    if( gameStartArgs->isUseSuperJump ){
        m_startDistance = MAGATAMA_JUMP_DISTANCE;
    }
    //開始速度指定
    float startSpeedDistance = gameStartArgs->isBonusStage ? 3000 : g_initDistance;
    
    m_distanceManager = DistanceManager::create(m_startDistance, startSpeedDistance);
    this->addChild(m_distanceManager);
    m_distanceManager->setVisible(false);
    
    //ワープエフェクトの登録
    m_distanceManager->m_eff_warp->makeDarken(this, PRTY_Darken);
    
    m_executeFlg = false;
    
    //弾を表示するレイヤーをbaseLayer上に配置
    m_p_beamLayer = NFSpriteCluster::create();
    this->addChild(this->m_p_beamLayer, PRTY_Beam);
    
    //レンタル状況
    m_isRental = User::getInstance()->isRentalBuddies();
    //プレイヤー管理クラス生成
    playerController = new PlayerController(m_isRental);
    playerController->setPositionY(-300);
    this->addChild(playerController,PRTY_Player);
    
    //守護精霊
    m_guardianManager = GuardianManager::create(m_isRental);
    this->addChild(m_guardianManager,PRTY_Guardian);
    
    //背景
    initStage();
    
    // 敵管理クラス生成
    enemyController = new EnemyController();
    this->addChild(enemyController, PRTY_Enemy);
    

    //加算されたスコアを表示するレイヤー
    m_p_scoreDispLayer = NFSpriteCluster::create();
    m_p_scoreDispLayer->setHandsOffChildProperty(true);
    this->addChild(this->m_p_scoreDispLayer, PRTY_AddScore);
    
    //獲得したコインと緑ジェムを表示するレイヤー
    m_p_addItemDispLayer = NFSpriteCluster::create();
    m_p_addItemDispLayer->setHandsOffChildProperty(true);
    this->addChild(m_p_addItemDispLayer, PRTY_AddItem);
    
    //boss 弾
    m_p_bossBeamLayer = NFSpriteCluster::create();
    this->addChild(m_p_bossBeamLayer, PRTY_EnemyBeam);
    
    // アイテム表示するレイヤーを配置
    itemController = new ItemController();
    itemController->autorelease();
    itemController->setHandsOffChildProperty(true);
    this->addChild(itemController, PRTY_Item);
    
    ItemUseController::launch(this, PRTY_ItemUseEff);
    
    //地面レイヤー
    groundObjecController = GroundObjectController::create();
    groundObjecController->settingCollectionData(
                    GameScene::sharedInstance()->getGameStartArgs()->collectionItemColor,
                    GameScene::sharedInstance()->getGameStartArgs()->collectionItemDistance
    );
    this->addChild(groundObjecController, PRTY_Block);
    
    NFSpriteCluster* prisonLayer = groundObjecController->getPrisonCluster();
    this->addChild(prisonLayer, PRTY_Prison);
    
    //隕石レイヤー
    this->m_p_killerLayer = NFSpriteCluster::create();
    this->addChild(this->m_p_killerLayer, PRTY_Killer);
    
    //優先度高めで表示したいものレイヤー
    m_p_noticeLayer = NFSpriteCluster::create();
    m_p_noticeLayer->setHandsOffChildProperty(true);
    this->addChild(m_p_noticeLayer, PRTY_Notice);
    
    //combo counter
    m_comboCounter = GameComboCounter::create();
    m_p_noticeLayer->addChild(m_comboCounter);
    
    //状態表示
    m_p_infoLayer = NFSpriteCluster::create();
    m_p_infoLayer->setVisible(false);
    this->addChild(this->m_p_infoLayer, PRTY_InfoUI);
    
    //ninja power.
    m_ninjaPowerCounter = NinjaPowerCounter::create(playerController);
    m_p_infoLayer->addChild(m_ninjaPowerCounter);
    
    //巻物所持情報
    m_gameHaveRollInfo = GameHaveRollInfo::create();
    m_p_infoLayer->addChild(m_gameHaveRollInfo);
    
    //coin counter
    m_p_coinCounter = GameCoinCounter::create();
    m_p_infoLayer->addChild(m_p_coinCounter, 0);
    
    m_warpGuage = GameWarpGauge::create();
    m_p_infoLayer->addChild(m_warpGuage, 0);
    
    //距離表示クリエイト
    m_distanceManager->createDistanceDisp(m_p_infoLayer);
    
    //金の寿司　使用アイコン
    if( gameStartArgs->isGoldSushi ){
        CCSprite* ico_info_life_gold_01 = CCSprite::create("ico_info_life_gold_01.png");
        ico_info_life_gold_01->setAnchorPoint(ccp(0.5, 0.5));
        ico_info_life_gold_01->setPosition(ccp(85.0, 830.0));
        m_p_infoLayer->addChild(ico_info_life_gold_01);
    }
    
    //二倍ゴールド
    if( gameStartArgs->isMultiGold ){
        useMultiGold(false);    //お試しなのでジェム加算はしない
    }
    
    m_gameButton = GameButton::create();
    m_p_infoLayer->addChild(m_gameButton);
    
    //sound BG
    playSound_Bg(BGM_STOP);
    
    whiteLayer = CCLayerColor::create(ccc4(255, 255, 255, 255), winWidth, winHeight);
	whiteLayer->setPosition(ccp(0, 0));
	this->addChild(whiteLayer, 100);
    
    //magatama
    if( gameStartArgs->isUseSuperJump ){
        roadSuperJumpData();
    }
    m_distanceManager->createScoreDispLayer(m_p_frendScoreLayer, PRTY_InfoRecode);

}

void GameObjectManager::roadSuperJumpData(){
    JumpData*  data = User::getInstance()->getJumpData();
    getComboCounter()->addCombo(data->combo);
    m_gameButton->setFrogNum(data->bomb);
    addScore( data->score, ccp(0,0));
}

#import "CCNodeUtil.h"
void GameObjectManager::showWhiteOutWipe(){
    if( whiteLayer ){
        whiteLayer->runAction
        (CCSequence::create(
                            CCFadeOut::create(0.5)
                            ,CCNodeUtil::createRemoveAction()
                            ,NULL));
        whiteLayer = NULL;
    }
}

float GameObjectManager::calcStartDashDistance(){
    float distance=0;
    if(GameScene::sharedInstance()->getGameStartArgs()->isThousandWarp){
        distance += STARTDASH_DISTANCE_ROLL;
    }
    if(GameScene::sharedInstance()->getGameStartArgs()->isSushiDash
       || m_useNum_gemDash
       || m_useNum_sushiDash  ){
        distance += STARTDASH_DISTANCE_SUSHI;
    }
    int dis = m_guardianManager->getSpecialSkillValue(kGdSpSkill_StartDash);
    if( dis > 0 ){
        distance += dis;
    }
    
    return distance;
}

GameCollectionBox* GameObjectManager::getCollectionBox(){
    GameCollectionBox* box = GameCollectionBox::create(
                        GameScene::sharedInstance()->getGameStartArgs()->collectionItemNum);
    m_p_noticeLayer->addChild(box);
    
    return box;
}

void GameObjectManager::start(){
    m_gameButton->setPauseButtonEnabled(false);//ポーズボタンは押せない

    if(m_p_beamLayer != NULL) m_p_beamLayer->removeAllChildrenWithCleanup(true);
    nowPlay = BGM_STOP;
    bg_play = false;
    
    m_distanceManager->init();  //距離系初期化
    
    m_executeFlg = true;
    
    if( !GameScene::sharedInstance()->getGameStartArgs()->isUseSuperJump ){
        m_score = 0;
    }
    
    m_isExistKiller = false;
    m_canRerive = true;
    m_canChange = true;
    
    playerController->start(); // 自機を動作開始
    enemyController->start();
    m_p_coinCounter->start();
    groundObjecController->start();
    
    //フィーバーゲージ関連の初期化
    m_warpGuage->reset();
    
    m_pauseCnt = 0;
    
    m_ninjaPowerCounter->start();
    
    m_isFinalBossKill = false;
    m_metalBossKillNum = 0;
    m_didRecommendToChange = false;
    
    m_debud_pause =false;

    lotteryMetalBossAppear();
    m_p_infoLayer->setVisible(false);
    
#ifdef DEBUG
    if( g_d_flg_warpBtnDisp ){
        playerController->debug_createWarpBtn();
    }
    if( g_d_flg_deathFromAbove ){
        debugContoroller->debug_death_from_above();
    }
    
    playerController->debug_showSuicideBtn(g_d_flg_suicide);
#endif

}
void GameObjectManager::finalBossKill(){
    m_isFinalBossKill = true;
}

void GameObjectManager::metalBossKill(){
    m_metalBossKillNum ++;
    QuestManager::addCount(kQuestConditionKillBossGold, 1);
}

void GameObjectManager::startItemUse(){
    if( m_canUseStartItem ){
        m_canUseStartItem = false;
        
        ItemUseController* itemUseController= ItemUseController::getInstance();
        //start effect スタック
        if( m_isRental ){
            itemUseController->reserveItemUse(kSkillItemType_RENTAL);
        }
        if(GameScene::sharedInstance()->getGameStartArgs()->isMultiGold
           || m_useNum_multiGold ){
            itemUseController->reserveItemUse(kSkillItemType_MULTIGOLD);
        }
        
        if( !GameScene::sharedInstance()->getGameStartArgs()->isUseSuperJump ){ //まがたま使用してない時のみ
            //スタート時のダッシュ処理
            Player* leader = playerController->getLeader();
            if( leader->hasAbility(kPlayerAbilityType_StartDash)){  //スーパーサスケスキル
                itemUseController->reserveItemUse(kSkillItemType_HIENDASH);
            }
            if( gameObjectManager->calcStartDashDistance() > 0  ){ //StartDash
                itemUseController->reserveItemUse(kSkillItemType_STARTDASH);
            }
        }
    }
}

void GameObjectManager::showBonusStageInfo(){
    const GameStartArgs* gameStartArgs = GameScene::sharedInstance()->getGameStartArgs();

    //bonus stage UI
    m_bonusStageUI = GameBonusStageUI::create(
                                              gameStartArgs->bonusStageLimitTime,
                                              gameStartArgs->bonusStageTitle,
                                              gameStartArgs->bonusStageSubTitle);
    m_p_noticeLayer->addChild(m_bonusStageUI);
}

const char music_bg[32] = "LN_ninjabgm004.m4a";
const char music_boss[32] = "LN_ninjabgm005.m4a";
const char music_fever[32] = "LN_ninjabgm007.m4a";
const char music_result[32] = "LN_ninjabgm008.m4a";

void GameObjectManager::playSound_Bg(BGM_State _state ){
    if(  GameScene::sharedInstance()->isBonusStage()
       &&(_state == BGM_PLAY)){
        _state = BGM_FEVER;
    }
    if( nowPlay == _state ){  //同じ音ならなにもしない
        return;
    }
    
    if(bg_play){
        pauseBackgroundMusic();
        bg_play = false;
    }
    nowPlay = _state;
    switch (_state) {
        case BGM_STOP:
            break;
        case BGM_PLAY:
            playBackgroundMusicLoop(music_bg);
            break;
        case BGM_FEVER:
            playBackgroundMusicLoop(music_fever);
            break;
        case BGM_BOSS:
            playBackgroundMusicLoop(music_boss);
            return;
        case BGM_GAMEOVER:
            playBackgroundMusicLoop(music_result);
            break;
        default:
            return;
    }
    
    bg_play = true;
}

bool GameObjectManager::beingProcessChangePlayer(){
    return m_beingProcessChangePlayer;
}

//復活
void GameObjectManager::useChangePlayer(){
    m_beingProcessChangePlayer = true;
    
    playerController->changeLeader();
    rerivePlayer();
    if( enemyController->isBossExist() ){
        playSound_Bg(BGM_BOSS);
        
    }else{
        playSound_Bg(BGM_PLAY);
    }
    m_canChange = false;
    
    m_beingProcessChangePlayer = false;
}

void GameObjectManager::useRerive(){
    playerController->revival(); // 自機を動作　再開
    rerivePlayer();
    m_canRerive = false;    //救済は一度きり
    m_useNum_Continue ++;
    
#ifdef DEBUG
    if( g_d_flg_infinityRelief ){
        m_canRerive = true;
    }
#endif
}

void GameObjectManager::rerivePlayer(){
    //出ている敵・隕石を消す
    enemyController->deathAllNormalEnemies();
    resetKiller();

    if( enemyController->isBossExist() ){
        playSound_Bg(BGM_BOSS);

    }else{
        playSound_Bg(BGM_PLAY);
    }
    GameStateManager::getInstance()->replaseState(new GameState_Run());
}
void GameObjectManager::allObjectsUpdate(float time){
    //敵更新
    enemyController->update(time);
    
    //プレイヤー更新
    playerController->update(time);
    
    //カエル更新
    Frog::updateIfPossible(time);
    
    m_guardianManager->update(time);
    
    //隕石更新
    CCObject *object = NULL;
    if(m_p_killerLayer->getChildrenCount() < 1){
        m_isExistKiller = false;
    }else{
        CCARRAY_FOREACH_REVERSE(m_p_killerLayer->getChildren(), object) {
            Object* i = (Killer*)object;
            i->update(time);
        }
    }
    
    //配置アイテム更新
    itemController->update(time);
    
    //地面オブジェクト更新
    groundObjecController->update(time);
    
    // 背景スクロール
    m_BGManager->update(time);
    
    
    ItemUseController::getInstance()->checkReserve();
}

void GameObjectManager::UIUpdate(float time){
    //当たり判定
    hitCheckAllObjects();
    
    //所持コイン表示を更新
    m_p_coinCounter->updateCount();
    
    //仲間パワーを表示
    m_ninjaPowerCounter->updateCount();
    
    //現在のスコア表示を更新
    m_distanceManager->updateDistance(time);
}


#import "BossBullet.h"
void GameObjectManager::hitCheckAllObjects(){
    
    if( m_pauseCnt >0 ){
        return;
    }
    
    CCObject *object1 = NULL;
    CCObject *object2 = NULL;
    
    CCArray* items = NULL;
    
    if( Frog::isAttacking() ){ //かえる攻撃中
        //アイテムとれる
        items = itemController->getItems();
        object2=NULL;
        CCARRAY_FOREACH_REVERSE(items, object2) {
            ItemBase* i = (ItemBase*)object2;
            if(i==NULL){
                NFLog("Not Item Class Added ItemLayer.");
                continue;
            }
            if( i->getPositionY() < WARP_KILL_POS_Y ){
                i->hasHit(NULL);
            }
        }
    }
    
    CCArray* beamArray = m_p_beamLayer->getChildren();
    object1= NULL;
    CCARRAY_FOREACH_REVERSE(beamArray, object1) {
        Beam* beam = dynamic_cast<Beam*>(object1);
        if( !beam ) continue;
        //弾＊敵
        if(beam->isBulletThrough()){
            enemyController->checkCollisionAll(beam);
        }
        else{
            enemyController->checkCollision(beam);
        }
        if( !beam->isStaged() ) continue;
        
        groundObjecController->hitcheckToBlock(beam);   //地面に立つ敵
        if( !beam->isStaged() ) continue;

        CCArray* bossBeams = m_p_bossBeamLayer->getChildren();  //弾*ボス弾
        object2=NULL;
        CCARRAY_FOREACH_REVERSE(bossBeams, object2){
            BossBullet* object = (BossBullet*)object2;
            if( beam->hitIfCollided(object) ){
                object->hasHit(beam);
                if( !beam->isStaged() || !object->isStaged() ) continue;
            }
        }
        //*killer
        object2=NULL;
        CCARRAY_FOREACH_REVERSE(m_p_killerLayer->getChildren(), object2) {
            Killer* i = (Killer*)object2;
            if(i==NULL){
                NFLog("Not Item Class Added ItemLayer.");
                continue;
            }
            if(beam->hitIfCollided(i)){
                i->hasHit(beam);
                break;
            }
        }

    }
    
    //cannon
    CCArray* players = playerController->getPlayers();
    object1= NULL;
    CCARRAY_FOREACH_REVERSE(players, object1) {
        Cannon* cannon = (Cannon*)object1;
        if(cannon==NULL){
            NFLog("Not Item Class Added ItemLayer.");
            continue;
        }
        hitCheckCannon(cannon);
    }

    itemController->checkDeleteItems();
}

void GameObjectManager::hitCheckCannon(Cannon *cannon){
    CCObject *object2 = NULL;
    CCArray* items = itemController->getItems();
    
    //cannon * item
    CCARRAY_FOREACH_REVERSE(items, object2) {
        ItemBase* i = (ItemBase*)object2;
        if(i==NULL){
            NFLog("Not Item Class Added ItemLayer.");
            continue;
        }
        if(cannon->hitIfCollided(i)){
            i->hasHit(cannon);
            break;
        }
    }
    //cannon * froudObject
    object2 = NULL;
    CCArray* groundArray = groundObjecController->getAllGroundObjects();
    CCARRAY_FOREACH_REVERSE(groundArray, object2) {
        Object* i = (Object*)object2;
        if(i==NULL){
            NFLog("Not Item Class Added ItemLayer.");
            continue;
        }
        if(cannon->hitIfCollided(i)){
            i->hasHit(cannon);
            break;
        }
    }
    groundObjecController->hitcheckToBlock(cannon);
    
    //自*enemy
    if( playerController->isWarp() ){
        enemyController->checkCollisionAll(cannon);
    }else{
        enemyController->checkCollision(cannon);
    }
    
    //自*killer
    object2 = NULL;
    CCARRAY_FOREACH(m_p_killerLayer->getChildren(), object2) {
        Killer* i = (Killer*)object2;
        if(i==NULL){
            NFLog("Not Item Class Added ItemLayer.");
            continue;
        }
        if(cannon->hitIfCollided(i)){
            i->hasHit(cannon);
            break;
        }
    }
    
    CCArray* bossBeams = m_p_bossBeamLayer->getChildren();
    object2 = NULL;
    CCARRAY_FOREACH_REVERSE(bossBeams, object2){
        BossBullet* object = (BossBullet*)object2;
        if( cannon->hitIfCollided(object) ){
            object->Object::hasHit(cannon);
        }
    }
}

void GameObjectManager::hitCheckWhenDeadWalk(){
    if( m_pauseCnt >0 ){
        return;
    }
    
    CCObject *object1 = NULL;
    //敵*自
    CCArray* players = playerController->getPlayers();
    CCARRAY_FOREACH( players, object1) {
        Cannon* cannon = (Cannon*)object1;
        if( cannon == NULL ){
            continue;
        }
        enemyController->checkCollisionAll(cannon);
        hitCheckCannon(cannon);
    }
}

void GameObjectManager::startIncrementFvGAnime(){
    m_warpGuage->startFvGuageIncrement();
}

void GameObjectManager::startWarp(){
    m_distanceManager->startWarp();
    m_p_beamLayer->removeAllChildrenWithCleanup(true);
    m_warpGuage->startFever();
    resetKiller();
}

void GameObjectManager::resetWarp(){
    m_warpGuage->finishFever();
    m_distanceManager->resetWarp();
        
    //出ている敵・隕石を消す
    enemyController->deathWarpAfter();
    resetKiller();
}

//Touches -----------------------------------------------------------------
void GameObjectManager::touchBegin(CCPoint point){
    playerController->informTouchedBegin(point);
}

void GameObjectManager::touchMove(CCPoint point){
    playerController->informTouchedMoves(point);
}
#import "GameProloge.h"
void GameObjectManager::touchEnd(CCPoint point){
    playerController->informTouchedEnd(point);
    
    if(g_d_flg_deathFromAbove && point.y > winSize.height*0.5){
        enemyController->debug_death();
    }
    
    GameState state = GameStateManager::getInstance()->getState();
    if( state == GMS_PROLOGE && GameProloge::getInstance()){
        GameProloge::getInstance()->remove();
        GameStateManager::getInstance()->replaseState(new GameState_Entry());
    }
    
#ifdef DEBUG
    //ポーズダイアログなしの一時停止　一度押すと止まり、もう一度押すと動き出す
    if( state == GMS_RUN){
        CCRect rect = CCRect(598.0, 900.0, 300, 100);
        if( rect.containsPoint(point) ){
            m_debud_pause = !m_debud_pause;
            if( m_debud_pause ){
                if( !isPause() )pause();
            }else{
                resume();
            }
        }
    }    
#endif
    
}

//UI -----------------------------------------------------------------

CCPoint GameObjectManager::getCoinGaugePos(){
    return m_p_coinCounter->getCoinGaugePos();
}

CCPoint GameObjectManager::getWarpGaugePos(){
    return m_warpGuage->getWarpGaugePos();
}


void GameObjectManager::summonFrog(){
    Frog* frog = Frog::launch();
    this->addChild(frog, PRTY_Frog);
}

//Layer Add Interface -------------------------------------------------------------
void GameObjectManager::addBossBeam(BossBullet *_bossBullet){
    m_p_bossBeamLayer->addChild(_bossBullet);
}

//隕石 -----------------------------------------------------------------
void GameObjectManager::resetKiller(){  //場に出ている隕石を全部消す
    CCObject* object = NULL;
    CCARRAY_FOREACH_REVERSE(m_p_killerLayer->getChildren(), object) {
        if( object != NULL ){
            Killer* k = (Killer*)object;
            k->explosion();
        }
    }
}
bool GameObjectManager::isExistKiller(){
    return m_p_killerLayer->getChildrenCount();
}

void GameObjectManager::addKiller(Killer *killer){
    m_p_killerLayer->addChild(killer);
}

void GameObjectManager::appearKiller(){
    CCPoint pos= gameObjectManager->getPlayerController()->getLeaderPosition();
    Killer* killer = Killer::create( CCPoint( pos.x, winSize.height ) );
    gameObjectManager->addKiller(killer);
}

//Distance
float GameObjectManager::getDistance(){
    return m_distanceManager->getDistance();
}

float GameObjectManager::getPlayerMoveSpeed(){
    return m_distanceManager->getPlayerMoveSpeed();
}

float GameObjectManager::getStartDistance(){
    return m_startDistance;
}

//scroll
float GameObjectManager::getScrollSpeed(){
    return m_BGManager->getScrollSpeed();
}

//coin
void GameObjectManager::addCoin(int value){
    m_p_coinCounter->addCoin(value);
}
int GameObjectManager::getCoinNum(){
    return m_p_coinCounter->getCoinTotalValue();
}

#import "EffectFactory.h"

//score
void GameObjectManager::addScore(int _score,  cocos2d::CCPoint _pos){
    m_score += _score;
    if(g_isDispParams){
        EffectFactory::createAddScore(_score, m_p_scoreDispLayer, _pos);
    }
}

void GameObjectManager::addBonusScore(int _score, bool _isDash){
    m_score += _score;
    EffectFactory::createAddBonusScore(_score, _isDash, m_p_scoreDispLayer);
}

int GameObjectManager::getScore(){
    return m_score;
}

void GameObjectManager::dispBuddyBonus(CCPoint _pos){
    EffectFactory::createBuddyBonus(m_p_scoreDispLayer, _pos);
}

//Notice
void GameObjectManager::addNoticeLayerChild(CCNode* _s, int zOder){
    if( m_p_noticeLayer == NULL ) return;
    m_p_noticeLayer->addChild(_s, zOder);
}

void GameObjectManager::setBuddyNotice(float _posX){
    
    if( buddy_help == NULL ){
        //仲間予告
        buddy_help = NFSpriteCluster::create("buddy_help.png");
        buddy_help->setAnchorPoint(ccp(0.5, 1.0));
        buddy_help->setPosition(ccp(100.0, 200.0));
        buddy_help->setScale(0.5);
        buddy_help->setOpacity(0.0);
        addNoticeLayerChild(buddy_help, 0);
    }
    
    //予告をだす
    buddy_help->setVisible(true);
    buddy_help->setPositionX(_posX);
    buddy_help->setPositionY(winSize.height*0.8 + buddy_help->getContentSize().height/2);
    buddy_help->setScale(0.5);
    buddy_help->setOpacity(0.0);
    
    buddy_help->runAction
    (CCSpawn::create
     (CCSequence::create
      (CCMoveBy::create(4.0 / 30.0, ccp(0.0, -10.0)),
       CCDelayTime::create(47.0 / 30.0),
       CCMoveBy::create(6.0 / 30.0, ccp(0.0, -20.0)),
       NULL),
      CCSequence::create
      (CCScaleTo::create(4.0 / 30.0, 1.1),
       CCScaleTo::create(2.0 / 30.0, 0.9),
       CCScaleTo::create(2.0 / 30.0, 1.0),
       CCDelayTime::create(9.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.1),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCDelayTime::create(10.0 / 30.0),
       CCScaleTo::create(4.0 / 30.0, 1.1),
       CCScaleTo::create(3.0 / 30.0, 1.0),
       CCDelayTime::create(16.0 / 30.0),
       NULL),
      CCSequence::create
      (CCFadeTo::create(4.0 / 30.0, 255.0),
       CCDelayTime::create(47.0 / 30.0),
       CCFadeTo::create(6.0 / 30.0, 0.0),
       NULL),
      NULL));
}

float GameObjectManager::calcBuddyNoticeIntervalDistance(){
    if( gameObjectManager->getPlayerController()->isWarp() ){
        return getPlayerMoveSpeed()*(BUDDY_NOTICE_TIME/m_distanceManager->getPlayerMoveSpeedRate());
    }else{
        return getPlayerMoveSpeed()* BUDDY_NOTICE_TIME;
    }
}

float GameObjectManager::calcBuddyNoticeIntervalPxcel(){
    return calcBuddyNoticeIntervalDistance() / DISTANCE_FOR_PIXCEL;
}


void GameObjectManager::lotteryMetalBossAppear(){
    int _rand = rand() % 100;
    if( _rand < User::getInstance()->getMetalBossAppearRate()){
        m_exchangeMetalBossNo = (rand()%4)+1;
        return;
    }
    m_exchangeMetalBossNo = -1;
}

void GameObjectManager::dispPauseLayer(){
    GameScene* gameScene = GameScene::sharedInstance();
    if(gameScene->pause()){
        m_executeFlg = false;
        pause();
#ifdef DEBUG
        debugContoroller->setVisible(true);
#endif
    }
}

void GameObjectManager::pause_ofExceptingPlayer(){
    pause();
    playerController->resume();
}

#import "GameContinueDialog.h"
void GameObjectManager::pause(){
    m_pauseCnt ++;
    
    playerController->pause();
    enemyController->pause();
    itemController->pause();
    ItemUseController::getInstance()->pause();
    groundObjecController->pause();
    m_distanceManager->pause();
    m_p_scoreDispLayer->pause();
    
    m_BGManager->setStop(true);

    m_p_noticeLayer->pause();
    m_p_beamLayer->pause();
    m_p_killerLayer->pause();
    m_p_infoLayer->pause();
    m_p_coinCounter->pause();  
    m_warpGuage->pause();
    m_p_bossBeamLayer->pause();
    Frog::pauseIfPossible();
    m_p_addItemDispLayer->pause();
    m_p_frendScoreLayer->pause();
    GameContinueDialog::pause();
    m_gameButton->setEnabled(false);
    m_guardianManager->pause();
}


#import "Player.h"
void GameObjectManager::endPauseLayer(){
#ifdef DEBUG
    debugContoroller->setVisible(false);
#endif
    
    m_executeFlg = true;
    resume();
    if( m_pauseCnt > 0){
        ItemUseController* itemUseController = ItemUseController::getInstance();
        if( itemUseController->isItemUsePause() ){
            itemUseController->resume();
        }

        if( Frog::isEmerging() ){
            Frog::resumeIfPossible();
        }

        GameContinueDialog::resume();
        
        GameState state = GameStateManager::getInstance()->getState();
        if( state == GMS_TIMEOUT
           || state == GMS_BONUSSTARTINFO){
            m_bonusStageUI->resume();
        }
    }
}

void GameObjectManager::resume(){
    m_pauseCnt --;
    m_pauseCnt = MAX( 0, m_pauseCnt );
    if( m_pauseCnt > 0 ) return;
    
    playerController->resume();
    enemyController->resume();
    itemController->resume();
    ItemUseController::getInstance()->resume();
    groundObjecController->resume();
    m_distanceManager->resume();
    m_p_scoreDispLayer->resume();
    
    m_BGManager->setStop(false);
    
    m_p_noticeLayer->resume();
    
    m_p_beamLayer->resume();
    m_p_killerLayer->resume();
    m_p_infoLayer->resume();
    m_p_coinCounter->resume();
    m_p_bossBeamLayer->resume();
    m_warpGuage->resume();
    Frog::resumeIfPossible();
    m_p_addItemDispLayer->resume();
    m_p_frendScoreLayer->resume();
    
    GameContinueDialog::resume();
    m_gameButton->setEnabled(true);
    m_guardianManager->resume();
}

void GameObjectManager::createTreasureGetIcon(){
    CCSprite* treasureIcon = CCSprite::create("item02_icon.png");
    treasureIcon->setAnchorPoint(ccp( 0.5, 0.5 ));
    treasureIcon->setPosition(ccp( 258,winSize.height-36 ));
    
    m_p_infoLayer->addChild(treasureIcon);
    
    CCPoint pos = ccpAdd( treasureIcon->getPosition(), EffectFactory::getRandomInterval(CCSize(80,80)));
    EffectFactory::createShine(m_p_infoLayer, pos);
}

void GameObjectManager::createMagatamaGetIcon(){
    CCSprite* magatamaIcon = CCSprite::create("ico_beads_warp_02.png");
    magatamaIcon->setAnchorPoint(ccp(0.5 , 0.5));
    magatamaIcon->setPosition(ccp(187.5, 874.5));
    m_p_infoLayer->addChild(magatamaIcon);
    
    CCPoint pos = ccpAdd(magatamaIcon->getPosition() , EffectFactory::getRandomInterval(CCSize(80,80)));
    EffectFactory::createShine(m_p_infoLayer, pos);
}

void GameObjectManager::createLastRunGetIcon(){
    CCSprite* icon = CCSprite::create("ykk_s03.png");
    icon->setAnchorPoint(ccp( 0.5, 0.5 ));
    icon->setPosition(ccp( 258,winSize.height-(36*2) ));
    
    m_p_infoLayer->addChild(icon);
    EffectFactory::createShine(icon, ccp(28, 28));
}

void GameObjectManager::draw(){
    
    if (!g_isGameDebug) {
        return;
    }
    
    glLineWidth(2.0f);
    ccDrawColor4F(0, 1, 1, 1);
    
    playerController->debugDraw();
    
    //敵
    CCObject* object;
    
    CCARRAY_FOREACH(m_p_killerLayer->getChildren(), object) {
        Object* p = (Object*)object;
        if(p==NULL){
            NFLog("[GameObjectManager::draw]p==NULL");
            continue;
        }
        ccDrawCircle(p->getHitPosition(), p->getRadius(), CC_DEGREES_TO_RADIANS(45), 12, true);
    }
    
}

int GameObjectManager::calcUseGem(){
    int num = 0;
    User* user = User::getInstance();
    if( m_useNum_Continue ){
        if( User::getInstance()->get_continue_item_cnt() < 1 ){
            num += user->getItemGemCost(ItemIdCONTINUE);
        }
    }
    if( m_useNum_Change ){
        num += user->getItemGemCost(ItemIdKAWARIMI);
    }
    if( m_useNum_LastRun ){
        num += user->getItemGemCost(ItemIdHIRYU);
    }
    if( m_useNum_multiGold ){
        num += user->getItemGemCost(ItemIdMULTI_GOLD);
    }
    if( m_useNum_gemDash ){
        num += user->getItemGemCost(ItemIdSUSHI_DASH);
    }
    return num;
}

void GameObjectManager::useMultiGold(bool isGem){
    itemController->setMultiGold(true);
    if( isGem ){
        m_useNum_multiGold++;
    }
    m_gameHaveRollInfo->setIcon(kSkillItemType_MULTIGOLD);
}

void GameObjectManager::useSushiDash(bool isGem){
    if( isGem ){
        m_useNum_gemDash++;
    }else{
        m_useNum_sushiDash++;
    }
    m_gameHaveRollInfo->setIcon(kSkillItemType_MAX);
}

/**
 * 岩を落とす位置を予約し、一定時間後に岩を落とします。
 */
void GameObjectManager::reserveTargetAndShotBlock(int raidBossId , CCPoint pos)
{
    if(groundObjecController){
        EffectFactory::createFallBlockTargetAnim(raidBossId , pos, groundObjecController, 0);
        groundObjecController->reserveTarget(raidBossId , pos);
    }
}

/*
    まがたま　まがまが
 */
//まがたま使用時の再開スコアを保存
void GameObjectManager::recordMagatamaJumpData(){
    m_jumpScore = getScore();
    m_jumpCombo = getComboCounter()->getComboNum();
    m_jumpBomb = m_gameButton->getFrogNum();
}


/*
 * レンタル(借)
 */
void GameObjectManager::finishRental(){
    m_isRental = false;
    m_guardianManager->finishRental();
    m_gameButton->finishRental();
}
