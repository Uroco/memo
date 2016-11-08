//
//  ActiveBuddyFormationLayer.cpp
//  NinjaFlight
//

#import "ActiveBuddyFormationLayer.h"
#import "Buddy.h"
#import "NFNumberLayer.h"
#import "UserBuddyData.h"
#import "User.h"
#import "CharaListTable.h"
#import "NinjaPowerInfo.h"

/*-----------------------------
 *  ActiveBuddyFrame
 ------------------------------*/
ActiveBuddyFrame::ActiveBuddyFrame() {
    buddyNo = BUDDY_INVALID_NO;
    m_isSelected=false;
    buddyNo = -1;
    buddyRank = -1;
    buddyLevel = -1;
    m_canDragged = true;
    m_frameName = "btn_change_buddy_frame_01.png";
}

ActiveBuddyFrame* ActiveBuddyFrame::create(int _positionNo, bool _isLocked){
    ActiveBuddyFrame* info = new ActiveBuddyFrame();
    info->autorelease();
    
    info->m_positionNo = _positionNo;
    info->m_isLocked = _isLocked;
    if(info->init()){
        return info;
    }
    CC_SAFE_DELETE(info);
    return NULL;
}

bool ActiveBuddyFrame::init(){
    InputCharactorFrame::init();
    
	if(isLocked()) {
		initLocked();
	} else {
        initOpened();
	}
    
    return true;
}

int ActiveBuddyFrame::getUnlockLevel(int _positionNo){
    return getBuddyUnlockLevel(m_positionNo);
}

void ActiveBuddyFrame::initOpened(){
    InputCharactorFrame::initOpened();
    
    m_profileSprite = CharaProfileSprite::create();
    this->addChild(m_profileSprite);
    
    m_profileSprite->setVisible(false);
}
void ActiveBuddyFrame::selectBuddy(UserBuddyData *userBuddyData){
    if( !userBuddyData ){
        NFLog("userBuddyData null.");
        return;
    }
    
    buddyNo = userBuddyData->no;
    m_isSelected=true;
    
    m_profileSprite->showBuddy(userBuddyData->attr, userBuddyData->rank, userBuddyData->level, userBuddyData->cstmtype);
    
    buddyRank = userBuddyData->rank;
    buddyLevel = userBuddyData->level;
    
    m_profileSprite->setVisible(true);

    statusBg->setVisible(false);
    changeFrameImage();
}

void ActiveBuddyFrame::deselectBuddy(bool _blindBg){
    m_isSelected=false;
    buddyNo = -1;
    buddyRank = -1;
    buddyLevel = -1;
    
    if( !isLocked() ){
        m_profileSprite->setVisible(false);
        statusBg->setVisible(true);
        blink(_blindBg);
    }
    changeFrameImage();
}
int ActiveBuddyFrame::getNinjaPower(){
    return m_profileSprite->isVisible() ? calcNinjaPower(buddyRank, buddyLevel) : 0;
}

/*-----------------------------
 *
 *  ActiveBuddyFormationLayer
 *
 ------------------------------*/
ActiveBuddyFormationLayer::ActiveBuddyFormationLayer(){
    selectedActiveBuddyArray = new CCArray();
    selectedActiveBuddyArray->retain();
    
    isBlindStatusBg = true;
    selectedActiveBuddyFrame = NULL;
    delegate =NULL;
    m_draggedIconParent =NULL;
    draggingBuddyPointerIcon =NULL;
}

ActiveBuddyFormationLayer::~ActiveBuddyFormationLayer(){
    selectedActiveBuddyArray->release();
    saveBuddyData();
}

CCPoint ActiveBuddyFormationLayer::getBuddyPosition(int position) {
	switch (position) {
		case 0:
			return ccp(226, winHeight - 216);
		case 1:
			return ccp(414.0, winHeight - 216.0);
		case 2:
			return ccp(132.0, winHeight - 372.0);
		case 3:
			return ccp(508, winHeight - 372.0);
		case 4:
			return ccp(320.0, winHeight - 372.0);
	}
	return ccp(0, 0);
}

bool ActiveBuddyFormationLayer::init(){
    CCLayer::init();
    
    m_inputFrameMenu = InputFrameMenu::create(this);
    this->addChild(m_inputFrameMenu);
    
    for(int i = 0; i < 5; i++) {
		selectedActiveBuddyArray->addObject(createBuddySelectFrame(i));
	}
    
    CCObject* _activeBuddyInfo;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
		if(!activeBuddyInfo->isLocked()) {
            this->reorderChild(activeBuddyInfo, 2);
		}
	}
    
    //点滅する仲間シルエットアイコン
    schedule(schedule_selector(ActiveBuddyFormationLayer::blinkBuddyBg), 0.6);
    
    //忍者パワー
    m_mineNinjaPower = NinjaPowerInfo::create(ccp(552.0, winHeight - 180.0),
                                            ccp(555.0, winHeight - 249.0));
    this->addChild(m_mineNinjaPower);
    
    return true;
}

ActiveBuddyFrame* ActiveBuddyFormationLayer::createFrame(int position, int isLocked){
    return ActiveBuddyFrame::create(position, isLocked);
}

ActiveBuddyFrame* ActiveBuddyFormationLayer::createBuddySelectFrame(int position) {
	User* user = User::getInstance();
	bool isLocked = getBuddyUnlockLevel(position) > user->getLevel();
    
	ActiveBuddyFrame* activeBuddyInfo = createFrame(position, isLocked);
    CCPoint basePosition = getBuddyPosition(position);
    activeBuddyInfo->setPosition(basePosition);
    this->addChild(activeBuddyInfo);
    
    //フレームのプライオリティをそろえるため、別add
    CCSprite* frame = activeBuddyInfo->getFrame();
    if( frame ){
        frame->setPosition(ccpAdd(frame->getPosition(), basePosition));
        this->addChild(frame, -5);
        
        InputFrameMenuItem* itemMenu = InputFrameMenuItem::create(activeBuddyInfo);
        itemMenu->setPosition(frame->getPosition());
        m_inputFrameMenu->addChild(itemMenu);
    }
    
	return activeBuddyInfo;
}

void ActiveBuddyFormationLayer::saveBuddyData() {
    User* user = User::getInstance();
	CCObject* _activeBuddyInfo;
	int counter = 0;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
        int buddyNo = activeBuddyInfo->getBuddyNo();
		if( isValidBuddyNo(buddyNo) ) {
			UserBuddyData* activeBuddyData = user->getBuddy(buddyNo);
            if( activeBuddyData ){
                user->setActiveBuddy(counter, activeBuddyData->no);
            }
		} else {
			user->unsetActiveBuddy(counter);
		}
        
		counter++;
	}
}
void ActiveBuddyFormationLayer::blinkBuddyBg() {
	isBlindStatusBg = !isBlindStatusBg;
    
	CCObject* _activeBuddyInfo;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
        activeBuddyInfo->blink(isBlindStatusBg);
	}
}
ActiveBuddyFrame* ActiveBuddyFormationLayer::getSelectedActiveBuddyFrameByBuddyNo(int buddyNo){
    CCObject* _activeBuddyInfo;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
        if(activeBuddyInfo->getBuddyNo() == buddyNo) {
            return activeBuddyInfo;
        }
	}
    return NULL;
}
void ActiveBuddyFormationLayer::initActiveBuddy() {
    int idx = 0;
	User* user = User::getInstance();
    
    for(int i = idx; i < 5; i++) {
        UserBuddyData* activeUserBuddyData = user->getActiveBuddy(i);
        if(!activeUserBuddyData) {
            defect(i);
		}else{
            join(i, activeUserBuddyData);
        }
    }
}

int ActiveBuddyFormationLayer::getSelectedBuddyCnt(int _buddyNo){
    int cnt = 0;
    CCObject* _activeBuddyInfo;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
        if(activeBuddyInfo->getBuddyNo() == _buddyNo) {
            cnt ++;
            if( !getSubBuddyKeyByNo(_buddyNo) ) break;
        }
	}
    return cnt;
}

void ActiveBuddyFormationLayer::touchBegan(cocos2d::CCPoint location, InputCharactorFrame *_pushFrame){
    selectedActiveBuddyFrame = (ActiveBuddyFrame*)_pushFrame;
}


ActiveBuddyFrame* ActiveBuddyFormationLayer::getSelectedActiveBuddyFrame(CCPoint location) {
	CCObject* _activeBuddyInfo;
	CCARRAY_FOREACH(selectedActiveBuddyArray, _activeBuddyInfo) {
		ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)_activeBuddyInfo;
		if(!activeBuddyInfo->isLocked()
           && activeBuddyInfo->isTouched(location)){
            return activeBuddyInfo;
		}
	}
	return NULL;
}

CCSprite* ActiveBuddyFormationLayer::createDraggedIcon(int buddyNo){
    UserBuddyData* userBuddyData = User::getInstance()->getBuddy(buddyNo);
    CCSprite* icon = createBuddyIcon(m, userBuddyData);
    icon->setAnchorPoint(ccp(0.5, 0.5));
    
    return icon;
}

void ActiveBuddyFormationLayer::touchMoved(cocos2d::CCPoint location){
    if( !draggingBuddyPointerIcon ){
        int buddyNo = selectedActiveBuddyFrame->getBuddyNo();
        if( !isValidBuddyNo(buddyNo) ) return;
        
        draggingBuddyPointerIcon = createDraggedIcon(buddyNo);
        if( !m_draggedIconParent  ){
            m_draggedIconParent = getParent();
        }
        m_draggedIconParent->addChild(draggingBuddyPointerIcon, 1000);
        
    }
    draggingBuddyPointerIcon->setPosition(location);
}

void ActiveBuddyFormationLayer::touchEnded(cocos2d::CCPoint location, InputCharactorFrame* _activateFrame){
    ActiveBuddyFrame* touchEndActiveBuddyFrame = (ActiveBuddyFrame*)_activateFrame;
    
    if( touchEndActiveBuddyFrame ){
        if(touchEndActiveBuddyFrame->getPositionNo()
           == selectedActiveBuddyFrame->getPositionNo()){
            //            //セットした仲間をタップ
            tapFrame(selectedActiveBuddyFrame);
            
        } else { // 場所入れ替え
            exchange(selectedActiveBuddyFrame, touchEndActiveBuddyFrame);
        }
    }else{
        //ドラッグしてエリア外に行ったとき
        draggedOut(selectedActiveBuddyFrame);
    }
    
    touchFinish();
}

void ActiveBuddyFormationLayer::touchFinish(){
    if(draggingBuddyPointerIcon) {  //ドラッグアイコン削除
        draggingBuddyPointerIcon->removeFromParentAndCleanup(true);
        draggingBuddyPointerIcon = NULL;
    }
    selectedActiveBuddyFrame = NULL;
    
    if( isChangedActiveBuddy){  //忍者編成変更されていたら変更する
        resetActiveNinjaPower();
    }
    isChangedActiveBuddy = false;
}

void ActiveBuddyFormationLayer::tapFrame(ActiveBuddyFrame *_frame){
    //セットした仲間をタップ　選択削除する
    playSoundEffect("LN_ninjase016.m4a");
    defect(_frame->getPositionNo());
}
// 場所入れ替え
void ActiveBuddyFormationLayer::exchange(ActiveBuddyFrame *selectFrame, ActiveBuddyFrame *touchFrame){
    playSoundEffect("LN_ninjase015.m4a");
    
    UserBuddyData* activeBuddy1 = NULL;
    UserBuddyData* activeBuddy2 = NULL;
    int activeBuddyPosition1 = -1;
    int activeBuddyPosition2 = -1;
    User* user = User::getInstance();
    
    activeBuddyPosition1 = selectFrame->getPositionNo();
    activeBuddyPosition2 = touchFrame->getPositionNo();
    activeBuddy1 = user->getBuddy(selectFrame->getBuddyNo());
    activeBuddy2 = user->getBuddy(touchFrame->getBuddyNo());
    
    if( activeBuddy1 ) defect(activeBuddyPosition1);
    if( activeBuddy2 ) defect(activeBuddyPosition2);
    
    if( activeBuddy1 )join(activeBuddyPosition2, activeBuddy1);
    if( activeBuddy2 )join(activeBuddyPosition1, activeBuddy2);
}

void ActiveBuddyFormationLayer::draggedOut(ActiveBuddyFrame *_frame){
    //ドラッグしてエリア外に行ったとき 選択削除
    playSoundEffect("LN_ninjase016.m4a");
    defect(selectedActiveBuddyFrame->getPositionNo());
}

void ActiveBuddyFormationLayer::replace(int buddyPosition, UserBuddyData *userBuddyData){
    ActiveBuddyFrame* activeBuddyInfo = getSelectedActiveBuddyFrame(buddyPosition);
    if( activeBuddyInfo->isSelected() ){
        defect(buddyPosition);
    }
    join(activeBuddyInfo, userBuddyData);
    resetActiveNinjaPower();
}

void ActiveBuddyFormationLayer::join(int buddyPosition, UserBuddyData *userBuddyData){
	ActiveBuddyFrame* activeBuddyInfo = getSelectedActiveBuddyFrame(buddyPosition);
    join(activeBuddyInfo, userBuddyData);
}
void ActiveBuddyFormationLayer::join(ActiveBuddyFrame *activeBuddyInfo, UserBuddyData* userBuddyData){
    if( !userBuddyData ) return;
    
    if(delegate)delegate->selectActiveBuddy(activeBuddyInfo, userBuddyData);
    activeBuddyInfo->selectBuddy(userBuddyData);
    User::getInstance()->setActiveBuddy(activeBuddyInfo->getPositionNo(), userBuddyData->no);
    
    m_mineNinjaPower->entryActiveBuddy(activeBuddyInfo->getPositionNo(), userBuddyData);
    isChangedActiveBuddy = true;
}

void ActiveBuddyFormationLayer::defect(int buddyPosition){
    ActiveBuddyFrame* activeBuddyInfo = (ActiveBuddyFrame*)getSelectedActiveBuddyFrame(buddyPosition);
    if(delegate)delegate->deselectActiveBuddy(activeBuddyInfo);
    activeBuddyInfo->deselectBuddy(isBlindStatusBg);
    
    User::getInstance()->unsetActiveBuddy(buddyPosition);
    
    m_mineNinjaPower->exitActiveBuddy(buddyPosition);
    isChangedActiveBuddy = true;
}
void ActiveBuddyFormationLayer::removeBuddy(int buddyNo){
    // 削除する味方を選択してたら選択解除
    ActiveBuddyFrame* activeBuddyframe = getSelectedActiveBuddyFrameByBuddyNo(buddyNo);
    if( activeBuddyframe ){
        defect(activeBuddyframe->getPositionNo());
    }
}

ActiveBuddyFrame* ActiveBuddyFormationLayer::getSelectedActiveBuddyFrame(int position){
    return (ActiveBuddyFrame*)selectedActiveBuddyArray->objectAtIndex(position);
}

void ActiveBuddyFormationLayer::entryNinjaPowerPlayer(int kind, int lv, int evolutionType){
    m_mineNinjaPower->entryPlayer(kind, lv, evolutionType);
}
void ActiveBuddyFormationLayer::resetActiveNinjaPower(){
    m_mineNinjaPower->resetNinjaPower();
    isChangedActiveBuddy =false;
}

/*　仲間編成　基底部分　終了 */


/*
 ActiveBuddyFormationLayer 継承部分
 Shop画面にあわせて改造
 */
/*---------------------------
 ShopActiveBuddyFrame
 ---------------------------*/
ShopActiveBuddyFrame::ShopActiveBuddyFrame(){
    setUserBuddyData = NULL;
//    m_frameName = "btn_change_buddy_03.png";
    unselectFrameName = "btn_change_buddy_03.png";
    selectedFrameName= "btn_change_buddy_01.png";
    frameRect= CCRect(0, 0, 132.0, 132.0);
}

ShopActiveBuddyFrame* ShopActiveBuddyFrame::create(int _positionNo, bool _isLocked){
    ShopActiveBuddyFrame* info = new ShopActiveBuddyFrame();
    info->autorelease();
    User* user = User::getInstance();
    
    if(_positionNo == 0){
        _isLocked = (user->getIsMenuTutorial() == true || user->getBuddyList()->count() > 0) ? false : true;
    }
    info->m_positionNo = _positionNo;
    info->m_isLocked = _isLocked;
    if(info->init()){
        return info;
    }
    CC_SAFE_DELETE(info);
    return NULL;
}

//const char* ShopActiveBuddyFrame::logoName_powerUp="logo_change_buddy_01.png"; // 強化ロゴ
//const char* ShopActiveBuddyFrame::logoName_evo="logo_change_buddy_02.png"; // 進化ロゴ
//const char* ShopActiveBuddyFrame::logoName_select="logo_change_buddy_03.png"; // 味方を選ぶ
void ShopActiveBuddyFrame::initOpened(){
    checkSelectFrameName();
    
    ActiveBuddyFrame::initOpened();
    
    // 強化ロゴ
    logo_change_buddy_01_powerup = NFSpriteCluster::create("logo_change_buddy_01.png");
    logo_change_buddy_01_powerup->setAnchorPoint(ccp(0.5, 0.5));
    logo_change_buddy_01_powerup->setPosition(ccp(2.0, 78.0));
    this->addChild(logo_change_buddy_01_powerup);
    
    // 進化ロゴ
    logo_change_buddy_01_evo = NFSpriteCluster::create("logo_change_buddy_02.png");
    logo_change_buddy_01_evo->setAnchorPoint(ccp(0.5, 0.5));
    logo_change_buddy_01_evo->setPosition(ccp(2.0, 78.0));
    this->addChild(logo_change_buddy_01_evo);
    
    // 味方を選ぶ
    logo_change_buddy_01_select = NFSpriteCluster::create("logo_change_buddy_03.png");
    logo_change_buddy_01_select->setAnchorPoint(ccp(0.5, 0.5));
    logo_change_buddy_01_select->setPosition(ccp(2.0, 78.0));
    this->addChild(logo_change_buddy_01_select);
    
    logo_change_buddy_01_powerup->setVisible(false);
    logo_change_buddy_01_evo->setVisible(false);
    logo_change_buddy_01_select->setVisible(false);
    
    frame->setAnchorPoint(ccp(0.494, 0.506));
    frame->setPosition(ccp(0, -2.0));
    
    // チュートリアル中は、0番のフレームは非表示にする
    if(User::getInstance()->getTutorialNo()==2 && getPositionNo()==0){
        frame->setVisible(false);
    }
}

// 強化、進化チェック
SelectBuddyTag ShopActiveBuddyFrame::checkSelectBuddyTag(){
    if( !setUserBuddyData ){
        if( isLocked() ){
            return SelectBuddyLockTag;
        }else{
            return SelectBuddyEmptyTag;
        }
    }
    
    // 進化可能チェック
    if (isEvolutionable(setUserBuddyData)==true) {
        return SelectBuddyEvoTag;
    }else{
        if(getBuddyMaxLevel(setUserBuddyData->attr, setUserBuddyData->rank, setUserBuddyData->cstmtype) > setUserBuddyData->level){
            return SelectBuddyPowerUpTag;
        }
    }
    return SelectBuddyNoneTag;
}

void ShopActiveBuddyFrame::checkSelectFrameName(){
    SelectBuddyTag tag = checkSelectBuddyTag();
    switch (tag) {
        case SelectBuddyPowerUpTag: // 強化
            selectedFrameName= "btn_change_buddy_01.png";
            break;
        case SelectBuddyEvoTag: // 進化
            selectedFrameName= "btn_change_buddy_02.png";
            break;
        case SelectBuddyNoneTag: // なにもできない
            selectedFrameName= "btn_change_buddy_03.png";
            break;
        default: break;
    };
}

void ShopActiveBuddyFrame::changeFrameImage(){
    if(isLocked()) return;
    
    logo_change_buddy_01_powerup->setVisible(false);
    logo_change_buddy_01_evo->setVisible(false);
    logo_change_buddy_01_select->setVisible(false);
    checkSelectFrameName();
    
    SelectBuddyTag tag = checkSelectBuddyTag();
//    bool logoVisible = true;
    switch (tag) {
        case SelectBuddyPowerUpTag: // 強化
            logo_change_buddy_01_powerup->setVisible(true);
//            CCNodeUtil::setSpriteImage(frame, "btn_change_buddy_01.png");
//            CCNodeUtil::setSpriteImage(m_imgLogo, logoName_powerUp);
            break;
            
        case SelectBuddyEvoTag: // 進化
            logo_change_buddy_01_evo->setVisible(true);
//            CCNodeUtil::setSpriteImage(frame, "btn_change_buddy_02.png");
//            CCNodeUtil::setSpriteImage(m_imgLogo, logoName_evo);
            break;
            
        case SelectBuddyEmptyTag: // 何もセットされていない
            logo_change_buddy_01_select->setVisible(true);
//            CCNodeUtil::setSpriteImage(m_imgLogo, logoName_select);
            break;
            
        default:
//            CCNodeUtil::setSpriteImage(frame, unselectFrameName.c_str());//"btn_change_buddy_03.png");
            break;
    }
    
    
    ActiveBuddyFrame::changeFrameImage();
}

void ShopActiveBuddyFrame::selectBuddy(UserBuddyData* userBuddyData){
    if( !userBuddyData ) return;
    
    setUserBuddyData = User::getInstance()->getBuddy(userBuddyData->no);
    ActiveBuddyFrame::selectBuddy(userBuddyData);
}

void ShopActiveBuddyFrame::deselectBuddy(bool _blindBg){
    setUserBuddyData =NULL;
    ActiveBuddyFrame::deselectBuddy(_blindBg);
}

void ShopActiveBuddyFrame::hideFrame(){
    if(logo_change_buddy_01_powerup) logo_change_buddy_01_powerup->setVisible(false);
    if(logo_change_buddy_01_evo) logo_change_buddy_01_evo->setVisible(false);
    if(logo_change_buddy_01_select) logo_change_buddy_01_select->setVisible(false);
//    if(m_imgLogo) m_imgLogo->setVisible(false);
    if(statusBg) statusBg->setVisible(false);
    if(frame) frame->setVisible(false);
    if( m_profileSprite->levelNumber ) m_profileSprite->levelNumber->setVisible(false);
    if( m_profileSprite->levelIcon ) m_profileSprite->levelIcon->setVisible(false);
    if( m_profileSprite->rareIcon ) m_profileSprite->rareIcon->setVisible(false);

}
/* --------------------------------
 * ShopActiveGuardianFrame
 -------------------------------- */
const char* ShopActiveGuardianFrame::unselectLogoName="logo_change_guardian_01.png";
const char* ShopActiveGuardianFrame::selectedLogoName="logo_change_guardian_02.png";

ShopActiveGuardianFrame* ShopActiveGuardianFrame::create(int _positionNo, bool _isLocked){
    ShopActiveGuardianFrame* info = new ShopActiveGuardianFrame();
    info->autorelease();
    
    info->m_positionNo = _positionNo;
    info->m_isLocked = _isLocked;
    if(info->init()){
        return info;
    }
    CC_SAFE_DELETE(info);
    return NULL;
}

void ShopActiveGuardianFrame::initOpened(){
    logo_change = CCSprite::create(unselectLogoName);
    logo_change->setAnchorPoint(ccp(0.5, 0.5));
    logo_change->setPosition(ccp(0.0, 60.0));
    this->addChild(logo_change);
    
    selectedFrameName= "btn_change_guardian_02.png";
    ActiveGuardianFrame::initOpened();
}

void ShopActiveGuardianFrame::changeFrameImage(){
    if( isSelected() ){
        CCNodeUtil::setSpriteImage(logo_change, selectedLogoName);
    }else{
        CCNodeUtil::setSpriteImage(logo_change, unselectLogoName);
    }
    ActiveGuardianFrame::changeFrameImage();
}
void ShopActiveGuardianFrame::hideFrame(){
    if(logo_change) logo_change->setVisible(false);
    if(statusBg) statusBg->setVisible(false);
    if(frame) frame->setVisible(false);
    if( m_profileSprite->levelIcon ) m_profileSprite->levelIcon->setVisible(false);
    if( m_profileSprite->rareIcon ) m_profileSprite->rareIcon->setVisible(false);
}
/* --------------------------------
 * ShopActiveBuddyFormationLayer
 -------------------------------- */
ShopActiveBuddyFormationLayer* ShopActiveBuddyFormationLayer::create(){
    ShopActiveBuddyFormationLayer* info = new ShopActiveBuddyFormationLayer();
    info->autorelease();
    if(info->init()){
        return info;
    }
    CC_SAFE_DELETE(info);
    return NULL;
}

CCPoint ShopActiveBuddyFormationLayer::getBuddyPosition(int position){
	switch (position) {
		case 0:
            
			return ccp(244.0, (winHeight - 960) / 2 + 502.0);
		case 1:
			return ccp(396.0, (winHeight - 960) / 2 + 502.0);
		case 2:
			return ccp(168.0, (winHeight - 960) / 2 + 366.0);
		case 3:
			return ccp(472.0, (winHeight - 960) / 2 + 366.0);
		case 4:
			return ccp(320.0, (winHeight - 960) / 2 + 366.0);
	}
	return ccp(0, 0);
}
CCPoint ShopActiveBuddyFormationLayer::getGuardianPosition(int position){
    switch (position) {
        case 1:
            return ccp(170.0, (winHeight - 960) / 2 + 622.0);
        case 2:
            return ccp(170.0, (winHeight - 960) / 2 + 622.0);
    }
    return ccp(0, 0);
}

void ShopActiveBuddyFormationLayer::tapFrame(ActiveBuddyFrame *_frame){
    delegate->tapActiveBuddyFrame(_frame);
}

ActiveBuddyFrame* ShopActiveBuddyFormationLayer::createFrame(int position, int isLocked){
    return ShopActiveBuddyFrame::create(position, isLocked);
}

CCSprite* ShopActiveBuddyFormationLayer::createDraggedIcon(int buddyNo){
    CCSprite* icon = ActiveBuddyFormationLayer::createDraggedIcon(buddyNo);
    // チームから外すロゴ
    CCSprite* logo_take_it_off = CCSprite::create("logo_take_it_off_01.png");
    logo_take_it_off->setAnchorPoint(ccp(0.5, 0.5));
    logo_take_it_off->setPosition(CCPoint(125,210));
    icon->addChild(logo_take_it_off);
    
    return icon;
}

void ShopActiveBuddyFormationLayer::startFadeOut(float time){
    CCObject* access =NULL;
    CCARRAY_FOREACH(getChildren(), access){
        CCNode* node = (CCNode*)access;
        if( !node ) continue;
        node->runAction(CCFadeOut::create(time));
    }
    //忍者パワーを非表示に
    m_mineNinjaPower->setVisible(false);
}

#import "SelectGuardianMenu.h"
bool ShopActiveBuddyFormationLayer::init(){
    ActiveBuddyFormationLayer::init();
    
    isChangedActiveBuddy= false;
    
    // ActiveBuddyFormationLayer::init()で一回addChildしているため、残ってしまう
    if(m_mineNinjaPower){
        m_mineNinjaPower->removeFromParentAndCleanup(true);
        m_mineNinjaPower = NULL;
    }
    
    // 忍者パワー
    m_mineNinjaPower = NinjaPowerInfo::createStyleBar(ccp(500.0, (winHeight - 960) / 2 + 764.0));
    this->addChild(m_mineNinjaPower);
    
    //守護霊
    initGuardianFrame();
    
    return true;
}

void ShopActiveBuddyFormationLayer::initGuardianFrame(){
    User* user = User::getInstance();
    int positionNo = 1;
    bool isLocked = getGuardinanUnlockLevel(positionNo) > user->getLevel();
    
    //frame
    CCPoint framePos = getGuardianPosition(positionNo);
    m_activeGuardianFrame = ShopActiveGuardianFrame::create(positionNo, isLocked);
    m_activeGuardianFrame->setPosition(framePos);
    this->addChild(m_activeGuardianFrame, -5);
    
    //フレームのプライオリティをそろえるため、別add
    CCSprite* frame = m_activeGuardianFrame->getFrame();
    if( frame ){
        frame->setPosition(framePos);
        this->addChild(frame, -10);
        
        InputFrameMenu* menu = InputFrameMenu::create(NULL);
        this->addChild(menu);
        
        InputFrameMenuItem* item = InputFrameMenuItem::create(m_activeGuardianFrame);
        item->setPosition(frame->getPosition());
        item->setTarget(this, menu_selector(ShopActiveBuddyFormationLayer::goToSelectGuardian));
        
        menu->addChild(item);
    }
    
    GuardianData* activeGuardianData= user->seekActiveGuardian(positionNo);
    m_activeGuardianFrame->select(activeGuardianData);
    
}

NFSpriteCluster* ShopActiveBuddyFormationLayer::deliverBuddyEntity(int position){
    ActiveBuddyFrame* frame = getSelectedActiveBuddyFrame(position);
    if( frame->isSelected()){
        NFSpriteCluster* buddy = frame->getAnimation();
        if( buddy )buddy->setPosition(ccpAdd(buddy->getPosition(), getBuddyPosition(position)));
        return buddy;
    }
    return NULL;
}

NFSpriteCluster* ShopActiveBuddyFormationLayer::deliverGuardianEntity(int position){
    NFSpriteCluster* guardian = m_activeGuardianFrame->getAnimation();
    if( guardian )guardian->setPosition(getGuardianPosition(position));
    return guardian;
}

void ShopActiveBuddyFormationLayer::hideFrame(){    //まがたま使用スタート時
    CCObject* access =NULL;
    CCARRAY_FOREACH(getChildren(), access){
        
        if(dynamic_cast<ShopActiveBuddyFrame*>(access)){
            ShopActiveBuddyFrame* activeBuddyInfo = (ShopActiveBuddyFrame*)access;
            if(!activeBuddyInfo) continue;
            activeBuddyInfo->hideFrame();
        }
    }
    m_activeGuardianFrame->hideFrame();
    
    if(m_mineNinjaPower) m_mineNinjaPower->setVisible(false);
}

void ShopActiveBuddyFormationLayer::goToSelectGuardian(){
    playSoundEffect("LN_ninjase014.m4a");
    CCScene* scene = SelectGuardianMenu::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void ShopActiveBuddyFormationLayer::blinkBuddyBg() {
    ActiveBuddyFormationLayer::blinkBuddyBg();
    m_activeGuardianFrame->blink(isBlindStatusBg);
}

//void ShopActiveBuddyFormationLayer::join(ActiveBuddyFrame *activeBuddyInfo, UserBuddyData *userBuddyData){
//    ActiveBuddyFormationLayer::join(activeBuddyInfo, userBuddyData);
//    m_mineNinjaPower->entryActiveBuddy(activeBuddyInfo->getPositionNo(), userBuddyData);
//    isChangedActiveBuddy = true;
//}
//void ShopActiveBuddyFormationLayer::defect(int buddyPosition){
//    ActiveBuddyFormationLayer::defect(buddyPosition);
//    m_mineNinjaPower->exitActiveBuddy(buddyPosition);
//    isChangedActiveBuddy = true;
//}



//void ShopActiveBuddyFormationLayer::touchEnded(cocos2d::CCPoint location, InputCharactorFrame *_activateFrame){
//    ActiveBuddyFormationLayer::touchEnded(location, _activateFrame);
//    if( isChangedActiveBuddy){
//        resetActiveNinjaPower();
//    }
//    isChangedActiveBuddy = false;
//}
/*【終了】ActiveBuddyFormationLayer 継承部分 */

