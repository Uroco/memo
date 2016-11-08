//
//  NFUIAnimationFactory.h
//  NinjaFlight
//

#ifndef __NinjaFlight__NFUIAnimationFactory__
#define __NinjaFlight__NFUIAnimationFactory__

#import "cocos2d.h"
using namespace cocos2d;

class NFUIAnimationFactory{
public:
    static void createAnimation_EventLogo(float x , float y, CCNode* parent); //EVENTロゴ
    static CCSprite* createAnimation_NewLogo(float x , float y, CCNode* parent, int zOrder=0);//NEW
    
};



#endif /* defined(__NinjaFlight__NFUIAnimationFactory__) */
