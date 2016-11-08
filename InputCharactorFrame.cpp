//
//  InputCharactorFrame.cpp
//  NinjaFlight
//
//  Created by KUBO AYAMI on 2014/10/02.
//
//

#import "InputCharactorFrame.h"
#import "CCNodeUtil.h"
#import "CharaListTable.h"
#import "NFNumberLayer.h"

using namespace cocos2d;

/*-----------------------------
 *  InputCharactorFrame
 ------------------------------*/
InputCharactorFrame::InputCharactorFrame() {
    statusBg = NULL;
    frame = NULL;
    m_isLocked = false;
    ico_rock=NULL;
    lv_rock_bg=NULL;
    m_isSelected=false;
    m_positionNo = 0;
    m_statusBgName_lock = "status_buddy_02.png";
    m_statusBgName_dark = "status_buddy_03.png";
    m_statusBgName_bright = "status_buddy_01.png";

    unselectFrameName= "btn_change_buddy_frame_01.png";
    selectedFrameName= "btn_change_buddy_frame_02.png";
    
    frameRect = CCRectMake(0, 0, 156.0, 156.0);
    m_profileSprite =NULL;
    m_canDragged=false;
}

bool InputCharactorFrame::isTouched(cocos2d::CCPoint location){
    if( !frame ) return false;
    
    return CCNodeUtil::getNodeRect(frame).containsPoint(location);
}
CCSprite* InputCharactorFrame::createStatusBg(){
    return CCSprite::create(isLocked() ?  m_statusBgName_lock.c_str(): m_statusBgName_dark.c_str());
}
bool InputCharactorFrame::init(){
    NFSpriteCluster::init();
    setAnchorPoint(ccp(0.5, 0.5));
    
    statusBg = createStatusBg();
    statusBg->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(statusBg);
    
    if(isLocked()) {
        initLocked();
    } else {
        initOpened();
    }
    
    return true;
}
void InputCharactorFrame::initLocked(){
    ico_rock = NFSpriteCluster::create("ico_rock_02.png");
    ico_rock->setAnchorPoint(ccp(0.5, 0.5));
    ico_rock->setPosition(ccp(-1.0, 1.0));
    this->addChild(ico_rock);
    
    lv_rock_bg = NFSpriteCluster::create("lv_rock_bg_01.png");
    lv_rock_bg->setAnchorPoint(ccp(0.5, 0.5));
    lv_rock_bg->setPosition(ccp(38, 14.0));
    this->addChild(lv_rock_bg);
    
    int unlockLevel = getUnlockLevel(m_positionNo);
    lockLevelNumber = NFNumberLayer::create(unlockLevel, "num_lv_01.png", 28, 34, -8, 0, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0);
    lockLevelNumber->setAnchorPoint(ccp(0.5, 0.5));
    lockLevelNumber->setPosition(ccp(34, 13));
    this->addChild(lockLevelNumber);
}

void InputCharactorFrame::initOpened(){
    if( isSelected() ){
        m_frameName = selectedFrameName;
    }else{
        m_frameName = unselectFrameName;
    }
    
    frame = NFSpriteCluster::create(m_frameName.c_str(), frameRect);
    frame->setAnchorPoint(ccp(0.494, 0.506));
    frame->setPosition(ccp(3, -5.0));
}

void InputCharactorFrame::changeFrameImage(){
    if( !frame ) return;
    
    if( isSelected() ){
        if( m_frameName.compare(selectedFrameName.c_str())==0 ) return;
        CCNodeUtil::setSpriteImage(frame, selectedFrameName.c_str());
        m_frameName = selectedFrameName;
    }else{
        if( m_frameName.compare(unselectFrameName.c_str())==0 ) return;
        CCNodeUtil::setSpriteImage(frame, unselectFrameName.c_str());
        m_frameName = unselectFrameName;
    }
    
    resetPushed();
}

void InputCharactorFrame::blink(bool _blind){
    if (!isSelected() && !isLocked()) {
        CCNodeUtil::setSpriteImage(statusBg, _blind ? m_statusBgName_dark.c_str() : m_statusBgName_bright.c_str());
    }
}

void InputCharactorFrame::framePushed(){
    if( !frame ) return;
    
    NFCharaTableCell::setTextureRectForSelectStatus(frame, kSelectStatusPushed);
}

void InputCharactorFrame::resetPushed(){
    if( !frame ) return;
    NFCharaTableCell::setTextureRectForSelectStatus(frame, kSelectStatusNone);
}

NFSpriteCluster* InputCharactorFrame::getAnimation(){
    if( m_profileSprite ){
        return m_profileSprite->animation;
    }
    return NULL;
}

/*
* InputFrameMenuItem
*/
InputFrameMenuItem* InputFrameMenuItem::create(InputCharactorFrame *_frame){
    InputFrameMenuItem *pRet = new InputFrameMenuItem();
    pRet->initWithTarget(NULL, NULL);
    pRet->autorelease();
    pRet->setAnchorPoint(ccp(0.5, 0.5));
    pRet->m_inputFrame = _frame;
    
    pRet->setContentSize(_frame->frame->getContentSize());
    return pRet;
}

void InputFrameMenuItem::selected(){
    m_inputFrame->framePushed();
    NFSpriteCluster* animation = m_inputFrame->getAnimation();
    if( animation ){
        animation->setOpacity(255*0.5);
    }
}

void InputFrameMenuItem::unselected(){
    m_inputFrame->resetPushed();
    NFSpriteCluster* animation = m_inputFrame->getAnimation();
    if( animation ){
        animation->setOpacity(255);
    }
}

/*
 * InputFrameMenu
 */
InputFrameMenu * InputFrameMenu::create(InputFrameMenuDelegate* _delegate)
{
    InputFrameMenu *pRet = new InputFrameMenu();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->setPosition(0, 0);
        pRet->setAnchorPoint(ccp(0.5, 0.5));
        pRet->setContentSize(CCSize(0, 0));
        pRet->delegate = _delegate;
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool InputFrameMenu::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    bool ret = CCMenu::ccTouchBegan(pTouch, pEvent);
    if(ret && delegate){
        CCPoint locationInView = pTouch->getLocationInView();
        CCPoint location = CCDirector::sharedDirector()->convertToGL(locationInView);
        
        InputCharactorFrame* _pushFrame= ((InputFrameMenuItem*)m_pSelectedItem)->getInputFrame();
        delegate->touchBegan(location, _pushFrame);
    }
    return ret;
}

void InputFrameMenu::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCMenu::ccTouchMoved(pTouch, pEvent);
    if( !delegate ) return;
    
    CCPoint locationInView = pTouch->getLocationInView();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(locationInView);
    delegate->touchMoved(location);
}

void InputFrameMenu::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCMenu::ccTouchEnded(pTouch, pEvent);
    
    if( !delegate ) return;
    
    CCPoint locationInView = pTouch->getLocationInView();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(locationInView);
    
    InputCharactorFrame* _activateFrame = NULL;
    if( m_pSelectedItem ){
        _activateFrame= ((InputFrameMenuItem*)m_pSelectedItem)->getInputFrame();
    }
    delegate->touchEnded(location, _activateFrame);

}


#import "BuddyAnimationCluster.h"
#import "BuddyData.h"
CharaProfileSprite::CharaProfileSprite(){
    levelIcon = NULL;
    levelNumber =NULL;
    rareIcon =NULL;
    animation = NULL;
}
CharaProfileSprite* CharaProfileSprite::create(){
    CharaProfileSprite* info = new CharaProfileSprite();
    info->autorelease();
    info->init();
//    info->changeLevel(0);
    return info;
}

CharaProfileSprite* CharaProfileSprite::createBuddy(int attr, int rare, int lv, int costumeType){
    CharaProfileSprite* info = new CharaProfileSprite();
    info->autorelease();
    info->init();
    info->showBuddy(attr, rare, lv, costumeType);
    return info;
}

CharaProfileSprite* CharaProfileSprite::createPlayer(int kind, int lv, int evolutionType, bool isMine){
    CharaProfileSprite* info = new CharaProfileSprite();
    info->autorelease();
    info->init();
    info->showPlayer(kind, lv, evolutionType, isMine);
    return info;
}

CharaProfileSprite* CharaProfileSprite::createGuardian(int _id){
    CharaProfileSprite* info = new CharaProfileSprite();
    info->autorelease();
    info->init();
    info->showGuardian(_id);
    return info;
}

void CharaProfileSprite::changeLevel(int lv){
    if( !levelIcon ){
        levelIcon = NFSpriteCluster::create("lv_bg_s_01.png");
        levelIcon->setAnchorPoint(ccp(0.5, 0.5));
        levelIcon->setPosition(ccp(26, -33.0));
        this->addChild(levelIcon, 10);
    }
    if( !levelNumber ){
        levelNumber = NFNumberLayer::create(0, "num_lv_s_01.png", 18.0, 24.0, -4, 0, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0);
        levelNumber->setPosition(ccp(37, -33.0));
        this->addChild(levelNumber, 11);
    }
    levelNumber->setNum(lv);
}

void CharaProfileSprite::changeRare(int rare){
    if( rareIcon ){
        rareIcon->removeFromParentAndCleanup(true);
    }
    rareIcon = createBuddyRareIcon(rare_s, rare);
    rareIcon->setAnchorPoint(ccp(0.5, 0.5));
    rareIcon->setPosition(ccp(-1, -62.0));
    this->addChild(rareIcon, 10);
}

void CharaProfileSprite::showBuddy(int attr, int rare, int lv, int costumeType){
    changeLevel(lv);
    changeRare(rare);
    
    if( animation ){
        animation->removeFromParentAndCleanup(true);
    }
    animation = BuddyAnimationCluster::createBuddyAnimation(attr, rare, costumeType);
    animation->setAloneProperty(true);
    this->addChild(animation);
    
    ((BuddyAnimationCluster*)animation)->setAnimation(BDAS_RUN);
}

//#import "PlayerAnimationCluster.h"
#import "Player.h"
void CharaProfileSprite::showPlayer(int kind, int lv, int evolutionType, bool isMine){
    changeLevel(lv);
    
    if( animation ){
        animation->removeFromParentAndCleanup(true);
    }
    animation= Player::create(PlayerCreateData((CharactorType)kind,
                                               evolutionType,
                                               lv,
                                               false,
                                               isMine));
    //PlayerAnimationCluster::create(kind, evolutionType);
    animation->setAloneProperty(true);
    animation->setPosition(ccp(0,0));
    this->addChild(animation);
    
//    ((PlayerAnimationCluster*)animation)->setAnimation(PAS_RUN);
}

#import "GuardianData.h"
#import "GuardianAnimationCluster.h"
void CharaProfileSprite::showGuardian(int _id){
    changeRare(getGuardianRankNum(_id));
    rareIcon->setPosition(ccp(1.0, -54.5));
    
    if( animation ){
        animation->removeFromParentAndCleanup(true);
    }
    animation= GuardianAnimation::create(_id);
    animation->setAloneProperty(true);
    this->addChild(animation);
}