//
//  CharaListTable.cpp
//  NinjaFlight
//
//  Created by KUBO AYAMI on 2014/09/17.
//
//
#import "CommonDefine.h"
#import "CharaListTable.h"
#import "SoundManager.h"


/*------------------------
 * NFCharaTableCell
 */
NFCharaTableCell::NFCharaTableCell(){
    isSelect=false;
    isPush = false;
    isUsing = false;
    m_isDraggedLock=false;
    index = 0;
//    m_isLocked = false;
    m_isEmpty = false;
    hasNum=1;
    leftNum=1;
    
    buddy_s_0_11 =NULL;
    btn_select_pet_s_011 =NULL;
    m_icoCheckPos = ccp(304.0 - 318, 170.0 - 160 + 158);
}

void NFCharaTableCell::createCheckIcon(){
    if( btn_select_pet_s_011->getChildByTag(TAG_CHECK_ICON) ) return;
    
    CCSprite* ico_check_box_on_011 = CCSprite::create("ico_check_box_on_01.png");
//    ico_check_box_on_011->setAnchorPoint(ccp(0.5, 0.5));
    ico_check_box_on_011->setAnchorPoint(ccp(0, 1));
    ico_check_box_on_011->setPosition(m_icoCheckPos);
    ico_check_box_on_011->setTag(TAG_CHECK_ICON);
    btn_select_pet_s_011->addChild(ico_check_box_on_011);
    buddy_s_0_11->setOpacity(128);
}
void NFCharaTableCell::removeCheckIcon(){
    btn_select_pet_s_011->removeChildByTag(TAG_CHECK_ICON, true);
    if( buddy_s_0_11 )buddy_s_0_11->setOpacity(255);
}

void NFCharaTableCell::calcLeftNum(bool _isSelect, bool cansel) {
	if (!buddy_s_0_11) {
		return;
	}
    
	if(_isSelect) {
        if( !cansel )leftNum --;
	} else {
        if( !cansel )leftNum ++;
        if( hasNum > leftNum ){
            _isSelect =true;    //別の場所で選択されていたら選択状態は有効
        }
	}
    isSelect = _isSelect;
    leftNum = MAX(0, leftNum);
    leftNum = MIN(hasNum, leftNum);
}


bool NFCharaTableCell::isEmpty(){
    return m_isEmpty;
}

void NFCharaTableCell::onPushInList(bool _isPush) {
    if( m_isEmpty ) return;
    if( !isPush && !_isPush ){
        return;
    }
    
	CCObject* _child;
	CCARRAY_FOREACH(btn_select_pet_s_011->getChildren(), _child) {
		CCNode* child = (CCNode*)_child;
		child->setPosition(ccpAdd(child->getPosition(), ccp(0, _isPush ? -4 : 4)));
	}
    
    if( _isPush ){
        if( isSelected() ){
            changeBtnState(kSelectStatusSelectedPushed);
        }else{
            changeBtnState(kSelectStatusPushed);
        }
    }
    
    isPush = _isPush;
}

void NFCharaTableCell::beginDragged(){
    buddy_s_0_11->setOpacity(255 * 0.5);
}

void NFCharaTableCell::selected(){
    if( m_isEmpty ) return;
    
    calcLeftNum(true, false);
    if( isSelected() ){
        createCheckIcon(); //チェックアイコン生成
        changeBtnState(kSelectStatusSelected);
    }
    onPushInList(false);
    isSelect = true;
}

void NFCharaTableCell::deselected(){
    if( m_isEmpty ) return;
    
    calcLeftNum(false, false);
    if( !isSelected() ){
        removeCheckIcon();  //チェックアイコンを消す
        isSelect = false;
        changeBtnState(kSelectStatusNone);
    }
    onPushInList(false);
}

void NFCharaTableCell::pushed(){
    if( m_isEmpty ) return;
    
    onPushInList(true);
}

void NFCharaTableCell::canselPushed(){
    if( m_isEmpty ) return;
    
    calcLeftNum(false, true);
    if( isSelected() ){
        selected();
    }else{
        deselected();
        buddy_s_0_11->setOpacity(255);
    }
}

// リスト領域の選択状態を変える
void NFCharaTableCell::changeBtnState(SelectStatus state){
    if( isChangeTexture( state ) ){
        setTextureRectForSelectStatus(btn_select_pet_s_011, state);
    }
}

bool NFCharaTableCell::isChangeTexture(SelectStatus state){
    CC_UNUSED_PARAM(state);
    return true;
}

void NFCharaTableCell::lockDrag(){
    m_isDraggedLock = true;
}
void NFCharaTableCell::unlockDrag(){
    m_isDraggedLock = false;
}

CCSize NFCharaTableCell::getCellSize(){
    return btn_select_pet_s_011->getContentSize();
}

void NFCharaTableCell::setTextureRectForSelectStatus(CCSprite* sprite, SelectStatus selectStatus) {
	if(sprite == NULL) {
		return;
	}
	
	CCSize spriteSize = sprite->getContentSize();
	int nodeTextureLeft;
	switch (selectStatus) {
		case kSelectStatusNone:
			nodeTextureLeft = 0;
			break;
		case kSelectStatusPushed:
			nodeTextureLeft = 1;
			break;
		case kSelectStatusSelected:
			nodeTextureLeft = 2;
			break;
		case kSelectStatusSelectedPushed:
			nodeTextureLeft = 3;
			break;
	}
	sprite->setTextureRect(CCRectMake(spriteSize.width * nodeTextureLeft, 0, spriteSize.width, spriteSize.height));
}

/*----------------------------------
 *  CharaListTableDelegate
 -----------------------------------*/
CharaListTableDelegate::CharaListTableDelegate(){
    doBanTouchToTable = false;
}

/*----------------------------
 *
 *
 *  CharaListTable
 -----------------------------*/
CharaListTable::CharaListTable(){
    cellCount=0;
    showingPageNo = 0;
    listXNum = LIST_X_NUM;
    
    m_table = NULL;
    delegate = NULL;
    m_draggingIcon =NULL;
    m_holdCell =NULL;
    m_cellSize = DefaultCellSize;
    
    pageDictionary = CCDictionary::create();
	pageDictionary->retain();
    
    pagingDottoArray = new CCArray();
    pagingDottoArray->retain();
}
CharaListTable::~CharaListTable(){
    cellCount=0;
    pageDictionary->release();
}

CharaListTable* CharaListTable::create(){
    CharaListTable* table = new CharaListTable();
    table->autorelease();
    table->init();
    return table;
}

bool CharaListTable::init(){
    CCLayer::init();
    
    createBG(); //ページ背景
    createScrollBtn();  //左右ボタン
    reroadTable();
    
    return true;
}

void CharaListTable::createBG(){
    
}

void CharaListTable::createScrollBtn(){
    //スクロールボタン
    CCMenu* rootMenuR = CCMenu::create();
	rootMenuR->setAnchorPoint(ccp(0, 0));
	rootMenuR->setPosition(ccp(0, 0));
	this->addChild(rootMenuR, kCLTZ_ScrollBtn_R);
	CCSprite* btn_scroll_right_xs_01 = CCSprite::create("btn_scroll_right_xs_01.png", CCRectMake(0, 0, 54.0, 72.0));
    CCSprite* btn_scroll_right_xs_01Push = CCSprite::create("btn_scroll_right_xs_01.png", CCRectMake(54.0, 0, 54.0, 72.0));
	btn_scroll_right_01Btn = NFMenuItemSprite::create(btn_scroll_right_xs_01, btn_scroll_right_xs_01Push);
	btn_scroll_right_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_scroll_right_01Btn->setPosition(ccp(605.0, winHeight - 612.0));
    rootMenuR->addChild(btn_scroll_right_01Btn);
	
    CCMenu* rootMenuL = CCMenu::create();
	rootMenuL->setAnchorPoint(ccp(0, 0));
	rootMenuL->setPosition(ccp(0, 0));
	this->addChild(rootMenuL, kCLTZ_ScrollBtn_L);
    CCSprite* btn_scroll_left_xs_01 = CCSprite::create("btn_scroll_left_xs_01.png", CCRectMake(0, 0, 54.0, 72.0));
    CCSprite* btn_scroll_left_xs_01Push = CCSprite::create("btn_scroll_left_xs_01.png", CCRectMake(54.0, 0, 54.0, 72.0));
    btn_scroll_left_01Btn = NFMenuItemSprite::create(btn_scroll_left_xs_01, btn_scroll_left_xs_01Push);
    btn_scroll_left_01Btn->setAnchorPoint(ccp(0.5, 0.5));
    btn_scroll_left_01Btn->setPosition(ccp(43.0, winHeight - 612.0));
    rootMenuL->addChild(btn_scroll_left_01Btn);
    
    // スクロールボタンの位置を設定
	int scrollBtnCenter = calcTablePosition().y + getTableHeight() / 2;
	btn_scroll_right_01Btn->setPosition(ccp(btn_scroll_right_01Btn->getPositionX(), scrollBtnCenter));
	btn_scroll_left_01Btn->setPosition(ccp(btn_scroll_left_01Btn->getPositionX(), scrollBtnCenter));
    
    // ボタンの動作を定義
	btn_scroll_right_01Btn->setTarget(this, menu_selector(CharaListTable::pushScrollBtn));
	btn_scroll_left_01Btn->setTarget(this, menu_selector(CharaListTable::pushScrollBtn));
}

void CharaListTable::pushScrollBtn(NFMenuItemSprite* sender) {
	playSoundEffect("LN_ninjase015.m4a");
    m_table->scrollPage(sender == btn_scroll_right_01Btn ? 1 : -1);
}

void CharaListTable::resetTable(){
    if( m_table ){
        m_table->removeFromParentAndCleanup(true);
        m_table = NULL;
        pageDictionary->removeAllObjects();
        cellCount=0;
    }
}
CCPoint CharaListTable::calcTablePosition(){
    float posY = (960 - 444) - 322 / 2 + (winHeight - winHeightMin) / 2 - getTableHeight() / 2;
    if( getListNumY() == LISY_MIN_NUM_Y ){
        posY = posY + (winHeight - winHeightMin) / 4;
    }
    return CCPoint(0, posY);
}

CCPoint CharaListTable::calcCellPosition(int xCnt, int yCnt){
    int listNumY = getListNumY();   //タテ何列か
    return ccp(xCnt * m_cellSize.width + 87 + 82,
               (listNumY - yCnt) * m_cellSize.height -73);
}

void CharaListTable::reroadTable(){
    resetTable();
    
    m_table = NFTableView::create(this, CCSizeMake(640.0, getTableHeight()), true);
    m_table->setDirection( kCCScrollViewDirectionHorizontal );
    m_table->setDelegate(this);
    m_table->setPosition(calcTablePosition());// テーブル位置設定
    this->addChild(m_table);
    m_table->setNFTableViewDelegate(this);
    
    onPagingEnded(m_table, 0);
    m_table->reloadData();
    
    dottoPosY = m_table->getPositionY()+8;
}

int CharaListTable::getListNumY() {
	return LISY_MIN_NUM_Y + (winHeight - 960) / m_cellSize.height; //NFCharaTableCellSize.height;
}

int CharaListTable::getTableHeight() {
	return getListNumY() * m_cellSize.height + 16;
}

int CharaListTable::getMaxPageNum() {
	return (cellCount - 1) / (getListNumY() * listXNum)+1;
}
void CharaListTable::scrollViewDidScroll(CCScrollView* view){
}

bool CharaListTable::canDispAlreadyPage(cocos2d::extension::CCTableViewCell *page){
    return true;
}

int CharaListTable::getMaxCellNum(){
    return 1;
}

NFCharaTableCell* CharaListTable::createCell(int idx){
    NFCharaTableCell* tablecell =  NFCharaTableCell::create();
    return tablecell;
}

CCTableViewCell* CharaListTable::createPageView(){
    CCTableViewCell* tablecell = new CCTableViewCell();
    tablecell->autorelease();
    return tablecell;
}

CCTableViewCell* CharaListTable::createPage(unsigned int idx){
    int listNumY = getListNumY();   //タテ何列か
    bool isLoopEnd=false;
    int cellIndex = idx * listNumY * listXNum;
    
    CCTableViewCell* page = createPageView();//BuddyCharaListTablePage::create();
    
	for(int yCnt = 0; yCnt < listNumY && !isLoopEnd; yCnt++) {
		for(int xCnt = 0; xCnt < listXNum ; xCnt++) {
            NFCharaTableCell* cell = createCell(cellIndex);
            if( cell ){
                CCPoint pos = calcCellPosition(xCnt, yCnt);
                cell->setPosition(pos);
                cell->setIndex(cellIndex);
                page->addChild(cell);
            }
            
			cellIndex++;
			if(cellIndex >= getMaxCellNum()){ //buddyListMax) {
                isLoopEnd=true;
                break;
			}
		}
	}
    
    return page;
}

//リスト１ページ分生成
CCTableViewCell* CharaListTable::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell* page = (CCTableViewCell*)pageDictionary->objectForKey(idx);
	if(page ) {
        if( canDispAlreadyPage(page) ){
            return page;
        }else{
            pageDictionary->removeObjectForKey(idx);
            page->removeFromParentAndCleanup(true);
        }
	}
    
    page = createPage(idx);
	pageDictionary->setObject(page, idx);
    return page;
}

unsigned int CharaListTable::numberOfCellsInTableView(CCTableView *table){
	return getMaxPageNum();
}
CCSize CharaListTable::cellSizeForTable(CCTableView *table){
    return CCSizeMake(640, getTableHeight());
}

// ページング用の点の設定
void CharaListTable::initPagingDotto() {
    // データ初期化
	highlightDotto = NULL;
	
	CCObject* _pagingDotto;
	CCARRAY_FOREACH(pagingDottoArray, _pagingDotto) {
		CCSprite* pagingDotto = (CCSprite*)_pagingDotto;
		pagingDotto->removeFromParentAndCleanup(true);
	}
	pagingDottoArray->removeAllObjects();
	
	// ドット追加
	int maxPageNo = getMaxPageNum();
    int leftDottoX = 304 - DOTTO_INTERVAL_X * (maxPageNo - 1) / 2;
	for(int i = 0; i < maxPageNo; i++) {
		CCSprite* point_scroll_011 = CCSprite::create("point_scroll_01.png", CCRectMake(0, 0, DOTTO_SIZE, DOTTO_SIZE));
		point_scroll_011->setAnchorPoint(ccp(0.0, 1.0));
		point_scroll_011->setPosition(ccp(leftDottoX + i * DOTTO_INTERVAL_X,
                                          dottoPosY));
		this->addChild(point_scroll_011);
		
		pagingDottoArray->addObject(point_scroll_011);
	}
	
	refreshPagingDotto();
}

void CharaListTable::refreshPagingDotto() {
    if (showingPageNo < 0) {
        return;
    }
	if(highlightDotto) {
		highlightDotto->setTextureRect(CCRectMake(0, 0, DOTTO_SIZE, DOTTO_SIZE));
	}
	
	int pagingDottoCount = pagingDottoArray->count();
	if(pagingDottoCount > showingPageNo) {
		highlightDotto = (CCSprite*)pagingDottoArray->objectAtIndex(showingPageNo);
		highlightDotto->setTextureRect(CCRectMake(DOTTO_SIZE, 0, DOTTO_SIZE, DOTTO_SIZE));//ページングのドットを青くする
	}
}

void CharaListTable::onPagingEnded(NFTableView* table, int pageNo) {
    CC_UNUSED_PARAM(table);
    
	showingPageNo = pageNo;
	initPagingDotto(); // 毎回生成するのはコストがでかすぎませんかね
    
    int maxPageNo = getMaxPageNum();
    
    btn_scroll_left_01Btn->setVisible(pageNo > 0);
	btn_scroll_right_01Btn->setVisible(pageNo < maxPageNo - 1);
}

void CharaListTable::setEnabled(bool _st){
    btn_scroll_right_01Btn->setEnabled(_st);
	btn_scroll_left_01Btn->setEnabled(_st);
    
    if(_st){
    }else{
        deleteDragIcon();
    }
}

void CharaListTable::pagingBack() {
    m_table->scrollPage(showingPageNo);
    if( showingPageNo >= 0 ){
        initPagingDotto();
    }
}

//dragg
void CharaListTable::endDragged(){
    deleteDragIcon();
}

void CharaListTable::deleteDragIcon(){
    if (m_draggingIcon) {
        m_draggingIcon->removeFromParentAndCleanup(true);
        m_draggingIcon=NULL;
    }
}
void CharaListTable::makeCreateIcon(NFCharaTableCell* _cell){
    deleteDragIcon();
    m_draggingIcon = createDragIcon(_cell);
    getParent()->addChild(m_draggingIcon, 100);
}
CCSprite* CharaListTable::createDragIcon(NFCharaTableCell *_cell){
    CCSprite* ico = CCSprite::create("ico_cursor_05.png");
    return ico;
}

//touch
//仲間リストテーブルの押されたBuddyTableCellを返す
NFCharaTableCell* CharaListTable::getPushedBuddyOnList(CCPoint location) {
    
    CCTableViewCell* cell = (CCTableViewCell*)pageDictionary->objectForKey(showingPageNo);
    if(!cell) return NULL;
    
    CCObject* child;
    CCARRAY_FOREACH(cell->getChildren(), child) {
        NFCharaTableCell* parsedCell = dynamic_cast<NFCharaTableCell*>(child);
        if( !parsedCell ) continue;
        
        int parsedBuddyX = parsedCell->getPositionX() + m_table->getPositionX();
        int parsedBuddyY = parsedCell->getPositionY() + m_table->getPositionY();
        int width = parsedCell->getCellSize().width;
        int height = parsedCell->getCellSize().height;
        // anchorPointはccp(0.5, 0.5)
        if(parsedBuddyX - width / 2 < location.x
           && parsedBuddyX + width / 2 > location.x
           && parsedBuddyY + height / 2 > location.y
           && parsedBuddyY - height / 2 < location.y) {
            return parsedCell;
        }
    }
	
	return NULL;
}

void CharaListTable::checkHoldCell(cocos2d::CCPoint location){
    m_holdCell = getPushedBuddyOnList(location);
    if(m_holdCell) {
        m_holdCell->pushed();
	}
}
void CharaListTable::resetHoldCell(){
	if(m_holdCell != NULL) {
        m_holdCell->canselPushed();
		m_holdCell = NULL;
	}
    deleteDragIcon();
}

bool CharaListTable::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
    if( delegate && delegate->doBanTouchToTable ) return false;
    if(pTouch->getID() > 0) {
		return false;
	}
    if( !m_doScrollLock ) m_table->ccTouchBegan(pTouch, pEvent);
    
    CCPoint locationInView = pTouch->getLocationInView();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(locationInView);
    // 選択中の仲間を求める
	checkHoldCell(location);
    return m_holdCell; //該当がないとNULL
}

void CharaListTable::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    if( delegate && delegate->doBanTouchToTable ) return;
    
    CCPoint locationInView = pTouch->getLocationInView();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(locationInView);
    
	// 横方向の移動（スクロール）か縦方向の移動（味方のドラッグ）か判定する
	if(delegate->touchMode == kSelectBuddyTouchModeUnknown) {
        checkTouchMode(location);
        if( delegate->touchMode == kSelectBuddyTouchModeVertical ){
            //縦方向だったらテーブルの横スクロールを止める
            if( !m_doScrollLock ) m_table->ccTouchEnded(pTouch, pEvent);
        }
    }
    
    switch (delegate->touchMode) {
        case kSelectBuddyTouchModeUnknown:
            //なにもしない
            break;
        case kSelectBuddyTouchModeHorizontal:
            //テーブルを横にスクロール
            if( !m_doScrollLock ) m_table->ccTouchMoved(pTouch, pEvent);
            break;
            
        case kSelectBuddyTouchModeVertical:
            if( m_holdCell ){
                if(m_draggingIcon) {
                    m_draggingIcon->setPosition(location);
                }
            }
            break;
        default:
            break;
    }
    
}

void CharaListTable::checkTouchMode(cocos2d::CCPoint location){
    float moveDiffX = location.x - delegate->touchBeganPoint.x;
    float moveDiffY = location.y - delegate->touchBeganPoint.y;
    if(sqrt(moveDiffX * moveDiffX + moveDiffY * moveDiffY) > 30) {
        if(moveDiffX == 0 ? moveDiffY < 0 : atan(moveDiffY / abs(moveDiffX)) < M_PI * 15 / 180) {
            //横方向の移動（スクロール）
            delegate->touchMode = kSelectBuddyTouchModeHorizontal;
            resetHoldCell();
        } else if(m_holdCell) {
            //縦方向の移動（味方のドラッグ）
            delegate->touchMode = kSelectBuddyTouchModeVertical;
            
            //ドラッグ可能かチェック
            if(delegate->canDragged(m_holdCell)
               && !m_holdCell->isDraggedLock()){
                m_holdCell->beginDragged();
                makeCreateIcon(m_holdCell);//指のとこに出るアイコンを生成
            }else{
                m_holdCell->canselPushed();
                m_holdCell = NULL;
                delegate->touchMode = kSelectBuddyTouchModeUnknown;
            }
        }
    }
}

void CharaListTable::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    if( delegate && delegate->doBanTouchToTable ) return;
    
    CCPoint location;
	if(pTouch) {
		CCPoint locationInView = pTouch->getLocationInView();
		location = CCDirector::sharedDirector()->convertToGL(locationInView);
        if( !m_doScrollLock ) m_table->ccTouchEnded(pTouch, pEvent);
	} else {
		location = ccp(-1, -1);
	}
    
    switch (delegate->touchMode) {
        case kSelectBuddyTouchModeUnknown:
            if(m_holdCell) {
                CCSprite* touchEndSprite = getPushedBuddyOnList(location);
                if(touchEndSprite == m_holdCell
                   && delegate->tapBuddyCell(m_holdCell, location))
                {
                    tapCell(m_holdCell); // リスト部分のタップ
                }
            }
            break;
        case kSelectBuddyTouchModeVertical:
            if(m_holdCell) {
                //ドラッグ終了なら選択されていたセルをdelegateに渡す
                if(delegate->touchEndSelectedBuddyCell(m_holdCell,location)){
                    m_holdCell=NULL;
                }
            }
            break;
            
        default:
            break;
    }
    
    resetTouch();
}

void CharaListTable::resetTouch(){
    resetHoldCell();
    m_table->resetTouched();
}

void CharaListTable::tapCell(NFCharaTableCell *_cell){
    playSoundEffect("LN_ninjase015.m4a");
    
}

