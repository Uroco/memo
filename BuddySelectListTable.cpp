//
//  BuddySelectListTable.cpp
//  NinjaFlight
//
#import "CommonDefine.h"
#import "BuddySelectListTable.h"
#import "HttpConnector.h"
#import "NFDialog.h"

/*------------------------
 * BuddyTableCell
 */

BuddyTableCell::BuddyTableCell() {
    m_isCheese=false;
    buddyData = UserBuddyData::create(-1, 0, 1, 1, 0, 0);
    m_materialEvolutionCover=NULL;
    evelutionIcon=NULL;
    m_isFavorite=false;
    num_batch_a_01 =NULL;
}

BuddyTableCell::~BuddyTableCell(){
    buddyData->release();
}

BuddyTableCell* BuddyTableCell::create(UserBuddyData *_buddyData, bool _isUsing, bool _showRegularFrame){
    BuddyTableCell* cell = new BuddyTableCell();
    cell->autorelease();
    cell->init(_buddyData, kType_Buddy, 1, _isUsing, _showRegularFrame);
    cell->initBuddyCell();
    return cell;
}

BuddyTableCell* BuddyTableCell::createCheese(UnionMateriaType _type, int _num){
    BuddyTableCell* cell = new BuddyTableCell();
    cell->autorelease();
    cell->init(NULL, _type, _num);
    cell->initCheeseCell();
    return cell;
}

BuddyTableCell* BuddyTableCell::createMetalBuddy(int no, int _num, bool _isUsing, bool _showRegularFrame){
    BuddyTableCell* cell = new BuddyTableCell();
    cell->autorelease();
    cell->init(makeMetalBuddyData(no), kType_Metal, _num, _isUsing, _showRegularFrame);
    cell->initSubBuddyCell();
    return cell;
}

bool BuddyTableCell::init(UserBuddyData* _buddyData, UnionMateriaType _type, int _num, bool _isUsing, bool _showRegularFrame){
    CCSprite::init();
    setAnchorPoint(ccp(0.5, 0.5));
    
    isUsing=_isUsing;
    showRegularFrame= _showRegularFrame;
    
    const char* selectBtnFilename;
    if( _isUsing && _showRegularFrame){
        selectBtnFilename = "btn_select_pet_s_02.png";  //「使用中」枠
    }else{
        selectBtnFilename = "btn_select_pet_s_01.png";  //通常枠
    }
    btn_select_pet_s_011 = CCSprite::create(selectBtnFilename, CCRectMake(0, 0, DefaultCellSize.width, DefaultCellSize.height));
    btn_select_pet_s_011->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(btn_select_pet_s_011);
    
    if( isUsing && showRegularFrame ){
        CCSprite* ico_select_01 = CCSprite::create("ico_select_01.png");
		ico_select_01->setAnchorPoint(ccp(0.5, 0.5));
		ico_select_01->setPosition(ccp(416- 395 + DefaultCellSize.width * 0.5, 143 - 81 + DefaultCellSize.height * 0.5));
		btn_select_pet_s_011->addChild(ico_select_01, 10);
    }
    
    cellType = _type;
    hasNum = _num;
    leftNum = _num;
    if( _buddyData ){
        buddyData = UserBuddyData::create(_buddyData->no, _buddyData->attr, _buddyData->rank, _buddyData->level, _buddyData->exp, _buddyData->dispflg, _buddyData->cstmtype);
    }else{
        int no = -1;
        switch (cellType) {
            case kType_cGold: no= CHEESE_GOLD_NO;
                break;
            case kType_cSilver: no= CHEESE_SILVER_NO;
                break;
            default:
                NFLog("No Cheese!!!!");
                return false;
        }
        
        buddyData = UserBuddyData::create(no, 0, 1, 1, 0, 0);
        
    }
    buddyData->retain();
    return true;
}

void BuddyTableCell::initBuddyCell(){
    
    positionDiff = ccp(-395 + 154 * 0.5, -81 + 158 * 0.5);
    
    buddy_s_0_11 = createBuddyIcon(s, buddyData);
    buddy_s_0_11->setAnchorPoint(ccp(0.5, 0.5));
    buddy_s_0_11->setPosition(ccpAdd(ccp(392, 84), positionDiff));
    btn_select_pet_s_011->addChild(buddy_s_0_11);
    
    CCSprite* lv_bg_s_011 = CCSprite::create("lv_bg_s_01.png");
    lv_bg_s_011->setAnchorPoint(ccp(0.5, 0.5));
    lv_bg_s_011->setPosition(ccpAdd(ccp(412, 52), positionDiff));
    btn_select_pet_s_011->addChild(lv_bg_s_011);
    
    NFNumberLayer* num_lv_s_011 = NFNumberLayer::create(buddyData->level, "num_lv_s_01.png", 18.0, 24.0, -4, 0, kNumAlignCenter, ccp(0.5, 0.5), 1, NULL, 0, NULL, 0);
    num_lv_s_011->setPosition(ccpAdd(ccp(422, 51), positionDiff));
    btn_select_pet_s_011->addChild(num_lv_s_011);
    
    CCSprite* ico_rare_s_011 = createBuddyRareIcon(rare_s, buddyData->rank);
    ico_rare_s_011->setAnchorPoint(ccp(0.5, 0.5));
    ico_rare_s_011->setPosition(ccpAdd(ccp(393, 22), positionDiff));
    btn_select_pet_s_011->addChild(ico_rare_s_011, 10);
    
    
    if(!buddyData->dispflg) {
        CCSprite* ico_new_011 = CCSprite::create("ico_new_01.png");
        ico_new_011->setAnchorPoint(ccp(0.5, 0.5));
        ico_new_011->setPosition(ccp(433 - 395 + DefaultCellSize.width * 0.5, 143 - 81 + DefaultCellSize.height * 0.5));
        btn_select_pet_s_011->addChild(ico_new_011, 20);
    }
    
    //お気に入りアイコン
    if( User::getInstance()->isBuddyFavorite(buddyData->no) ){
        m_isFavorite = true;
        CCSprite* ico_heart_01 = CCSprite::create("ico_heart_01.png");
        ico_heart_01->setAnchorPoint(ccp(0.5, 0.5));
        ico_heart_01->setPosition(ccp(40.0, 50.0));
        btn_select_pet_s_011->addChild(ico_heart_01);
    }
    
    if (isEvolutionable(buddyData)) {
        //進化可能アイコンをつける
        evelutionIcon = CCSprite::create();
        btn_select_pet_s_011->addChild(evelutionIcon, 10);
        
        createEvolutionIcon(false, evelutionIcon);
    }
}

void BuddyTableCell::calcLeftNum(bool _isSelect, bool cansel){
    NFCharaTableCell::calcLeftNum(_isSelect, cansel);
    if( num_batch_a_01 ) num_batch_a_01->setNum(leftNum);
}

//進化可能、進化素材の点滅アイコンタグ
#define TAG_FLASHING_ICON_1 11
#define TAG_FLASHING_ICON_2 22

void BuddyTableCell::createEvolutionIcon(bool _isMaterial, cocos2d::CCSprite *_parent){
    const char* filename01 = NULL;
    const char* filename02 = NULL;
    
    if( _isMaterial ){
        filename01="logo_material_01.png";
        filename02="logo_material_02.png";
    }else{
        filename01="logo_evolution_01.png";
        filename02="logo_evolution_02.png";
    }
    
    CCSprite* logo_evolution_01 = CCSprite::create(filename01);
    _parent->addChild(logo_evolution_01, 0 , TAG_FLASHING_ICON_1);
    
    
    CCSprite* logo_evolution_02 = CCSprite::create(filename02);
    _parent->addChild(logo_evolution_02, 0 , TAG_FLASHING_ICON_2);

    startIconAnimation(_parent);
}

void BuddyTableCell::startIconAnimation(cocos2d::CCSprite *_parent){
    CCSprite* logo_evolution_01 = (CCSprite*)_parent->getChildByTag(TAG_FLASHING_ICON_1);
    CCSprite* logo_evolution_02 = (CCSprite*)_parent->getChildByTag(TAG_FLASHING_ICON_2);

    if( logo_evolution_01 ){
        logo_evolution_01->setAnchorPoint(ccp(0.5, 0.5));
        logo_evolution_01->setPosition(ccpAdd(ccp(394.0, 123.0), positionDiff));
        
        logo_evolution_01->runAction
        (CCRepeatForever::create
         ((CCActionInterval*)CCSequence::create
          (CCScaleTo::create(9.0 / 30.0, 1.2),
           CCScaleTo::create(10.0 / 30.0, 1.0),
           CCDelayTime::create(11.0 / 30.0),
           NULL)));
    }
    
    if( logo_evolution_02 ){
        logo_evolution_02->setAnchorPoint(ccp(0.5, 0.5));
        logo_evolution_02->setPosition(ccpAdd(ccp(394.0, 123.0), positionDiff));
        logo_evolution_02->setOpacity(0);
        
        logo_evolution_02->runAction
        (CCRepeatForever::create
         ((CCActionInterval*)CCSpawn::create
          (CCSequence::create
           (CCScaleTo::create(9.0 / 30.0, 1.2),
            CCScaleTo::create(10.0 / 30.0, 1.0),
            CCDelayTime::create(11.0 / 30.0),
            NULL),
           CCSequence::create
           (CCFadeTo::create(9.0 / 30.0, 255.0),
            CCFadeTo::create(10.0 / 30.0, 0.0),
            CCDelayTime::create(11.0 / 30.0),
            NULL),
           NULL)));
    }
}

void BuddyTableCell::refreshFlashAnimation(){
    if( evelutionIcon ) startIconAnimation(evelutionIcon);
    if(m_materialEvolutionCover) startIconAnimation(m_materialEvolutionCover);
}

void BuddyTableCell::initCheeseCell(){
    m_isCheese = true;
    CCPoint positionDiff = ccp(-395 + DefaultCellSize.width * 0.5, -81 + DefaultCellSize.height * 0.5);
    // チーズの場合
    buddy_s_0_11 = createCheeseSprite(buddyData->no, true);
    buddy_s_0_11->setAnchorPoint(ccp(0.5, 0.5));
    buddy_s_0_11->setPosition(ccpAdd(ccp(392, 84), positionDiff));
    btn_select_pet_s_011->addChild(buddy_s_0_11);
    
    num_batch_a_01 = NFNumberLayer::create(hasNum, "num_batch_a_01.png", 28.0, 32.0, -8, 0, kNumAlignRight, ccp(0.5, 0.5), 1, "item", 2, NULL, 0, NULL, 0, 0, 0, 0);
    num_batch_a_01->setPosition(ccp(442.0 - 395 + DefaultCellSize.width * 0.5, 134.0 - 81 + DefaultCellSize.height * 0.5));
    btn_select_pet_s_011->addChild(num_batch_a_01, 10);
}

CCSprite* BuddyTableCell::createCheeseSprite(int buddyNo, bool isSmall) {
    // 手持ちのきんチーズを全て投入すると、getGoldCheeseCount == 0 になってしまうので、選択中の個数もチェック
    bool isGold = buddyNo == CHEESE_GOLD_NO ? true:false;
	char imgFileNam[24];
	sprintf(imgFileNam, "img_cheese%s_0%d.png", isSmall ? "" : "_m", isGold ? 2 : 1);
	return CCSprite::create(imgFileNam);
}

void BuddyTableCell::initSubBuddyCell(){
    CCPoint positionDiff = ccp(-395 + DefaultCellSize.width * 0.5, -81 + DefaultCellSize.height * 0.5);
   
    buddy_s_0_11 = createBuddyIcon(s, buddyData);
    buddy_s_0_11->setAnchorPoint(ccp(0.5, 0.5));
    buddy_s_0_11->setPosition(ccpAdd(ccp(392, 84), positionDiff));
    btn_select_pet_s_011->addChild(buddy_s_0_11);
    
    num_batch_a_01 = NFNumberLayer::create(hasNum, "num_batch_a_01.png", 28.0, 32.0, -8, 0, kNumAlignRight, ccp(0.5, 0.5), 1, "item", 2, NULL, 0, NULL, 0, 0, 0, 0);
    num_batch_a_01->setPosition(ccp(442.0 - 395 + DefaultCellSize.width * 0.5, 134.0 - 81 + DefaultCellSize.height * 0.5));
    btn_select_pet_s_011->addChild(num_batch_a_01, 10);
}

#import "NFBlackoutLayer.h"
void BuddyTableCell::conversionEvolutionMode(UserBuddyData *_buddyData){
    if( isSelected() ) return;
    
    m_materialEvolutionCover = CCSprite::create();
    btn_select_pet_s_011->addChild(m_materialEvolutionCover);
    
    if( canUseBuddyToEvelution(_buddyData, buddyData) ){
        //進化合成　素材アイコンをつける
        createEvolutionIcon(true, m_materialEvolutionCover);
        
        if( evelutionIcon ){    //進化可能　アイコンが点いている場合は位置調整
            m_materialEvolutionCover->setPositionY(-12);
            evelutionIcon->setPositionY(20);
        }
    }else{
        lockDrag();
        const char* filename = isUsing ? "dark_list_buddy_02.png":"dark_list_buddy_01.png";
        CCSprite* blackout = CCSprite::create(filename);
        blackout->setAnchorPoint(ccp( 0.5, 0.5 ));
        blackout->setPosition(ccp(DefaultCellSize.width*0.5, DefaultCellSize.height*0.5));
        blackout->setOpacity(255*0.6);
        m_materialEvolutionCover->addChild(blackout);
    }
}

void BuddyTableCell::conversionBasic(){
    if( m_materialEvolutionCover ){
        m_materialEvolutionCover->removeFromParentAndCleanup(true);
        m_materialEvolutionCover=NULL;
    }
    if( evelutionIcon )evelutionIcon->setPositionY(0);
    unlockDrag();
}

bool BuddyTableCell::isChangeTexture(SelectStatus state){
    if( state == kSelectStatusNone && hasNum > leftNum ){
        return false;
    }
    return true;
}




/*-----------------------
 BuddyListData
    リスト時に使う共通のデータ管理クラス
 -----------------------*/
BuddyListData::~BuddyListData(){
    if( listBuddy ){
        listBuddy->release();
    }
    allBuddyDictionary->release();
    m_metalArray->release();
}

BuddyListData::BuddyListData(){
    listBuddy=NULL;
    allBuddyDictionary=NULL;
    
    m_metalArray = CCArray::create();
    m_metalArray->retain();
}
void BuddyListData::reloadBuddyData(){
    usingBuddycnt =0;
    
    //正規の仲間
    for(int i = 0; i < MAX_BUDDY_NUM; i ++){
        UserBuddyData* buddyData = NULL;
        buddyData = User::getInstance()->getActiveBuddy(i);
        m_usingBuddydata[i] = buddyData;
    }
}

BuddyListData* BuddyListData::create(bool _isTutorial, bool _isExistCheese, bool _isExistMetal){
    
    BuddyListData* obj = new BuddyListData();
    obj->autorelease();
    if(obj->init(_isTutorial, _isExistCheese, _isExistMetal)){
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return NULL;
}

bool BuddyListData::init(bool _isTutorial, bool _isExistCheese, bool _isExistMetal){
    isTutorialMode = _isTutorial;
    isExistCheese = _isExistCheese;
    m_isExistMetal = _isExistMetal;
    
    if(isTutorialMode) {
        //偽の仲間一覧を作る
        UserBuddyData* buddy1 = UserBuddyData::create(0, 0, 1, 1, 0, 1);
        UserBuddyData* buddy2 = UserBuddyData::create(1, 3, 1, 1, 0, 1);
        
        listBuddy = CCArray::create();
        listBuddy->addObject(buddy1);
        listBuddy->addObject(buddy2);
        
        allBuddyDictionary = CCDictionary::create();
        allBuddyDictionary->setObject(buddy1, buddy1->no);
        allBuddyDictionary->setObject(buddy2, buddy2->no);
        
        m_isExistMetal = false;
	} else {
        sort();
        allBuddyDictionary = User::getInstance()->getBuddyMap();
	}
    listBuddy->retain();
    allBuddyDictionary->retain();
    
    makeMetalBuddyArray();  //メタル忍者のデータ集計
    reloadBuddyData();
    
    return true;
}

int BuddyListData::getGoldCheeseCount() {
	if (isTutorialMode || !isExistCheese) {
		return 0;
	}
	return User::getInstance()->getGoldMaterialCnt();
}

int BuddyListData::getSilverCheeseCount() {
	if (isTutorialMode || !isExistCheese) {
		return 0;
	}
	return User::getInstance()->getSilverMaterialCnt();
}

int BuddyListData::getCheeseOffset() {
    int offset = 0;
    if( isExistCheese ){
        if (getGoldCheeseCount()) {
            offset++;
        }
        if (getSilverCheeseCount()) {
            offset++;
        }
    }
	return offset;
}

bool BuddyListData::checkCheeseNo(int buddyNo){
    if( buddyNo == CHEESE_GOLD_NO ) return true;
    if( buddyNo == CHEESE_SILVER_NO ) return true;
    return false;
}

bool BuddyListData::isGoldCheese(int buddyNo){
    return buddyNo == CHEESE_GOLD_NO;
}
bool BuddyListData::isSilverCheese(int buddyNo){
    return buddyNo == CHEESE_SILVER_NO;
}

int BuddyListData::getMetalBuddyOffset(){
    if( !isExistMetal() ) return 0;
	return m_metalArray->count();
}

void BuddyListData::setBuddyList(cocos2d::CCArray *_array){
    listBuddy = _array;
    // 取得したものを表示
    CCObject* aChild = NULL;
    CCARRAY_FOREACH( listBuddy, aChild ) {
        UserBuddyData* a = (UserBuddyData*)aChild;
        NFLog("-------no:%d", a->no);
        NFLog("-------exp:%d", a->exp);
    }
}

void BuddyListData::makeMetalBuddyArray(){
    m_metalArray->removeAllObjects();
    
    for (int i = 0; i < 8; i++) {
        SubBuddyKey key;
        switch (i) {
            case 0: key = kSilverSpike; break;
            case 1: key = kSilverThunder; break;
            case 2: key = kSilverFire; break;
            case 3: key = kSilverPoison; break;
            case 4: key = kGoldSpike; break;
            case 5: key = kGoldThunder; break;
            case 6: key = kGoldFire; break;
            case 7: key = kGoldPoison; break;
        }
        if( User::getInstance()->getSubBuddyCnt(key) ){
            m_metalArray->addObject(CCInteger::create(key));
        }
    }
}


/*========================
    sort
==========================*/
bool BuddyListData::sortAndPatternSaved(BuddySortPattern _sortPattern){
    BuddySortPattern prvPattern = (BuddySortPattern)User::getInstance()->getBuddyListSortPattern();
    if( prvPattern != _sortPattern ){
        listBuddy->release();
        excuteSort(_sortPattern);
        
        //パターン保存
        User::getInstance()->saveBuddyListSortPattern(_sortPattern);
        return true;
    }
    return false;
}

void BuddyListData::sort(){
    BuddySortPattern _sortPattern = (BuddySortPattern)User::getInstance()->getBuddyListSortPattern();
    excuteSort(_sortPattern);
}

void BuddyListData::excuteSort(BuddySortPattern sortPattern){
    User* user = User::getInstance();
    CCArray* newBuddiesList = CCArray::create();
    CCArray* afterSortList = NULL;
    CCArray* buddies = user->getBuddyList();
    NFLog("before sort all buddy num [%d]", buddies->count());
    
    CCArray* copyBuddies=CCArray::create();
    if( sortPattern == kbSortPatternNew){
        CCObject* access = NULL;
        CCARRAY_FOREACH_REVERSE(buddies, access){
            copyBuddies->addObject(access);
        }
    }else{
        CCObject* access = NULL;
        CCARRAY_FOREACH(buddies, access){
            copyBuddies->addObject(access);
        }
    }
    
    //お気に入りは常にリストの先頭に
    CCArray* favoriteArray = user->getBuddyFavoriteList();
    CCObject* access = NULL;
    CCARRAY_FOREACH(favoriteArray, access){
        CCInteger* no = (CCInteger*)access;
        UserBuddyData* _data = user->getBuddy(no->getValue());
        if( _data ){
            newBuddiesList->addObject(_data);
            copyBuddies->removeObject(_data);
        }
    }
    
    switch (sortPattern) {
        case kbSortPatternOld:
        case kbSortPatternNew:  //なにもしない
            break;
        case kbSortPatternHighRank:
            afterSortList = highRankSort(copyBuddies);
            break;
        case kbSortPatternLowRank:
            afterSortList = lowRankSort(copyBuddies);
            break;
        case kbSortPatternAttr:
            afterSortList = attributeSort(copyBuddies);
            break;
    }
    
    access = NULL;
    CCARRAY_FOREACH(copyBuddies, access){
        newBuddiesList->addObject(access);
    }
    if( afterSortList ){
        access = NULL;
        CCARRAY_FOREACH(afterSortList, access){
            newBuddiesList->addObject(access);
        }
    }
    
    listBuddy = newBuddiesList;
    listBuddy->retain();
    
    NFLog("after sort all buddy num [%d]", newBuddiesList->count());
}

CCArray* BuddyListData::lowRankSort(CCArray* buddyArray){
    CCArray* newBuddiesList = CCArray::create();
    CCObject* access = NULL;
    //ランク低い順
    for (int rareNum = 1; rareNum <= MAX_BUDDY_RANK ; rareNum ++) {
        access = NULL;
        CCArray* sameRareArray = siftRank(buddyArray, rareNum);
        for (int attr = Normal ; sameRareArray->count() > 0 && attr < MaxBuddyAttr; attr++) {
            CCArray* sameAttrList = siftAttr(sameRareArray, attr);
            for (int type = kCostumBasic ; sameAttrList->count() > 0 && type < kCostumeTypeMax ; type++) {
                CCArray* sameTypeList = sortCostumeType(sameAttrList, type);
                sortLevel(sameTypeList);
                access = NULL;
                CCARRAY_FOREACH(sameTypeList, access){
                    newBuddiesList->addObject(access);
                }
            }
            
        }
    }
    
    return newBuddiesList;
}
CCArray* BuddyListData::highRankSort(CCArray* buddyArray){
    CCArray* newBuddiesList = CCArray::create();
    CCObject* access = NULL;
    //ランク高い順
    for (int rareNum = MAX_BUDDY_RANK; rareNum > 0 ; rareNum --) {
        access = NULL;
        CCArray* sameRareArray = siftRank(buddyArray, rareNum);
        for (int attr = Normal ; sameRareArray->count() > 0 && attr < MaxBuddyAttr; attr++) {
            CCArray* sameAttrList = siftAttr(sameRareArray, attr);
            for (int type = kCostumBasic ; sameAttrList->count() > 0 && type < kCostumeTypeMax ; type++) {
                CCArray* sameTypeList = sortCostumeType(sameAttrList, type);
                sortLevel(sameTypeList);
                access = NULL;
                CCARRAY_FOREACH(sameTypeList, access){
                    newBuddiesList->addObject(access);
                }
            }
            
        }
    }
    
    return newBuddiesList;
}

//属性順
CCArray* BuddyListData::attributeSort(cocos2d::CCArray *buddyArray){
    CCArray* newBuddiesList = CCArray::create();
    CCObject* access = NULL;
    for (int attr = Normal ; buddyArray->count() > 0 && attr < MaxBuddyAttr; attr++){
        access = NULL;
        CCArray* sameAttrList = siftAttr(buddyArray, attr);
        for (int rareNum = MAX_BUDDY_RANK; sameAttrList->count() > 0 && rareNum > 0 ; rareNum --){
            CCArray* sameRareArray = siftRank(sameAttrList, rareNum);
            for (int type = kCostumBasic ; sameRareArray->count() > 0 && type < kCostumeTypeMax ; type++) {
                CCArray* sameTypeList = sortCostumeType(sameRareArray, type);
                if( sameTypeList->count() > 0 ){
                    sortLevel(sameTypeList);
                    access = NULL;
                    CCARRAY_FOREACH(sameTypeList, access){
                        newBuddiesList->addObject(access);
                    }
                }
            }
            
        }
    }
    
    return newBuddiesList;
}

void BuddyListData::sortLevel(CCArray* buddyDataArray){
    excuteBubbleSort(buddyDataArray, &BuddyListData::comparisonLevel);
}

CCArray* BuddyListData::sift(cocos2d::CCArray *_buddyDataArray, int value, bool (BuddyListData::*_comparisonFunc)(int comparisonNum, UserBuddyData *buddyData)){
    CCArray* list = CCArray::create();
    CCObject* access = NULL;
    CCARRAY_FOREACH_REVERSE(_buddyDataArray, access){
        UserBuddyData* _buddyData = (UserBuddyData*)access;
        if( (this->*_comparisonFunc)(value, _buddyData) ){
            list->addObject(_buddyData);
            _buddyDataArray->removeObject(_buddyData);
        }
    }
    return list;
}

CCArray* BuddyListData::siftRank(CCArray* _buddyDataArray, int rank){
    return sift(_buddyDataArray, rank, &BuddyListData::comparisonRank);
}

CCArray* BuddyListData::siftAttr(CCArray* _buddyDataArray, int attr){
    return sift(_buddyDataArray, attr, &BuddyListData::comparisonAttr);
}
CCArray* BuddyListData::sortCostumeType(CCArray* _buddyDataArray, int type){
    return sift(_buddyDataArray, type, &BuddyListData::comparisonCostumeType);
}

bool BuddyListData::comparisonAttr(int comparisonNum, UserBuddyData *buddyData){
    if( comparisonNum == buddyData->attr ){
        return true;
    }
    return false;
}
bool BuddyListData::comparisonRank(int comparisonNum, UserBuddyData *buddyData){
    if( comparisonNum == buddyData->rank ){
        return true;
    }
    return false;
}
bool BuddyListData::comparisonCostumeType(int comparisonNum, UserBuddyData *buddyData){
    if( comparisonNum == buddyData->cstmtype ){
        return true;
    }
    return false;
}


void BuddyListData::excuteBubbleSort(cocos2d::CCArray *buddyDataArray, bool (BuddyListData::*_comparisonFunc)(UserBuddyData* buddyData, UserBuddyData* nextBuddyData)){
    int maxCount = buddyDataArray->count();
    for (int j = 0; j < maxCount ; j ++) {
        for (int i = maxCount-1; i > j ; i--) {
            UserBuddyData* buddyData = (UserBuddyData*)buddyDataArray->objectAtIndex(i);
            UserBuddyData* nextBuddyData = (UserBuddyData*)buddyDataArray->objectAtIndex(i-1);
            if((this->*_comparisonFunc)(buddyData, nextBuddyData) ){ //比較メソッドを呼ぶ
                buddyDataArray->exchangeObjectAtIndex(i, i-1);
            }
        }
    }
}

bool BuddyListData::comparisonLevel(UserBuddyData *buddyData, UserBuddyData *nextBuddyData){
    if( buddyData->level > nextBuddyData->level ){
        return true;
    }
    return false;
}

/*----------------------------------
 *  BuddySelectListTablePage
 *      １ページの管理クラス
 -----------------------------------*/
bool BuddySelectListTablePage::init(){
    m_isEvolution = false;
    return true;
}
void BuddySelectListTablePage::conversionGouseiEvolutionMode(UserBuddyData *_baseBuddyData){
    if( m_isEvolution ) return;
    m_isEvolution = true;
    
    CCObject* child3;
    CCARRAY_FOREACH(getChildren(), child3) {
        BuddyTableCell* cell = (BuddyTableCell*)child3;
        if( !cell ) continue;
        cell->conversionEvolutionMode(_baseBuddyData);
    }
    
}
void BuddySelectListTablePage::conversionBasicMode(){
    if( !m_isEvolution ) return;
    m_isEvolution = false;
    
    CCObject* child3;
    CCARRAY_FOREACH(getChildren(), child3) {
        BuddyTableCell* cell = (BuddyTableCell*)child3;
        if( !cell ) continue;
        cell->conversionBasic();
    }
}

void BuddySelectListTablePage::startFlashingAnimation(){
    CCObject* child3;
    CCARRAY_FOREACH(getChildren(), child3) {
        BuddyTableCell* cell = (BuddyTableCell*)child3;
        if( !cell ) continue;
        cell->refreshFlashAnimation();
    }
}

/*----------------------------
 *
 *  BuddySelectListTable
 *
 -----------------------------*/

BuddySelectListTable::BuddySelectListTable(){
	highlightDotto = NULL;
    buddyCellDictionary = CCDictionary::create();
    buddyCellDictionary->retain();
    m_isEvolution= false;
    m_doScrollLock=false;
}
BuddySelectListTable::~BuddySelectListTable(){
    newBuddyArray->release();
    buddyCellDictionary->release();
    pagingDottoArray->release();
}

BuddySelectListTable* BuddySelectListTable::create(BuddyListData* data, BuddySelectListTableDelegate* _delegate,
    EmbeddedScene _enbeddedScene){
    BuddySelectListTable* obj = new BuddySelectListTable();
    obj->autorelease();
    obj->delegate = _delegate;
    obj->m_buddyListData = data;
    obj->m_enbeddedScene = _enbeddedScene;
    if(obj->init()){
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return NULL;
}

bool BuddySelectListTable::init(){
    newBuddyArray = CCArray::create();   //Newがついてる仲間リスト
    newBuddyArray->retain();
    
    CharaListTable::init();
    
    //ソートボタン
    m_sortBtnMenu = NULL;
    createSortBtn();
    
    return true;
}

void BuddySelectListTable::reroadTable(){
    m_buddyListData->reloadBuddyData();
    CharaListTable::reroadTable();
}

bool BuddySelectListTable::canDispAlreadyPage(cocos2d::extension::CCTableViewCell *page){
    inspectionMode((BuddySelectListTablePage*)page);
    return true;
}

int BuddySelectListTable::getMaxPageNum() {
    int buddyCount = getMaxCellNum();
//    m_buddyListData->listBuddy->count()
//    + m_buddyListData->getCheeseOffset()
//    + m_buddyListData->getMetalBuddyOffset();
	if(buddyCount == 0) {
		return 0;
	}
	return (buddyCount - 1) / (getListNumY() * LIST_X_NUM)+1;
}

int BuddySelectListTable::getMaxCellNum(){
    return m_buddyListData->listBuddy->count()
    + m_buddyListData->getCheeseOffset()
    + m_buddyListData->getMetalBuddyOffset();
}

NFCharaTableCell* BuddySelectListTable::createCell(int idx){
    int cheeseOffset =  m_buddyListData->getCheeseOffset();
    int subBuddyOffset = m_buddyListData->getMetalBuddyOffset();
    
    BuddyTableCell* buddyCell = NULL;
    if(idx < cheeseOffset ) {
        buddyCell = createCheeseCell(idx);
        
    }else if( idx <= cheeseOffset + subBuddyOffset -1 ){
        buddyCell = createMetalBuddyCell(idx, cheeseOffset, subBuddyOffset);
    }else{
        int index = idx - cheeseOffset - subBuddyOffset;
        buddyCell = createBuddyCell(index);
    }
    
    if( buddyCell ){
        buddyCellDictionary->setObject(buddyCell, buddyCell->buddyData->no);
        int selectedNum =delegate->isSelected(buddyCell->buddyData->no);
        for (int i = 0; i < selectedNum; i++) { //選択されていたら選択状態に
            buddyCell->selected();
        }
    }
    
    return buddyCell;
}

CCTableViewCell* BuddySelectListTable::createPageView(){
    return BuddySelectListTablePage::create();
}
CCTableViewCell* BuddySelectListTable::createPage(unsigned int idx){
    CCTableViewCell* page = CharaListTable::createPage(idx);
    inspectionMode((BuddySelectListTablePage*)page);
    return page;
}

void BuddySelectListTable::createBG(){
    float downY = getListNumY() > 2 ? 154+12 : 0;
    downY = downY == 0 ? downY + (winHeight - winHeightMin) / 2 :downY;
    
    CCSprite* bg_sort_03 = CCSprite::create("bg_sort_03.png");
    bg_sort_03->setAnchorPoint(ccp(0.5, 0.5));
    bg_sort_03->setPosition(ccp(320, winHeight - 746.0 - downY));
    this->addChild(bg_sort_03, kCLTZ_BG);
    
    CCSprite* variable_bg_sort_02 = CCSprite::create("variable_bg_sort_02.png");
    variable_bg_sort_02->setAnchorPoint(ccp(0.0, 0.0));
    variable_bg_sort_02->setPosition(ccp(92.0, bg_sort_03->getPositionY() + bg_sort_03->getContentSize().height*0.5));
    float scaleY = getListNumY() > 2 ? 318+12 : 164 + (winHeight - winHeightMin) / 2;
    scaleY = scaleY / variable_bg_sort_02->getContentSize().height;    //画像サイズで割る
    variable_bg_sort_02->setScaleY(scaleY);
    this->addChild(variable_bg_sort_02, kCLTZ_BG);
    
    CCSprite* bg_sort_01 = CCSprite::create("bg_sort_01.png");
    bg_sort_01->setAnchorPoint(ccp(0.5, 0.5));
    bg_sort_01->setPosition(ccp(277.0, winHeight - 512.0));
    this->addChild(bg_sort_01, kCLTZ_BG);
}

void BuddySelectListTable::createSortBtn(){
    if( m_sortBtnMenu ){
        m_sortBtnMenu->removeAllChildrenWithCleanup(true);
    }
    m_sortBtnMenu = CCMenu::create();
    m_sortBtnMenu->setAnchorPoint(ccp(0, 0));
    m_sortBtnMenu->setPosition(ccp(0, 0));
    this->addChild(m_sortBtnMenu, kCLTZ_ScrollBtn_L);
    
    BuddySortPattern _sortPattern = (BuddySortPattern)User::getInstance()->getBuddyListSortPattern();
    
    char filename[128];
    sprintf(filename,"btn_sort_s_%d.png",_sortPattern);
    
    CCSprite* btn_sort_s_new_01 = CCSprite::create(filename, CCRectMake(0, 0, 92.0, 110.0));
    CCSprite* btn_sort_s_new_01Push = CCSprite::create(filename, CCRectMake(92.0, 0, 92.0, 110.0));
    NFMenuItemSprite* btn_sort_s_new_01Btn = NFMenuItemSprite::create(btn_sort_s_new_01, btn_sort_s_new_01Push);
    btn_sort_s_new_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_sort_s_new_01Btn->setPosition(ccp(56.2, winHeight - 515.0));
    m_sortBtnMenu->addChild(btn_sort_s_new_01Btn);
    
    btn_sort_s_new_01Btn->setTarget(this, menu_selector(BuddySelectListTable::pushSortBtn));
}
void BuddySelectListTable::setSortLock(bool st){
    m_sortBtnMenu->setEnabled(!st);
}

CCSprite* BuddySelectListTable::createDragIcon(NFCharaTableCell *_cell){
    BuddyTableCell* cell = (BuddyTableCell*)_cell;
    return createDragIcon(cell->buddyData, cell->isCheese());
}

CCSprite* BuddySelectListTable::createDragIcon(UserBuddyData *_buddyData, bool isCheese){
    CCSprite* icon=NULL;
    if(!isCheese) {
        icon = createBuddyIcon(m, _buddyData);
    } else {
        icon = BuddyTableCell::createCheeseSprite(_buddyData->no, false);
    }
    icon->setAnchorPoint(ccp(0.5, 0.5));
    return icon;
}

//使っていない　指定された仲間のページまでページをめくる
void BuddySelectListTable::showPageAtBuddyNo(int buddyNo){
    CCObject* access = NULL;
    int index = 0;
    CCARRAY_FOREACH(m_buddyListData->listBuddy, access){
        UserBuddyData* _userBuddyData = (UserBuddyData*)access;
        if( _userBuddyData->no == buddyNo ){
            break;
        }
        index ++;
    }
    index += m_buddyListData->getCheeseOffset();
    int listNumY = getListNumY();   //タテ何列か
    int onePageNum = listNumY * LIST_X_NUM;
    int pageNo = 0;
    if( index > onePageNum ){
        pageNo = index / onePageNum;
    }
    pageNo = pageNo+1;
    pageNo = MIN(pageNo, getMaxPageNum());

    NFLog("pageNo %d", pageNo-showingPageNo);
    m_table->scrollPage(pageNo-showingPageNo);
    m_table->updateCellAtIndex(pageNo);
}

void BuddySelectListTable::reloadEvolutionGouseiMode(UserBuddyData *_buddyData){
    m_isEvolution = true;
    m_evolutionBaseBuddy = User::getInstance()->getBuddy(_buddyData->no);
    BuddySelectListTablePage* page = (BuddySelectListTablePage*)pageDictionary->objectForKey(showingPageNo);
    conversionGouseiEvolutionModeAtPage(page, _buddyData);
    m_table->reloadData();
}

void BuddySelectListTable::conversionGouseiEvolutionModeAtPage(BuddySelectListTablePage* _page, UserBuddyData *_baseBuddyData){
//    BuddySelectListTablePage* page = (BuddySelectListTablePage*)pageDictionary->objectForKey(_pageNo);
    if(!_page) return;
    
    _page->conversionGouseiEvolutionMode(_baseBuddyData);
}

void BuddySelectListTable::reloadBasicMode(){
    m_isEvolution=false;
    m_evolutionBaseBuddy=NULL;
    
    BuddySelectListTablePage* page = (BuddySelectListTablePage*)pageDictionary->objectForKey(showingPageNo);
    conversionBasicModeAtPage(page);
    m_table->reloadData();
}
void BuddySelectListTable::conversionBasicModeAtPage(BuddySelectListTablePage* _page){
    if(!_page) return;
    _page->conversionBasicMode();
}

bool BuddySelectListTable::isUsing(UserBuddyData *_userBuddyData){
    if( m_buddyListData->usingBuddycnt < MAX_BUDDY_NUM ){
        for(int i = 0; i < MAX_BUDDY_NUM ; i++){
            if( m_buddyListData->m_usingBuddydata[i]
               && m_buddyListData->m_usingBuddydata[i]->no == _userBuddyData->no ){
                m_buddyListData->usingBuddycnt ++;
                return true;
            }
        }
    }
    return false;
}

BuddyTableCell* BuddySelectListTable::createBuddyCell(int buddisIndex){
    BuddyTableCell* buddyCell = NULL;
    //仲間
    UserBuddyData* _userBuddyData = (UserBuddyData*)m_buddyListData->listBuddy->objectAtIndex(buddisIndex);
    bool _isUsing = isUsing(_userBuddyData);
    
    //合成画面のみ　「使用中」枠をだす
    bool showRegularFrame = m_enbeddedScene == kEmbedded_Gousei;
    buddyCell = BuddyTableCell::create(_userBuddyData,
                                       _isUsing,
                                       showRegularFrame);
    //new仲間だったら
    if(!_userBuddyData->dispflg){
        newBuddyArray->addObject(CCInteger::create(_userBuddyData->no));
    }
    return buddyCell;
}

BuddyTableCell* BuddySelectListTable::createCheeseCell(int buddisIndex){
    BuddyTableCell* buddyCell = NULL;
    if( buddisIndex == 0 ){
        if (m_buddyListData->getGoldCheeseCount() > 0) { //金チーズ生成
            buddyCell = BuddyTableCell::createCheese(kType_cGold, m_buddyListData->getGoldCheeseCount());
        } else if (m_buddyListData->getSilverCheeseCount() > 0) {    //銀チーズ生成
            buddyCell = BuddyTableCell::createCheese(kType_cSilver,m_buddyListData->getSilverCheeseCount());
        }
    }else if( buddisIndex == 1 ){
        buddyCell = BuddyTableCell::createCheese(kType_cSilver, m_buddyListData->getSilverCheeseCount());
    }
    return buddyCell;
}
BuddyTableCell* BuddySelectListTable::createMetalBuddyCell(int buddisIndex, int cheeseOffset, int metalOffset){
    CCArray* metalBuddyArray = m_buddyListData->getMetalArray();
    int index = buddisIndex - cheeseOffset;
    
    SubBuddyKey key = (SubBuddyKey)((CCInteger*)metalBuddyArray->objectAtIndex(index))->getValue();
    int num = User::getInstance()->getSubBuddyCnt(key);
    MetalBuddyCellNo no = getMetalCellNo(key);
    
    //合成画面のみ　「使用中」枠をだす
    bool showRegularFrame = m_enbeddedScene == kEmbedded_Gousei;
    bool _isUsing = isUsing(makeMetalBuddyData(no));
    BuddyTableCell* buddyCell = BuddyTableCell::createMetalBuddy(no, num, _isUsing, showRegularFrame);
    return buddyCell;
}

void BuddySelectListTable::inspectionMode(BuddySelectListTablePage* _page){
    if( m_isEvolution ){
        conversionGouseiEvolutionModeAtPage(_page, m_evolutionBaseBuddy);
    }else{
        conversionBasicModeAtPage(_page);
    }
    _page->startFlashingAnimation();
}

void BuddySelectListTable::onPagingEnded(NFTableView* table, int pageNo) {
    CharaListTable::onPagingEnded(table, pageNo);
    
    //new表示終了処理
    if(newBuddyArray->count()>0) {
		CCDictionary* data = CCDictionary::create();
		data->setObject(CCString::create("setShown"), "m");
		data->setObject(newBuddyArray, "shownBuddy");
		HttpConnector* connector = new HttpConnector(NULL, NULL);
		
		std::string url = GAMESERVER_URL;
		url.append("composition.nhn");
		connector->setIsShowLoading(false);
		connector->connect(url, data);
		
		// Userのデータを変える
		CCObject* access=NULL;
		CCARRAY_FOREACH(newBuddyArray, access) {
			CCInteger* shownNo = (CCInteger*)access;
            
			UserBuddyData* _userBuddyData = User::getInstance()->getBuddy(shownNo->getValue());
            if( _userBuddyData ){
                _userBuddyData->dispflg = 1;
            }
		}
        
        newBuddyArray->removeAllObjects();
	}
}

BuddyTableCell* BuddySelectListTable::getBuddyTableCell(int buddyNo){
    return (BuddyTableCell*)buddyCellDictionary->objectForKey(buddyNo);
}

UserBuddyData* BuddyListData::getUserBuddyData(int buddyNo){
    if(checkCheeseNo(buddyNo)){
        return NULL;
    }
    else if( getSubBuddyKeyByNo(buddyNo) < 0 ){
        return makeMetalBuddyData(buddyNo);
    }
    else if( buddyNo <= 0 ){
        return NULL;
    }
    
    return (UserBuddyData*)allBuddyDictionary->objectForKey(buddyNo);
}

void BuddySelectListTable::sellBuddy(UserBuddyData* sellUserBuddyData) {
    if( !DELEGATE->canBuddySell(sellUserBuddyData) ){
        return;
    }
    // 通信
    CCDictionary* data = CCDictionary::create();
    data->setObject(CCString::create("sellBuddy"), "m");
    data->setObject(CCInteger::create(sellUserBuddyData->no), "sellBuddyNo"); // 売却する相棒Noを指定
    NFLog("sellBuddy[%d]", sellUserBuddyData->no);
    HttpConnector* connector = new HttpConnector(this, menu_selector(BuddySelectListTable::finishSellBuddyCallBack));
    
    std::string url = GAMESERVER_URL;
    url.append("composition.nhn");
    connector->connect(url, data);
}

/**
 * 売却処理通信コールバック
 */
void BuddySelectListTable::finishSellBuddyCallBack(CCDictionary* map)
{
    // 成功だったら
    CCInteger* result = (CCInteger *)map->objectForKey("result");
    NFLog("finishSellBuddyCallBack result[%d]" , result->getValue());
    if(result->getValue() != 0)return;  //error.
    
    User* user = User::getInstance();
    //メタルバデーの情報更新
    user->setSubBuddy(map);
    
    CCInteger* sellBuddyId = (CCInteger *)map->objectForKey("sellBuddyId");
    int sellBuddyNo = sellBuddyId->getValue();
    SubBuddyKey subBuddyKey = getSubBuddyKeyByNo(sellBuddyNo);
    //編隊に入れている味方を削除した時は外す
    for (int i = 0; i < 5; i++) {
        UserBuddyData* activeBuddyData = user->getActiveBuddy(i);
        if (activeBuddyData && activeBuddyData->no == sellBuddyNo) {
            if( subBuddyKey ){
                user->checkUnsetActiveSubBuddy(sellBuddyNo);break;
            }
            user->unsetActiveBuddy(i);
            break;
        }
    }
    
    if( !subBuddyKey ){
        // 味方データを消す
        buddyCellDictionary->removeObjectForKey(sellBuddyNo);
        UserBuddyData* deleteBuddy = User::getInstance()->getBuddy(sellBuddyNo);
        m_buddyListData->listBuddy->removeObject(deleteBuddy);
        user->deleteBuddy(sellBuddyNo);
    }else{
        m_buddyListData->makeMetalBuddyArray();
    }
    
    //獲得したコインを加算する
    CCInteger * afterCoin = (CCInteger *)map->objectForKey("afterCoin");
    User::getInstance()->setCoin(afterCoin->getValue());
    DELEGATE->finishSellBuddy(afterCoin->getValue());
    NFLog("finish sell result[%d] afterCoin[%d]" , result->getValue() , afterCoin->getValue());
    
    
    // リストの描画更新
	pageDictionary->removeAllObjects();
    m_table->reloadData();
    
	// ページが少なくなって、かつ最後のページを表示していた時
	if(showingPageNo >= getMaxPageNum()) {
        showingPageNo --;
		runAction(CCSequence::create(CCDelayTime::create(0.01),
									 CCCallFunc::create(this, callfunc_selector(BuddySelectListTable::pagingBack)),
									 NULL));
	} else {
		onPagingEnded(m_table, showingPageNo);
	}
	
	NFDialog* dialog = NFDialog::create();
	dialog->message = t00414;
	dialog->showOkDialog();
}

void BuddySelectListTable::tapCell(NFCharaTableCell* _cell){
    showBuddyDetail((BuddyTableCell*)_cell);
}

void BuddySelectListTable::showBuddyDetail(BuddyTableCell* selectedBuddyCell){
    if(User::getInstance()->getIsMenuTutorial() == false){
        return;
    }
    
    playSoundEffect("LN_ninjase015.m4a");
    UserBuddyData* _userBuddyData=NULL;
    bool isGold = false;
    bool canRemove = true;
    if(!selectedBuddyCell->isCheese() ) {
        _userBuddyData = selectedBuddyCell->buddyData;
        //売却できるか確認
        canRemove = DELEGATE->canBuddySell(selectedBuddyCell->buddyData);
    } else {
        isGold = selectedBuddyCell->isGoldCheese();
    }
    
    BuddyDetailDialog* dialog = BuddyDetailDialog::create(_userBuddyData, isGold, this, menu_selector(BuddySelectListTable::sellBuddy), true, canRemove);
    dialog->setFavoriteCallback(menu_selector(BuddySelectListTable::pushedFavoriteBtn));
    dialog->setCloseCallBack(menu_selector(BuddySelectListTable::closeBuddyDetailDialog));
    if( delegate )DELEGATE->openBuddyDetailDialog(dialog);
    this->getParent()->addChild(dialog, 1000);
}

void BuddySelectListTable::closeBuddyDetailDialog(UserBuddyData *userBuddyData){
    DELEGATE->closeBuddyDetailDialog();
}

void BuddySelectListTable::pushSortBtn(){
    BuddyListSortDialog* dialog = BuddyListSortDialog::create(this , menu_selector(BuddySelectListTable::pushedSortChange), menu_selector(BuddySelectListTable::pushedSortClose));
    getParent()->addChild(dialog, 1000);
    DELEGATE->pushBuddyListSortButton();
}

void BuddySelectListTable::pushedSortClose(){
    DELEGATE->closeBuddyListSortDialog();
}

void BuddySelectListTable::pushedSortChange(CCObject* sender){
    CCInteger* no = (CCInteger*)sender;
    if(m_buddyListData->sortAndPatternSaved((BuddySortPattern)no->getValue())){
        createSortBtn();
        reroadTable();
    }
}
void BuddySelectListTable::pushedFavoriteBtn(UserBuddyData* userBuddyData){
    m_buddyListData->sort();
    reroadTable();
    BuddyTableCell* cell = getBuddyTableCell(userBuddyData->no);
    DELEGATE->pushFavoriteBtn(cell);
}

//*
//     BuddyListSortDialog  *//
//*
BuddyListSortDialog*  BuddyListSortDialog::create(cocos2d::CCObject *_callbackTarget, SEL_MenuHandler _sortBtnPushed, SEL_MenuHandler _dialogClose){
    BuddyListSortDialog* obj = new BuddyListSortDialog();
    obj->autorelease();
    obj->callbackTarget = _callbackTarget;
    obj->sortBtnPushed = _sortBtnPushed;
    obj->dialogClose = _dialogClose;
    obj->init();
    return obj;
};

void BuddyListSortDialog::onPushSort(CCObject* sender){
    playSoundEffect("LN_ninjase015.m4a");

    if(callbackTarget && sortBtnPushed) {
        CCInteger* no = (CCInteger*)((CCMenuItem*)sender)->getUserObject();
        (callbackTarget->*sortBtnPushed)(no);
    }
    close();
}

void BuddyListSortDialog::close() {
    if(callbackTarget && dialogClose) {
        (callbackTarget->*dialogClose)(NULL);
    }
	removeFromParentAndCleanup(true);
}

bool BuddyListSortDialog::init(){
    CCLayer* configLayer= CCNodeUtil::createTouchBlockLayer(128);
    this->addChild(configLayer);
    
    createDialogBg();
    
    menu = TopPriorityMenu::create();
    menu->setPosition(ccp( 0, 0));
    this->addChild(menu,0, 0);
    
    BuddySortPattern _sortPattern = (BuddySortPattern)User::getInstance()->getBuddyListSortPattern();
    float originPosY = (winHeight - 960) / 2 + 584.0;
    for (int i = kbSortPatternOld; i < kbSortPatternMax; i ++) {
        char filename[128];
        if( i == _sortPattern ){
            sprintf(filename, "btn_sort_%d_on_01.png", i);
        }else{
            sprintf(filename, "btn_sort_%d_off_01.png", i);
        }
        
        CCSprite* btn_sort_01 = CCSprite::create(filename, CCRectMake(0, 0, 386.0, 96.0));
        CCSprite* btn_sort_01Push = CCSprite::create(filename, CCRectMake(386.0, 0, 386.0, 96.0));
        NFMenuItemSprite* btn_sort_Btn = NFMenuItemSprite::create(btn_sort_01, btn_sort_01Push);
        btn_sort_Btn->setAnchorPoint(ccp(0.5, 0.5));
        btn_sort_Btn->setPosition(ccp(323.0, originPosY - ((i-1) * 96)));
        btn_sort_Btn->setUserObject(CCInteger::create(i));
        menu->addChild(btn_sort_Btn);
        btn_sort_Btn->setTarget(this, menu_selector(BuddyListSortDialog::onPushSort));

    }
    
    NFLabelTTF* txt_dialog_sort_01_9f9075 = NFLabelTTF::create(t00537, FONT_W6, 20, CCSizeMake(644.0, 22.0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    txt_dialog_sort_01_9f9075->setColor(ccc3(0x9f, 0x90, 0x75));
    txt_dialog_sort_01_9f9075->setAnchorPoint(ccp(0.5, 1.0));
    txt_dialog_sort_01_9f9075->setPosition(ccp(317.0, (winHeight - 960) / 2 + 686.0));
    this->addChild(txt_dialog_sort_01_9f9075);
    
    if(!User::getInstance()->isSortTutorial()){
        showSortTutorialDialog();
        btn_close_xs_01Btn->setEnabled(false);
        menu->setEnabled(false);
    }
    
    return true;
}

void BuddyListSortDialog::tutorialClose(){
    btn_close_xs_01Btn->setEnabled(true);
    menu->setEnabled(true);
    tutorialLayer->removeFromParentAndCleanup(true);
    close();
}

void BuddyListSortDialog::createDialogBg(){
    CCSprite* dialog_bg_03 = CCSprite::create("dialog_bg_03.png");
    dialog_bg_03->setAnchorPoint(ccp(0.5, 0.5));
    dialog_bg_03->setPosition(ccp(320.0, (winHeight - 960) / 2 + 62.0));
    this->addChild(dialog_bg_03);
    
    CCSprite* tile_dialog_bg_02_03 = CCSprite::create("tile_dialog_bg_02_03.png", CCRectMake(0, 0, 32.0, 596.0));
    tile_dialog_bg_02_03->getTexture()->setTexParameters(&texParamsRepeatVertical);
    tile_dialog_bg_02_03->setAnchorPoint(ccp(0.0, 0.0));
    tile_dialog_bg_02_03->setPosition(ccp(578.0, (winHeight - 960) / 2 + 74.0));
    this->addChild(tile_dialog_bg_02_03);
    
    CCSprite* tile_dialog_bg_02_02 = CCSprite::create("tile_dialog_bg_02_02.png", CCRectMake(0, 0, 484.0, 596.0));
    tile_dialog_bg_02_02->getTexture()->setTexParameters(&texParamsRepeatBoth);
    tile_dialog_bg_02_02->setAnchorPoint(ccp(0.0, 0.0));
    tile_dialog_bg_02_02->setPosition(ccp(94.0, (winHeight - 960) / 2 + 74.0));
    this->addChild(tile_dialog_bg_02_02);
    
    CCSprite* tile_dialog_bg_02_01 = CCSprite::create("tile_dialog_bg_02_01.png", CCRectMake(0, 0, 64.0, 596.0));
    tile_dialog_bg_02_01->getTexture()->setTexParameters(&texParamsRepeatVertical);
    tile_dialog_bg_02_01->setAnchorPoint(ccp(0.0, 0.0));
    tile_dialog_bg_02_01->setPosition(ccp(30.0, (winHeight - 960) / 2 + 74.0));
    this->addChild(tile_dialog_bg_02_01);
    
    CCSprite* dialog_pattern_01 = CCSprite::create("dialog_pattern_01.png");
    dialog_pattern_01->setAnchorPoint(ccp(0.5, 0.5));
    dialog_pattern_01->setPosition(ccp(320.0, (winHeight - 960) / 2 + 168.0));
    this->addChild(dialog_pattern_01);
    
    CCSprite* dialog_bg_01 = CCSprite::create("dialog_bg_01.png");
    dialog_bg_01->setAnchorPoint(ccp(0.468, 0.919));
    dialog_bg_01->setPosition(ccp(300.0, (winHeight - 960) / 2 + 894.0));
    this->addChild(dialog_bg_01);
    
    TopPriorityMenu* menu = TopPriorityMenu::create();
    menu->setPosition(ccp( 0, 0));
    this->addChild(menu,0, 0);
    CCSprite* btn_close_xs_01 = CCSprite::create("btn_close_xs_01.png", CCRectMake(0, 0, 108.0, 108.0));
    CCSprite* btn_close_xs_01Push = CCSprite::create("btn_close_xs_01.png", CCRectMake(108.0, 0, 108.0, 108.0));
    btn_close_xs_01Btn = NFMenuItemSprite::create(btn_close_xs_01, btn_close_xs_01Push);
    btn_close_xs_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_close_xs_01Btn->setPosition(ccp(578.0, (winHeight - 960) / 2 + 710.0));
    menu->addChild(btn_close_xs_01Btn);
    
    btn_close_xs_01Btn->setTarget(this, menu_selector(BuddyListSortDialog::close));
}

void BuddyListSortDialog::showSortTutorialDialog(){
    User::getInstance()->setSortTutorial(true);
    
    tutorialLayer = CCNodeUtil::createTouchBlockLayer(0);
    this->addChild(tutorialLayer);

    NFBlackoutLayer* blackout_circle_012 = NFBlackoutLayer::create(640, 4.0);
    blackout_circle_012->setPosition(ccp(0.0, (winHeight - 960) / 2 + 84.0));
    tutorialLayer->addChild(blackout_circle_012);
    
    CCSprite* new_system_info_bg_03 = CCSprite::create("new_system_info_bg_03.png");
    new_system_info_bg_03->setAnchorPoint(ccp(0.5, 0.5));
    new_system_info_bg_03->setPosition(ccp(319.0, (winHeight - 960) / 2 + 743.0));
    tutorialLayer->addChild(new_system_info_bg_03);
    
    CCSprite* tile_new_system_info_bg_02_03 = CCSprite::create("tile_new_system_info_bg_02_03.png", CCRectMake(0, 0, 16.0, 114.0));
    tile_new_system_info_bg_02_03->getTexture()->setTexParameters(&texParamsRepeatVertical);
    tile_new_system_info_bg_02_03->setAnchorPoint(ccp(0.0, 0.0));
    tile_new_system_info_bg_02_03->setPosition(ccp(600.0, (winHeight - 960) / 2 + 766.0));
    tutorialLayer->addChild(tile_new_system_info_bg_02_03);
    
    CCSprite* tile_new_system_info_bg_02_02 = CCSprite::create("tile_new_system_info_bg_02_02.png", CCRectMake(0, 0, 562.0, 114.0));
    tile_new_system_info_bg_02_02->getTexture()->setTexParameters(&texParamsRepeatBoth);
    tile_new_system_info_bg_02_02->setAnchorPoint(ccp(0.0, 0.0));
    tile_new_system_info_bg_02_02->setPosition(ccp(38.0, (winHeight - 960) / 2 + 766.0));
    tutorialLayer->addChild(tile_new_system_info_bg_02_02);
    
    CCSprite* tile_new_system_info_bg_02_01 = CCSprite::create("tile_new_system_info_bg_02_01.png", CCRectMake(0, 0, 16.0, 114.0));
    tile_new_system_info_bg_02_01->getTexture()->setTexParameters(&texParamsRepeatVertical);
    tile_new_system_info_bg_02_01->setAnchorPoint(ccp(0.0, 0.0));
    tile_new_system_info_bg_02_01->setPosition(ccp(22.0, (winHeight - 960) / 2 + 766.0));
    tutorialLayer->addChild(tile_new_system_info_bg_02_01);
    
    CCSprite* new_system_info_bg_01 = CCSprite::create("new_system_info_bg_01.png");
    new_system_info_bg_01->setAnchorPoint(ccp(0.5, 0.5));
    new_system_info_bg_01->setPosition(ccp(319.0, (winHeight - 960) / 2 + 903.5));
    tutorialLayer->addChild(new_system_info_bg_01);
    
    CCSprite* new_system_info_bg_arrow_01 = CCSprite::create("new_system_info_bg_arrow_01.png");
    new_system_info_bg_arrow_01->setAnchorPoint(ccp(0.5, 0.5));
    new_system_info_bg_arrow_01->setPosition(ccp(336.0, (winHeight - 960) / 2 + 712.0));
    tutorialLayer->addChild(new_system_info_bg_arrow_01);
    
    NFLabelTTF* txt_tutorial_new_system_08_t00550 = NFLabelTTF::create(t00550, FONT_W6, 30, CCSizeMake(832.0, 106.0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    txt_tutorial_new_system_08_t00550->setColor(ccc3(0x52, 0x43, 0x37));
    txt_tutorial_new_system_08_t00550->setAnchorPoint(ccp(0.5, 1.0));
    txt_tutorial_new_system_08_t00550->setPosition(ccp(320.0, (winHeight - 960) / 2 + 862.0));
    tutorialLayer->addChild(txt_tutorial_new_system_08_t00550);
    
    NFLabelTTF* txt_tutorial_new_system_01_t00402 = NFLabelTTF::create(t00402, FONT_W6, 26, CCSizeMake(156.0, 26.0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    txt_tutorial_new_system_01_t00402->setColor(ccc3(0xff, 0x78, 0x00));
    txt_tutorial_new_system_01_t00402->setAnchorPoint(ccp(0.5, 1.0));
    txt_tutorial_new_system_01_t00402->setPosition(ccp(320.0, (winHeight - 960) / 2 + 893.0));
    tutorialLayer->addChild(txt_tutorial_new_system_01_t00402);
    
    TopPriorityMenu* rootMenu01 = TopPriorityMenu::create();
    rootMenu01->setAnchorPoint(ccp(0, 0));
    rootMenu01->setPosition(ccp(0, 0));
    tutorialLayer->addChild(rootMenu01);
    CCSprite* btn_tutorial_start_01 = CCSprite::create("btn_tutorial_start_01.png", CCRectMake(0, 0, 238.0, 98.0));
    CCSprite* btn_tutorial_start_01Push = CCSprite::create("btn_tutorial_start_01.png", CCRectMake(238.0, 0, 238.0, 98.0));
    NFMenuItemSprite* btn_tutorial_start_01Btn = NFMenuItemSprite::create(btn_tutorial_start_01, btn_tutorial_start_01Push);
    btn_tutorial_start_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_tutorial_start_01Btn->setPosition(ccp(321.0, 73.0));
    rootMenu01->addChild(btn_tutorial_start_01Btn);
    
    btn_tutorial_start_01Btn->setTarget(this, menu_selector(BuddyListSortDialog::tutorialClose));
}
