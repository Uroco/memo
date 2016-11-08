//
//  Object.h
//  NinjaFlight
//


#ifndef __NinjaFlight__Object__
#define __NinjaFlight__Object__

#import "NFSpriteCluster.h"
#import "FixedValue.h"

enum ObjectType{
    BASE
    ,BEAM
//    ,FROG
    ,PLAYER
    ,BUDDY
    ,ENEMY
    ,ITEM
    ,PRISON
    ,WEAPON
};

class Object : public NFSpriteCluster{
protected:
    ObjectType objectType;
    bool m_isHit;
    bool m_isStaged;      //ステージに存在しているかどうか
    bool m_isDraw;
    cocos2d::CCPoint m_spaceHitPos;   //当たり判定中心のズレ幅
    float m_radius;
    
    virtual void hitToBeam(Object* obj ){};
    virtual void hitToEnemy(Object* obj){};
    virtual void hitToItem(Object* obj){};
    
public:
    Object();
    ~Object();
    CREATE_FUNC(Object);
    void setIsDraw( bool state ){ m_isDraw = state; };
    float getRadius(){ return m_radius; };
    void setRadius(float rad){ m_radius = rad; }
    bool isHit() {return m_isHit; };
    void setHit(bool state){ m_isHit = state; }

    bool checkHitObjectRadius(Object* obj);   //当たり判定
    virtual bool hitIfCollided(Object* obj );
    virtual void hasHit(Object* obj);
    
    ObjectType getObjectType();
    cocos2d::CCPoint getHitPosition();
    
    bool isStaged(){ return m_isStaged;}
    void setStaged(bool st){ m_isStaged=st; }
    
    void setSpaceHitPos(CCPoint _pos){ m_spaceHitPos = _pos; };
};

//--------------------
// CarryObject
//　下に向かって流れていくオブジェクト
//--------------------
class CarryObject : public Object{
protected:
    bool m_isExit;  //退場フラグ
    float   m_passSpeedRate;

    CarryObject();
    virtual void pass(float time);
public:
    virtual void update(float time);
    
    bool isExit(){ return m_isExit; }
};


#endif /* defined(__NinjaFlight__Object__) */
