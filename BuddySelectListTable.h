//
//  BuddySelectListTable.h
//  NinjaFlight
//

#ifndef __NinjaFlight__BuddySelectListTable__
#define __NinjaFlight__BuddySelectListTable__

#import "cocos2d.h"
#import "BuddyData.h"
#import "NFNumberLayer.h"
#import "BuddyDetailDialog.h"
#import "User.h"
#import "CharaListTable.h"


using namespace cocos2d;

/* BuddyTableCell
 * リスト内　仲間一人分のセルオブシェクト
 */
typedef enum{
    kType_Buddy =0
    ,kType_cGold  //金チーズ
    ,kType_cSilver //銀チーズ
    ,kType_Metal    //メタル忍者
}UnionMateriaType;

class BuddyTableCell : public NFCharaTableCell {
private:
    CCPoint positionDiff;
    bool showRegularFrame;  //使用中枠を使用するか
    bool m_isCheese;
    bool m_isFavorite;
    NFNumberLayer* num_batch_a_01;
    
    BuddyTableCell();
    bool init(UserBuddyData* _buddyData, UnionMateriaType _type, int _num, bool _isUsing = false, bool _showRegularFrame=false);
    void initBuddyCell();
    void initCheeseCell();
    void initSubBuddyCell();
    
    virtual void calcLeftNum(bool _isSelect, bool cansel);
    virtual bool isChangeTexture(SelectStatus state);
    
    void createEvolutionIcon(bool _isMaterial, CCSprite* _parent);
    void startIconAnimation(CCSprite* _parent);
    
    UnionMateriaType cellType;
    CCSprite*   m_materialEvolutionCover;
    CCSprite* evelutionIcon;    //進化可能アイコン
public:
    ~BuddyTableCell();
    static BuddyTableCell* create(UserBuddyData* _buddyData, bool _isUsing = false, bool _showRegularFrame=false);
    static BuddyTableCell* createCheese(UnionMateriaType _type, int _num);
    static BuddyTableCell* createMetalBuddy(int no, int _num, bool _isUsing, bool _showRegularFrame=false);
    
    static CCSprite* createCheeseSprite(int buddyNo, bool isSmall);
    
    UserBuddyData* buddyData;
    
    bool isGoldCheese(){ return cellType == kType_cGold; }
    bool isSilverCheese(){ return cellType == kType_cSilver; }
    bool isCheese(){ return m_isCheese; }
    bool isFavorite(){ return m_isFavorite; }
    
    void conversionEvolutionMode(UserBuddyData* _buddyData);
    void conversionBasic();
    
    void refreshFlashAnimation();
};

/*-----------------------
 *  Buddy List Data
 ------------------------*/

#define CHEESE_GOLD_NO -1
#define CHEESE_SILVER_NO -2

class BuddyListData:public CCObject{
    bool isTutorialMode;
    bool isExistCheese;
    bool m_isExistMetal;
    bool init(bool _isTutorial, bool _isExistCheese, bool _isExistMetal);
    CCArray* m_metalArray;
    
    //sort
    CCArray* lowRankSort(CCArray* buddyArray);
    CCArray* highRankSort(CCArray* buddyArray);
    CCArray* attributeSort(CCArray* buddyArray);
    
    CCArray* sift(CCArray* _buddyDataArray, int value, bool (BuddyListData::*_comparisonFunc)(int comparisonNum, UserBuddyData* buddyData));
    CCArray* siftRank(CCArray* _buddyDataArray, int rank);
    CCArray* siftAttr(CCArray* _buddyDataArray, int attr);
    CCArray* sortCostumeType(CCArray* buddyDataArray, int type);
    bool comparisonRank(int comparisonNum, UserBuddyData* buddyData);
    bool comparisonAttr(int comparisonNum, UserBuddyData* buddyData);
    bool comparisonCostumeType(int comparisonNum, UserBuddyData* buddyData);
    
    void sortLevel(CCArray* buddyDataArray);
    void excuteBubbleSort(CCArray* buddyDataArray,bool (BuddyListData::*_comparisonFunc)(UserBuddyData* buddyData, UserBuddyData* nextBuddyData));
    bool comparisonLevel(UserBuddyData* buddyData, UserBuddyData* nextBuddyData);//大きい順
    
public:
    BuddyListData();
    ~BuddyListData();
    static BuddyListData* create(bool _isTutorial, bool _isExistCheese, bool _isExistMetal = true);
    
    CCArray* listBuddy; //リスト用　全仲間配列　これに入っている仲間がリストとして生成される。
    CCDictionary* allBuddyDictionary;   //仲間NoでUserBuddyDataを引用用
    
    //使用中仲間データ
    UserBuddyData* m_usingBuddydata[MAX_BUDDY_NUM];
    int usingBuddycnt;
    void reloadBuddyData();
    
    //cheese
    static bool checkCheeseNo(int buddyNo); //チーズならtureを返す
    static bool isGoldCheese(int buddyNo);
    static bool isSilverCheese(int buddyNo);
    int getGoldCheeseCount();
	int getSilverCheeseCount();
	int getCheeseOffset();
    
    //metal buddy
    void setExistMetal(bool st){ m_isExistMetal = st; }
    bool isExistMetal(){ return m_isExistMetal; }
    int getMetalBuddyOffset();
    
    UserBuddyData* getUserBuddyData(int buddyNo); //チーズならNULL
    void setBuddyList(CCArray* _array);
    
    //sort
    void sort();
    void excuteSort(BuddySortPattern _sortPattern);
    bool sortAndPatternSaved(BuddySortPattern sortPattern); //saveしたらtrueを返す
    
    //metal
    CCArray* getMetalArray(){ return m_metalArray; }
    void makeMetalBuddyArray();
};

/*----------------------------------
 *  BuddySelectListTablePage
 *      １ページの管理クラス
 -----------------------------------*/
class BuddySelectListTablePage : public CCTableViewCell{
    bool m_isEvolution; //進化合成モード
    bool init();
public:
    CREATE_FUNC(BuddySelectListTablePage);
    void conversionGouseiEvolutionMode(UserBuddyData *_baseBuddyData);
    void conversionBasicMode();
    void startFlashingAnimation();
};

/*----------------------------------
 *  CharaListTableDelegate
 *  @埋め込む画面はこのクラスを継承してください。
 -----------------------------------*/
class BuddySelectListTableDelegate:public CharaListTableDelegate{
//protected:
//    BuddySelectListTableDelegate();
public:
    //仲間を売れるかの判定　売れる場合はtrueをかえすようにしてください
    virtual bool canBuddySell(UserBuddyData* sellUserBuddyData)=0;
    
    //仲間売却ボタンが押された時通知する
    virtual void pushBuddySellBtn(UserBuddyData* sellUserBuddyData){}
    //仲間を売り終わった時通知する
    virtual void finishSellBuddy(int afterCoin)=0;
    virtual void pushBuddyListSortButton(){}    //並び替えボタンを押したときに呼ばれる
    virtual void closeBuddyListSortDialog(){}   //ソート選択ダイアログが閉じたときに呼ばれる
    virtual void pushFavoriteBtn(BuddyTableCell* cell){}//お気に入りボタンが押された時呼ばれる
    virtual void closeBuddyDetailDialog(){} //仲間詳細ダイアログが閉じた時呼ばれる
    virtual void openBuddyDetailDialog(BuddyDetailDialog* dialog){} //仲間詳細ダイアログが開く直前に呼ばれる
};


/*----------------------------
 *  BuddySelectListTable
 -----------------------------*/
typedef enum{
    kEmbedded_SelectBuddy,  //仲間選択画面
    kEmbedded_Gousei        //合成画面
}EmbeddedScene;
class BuddySelectListTable: public CharaListTable
{
#define DELEGATE ((BuddySelectListTableDelegate*)delegate)
    BuddySelectListTable();
    bool init();
    
    BuddyListData* m_buddyListData;
    CCDictionary* buddyCellDictionary; //BuddyTableCell* 引用用
    CCArray* newBuddyArray;
    EmbeddedScene m_enbeddedScene;  //埋め込み画面
    
    //evolution
    bool m_isEvolution;
    UserBuddyData* m_evolutionBaseBuddy;
    
    virtual bool canDispAlreadyPage(CCTableViewCell* page);
    virtual CCTableViewCell* createPageView();
    virtual CCTableViewCell* createPage(unsigned int idx);
    virtual NFCharaTableCell* createCell(int idx);
    
    //cell create
    BuddyTableCell* createBuddyCell(int buddisIndex);
    BuddyTableCell* createCheeseCell(int buddisIndex);
    BuddyTableCell* createMetalBuddyCell(int buddisIndex, int cheeseOffset, int metalOffset);
    
    //conversion mode
    void conversionGouseiEvolutionModeAtPage(BuddySelectListTablePage* _page, UserBuddyData *_baseBuddyData);
    void conversionBasicModeAtPage(BuddySelectListTablePage* _page);
    void inspectionMode(BuddySelectListTablePage* _page);
    
    //sort
    CCMenu* m_sortBtnMenu;
    void createSortBtn();
    void pushSortBtn();
    void pushedSortChange(CCObject* sender);
    void pushedSortClose();
    
    //favorite
    void pushedFavoriteBtn(UserBuddyData* userBuddyData);
    
    //detailDialog
    void closeBuddyDetailDialog(UserBuddyData* userBuddyData);
    
    //page
    virtual void createBG();
    
public:
    ~BuddySelectListTable();
    static BuddySelectListTable* create(BuddyListData* data, BuddySelectListTableDelegate* _delegate, EmbeddedScene _enbeddedScene);

    virtual int getMaxPageNum();
    virtual int getMaxCellNum();
	
    BuddyTableCell* getBuddyTableCell(int buddyNo);
    
    void sellBuddy(UserBuddyData* removedUserBuddyData);
    void finishSellBuddyCallBack(CCDictionary* map);
    virtual void onPagingEnded(NFTableView* table, int pageNo);
    void showPageAtBuddyNo(int buddyNo);
    
    //drag
    virtual CCSprite* createDragIcon(NFCharaTableCell* _cell);
    static CCSprite* createDragIcon(UserBuddyData* _buddyData, bool isCheese);
    
    //evolution gousei
    void reloadEvolutionGouseiMode(UserBuddyData* _buddyData);
    void reloadBasicMode();

    virtual void tapCell(NFCharaTableCell* _cell);
    void showBuddyDetail(BuddyTableCell* selectedBuddyCell); //リスト内たっぷで仲間詳細表示
    
    bool isUsing(UserBuddyData* _userBuddyData);
    virtual void reroadTable(); //リスト再読み込み(再生成)
    void setSortLock(bool st);  //ソートボタンを押せなくする
};

class BuddyListSortDialog:public CCLayer{
    CCObject* callbackTarget;
    SEL_MenuHandler sortBtnPushed;
    SEL_MenuHandler dialogClose;
    
    CCLayer* tutorialLayer;
    NFMenuItemSprite* btn_close_xs_01Btn;
    TopPriorityMenu* menu;
    
    void createDialogBg();
    bool init();
    void onPushSort(CCObject* sender);
    void close();
    void showSortTutorialDialog();

    void tutorialClose();
public:
    static BuddyListSortDialog* create(CCObject* _callbackTarget, SEL_MenuHandler _sortBtnPushed, SEL_MenuHandler _dialogClose);
};


#endif /* defined(__NinjaFlight__BuddySelectListTable__) */
