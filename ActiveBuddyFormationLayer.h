//
//  ActiveBuddyFormationLayer.h
//  NinjaFlight
//

#ifndef __NinjaFlight__ActiveBuddyFormationLayer__
#define __NinjaFlight__ActiveBuddyFormationLayer__

/*  ActiveBuddyFormationLayer
*      仲間編成クラスファイル
 ドラッグアンドドロップで、仲間の編成を行うパーツ。 
 Frame と　Layerでワンセット。
*/
#import "InputCharactorFrame.h"

/*-----------------------------
 *  ActiveBuddyFrame
 *      仲間をはめる枠クラス
 ------------------------------*/
using namespace cocos2d;
class NFNumberLayer;
class Buddy;
class UserBuddyData;

class ActiveBuddyFrame : public InputCharactorFrame {
protected:
    int buddyNo;
    int buddyRank;
    int buddyLevel;
    
    ActiveBuddyFrame();
    virtual bool init();
    virtual void initOpened();
    virtual int getUnlockLevel(int _positionNo);
public:
	static ActiveBuddyFrame* create(int _positionNo, bool _isLocked);
    virtual void selectBuddy(UserBuddyData* userBuddyData);
    virtual void deselectBuddy(bool _blindBg);
    
    int getBuddyNo(){ return buddyNo; }
    int getNinjaPower();
};

/*-----------------------------
 *  ActiveBuddyFormationLayer
 *      仲間編成クラス
 ------------------------------*/
class ActiveBuddyFormationLayerDelegate{
public:
    virtual void selectActiveBuddy(ActiveBuddyFrame* _activeBuddyFrame, UserBuddyData* userBuddyData)=0;
    virtual void deselectActiveBuddy(ActiveBuddyFrame* _activeBuddyFrame)=0;
    virtual void tapActiveBuddyFrame(ActiveBuddyFrame* _activeBuddyFrame){};
};

class NinjaPowerInfo;
class ActiveBuddyFormationLayer : public CCLayer , InputFrameMenuDelegate{
protected:
    ActiveBuddyFormationLayerDelegate* delegate;
    CCNode* m_draggedIconParent;
    InputFrameMenu* m_inputFrameMenu;
    NinjaPowerInfo* m_mineNinjaPower; // キャラの忍者パワー
    bool isChangedActiveBuddy;  //キャラを変更したかどうか
    
    ActiveBuddyFormationLayer();
    virtual bool init();
    ActiveBuddyFrame* createBuddySelectFrame(int position);
    
    //ここから呼び出されるポジションに枠が配置される
    virtual CCPoint getBuddyPosition(int position);
    //フレームを１つ作るときこれが呼ばれる
    virtual ActiveBuddyFrame* createFrame(int position, int isLocked);
    //フレームがタップされた際に呼ばれる
    virtual void tapFrame(ActiveBuddyFrame* _frame);
    //フレームの中身が交換される際呼ばれる
    virtual void exchange(ActiveBuddyFrame* selectFrame, ActiveBuddyFrame* touchFrame);
    //ドラッグしてエリア外に行ったとき呼ばれる
    virtual void draggedOut(ActiveBuddyFrame* _frame);
    //ドラッグ中に指のところに表示するアイコンを生成する
    virtual CCSprite* createDraggedIcon(int buddyNo);
    
    //編隊に入れる
    virtual void join(int buddyPosition, UserBuddyData* userBuddyData);
    virtual void join(ActiveBuddyFrame* activeBuddyInfo, UserBuddyData* userBuddyData);
    
public:
    ~ActiveBuddyFormationLayer();
    CREATE_FUNC(ActiveBuddyFormationLayer);
    void initActiveBuddy();
    
    CCArray* selectedActiveBuddyArray;  //ActiveBuddyFrame配列
    ActiveBuddyFrame* selectedActiveBuddyFrame;  //ドラッグ開始時に選択されていた仲間選択枠
	CCSprite* draggingBuddyPointerIcon; //ドラッグ時　指についてくるあいこん
    
    void setDelegate(ActiveBuddyFormationLayerDelegate* _delegate){ delegate = _delegate; }
    
    //blink
    bool isBlindStatusBg;
	virtual void blinkBuddyBg();
    
	ActiveBuddyFrame* getSelectedActiveBuddyFrame(CCPoint location);
    ActiveBuddyFrame* getSelectedActiveBuddyFrame(int position);
    ActiveBuddyFrame* getSelectedActiveBuddyFrameByBuddyNo(int buddyNo);
    
    //入れ替え　先に入っているのがあれば選択解除して入れる
    virtual void replace(int buddyPosition, UserBuddyData* userBuddyData);
    //編隊から外す
	virtual void defect(int buddyPosition);
    // 削除する味方を選択してたら選択解除
    void removeBuddy(int buddyNo);
    
    //delegate
    virtual void touchBegan(cocos2d::CCPoint location, InputCharactorFrame* _pushFrame);
    virtual void touchMoved(cocos2d::CCPoint location);
    virtual void touchEnded(cocos2d::CCPoint location, InputCharactorFrame* _activateFrame);
    void touchFinish();    //タッチの流れが終了した際
    
    //セットしてる仲間をセーブ
    void saveBuddyData();
    //引数の仲間ナンバーが選択されている数を返す
    int getSelectedBuddyCnt(int _buddyNo);
    //ドラッグするときに出るアイコンの親レイヤー設定　デフォルトは自分の親
    void setDraggedIconParent(CCNode* parent){ m_draggedIconParent = parent; }
    
    void entryNinjaPowerPlayer(int kind, int lv, int evolutionType);
    void resetActiveNinjaPower();
};
/*　仲間編成　基底部分　終了 */

/*
 Shop画面用　編成レイヤー
 ActiveBuddyFormationLayer 継承
 */
typedef enum {
    SelectBuddyPowerUpTag, // 強化
    SelectBuddyEvoTag,     // 進化
    SelectBuddyEmptyTag,     //空
    SelectBuddyNoneTag,    // なにもできない
    SelectBuddyLockTag, //ロックがかかっている
} SelectBuddyTag;

class ShopActiveBuddyFrame : public ActiveBuddyFrame{
    CCSprite* logo_change_buddy_01_powerup;
    CCSprite* logo_change_buddy_01_evo;
    CCSprite* logo_change_buddy_01_select;
    
    ShopActiveBuddyFrame();
    virtual void initOpened();
    UserBuddyData* setUserBuddyData;
    
    virtual void changeFrameImage();
    
    void checkSelectFrameName();
public:
    static ShopActiveBuddyFrame* create(int _positionNo, bool _isLocked);
    virtual void selectBuddy(UserBuddyData* userBuddyData);
    virtual void deselectBuddy(bool _blindBg);
    
    SelectBuddyTag checkSelectBuddyTag();
    
    void hideFrame();
};

#import "ActiveGuardianFrame.h"
class ShopActiveGuardianFrame : public ActiveGuardianFrame{
    CCSprite* logo_change;
    static const char* unselectLogoName;
    static const char* selectedLogoName;
    
    virtual void initOpened();
    virtual void changeFrameImage();
public:
    static ShopActiveGuardianFrame* create(int _positionNo, bool _isLocked);
    void hideFrame();
};

class ShopActiveBuddyFormationLayer : public ActiveBuddyFormationLayer{
    ShopActiveGuardianFrame* m_activeGuardianFrame;

    virtual ActiveBuddyFrame* createFrame(int position, int isLocked);
    
    virtual CCSprite* createDraggedIcon(int buddyNo);
    virtual void tapFrame(ActiveBuddyFrame* _frame);
    
    virtual bool init();
    virtual void initGuardianFrame();
    virtual void blinkBuddyBg();
    
    void goToSelectGuardian();
    
//    virtual void join(ActiveBuddyFrame* activeBuddyInfo, UserBuddyData* userBuddyData);
//    virtual void defect(int buddyPosition);//編隊から外す
public:
    virtual CCPoint getBuddyPosition(int position);
    virtual CCPoint getGuardianPosition(int position);
    
    static ShopActiveBuddyFormationLayer* create();
    NFSpriteCluster* deliverBuddyEntity(int position);    //引き渡し
    NFSpriteCluster* deliverGuardianEntity(int position);    //引き渡し
    void startFadeOut(float time);
    void hideFrame();
    
//    virtual void touchEnded(cocos2d::CCPoint location, InputCharactorFrame* _activateFrame);
};


#endif /* defined(__NinjaFlight__ActiveBuddyFormationLayer__) */
