
using namespace cocos2d;
#define FIRST_MODE 1 //0:Player 1:Buddy 2:Boss 3:Enemy


//player
#define FIRST_PLAYER_NO CharactorType_Brown
#define FIRST_PLAYER_SHOT_TYPE 1
#define FIRST_PLAYER_EVOLUTION_TYPE 1

//buddy
#define FIRST_BUDDY_NO 5 //rank
#define FIRST_ATTR_NO Thunder    //Normal Thunder Fire Splush Cure Master Mecha Cosmo
#define FIRST_BUDDY_COSTUME_NO kCostumeSengoku //kCostumBasic  kCostumeSengoku
#define FIRST_BUDDY_LV 1
//boss
#define FIRAST_BOSS_NO kRBossType5_MechaEgypt
CCScene* AnotherWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AnotherWorld *layer = AnotherWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
    	
    // return the scene
    return scene;
}

#import "BonusRoulettDialog.h"
void AnotherWorld::test(){
    BonusRoulettDialog::show(2546, this, this,menu_selector(AnotherWorld::test2));
    
    CCMenu* rootMenu01 = CCMenu::create();
    rootMenu01->setAnchorPoint(ccp(0, 0));
    rootMenu01->setPosition(ccp(0, 0));
    this->addChild(rootMenu01);
    CCSprite* btn_close_01 = CCSprite::create("btn_close_01.png", CCRectMake(0, 0, 242.0, 124.0));
    CCSprite* btn_close_01Push = CCSprite::create("btn_close_01.png", CCRectMake(242.0, 0, 242.0, 124.0));
    NFMenuItemSprite* btn_close_01Btn = NFMenuItemSprite::create(btn_close_01, btn_close_01Push);
    btn_close_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_close_01Btn->setPosition(ccp(50.0, (winHeight - 960) / 2 + 800.0));
    rootMenu01->addChild(btn_close_01Btn);
    btn_close_01Btn->setTarget(this, menu_selector(AnotherWorld::test));
}

void AnotherWorld::test2(cocos2d::CCObject *sender){
    BonusRoulettDialog* dialog =(BonusRoulettDialog*)sender;
    NFLog("result coin[%d]", dialog->getResultGold());
    NFLog("user gem[%d]", dialog->getUseGemNum());
}

#import "GoldTicketDialog.h"
#import "Coin.h"

// on "init" you need to initialize your instance
bool AnotherWorld::init()
{
#ifdef DEBUG
    m_charaPos = CCPoint(winSize.width/2, winSize.height*0.55);
    
//    scheduleOnce(schedule_selector(AnotherWorld::test), 1.0f);
//    return true;
    
   initFixedValue();


    //背景
    m_BGManager = new BGManager(BGSet_Normal);
    this->addChild(m_BGManager->getBGStageSet()->getBG(), -200);
    this->addChild(m_BGManager->getBGStageSet()->getBGEffect(), -10);
        
    testLayer = CCLayer::create();
    this->addChild(testLayer,10);
    
    parLayer =CCLayer::create();
    this->addChild(parLayer,20);
    
    float menuFontScale = 1.5;
    float btnSpace = 150;
    float btnXpos = 0;
    m_canUpdate =true;
    
    CCMenuItemFont* _enemy = CCMenuItemFont::create("Enemy",
                                                    this,
                                                    menu_selector(AnotherWorld::enemyMode));
    _enemy->setPositionX(btnXpos);
    _enemy->setScale(menuFontScale);
    btnXpos += btnSpace;
    CCMenuItemFont* _boss = CCMenuItemFont::create("Boss",
                                                  this,
                                                  menu_selector(AnotherWorld::bossMode));
    _boss->setPositionX(btnXpos);
    _boss->setScale(menuFontScale);
    btnXpos += btnSpace;
    CCMenuItemFont* _buddy = CCMenuItemFont::create("Buddy",
                                                  this,
                                                  menu_selector(AnotherWorld::buddyMode));
    _buddy->setPositionX(btnXpos);
    _buddy->setScale(menuFontScale);
    btnXpos += btnSpace;
    CCMenuItemFont* _player = CCMenuItemFont::create("Player",
                                                    this,
                                                    menu_selector(AnotherWorld::playerMode));
    _player->setPositionX(btnXpos);
    _player->setScale(menuFontScale);
    btnXpos += btnSpace;

    CCMenuItemFont* btn_title = CCMenuItemFont::create("Re:start");
    btn_title->setPosition(ccp(winSize.width*0.8, -winSize.height*0.8));
    btn_title->setTarget(this, menu_selector(AnotherWorld::exit));
    
//    CCMenuItemFont* btn_reset = CCMenuItemFont::create("scroll reset");
//    btn_reset->setPosition(ccp(winSize.width*0.2, -winSize.height*0.85));
//    btn_reset->setTarget(this, menu_selector(AnotherWorld::resetScroll));
    
    CCMenu* menu_1 = CCMenu::create(_enemy, _boss,_buddy, btn_title,_player, NULL);
    menu_1->setPosition(ccp( 80,winSize.height*0.9 ));
    this->addChild(menu_1);
    
    noDisp = NFNumberLayer::create(0, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    noDisp->setPosition(ccp(80, winSize.height*0.7));
    this->addChild(noDisp);
    
    switch (FIRST_MODE ) {
        case AMS_PLAYER:
            playerMode();
            break;
        case AMS_BUDDY:
            buddyMode();
            break;
        case AMS_BOSS:
            bossMode();
            break;
        case AMS_ENEMY:
            enemyMode();
            break;
    }
    
    scheduleUpdate();
#endif
    return true;
}


void AnotherWorld::exit(){
	GameStartArgs gameStartArgs;
    CCScene* title = GameScene::scene(gameStartArgs);
	CCDirector::sharedDirector()->replaceScene(title);
}

//void AnotherWorld::resetScroll(){
//    gameObjectManager->getDistanceManager()->resetDistance(0);
//}

void AnotherWorld::controllUpdate(){
    m_canUpdate = !m_canUpdate;
    if( m_canUpdate ){
        btn_actionControl->setString("stop action");
    }else{
        btn_actionControl->setString("start action");
    }
}

//-----------------------
// Player..
//-----------------------
void AnotherWorld::playerMode(){
//    GoldTicketDialog::show(99999);
//    return; //kari
    
    m_state = AMS_PLAYER;
    parLayer->removeAllChildrenWithCleanup(true);
    testLayer->removeAllChildrenWithCleanup(true);
    
    playerNo = FIRST_PLAYER_NO;
    shotType = FIRST_PLAYER_SHOT_TYPE;
    evolutionType = FIRST_PLAYER_EVOLUTION_TYPE;
    
    CCMenuItemFont* damage = CCMenuItemFont::create("damage!",
                                                    this,
                                                    menu_selector(AnotherWorld::p_damage));
    CCMenuItemFont* run = CCMenuItemFont::create("run!",
                                                 this,
                                                 menu_selector(AnotherWorld::p_run));
    run->setPositionY(-120);
    
    CCMenuItemFont* fly = CCMenuItemFont::create("Fly!",
                                                 this,
                                                 menu_selector(AnotherWorld::p_fly));
    fly->setPositionY(-240);
    
    CCMenuItemFont* next = CCMenuItemFont::create("next",
                                                  this,
                                                  menu_selector(AnotherWorld::p_next));
    next->setPosition(ccp( -200, 0 ) );
    
    
    CCMenuItemFont* clone = CCMenuItemFont::create("clone...",
                                                   this,
                                                   menu_selector(AnotherWorld::p_clone));
    clone->setPosition(ccp( 200, -200 ) );
    
    CCMenuItemFont* reset = CCMenuItemFont::create("Reset.",
                                                   this,
                                                   menu_selector(AnotherWorld::p_reset));
    reset->setPosition(ccp( -200, 200 ) );
    
    CCMenuItemFont* shotlvup = CCMenuItemFont::create("ShotType Cng.",
                                                  this,
                                                  menu_selector(AnotherWorld::p_shotLvCng));
    shotlvup->setPosition(ccp( 200, 0 ) );
    
    CCMenuItemFont* cstm = CCMenuItemFont::create("change evolution",
                                                  this,
                                                  menu_selector(AnotherWorld::p_cngEvolution));
    cstm->setPosition(ccp( 200, 210 ) );
    
    btn_actionControl = CCMenuItemFont::create("str",
                                                  this,
                                                  menu_selector(AnotherWorld::controllUpdate));
    btn_actionControl->setPosition(ccp(-200, 380));
    btn_actionControl->setColor(ccYELLOW);
    controllUpdate();
    
    CCMenu* menu_1 = CCMenu::create(damage, run, next,clone,reset,shotlvup,cstm,fly,btn_actionControl,NULL);
    menu_1->setPosition(ccp( winSize.width/2,winSize.height*0.4 ));
    testLayer->addChild(menu_1);
    
    dy_rankDisp = NFNumberLayer::create(shotType, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_rankDisp->setPosition(ccp(winSize.width*0.7, winSize.height*0.45));
    testLayer->addChild(dy_rankDisp);
    
    m_shotLayer=NFSpriteCluster::create();
    testLayer->addChild(m_shotLayer, 5);
    
    m_effect=NFSpriteCluster::create();
    m_effect->setPosition(ccpAdd(m_charaPos, ccp(100, 100)));
    testLayer->addChild(m_effect, 5);
    
    dy_costumeDisp = NFNumberLayer::create(evolutionType, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_costumeDisp->setPosition(ccp(winSize.width/2 + 200, winSize.height*0.7));
    testLayer->addChild(dy_costumeDisp);
    
    p_create();
//    testLayer->schedule(schedule_selector(AnotherWorld::p_shotEff),0.5);
    p_shotEff();
    
//    GoldTicketDialog::show(1982);
}

void AnotherWorld::p_create(){
    int shotLevel = shotType*3;
    
    player = Player::create(PlayerCreateData((CharactorType)playerNo,
                            evolutionType,
                            shotLevel));
    if( !player ){
        player = (Player*)Cannon::create(ccp(0,0));
    }else{
        player->getAnimationObj()->setAnimation(PAS_RUN);
        player->setDrawShotLayer(m_shotLayer);
    }
    
    player->setPosition(m_charaPos);
    testLayer->addChild(player);
    noDisp->setNum(playerNo);
    
    dy_rankDisp->setNum(shotType);
    dy_costumeDisp->setNum(evolutionType);
}

void AnotherWorld::p_cngEvolution(){
    evolutionType ++;
    if( evolutionType > 1 ){
        evolutionType = 0;
    }
    player->removeFromParentAndCleanup(true);
    p_create();
}
void AnotherWorld::p_next(){
    playerNo ++;
    if( playerNo > CharactorType_Brown ){
        playerNo = CharactorType_Normal;
    }
    else if( playerNo > CharactorType_Assault ){
        playerNo = CharactorType_Brown;
    }
    
    player->removeFromParentAndCleanup(true);
    p_create();
}

void AnotherWorld::p_damage(){
    if(player->getAnimationObj() !=NULL ){
        playSoundEffect(g_SEName_player_death);
        player->getAnimationObj()->setAnimation(PAS_DAMAGE);
    }
}

void AnotherWorld::p_run(){
    if(player->getAnimationObj() !=NULL )
    player->getAnimationObj()->setAnimation(PAS_RUN);
}

void AnotherWorld::p_fly(){
    if(player->getAnimationObj() !=NULL )
        player->getAnimationObj()->setAnimation(PAS_FRYING);
}

void AnotherWorld::p_clone(){
    if(player->getAnimationObj() !=NULL ){
        Cannon* clone = player->createClone();
        clone->setPositionY(player->getPositionY());
        clone->setPositionX(player->getPositionX()+150);
        clone->setOpacity(128);
        testLayer->addChild(clone);
    }
}

void AnotherWorld::p_reset(){
    player->removeFromParentAndCleanup(true);
    p_create();
}

void AnotherWorld::p_shotLvCng(){
    shotType ++;
    if( shotType > PLAYER_MAX_SHOT_STYLE_NUM ){
        shotType = 1;
    }
    if( player !=NULL )player->removeFromParentAndCleanup(true);
    p_create();
}
#import "EffectFactory.h"
void AnotherWorld::p_shotEff(){
    if(!player->getAnimationObj()) return;
    
    if(m_state != AMS_PLAYER){
        return;
    }
    switch (playerNo) {
        case CharactorType_Normal:
            EffectFactory::createSlashEffectAnimation_Normal(m_effect);
            break;
        case CharactorType_Kunoichi:
            EffectFactory::createSlashEffectAnimation_Kunoichi(m_effect);
            break;
            
        case CharactorType_Musasabi:
            EffectFactory::createSlashEffectAnimation_Musasabi(m_effect);
            break;
            
        case CharactorType_Revive:
            EffectFactory::createSlashEffectAnimation_Revive(m_effect);
            break;
            
        case CharactorType_Assault:
            EffectFactory::createSlashEffectAnimation_Assult(m_effect);
            break;
        case CharactorType_Brown:
            EffectFactory::createSlashEffectAnimation_Brown(m_effect);
            break;
        default:
            break;
    }
    
    scheduleOnce(schedule_selector(AnotherWorld::p_shotEff), PARTICLE_REMOVE_TIME);

}
//void AnotherWorld::p_shottEff2(){
//    scheduleOnce(schedule_selector(AnotherWorld::p_shotEff), 0.5);
//}

//-----------------------
// budDY..
//----------------------
void AnotherWorld::buddyMode(){
    m_state = AMS_BUDDY;
    testLayer->removeAllChildrenWithCleanup(true);
    
    buddyRank = FIRST_BUDDY_NO;
    buddyAttr = FIRST_ATTR_NO;
    buddyConsumeType = FIRST_BUDDY_COSTUME_NO;
    kakudaiRitu=1;
    buddyLevel = FIRST_BUDDY_LV;
    
    CCMenuItemFont* damage = CCMenuItemFont::create("damage!",
                                                    this,
                                                    menu_selector(AnotherWorld::dy_damage));
    CCMenuItemFont* run = CCMenuItemFont::create("run!",
                                                    this,
                                                    menu_selector(AnotherWorld::dy_run));
    run->setPositionY(-120);
    CCMenuItemFont* shot = CCMenuItemFont::create("shot!",
                                                  this,
                                                  menu_selector(AnotherWorld::dy_shot));
    shot->setPositionY(-240);
    
    CCMenuItemFont* next = CCMenuItemFont::create("change Attr",
                                                  this,
                                                  menu_selector(AnotherWorld::dy_next));
    next->setPosition(ccp( -200, 0 ) );
    
    CCMenuItemFont* rank = CCMenuItemFont::create("change rank",
                                                  this,
                                                  menu_selector(AnotherWorld::dy_cangeRank));
    rank->setPosition(ccp( -200, -100 ) );
    
    CCMenuItemFont* cstm = CCMenuItemFont::create("change costume",
                                                  this,
                                                  menu_selector(AnotherWorld::dy_cangeCostume));
    cstm->setPosition(ccp( -200, -200 ) );
    
    CCMenuItemFont* clone = CCMenuItemFont::create("clone...",
                                                 this,
                                                 menu_selector(AnotherWorld::dy_clone));
    clone->setPosition(ccp( 200, -200 ) );
    
    CCMenuItemFont* kakudai = CCMenuItemFont::create("kakudai",
                                                   this,
                                                   menu_selector(AnotherWorld::dy_kakudai));
    kakudai->setPosition(ccp( 200, 0 ) );
    
    btn_actionControl = CCMenuItemFont::create("action contr",
                                                this,
                                                menu_selector(AnotherWorld::controllUpdate));
    btn_actionControl->setPosition(ccp(200, 100));
    btn_actionControl->setColor(ccYELLOW);
    controllUpdate();
    
    CCMenuItemFont* shotlvup = CCMenuItemFont::create("change ShotLv",
                                                      this,
                                                      menu_selector(AnotherWorld::dy_shotLvCng));
    shotlvup->setPosition(ccp( -200, 100 ) );
    
    CCMenu* menu_1 = CCMenu::create(damage, run, shot, next,rank,clone,cstm,kakudai,shotlvup,btn_actionControl, NULL);
    menu_1->setPosition(ccp( winSize.width/2,winSize.height*0.4 ));
    testLayer->addChild(menu_1);
    
    dy_rankDisp = NFNumberLayer::create(buddyRank, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_rankDisp->setPosition(ccp(180, winSize.height*0.7));
    testLayer->addChild(dy_rankDisp);
    
    dy_costumeDisp = NFNumberLayer::create(buddyConsumeType, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_costumeDisp->setPosition(ccp(winSize.width/2 + 200, winSize.height*0.7));
    testLayer->addChild(dy_costumeDisp);
    
    dy_LvDisp = NFNumberLayer::create(buddyLevel, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_LvDisp->setPosition(ccp(noDisp->getPositionX(), noDisp->getPositionY()-120));
    testLayer->addChild(dy_LvDisp);
    
    
    NFLabelTTF* attrText= NFLabelTTF::create("attr", FONT_W6, 32);
    attrText->setPosition(ccp( noDisp->getPositionX(), noDisp->getPositionY()+50));
    testLayer->addChild(attrText);
    
    NFLabelTTF* rankText= NFLabelTTF::create("rank", FONT_W6, 32);
    rankText->setPosition(ccp( dy_rankDisp->getPositionX(), dy_rankDisp->getPositionY()+50));
    testLayer->addChild(rankText);
    
    NFLabelTTF* cosText= NFLabelTTF::create("costume", FONT_W6, 32);
    cosText->setPosition(ccp( dy_costumeDisp->getPositionX(), dy_costumeDisp->getPositionY()+50));
    testLayer->addChild(cosText);
    
    NFLabelTTF* lvText= NFLabelTTF::create("Lv", FONT_W6, 32);
    lvText->setPosition(ccp( dy_LvDisp->getPositionX(), dy_LvDisp->getPositionY()+50));
    testLayer->addChild(lvText);
    
    m_shotLayer=NFSpriteCluster::create();
    testLayer->addChild(m_shotLayer, 5);
    
    dy_create();
}
#import "BuddyCluster.h"
void AnotherWorld::dy_create(){
    noDisp->setNum(buddyAttr);
    dy_rankDisp->setNum(buddyRank);
    dy_LvDisp->setNum(buddyLevel);
    
    bool isNone = false;
    if( checkValidityBuddy(buddyAttr, buddyRank, buddyLevel, buddyConsumeType) ){
        buddy = createBuddyEntity(buddyAttr, buddyRank, buddyLevel, buddyConsumeType, m_charaPos);
        
        if( buddyRank < 4 &&  buddyAttr <= Splush ){
            buddy->setIncudation(true);
            BuddyRescueSprite* sprite = BuddyRescueSprite::create(buddy, ccp( 0, 0), 0);
            testLayer->addChild(sprite);
        }
        
    }else{
        buddy = (Buddy*)Cannon::create(m_charaPos);
        NFLabelTTF* text= NFLabelTTF::create("none.\nchange attr or\nrank or costume.", FONT_W6, 32);
        text->setAnchorPoint(ccp(0.5, 1));
        buddy->addChild(text, 100);
        text->setColor(ccRED);
        isNone = true;
    }
    testLayer->addChild(buddy);
    
    if(buddy->getAnimationObj() !=NULL && !isNone )
        buddy->getAnimationObj()->setAnimation(BDAS_RUN);
    
    buddy->setDrawShotLayer(m_shotLayer);
}

void AnotherWorld::dy_next(){
    buddyAttr ++;
    if( buddyAttr > MaxBuddyAttr-1 ){
       buddyAttr = Normal;
    }
    if( buddy !=NULL )buddy->removeFromParentAndCleanup(true);
    dy_create();
}

void AnotherWorld::dy_cangeRank(){
    buddyRank ++;
    if( buddyRank > MAX_BUDDY_RANK ){
        buddyRank = 1;
    }
    if( buddy !=NULL )buddy->removeFromParentAndCleanup(true);
    dy_create();
}

void AnotherWorld::dy_damage(){
    if(buddy->getAnimationObj() !=NULL )
    buddy->getAnimationObj()->setAnimation(BDAS_DAMAGE);
}

void AnotherWorld::dy_run(){
    if(buddy->getAnimationObj() !=NULL )
    buddy->getAnimationObj()->setAnimation(BDAS_RUN);

}

void AnotherWorld::dy_shot(){
    if(buddy->getAnimationObj() !=NULL )
    buddy->getAnimationObj()->setAnimation(BDAS_SHOT);
}
void AnotherWorld::dy_clone(){
    Cannon* clone = buddy->createClone();
    clone->setPositionY(buddy->getPositionY());
    clone->setPositionX(buddy->getPositionX()+150);
    clone->setOpacity(128);
    testLayer->addChild(clone);
}

void AnotherWorld::dy_cangeCostume(){
    buddyConsumeType ++;
    if( buddyConsumeType >= kCostumeTypeMax ){
        if( buddyConsumeType < BUDDY_METAL_COSTUME_TYPE_SILVER ){
            buddyConsumeType = BUDDY_METAL_COSTUME_TYPE_SILVER;
        }
        else if( buddyConsumeType > BUDDY_METAL_COSTUME_TYPE_GOLD ){
            buddyConsumeType = kCostumBasic;
        }
    }
    if( buddy !=NULL )buddy->removeFromParentAndCleanup(true);
    dy_costumeDisp->setNum(buddyConsumeType);
    
    
    dy_create();
}

void AnotherWorld::dy_kakudai(){
    kakudaiRitu ++;
    if( kakudaiRitu > 3 ){
        kakudaiRitu = 1;
    }
    buddy->setScale(kakudaiRitu);
}

void AnotherWorld::dy_shotLvCng(){
    buddyLevel += 10;
    if( buddyLevel > getBuddyMaxLevel(buddyAttr, buddyRank, buddyConsumeType) ){
        buddyLevel = 1;
    }
    if( buddy !=NULL )buddy->removeFromParentAndCleanup(true);
    dy_create();
}

//-----------------------
// Boss..
//-----------------------
void AnotherWorld::bossMode(){
    m_state = AMS_BOSS;
    testLayer->removeAllChildrenWithCleanup(true);
    
    enemyNo = FIRAST_BOSS_NO;
    CCMenuItemFont* damage = CCMenuItemFont::create("damage!",
                                                    this,
                                                    menu_selector(AnotherWorld::b_damage));
    CCMenuItemFont* attack = CCMenuItemFont::create("attack!",
                                                    this,
                                                    menu_selector(AnotherWorld::b_attack));
    attack->setPositionY(-120);
    CCMenuItemFont* back = CCMenuItemFont::create("back!",
                                                    this,
                                                    menu_selector(AnotherWorld::b_back));
    back->setPositionY(-240);
    
    CCMenuItemFont* wait = CCMenuItemFont::create("wait.",
                                                  this,
                                                  menu_selector(AnotherWorld::b_wait));
    wait->setPositionY(-360);
    
    CCMenuItemFont* next = CCMenuItemFont::create("next",
                                                  this,
                                                  menu_selector(AnotherWorld::b_next));
    next->setPosition(ccp( -200, 0 ) );
    CCMenuItemFont* death = CCMenuItemFont::create("Death...",
                                                   this,
                                                   menu_selector(AnotherWorld::b_death));
    death->setPosition(ccp( -200, -100 ) );
    
    CCMenuItemFont* freeze = CCMenuItemFont::create("freeze!",
                                                    this,
                                                    menu_selector(AnotherWorld::e_freeze));
    freeze->setPosition(ccp( 200, 0 ) );
    CCMenuItemFont* spark = CCMenuItemFont::create("spark!",
                                                   this,
                                                   menu_selector(AnotherWorld::e_thunder));
    spark->setPosition(ccp( 200, -100 ) );
    CCMenuItemFont* bom = CCMenuItemFont::create("bom!",
                                                 this,
                                                 menu_selector(AnotherWorld::e_fire));
    bom->setPosition(ccp( 200, -200 ) );
    CCMenuItemFont* reset = CCMenuItemFont::create("Reset.",
                                                   this,
                                                   menu_selector(AnotherWorld::b_reset));
    reset->setPosition(ccp( -200, 200 ) );
    
    CCMenuItemFont* shot = CCMenuItemFont::create("shot!!!",
                                                   this,
                                                   menu_selector(AnotherWorld::b_shot));
    shot->setPosition(ccp( -200, -200 ) );
    CCMenuItemFont* action = CCMenuItemFont::create("Action!!",
                                                    this,
                                                    menu_selector(AnotherWorld::b_action));
    action->setPosition(ccp( 200, 200 ) );
    
    CCMenuItemFont* exit = CCMenuItemFont::create("Exit.",
                                                    this,
                                                    menu_selector(AnotherWorld::b_exit));
    exit->setPosition(ccp( 200, 300 ) );
    
    CCMenu* menu_1 = CCMenu::create(damage, attack,back,wait,next,death,freeze,spark,bom,reset,shot, action,exit,NULL);
    menu_1->setPosition(ccp( winSize.width/2,winSize.height*0.4 ));
    testLayer->addChild(menu_1);
    
    b_shotLayer = NFSpriteCluster::create();
    testLayer->addChild(b_shotLayer, 100);
    
    b_create();
}

void AnotherWorld::b_create(){
    
    if( enemyNo < kBossTypesMax ){
        enemy = Boss::create((BossTypes)enemyNo, enemyNo);
        enemy->setPosition(m_charaPos);
        testLayer->addChild(enemy);
        noDisp->setNum(enemyNo);
        enemy->getAnimationObj()->setFunc(this, callfunc_selector(AnotherWorld::b_wait));
        ((Boss*)enemy)->setShotParent(b_shotLayer);
        
        //        if (enemyNo == 6) {
        //            ((PhantomBoss*)enemy)->appearanceProduction();
        //        }
        
    }
    else if( enemyNo < kRBossTypesMax ){
        if( enemyNo < kRBossAny ){
            enemyNo = kRBossType1_ThunderDragon;
        }
        
        RaidBossCreateData _data;
        _data.raidBossId = enemyNo; // レイドボスID
        _data.attr = Thunder; // レイドボスの属性(見た目)
        _data.lastHp = 500; // レイドボスの残りHP
        _data.maxHp = 500; // レイドボスの最大HP
        _data.bulletHp = 10; // レイドボスの弾HP
        _data.score = 5; // レイドボス スコア
        _data.bulletScore = 0; // レイドボス 弾スコア
        _data.dropCnt = 20; // ドロップ数。内容はランダム
        _data.weakBuddyType = Thunder; // 特攻仲間タイプ
        _data.weakAtk = 50; // 特攻仲間の攻撃力倍率。100分率。
        
        enemy = Boss::createRaidBoss(_data);
        enemy->setPositionY(770);
        //        enemy->setPosition(m_charaPos);
        testLayer->addChild(enemy);
        noDisp->setNum(enemyNo);
        enemy->getAnimationObj()->setFunc(this, callfunc_selector(AnotherWorld::b_wait));
        ((Boss*)enemy)->setShotParent(b_shotLayer);
    }else{
        enemyNo = 1;
        b_create();
    }
    
//    enemy->setColor(ccc3(204,100, 255));
}

void AnotherWorld::b_wait(){
    ((Boss*)enemy)->getAnimationObj()->setAnimation(EAS_WAIT);
}
void AnotherWorld::b_damage(){
    ((Boss*)enemy)->getAnimationObj()->setAnimation(EAS_DAMAGE);
}
void AnotherWorld::b_attack(){
    ((Boss*)enemy)->getAnimationObj()->setAnimation(EAS_ATTACK);
    if( enemyNo == 5 ){
//        ((Boss*)enemy)->schedule(schedule_selector(Boss::debugAttack), 0.1);
//        ((Boss*)enemy)->schedule(schedule_selector(Boss::debugAttack), 0.1, 80, 0);
    }
}
void AnotherWorld::b_back(){
    ((Boss*)enemy)->getAnimationObj()->setAnimation(EAS_BACK);
}
void AnotherWorld::b_next(){
    enemyNo ++;
    enemy->removeFromParentAndCleanup(true);
    b_create();
}
void AnotherWorld::b_death(){
    if( enemy->isDead() ){
        enemy->removeFromParentAndCleanup(true);
        b_create();
    }
    enemy->explosion();
}
void AnotherWorld::b_reset(){
    enemy->removeFromParentAndCleanup(true);
    b_create();
}

void AnotherWorld::b_shot(){
    ((Boss*)enemy)->debugShot();
//    ((Boss*)enemy)->schedule(schedule_selector(Boss::debugShot), 0.01);
}

void AnotherWorld::b_action(){
    enemy->scheduleUpdate();
}

void AnotherWorld::b_exit(){
    ((Boss*)enemy)->doExit();
}

//-----------------------
// Enemy..
//-----------------------
void AnotherWorld::enemyMode(){
    m_state = AMS_ENEMY;
    testLayer->removeAllChildrenWithCleanup(true);
    
    enemyNo = 1;
    enemyType = 1;
    
    dy_costumeDisp = NFNumberLayer::create(evolutionType, "num_distance_m_01.png", 36.0, 44.0, -8, 22.0, kNumAlignLeft, ccp(0.5, 0.5));
    dy_costumeDisp->setPosition(ccp(winSize.width/2 + 200, winSize.height*0.7));
    testLayer->addChild(dy_costumeDisp);
    
    CCMenuItemFont* damage = CCMenuItemFont::create("damage!",
                                                    this,
                                                    menu_selector(AnotherWorld::e_damage));
    CCMenuItemFont* freeze = CCMenuItemFont::create("freeze!",
                                                    this,
                                                    menu_selector(AnotherWorld::e_freeze));
    freeze->setPositionY(-120);
    
    CCMenuItemFont* spark = CCMenuItemFont::create("spark!",
                                                    this,
                                                    menu_selector(AnotherWorld::e_thunder));
    spark->setPositionY(-240);
    CCMenuItemFont* bom = CCMenuItemFont::create("bom!",
                                                   this,
                                                   menu_selector(AnotherWorld::e_fire));
    bom->setPositionY(-360);
    
    CCMenuItemFont* next = CCMenuItemFont::create("next",
                                                    this,
                                                    menu_selector(AnotherWorld::e_next));
    next->setPosition(ccp( -100, -100 ) );
    CCMenuItemFont* death = CCMenuItemFont::create("Death...",
                                                  this,
                                                  menu_selector(AnotherWorld::e_death));
    death->setPosition(ccp( -100, -200 ) );
    CCMenuItemFont* reset = CCMenuItemFont::create("Reset.",
                                                   this,
                                                   menu_selector(AnotherWorld::e_reset));
    reset->setPosition(ccp( -200, 200 ) );
    CCMenuItemFont* cangeType = CCMenuItemFont::create("Cange Type",
                                                      this,
                                                      menu_selector(AnotherWorld::e_cangeType));
    cangeType->setPosition(ccp( 200, 0 ) );

    
    CCMenu* menu_1 = CCMenu::create(damage, next,death,freeze,reset,spark,bom,cangeType,NULL);
    menu_1->setPosition(ccp( winSize.width/2,winSize.height*0.4 ));
    testLayer->addChild(menu_1);
    
    e_create();
}
#import "Beam.h"
void AnotherWorld::e_freeze(){
    enemy->hasHit(WaterBeam::create("bld_frc01.png" ,0, 2));
}

void AnotherWorld::e_cangeType(){
    enemyType ++;
    if( enemyType > 2 ){
        enemyType = 1;
    }
    if( enemy !=NULL )enemy->removeFromParentAndCleanup(true);
    e_create();
}

void AnotherWorld::e_create(){
    if( enemyType == 2 ){
        enemy= StayEnemy::create(enemyNo, m_charaPos);
    }else{
        enemy = NormalEnemy::create(enemyNo,m_charaPos);
    }
    
    testLayer->addChild(enemy);
    noDisp->setNum(enemyNo);
}

void AnotherWorld::e_damage(){
    if(enemyNo == ENEMY_NO_MAX+1  ) return;
    enemy->getAnimationObj()->setAnimation(EAS_DAMAGE);
}
void AnotherWorld::e_death(){
    if( enemy->isDead() ){
        enemy->removeFromParentAndCleanup(true);
        e_create();
    }
    enemy->explosion();
}
void AnotherWorld::e_next(){
    enemyNo ++;
    if( enemyNo > ENEMY_NO_MAX ){ //ボムまで
        enemyNo = 1;
    }
    
    enemy->removeFromParentAndCleanup(true);
    e_create();
}

void AnotherWorld::e_reset(){
    enemy->removeFromParentAndCleanup(true);
    e_create();
}
void AnotherWorld::e_thunder(){
    ThunderBuddy* buddy = ThunderBuddy::create(ccp( m_charaPos.x, 0 ), 1, 1);
    Thunderbolt* thunder = Thunderbolt::create(buddy
                                    ,10
                                    ,kCostumBasic
                                    ,1);
    enemy->attackFromThunder(thunder);
}

void AnotherWorld::e_fire(){
    if( m_state == AMS_ENEMY ){
        EffectFactory::createExplosionAnimation(parLayer, this, callfunc_selector(AnotherWorld::e_death));
    }
    else if( m_state == AMS_BOSS ){
        EffectFactory::createExplosionAnimation(parLayer, this, callfunc_selector(AnotherWorld::b_death));
    }
    
}
#import "EffectFactory.h"
#import "Block.h"
#import "CCNodeUtil.h"
void AnotherWorld::update(float dt){
#ifdef DEBUG
    m_BGManager->update(dt);
    if( m_canUpdate ){
        switch (m_state) {
            case AMS_PLAYER:
                if(player->getAnimationObj() != NULL
                   && player->getAnimationObj()->getState() == PAS_RUN ){
                    player->shot(dt);
                }
                break;
            case AMS_BUDDY:
                if((buddy->getAnimationObj() != NULL
                   && !buddy->isImitation())
                   || buddy->getAttribute() == Mecha
                   ){
                    buddy->shot(dt);
                    
                    //thunder 特殊なショット
                    if( buddy->getAttribute() == Thunder ){
                        ThunderBuddy* tBuddy = (ThunderBuddy*)buddy;
                        if( tBuddy->canShot()){
                            CCPoint enepos = ccp( 0, m_charaPos.y + 200);
                            int interval = winSize.width*0.5;
                            for (int i = 0; i < tBuddy->getThunderNum(); i++) {
                                enepos.x = rand()%interval+g_ranePosX[1];
                                tBuddy->getThunderbolt()->hitToTarget(enepos);
                                EffectFactory::createShock(m_shotLayer, enepos);
                                playSoundEffect(g_SEName_shot_thunder);
                                tBuddy->resetShotTime();
                            }
                        }
                    }
                    
                    //mecha 特殊なショット
                    if( buddy->getAttribute() == Mecha ){
                        MechaBuddy* mBuddy = (MechaBuddy*)buddy;
                        if( buddy->canShot() ){
                            int cnt=0;
                            if( buddy->getRank() == 5 ){
                                cnt = 1;
                            }else if(buddy->getRank() == 6){
                                cnt = 2;
                            }
                            int interval = winSize.width*0.5;
                            for(int i = 0 ; i < cnt ; i++){
                                CCPoint enepos = ccp( 0, winSize.height*0.5 - 50);
                                enepos.x = rand()%interval+g_ranePosX[1];
                                enepos.y = rand()%interval;
                                
                                Block* block = Block::create(enepos, 1);
                                testLayer->addChild(block, -100);
                                block->runAction(
                                                 CCSequence::create(
                                                                    CCDelayTime::create(2.0)
                                                                    ,CCNodeUtil::createRemoveAction()
                                                                    ,NULL
                                                                    )
                                                 );
                                mBuddy->startAttack(block);
                            }
                            if(buddy->getRank() == 6){
                                mBuddy->changeLR();
                            }
                            mBuddy->resetShotTime();
                        }
                        mBuddy->updatePunches(dt);
                    }
                    
                }
                break;
                
            default:
                break;
        }
    }
#endif
}

void AnotherWorld::draw(){
    glLineWidth(2.0f);
    ccDrawColor4F(0, 1, 1, 1);
    
    CCPoint lpt1 = ccp(winSize.width/2, 0);
    CCPoint lpt2 = ccp(winSize.width/2, winSize.height);
    ccDrawLine(lpt1, lpt2);
    
    CCPoint lpt3 = ccp(0, m_charaPos.y);
    CCPoint lpt4 = ccp(winSize.width, m_charaPos.y);
    ccDrawLine(lpt3, lpt4);
}
