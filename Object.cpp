//
//  Object.cpp
//  NinjaFlight
//

#import "CommonDefine.h"
#import "Object.h"
#import "Enemy.h"

using namespace cocos2d;

Object::Object(){
    m_radius = 1.0f;
    m_isDraw = true;
    m_isHit = true;
    m_isStaged = true;
    objectType = BASE;
    m_spaceHitPos = CCPointZero;
}
Object::~Object(){
}

bool Object::hitIfCollided(Object* obj ){
    bool isHit = checkHitObjectRadius(obj);
    if( isHit){
        hasHit(obj);
    }
    return isHit;
}

bool Object::checkHitObjectRadius(Object* obj){
    if( !m_isHit || !obj->isHit() ){ //あたり判定をとらない設定のは虫ちゃん
        return false;
    }
    
    // 座標との距離が自分のサイズよりも小さい場合は当たったとみなします
    int dis = ccpDistance(this->getHitPosition(), obj->getHitPosition());
    
    return dis < this->m_radius + obj->getRadius();
}

void Object::hasHit(Object* obj){
    if(obj == NULL){
        return;
    }
    switch (obj->objectType) {
        case BEAM:
            this->hitToBeam(obj);
            break;
//        case CANNON:
//            this->hitToCannon(obj);
//            break;
        case ENEMY:
            this->hitToEnemy(obj);
            break;
        case ITEM:
            this->hitToItem(obj);
            break;
        default:
            break;
    }
}

ObjectType Object::getObjectType(){
    return objectType;
}

CCPoint Object::getHitPosition(){
    CCPoint position = this->getPosition();
    position.x += m_spaceHitPos.x;
    position.y += m_spaceHitPos.y;
    
    return position;
}

//--------------------
// CarryObject
//--------------------
CarryObject::CarryObject(){
    m_isExit=false;
    m_passSpeedRate = SCROLL_SPEED_RATE;

    scheduleUpdate();
}

void CarryObject::pass(float time){
    float _speed = 0;
    if( gameObjectManager ){
        _speed = gameObjectManager->getScrollSpeed()* m_passSpeedRate *-1;
    }
    float newY = getPositionY() + (_speed*time);
    
    setPositionY(newY);
    if( newY < 0 ){
        // 画面からでたら消す
        m_isExit = true;
    }
}

void CarryObject::update(float time){
    pass(time);
}
