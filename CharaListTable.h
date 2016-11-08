//
//  CharaListTable.h
//  NinjaFlight
//
//  Created by KUBO AYAMI on 2014/09/17.
//
//

#ifndef __NinjaFlight__CharaListTable__
#define __NinjaFlight__CharaListTable__

#import "cocos2d.h"
#import "CCNodeUtil.h"
#import "NFTableView.h"

using namespace cocos2d;

typedef enum {
    kSelectStatusNone,
    kSelectStatusPushed,
    kSelectStatusSelected,
    kSelectStatusSelectedPushed
} SelectStatus;

const static CCSize DefaultCellSize = CCSize(154.0, 158.0); //仲間リストのサイズ
#define TAG_CHECK_ICON 100

class NFCharaTableCell : public CCSprite {
protected:
     //(154.0, 158.0);
    
    bool isSelect;
    bool isPush;
    bool isUsing;   //デッキに使用中
    int  index;
    bool m_isDraggedLock;    //ドラッグ不可
    bool m_isEmpty;
    
    int hasNum; //所持数
    int leftNum; //残りの数
    CCPoint m_icoCheckPos;
    
    CCSprite* buddy_s_0_11; //セルの仲間アイコン
    CCSprite* btn_select_pet_s_011; //ボタン背景
    
    virtual void changeBtnState(SelectStatus state);
    virtual bool isChangeTexture(SelectStatus state);
    virtual void calcLeftNum(bool _isSelect, bool cansel);
    virtual void onPushInList(bool _isPush);
    
    virtual void createCheckIcon();
    void removeCheckIcon();
    
    NFCharaTableCell();
public:
    CREATE_FUNC(NFCharaTableCell);
    
    void selected();    //選択された
    void deselected();  //選択状態を解除
    void pushed();      //押された
    void canselPushed();   //押されたのを解除
    
    //lock
    void lockDrag();    //暗転　ドラッグ不可にする
    void unlockDrag();
    
    //drag
    void beginDragged(); //ドラッグ開始
    
    void setIndex( int _index ){ index= _index; }
    int getIndex(){ return index; }
    
    virtual bool isSelected(){ return isSelect; }
    virtual bool isDraggedLock(){ return m_isDraggedLock; }
    int getLeftNum(){ return leftNum; }
    bool isEmpty();
    
    virtual CCSize getCellSize();
    
    // 選択状態によって画像のTextureRectを変える
	static void setTextureRectForSelectStatus(CCSprite* sprite, SelectStatus selectStatus);
};


//タッチ種類
typedef enum {
    kSelectBuddyTouchModeVertical,  //タテの動き
    kSelectBuddyTouchModeHorizontal,//横の動き
	kSelectBuddyTouchModeUnknown,   //不明
	kSelectBuddyTouchModeArea,      //選択エリア内をタッチ
	kSelectBuddyTouchModeAreaMove   //選択エリア内を移動
} SelectBuddyTouchMode;

/*----------------------------------
 *  CharaListTableDelegate
 *  @埋め込む画面はこのクラスを継承してください。
 -----------------------------------*/
class CharaListTableDelegate{
protected:
    CharaListTableDelegate();
public:
    SelectBuddyTouchMode touchMode;
    CCPoint touchBeganPoint;
    bool doBanTouchToTable;    //タッチ判定をブロック
    
    //ドラッグできるかどうかの判定 dragできる場合はtrueをかえすようにしてください
    virtual bool canDragged(NFCharaTableCell* selectedCell)=0;
    
    //選択済みかどうかの判定　選択されている数を返すようにしてください
    virtual int isSelected(int charaNo)=0;
    //セルをタップしたときに通知 tapを許可するならtrueを返すようにしてください
    virtual bool tapBuddyCell(NFCharaTableCell* selectedCell, CCPoint location)=0;
    //タッチ終了時に選択されていた仲間セル　選択されたらtrueを返すようにしてください
    virtual bool touchEndSelectedBuddyCell(NFCharaTableCell* selectedCell, CCPoint location)=0;
};


/*----------------------------
 *  CharaListTable
 -----------------------------*/

typedef enum {
    kCLTZ_BG= -10,
    kCLTZ_ScrollBtn_L = -5,
    kCLTZ_Pages = 1,
    kCLTZ_Dotto = 5,
    kCLTZ_ScrollBtn_R = 10,
}CharaListTableZOrder;
class CharaListTable:public CCLayer, NFTableViewDelegate,CCTableViewDataSource, CCTableViewDelegate
{
protected:
#define DOTTO_INTERVAL_X 32
#define DOTTO_SIZE 32
#define LIST_X_NUM 3
#define LISY_MIN_NUM_Y 2    //リストタテ列数最小値
    int     listXNum;
    int     cellCount;
    int     showingPageNo;
    bool    m_doScrollLock;
    float   dottoPosY;

    NFTableView* m_table;
    CCDictionary* pageDictionary;
    CharaListTableDelegate* delegate;
    
    //ページめくりボタン
    NFMenuItemSprite* btn_scroll_right_01Btn;
	NFMenuItemSprite* btn_scroll_left_01Btn;
    
    CCSprite* m_draggingIcon; //ドラッグ中に指のとこにでるSprite
    NFCharaTableCell* m_holdCell;      //リスト内の選択中の仲間のBuddyTableCell
    CCSize m_cellSize;

    CharaListTable();
    bool init();
    virtual void resetTable();
    
    //create cells
    virtual bool canDispAlreadyPage(CCTableViewCell* page); //既にあるページを出す時呼ばれる　falseを返すと作り直し
    virtual CCTableViewCell* createPageView();
    virtual CCTableViewCell* createPage(unsigned int idx);
    virtual NFCharaTableCell* createCell(int idx);
    
    //inherited tabele
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){};
    CCSize cellSizeForTable(CCTableView *table);
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    //page
    virtual void createBG();

    //page dot
	CCArray* pagingDottoArray;
    CCSprite* highlightDotto;   //現在青くなっているページングdot●
	void initPagingDotto();
	void refreshPagingDotto();
    
    //button
    void createScrollBtn();
    void pushScrollBtn(NFMenuItemSprite* sender);
    
    //icon
    void makeCreateIcon(NFCharaTableCell* _cell);
    void deleteDragIcon();
    virtual CCSprite* createDragIcon(NFCharaTableCell* _cell);
    void resetHoldCell();
    
    //touch
    void checkTouchMode(CCPoint location);
    void checkHoldCell(CCPoint location);
    virtual void tapCell(NFCharaTableCell* _cell);

    //calc
    virtual CCPoint calcTablePosition();
    virtual CCPoint calcCellPosition(int xCnt, int yCnt);
public:
    ~CharaListTable();
    static CharaListTable* create();
    
    //page
    virtual void reroadTable(); //リスト再読み込み(再生成)
    virtual void onPagingEnded(NFTableView* table, int pageNo);
    void pagingBack();
    
    //touch relation
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    NFCharaTableCell* getPushedBuddyOnList(CCPoint location);
    void resetTouch();
    
    //drag
    void endDragged();

    //button
    void setEnabled(bool _st);
    void setScrollLock(bool st){ m_doScrollLock = st; };

    virtual int getListNumY();
	virtual int getTableHeight();
	virtual int getMaxPageNum();
    virtual int getMaxCellNum();
    NFCharaTableCell* getNowHoldCell(){ return m_holdCell; }
};


#endif /* defined(__NinjaFlight__CharaListTable__) */
