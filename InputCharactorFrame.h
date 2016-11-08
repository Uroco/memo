//
//  InputCharactorFrame.h
//  NinjaFlight
//
//  Created by KUBO AYAMI on 2014/10/02.
//
//

#ifndef __NinjaFlight__InputCharactorFrame__
#define __NinjaFlight__InputCharactorFrame__

#import "NFSpriteCluster.h"

/*
 忍者本体の動くアニメとレベル、レア星のセット表示
 */
class NFNumberLayer;
class CharaProfileSprite : public NFSpriteCluster{
    CharaProfileSprite();
public:
    CCSprite* levelIcon;
    NFNumberLayer* levelNumber;
    CCSprite* rareIcon;
    NFSpriteCluster* animation;
    
    void changeLevel(int lv);
    void changeRare(int rare);
    void showBuddy(int attr, int rare, int lv, int costumeType);
    void showPlayer(int kind, int lv, int evolutionType, bool isMine);
    void showGuardian(int _id);
    
    static CharaProfileSprite* create();
    static CharaProfileSprite* createBuddy(int attr, int rare, int lv, int costumeType);
    static CharaProfileSprite* createPlayer(int kind, int lv, int evolutionType, bool isMine);
    static CharaProfileSprite* createGuardian(int _id);
};

/*
 ショップ画面などの仲間とかをドラッグしてセットする四角い枠パーツ
 */
class InputFrameMenuItem;
class InputCharactorFrame:public NFSpriteCluster{
protected:
    friend class InputFrameMenuItem;
    
    CCSprite* statusBg;
    CCSprite* frame;
    cocos2d::CCRect frameRect;
    
    std::string m_statusBgName_lock;
    std::string m_statusBgName_dark;
    std::string m_statusBgName_bright;
    std::string m_frameName;
    std::string unselectFrameName;
    std::string selectedFrameName;
    
    CharaProfileSprite* m_profileSprite;
    
    //lock
    CCSprite* ico_rock;
    CCSprite* lv_rock_bg;
    NFNumberLayer* lockLevelNumber;
    
    bool m_isLocked;
    bool m_isSelected;  //仲間が設定されているとtrue
    int m_positionNo;
    bool m_canDragged;  //ドラッグできるかどうか
    
    InputCharactorFrame();
    virtual bool init();
    virtual CCSprite* createStatusBg();
    virtual void initLocked();
    virtual void initOpened();
    virtual void changeFrameImage();
    
    virtual int getUnlockLevel(int _positionNo)=0;
    
    virtual void framePushed();
    virtual void resetPushed();
public:
    bool isLocked(){ return m_isLocked; }
    bool isSelected(){return m_isSelected; }
    int getPositionNo(){ return m_positionNo; }
    CCSprite* getFrame(){ return frame; }
    bool canDragged(){ return m_canDragged; }
    
    bool isTouched(cocos2d::CCPoint location);
    
    void blink(bool _blind);

    NFSpriteCluster* getAnimation();
};

/*
 ドラッグしている際に、InputCharactorFrameの枠の絵がかわるための仕組み
 InputFrameMenuItem　と　InputFrameMenuをセットで使う
 同じタッチ判定を共有するInputFrameMenuItemは、すべて同じInputFrameMenuに入れてください
 */

//これを継承したクラスは、InputFrameMenuのタッチ判定を受け取ることができます
class InputFrameMenuDelegate{
public:
    virtual void touchBegan(cocos2d::CCPoint location, InputCharactorFrame* _pushFrame)=0;
    virtual void touchMoved(cocos2d::CCPoint location)=0;
    virtual void touchEnded(cocos2d::CCPoint location, InputCharactorFrame* _activateFrame)=0;
};

//ボタンひとつ
class InputFrameMenuItem : public cocos2d::CCMenuItem{
    InputCharactorFrame* m_inputFrame;
public:
    static InputFrameMenuItem* create(InputCharactorFrame* _frame);
    virtual void selected();
    virtual void unselected();
    InputCharactorFrame* getInputFrame(){ return m_inputFrame; };
};

//ボタン統括レイヤ
class InputFrameMenu:public cocos2d::CCMenu{
    InputFrameMenuDelegate* delegate;
public:
    static InputFrameMenu* create(InputFrameMenuDelegate* _delegate);
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif /* defined(__NinjaFlight__InputCharactorFrame__) */
