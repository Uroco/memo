//
//  NFSpriteCluster.h
//  NinjaFlight
//

#ifndef __NinjaFlight__NFSpriteCluster__
#define __NinjaFlight__NFSpriteCluster__

#import "cocos2d.h"

class NFSpriteCluster:public cocos2d::CCSprite{
    //If true the "m_isAlone ~" These flags, cut off interference from parents.
    bool m_isAloneProperty;
    bool m_isAloneAction;
    
    //If true the "m_isHandsOffChild~" These flags, cut off the interference to the children.
    bool m_isHandsOffChildProperty;
    bool m_isHandsOffChildAction;
    
    bool m_isPaused;
public:
    static NFSpriteCluster* create();
    static NFSpriteCluster* create(const char *pszFileName);
    static NFSpriteCluster* create(const char *pszFileName, const cocos2d::CCRect& rect);
    virtual bool init(void);
    virtual void pause();
    virtual void resume();
    
    virtual void setShader(const char* key);
    virtual void setColor(cocos2d::ccColor3B _color);
    virtual void setOpacity(GLubyte opacity);
    virtual void resetRotateAndScale();
    
	void setChildStatus(CCNode* pChild);
    virtual void addChild(CCNode *pChild);
    virtual void addChild(CCNode *pChild, int zOrder);
    virtual void addChild(CCNode *pChild, int zOrder, int tag);
    
    virtual void stopAction();
    
    void setAloneProperty( bool st ){ m_isAloneProperty = st; }
    bool isAloneProperty(){ return m_isAloneProperty; }

    void setAloneAction( bool st ){ m_isAloneAction = st; }
    bool isAloneAction(){ return m_isAloneAction; }

    void setHandsOffChildProperty( bool st ){ m_isHandsOffChildProperty = st; }
    bool isHandsOffChildProperty(){ return m_isHandsOffChildProperty; }
    
    void setHandsOffChildAction( bool st ){ m_isHandsOffChildAction = st; }
    bool isHandsOffChildAction(){ return m_isHandsOffChildAction; }
    
    bool isPaused(){ return m_isPaused; }
};


#endif /* defined(__NinjaFlight__NFSpriteCluster__) */
