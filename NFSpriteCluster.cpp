//
//  NFSpriteCluster.cpp
//  NinjaFlight
//

#import "NFSpriteCluster.h"

using namespace cocos2d;

NFSpriteCluster* NFSpriteCluster::create(){
    NFSpriteCluster* sprite = new NFSpriteCluster();
    sprite->autorelease();
    sprite->init();
    return sprite;
}

NFSpriteCluster* NFSpriteCluster::create(const char *pszFileName){
    NFSpriteCluster* sprite = new NFSpriteCluster();
    sprite->autorelease();
    sprite->init();
    sprite->CCSprite::initWithFile(pszFileName);
    return sprite;
}
NFSpriteCluster* NFSpriteCluster::create(const char *pszFileName, const cocos2d::CCRect &rect){
    NFSpriteCluster* sprite = new NFSpriteCluster();
    sprite->autorelease();
    sprite->init();
    sprite->CCSprite::initWithFile(pszFileName, rect);
    return sprite;
}

bool NFSpriteCluster::init(){
    CCSprite::init();
    m_isAloneProperty = false;
    m_isAloneAction = false;
    m_isHandsOffChildProperty = false;
    m_isHandsOffChildAction = false;
    m_isPaused=false;
    return true;
}

void NFSpriteCluster::pause(){
    this->pauseSchedulerAndActions();
    if( isHandsOffChildAction() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneAction() )child->pause();
            }else{
                CCNode* node = dynamic_cast<CCNode*>(access);
                if( node != NULL ){
                    node->pauseSchedulerAndActions();
                }
            }
        }
    }
    m_isPaused=true;
}

void NFSpriteCluster::resume(){
    this->resumeSchedulerAndActions();
    
    if( isHandsOffChildAction() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneAction() )child->resume();
            }else{
                CCNode* node = dynamic_cast<CCNode*>(access);
                if( node != NULL ){
                    node->resumeSchedulerAndActions();
                }
            }
        }
    }
    m_isPaused=false;
}

void NFSpriteCluster::setShader(const char *key){
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(key));
    this->getShaderProgram()->use();
    if( isHandsOffChildProperty() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){            
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneProperty() )child->setShader(key);
            }else{
                CCSprite* sprite = dynamic_cast<CCSprite*>(access);
                if( sprite != NULL ){
                    sprite->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(key));
                    sprite->getShaderProgram()->use();
                }
            }
        }
    }
}

void NFSpriteCluster::setColor(cocos2d::ccColor3B _color){
    CCSprite::setColor(_color);
    if( isHandsOffChildProperty() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneProperty() ) child->setColor(_color);
            }else{
                CCRGBAProtocol* sprite = dynamic_cast<CCRGBAProtocol*>(access);
                if( sprite != NULL ){
                    sprite->setColor(_color);
                }
            }
        }
    }
}

void NFSpriteCluster::setOpacity(GLubyte opacity){
    CCSprite::setOpacity(opacity);
    
    if( isHandsOffChildProperty() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){            
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneProperty() )
                    child->setOpacity(opacity);
            }else{
                CCRGBAProtocol* sprite = dynamic_cast<CCRGBAProtocol*>(access);
                if( sprite != NULL ){
                    sprite->setOpacity(opacity);
                }
            }
        }
    }
}

void NFSpriteCluster::resetRotateAndScale(){
    CCSprite::setRotation(0);
    CCSprite::setScale(1);
    
    if( isHandsOffChildProperty() ) return;
    
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){            
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneProperty())
                child->resetRotateAndScale();
            }else{
                CCNode* node = dynamic_cast<CCNode*>(access);
                if( node != NULL ){
                    node->setRotation(0);
                    node->setScale(1);
                }
            }
        }
    }
}

void NFSpriteCluster::setChildStatus(CCNode* pChild) {
    NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(pChild);
    if( child && child->isAloneProperty() ){
		return;
	}
	
	if(getShaderProgram()
	   && pChild->getShaderProgram() != getShaderProgram()) {
		pChild->setShaderProgram(getShaderProgram());
		pChild->getShaderProgram()->use();
	}
	
	CCRGBAProtocol* pChildRGBA = dynamic_cast<CCRGBAProtocol*>(pChild);
	if(pChildRGBA) {
		pChildRGBA->setColor(getColor());
		pChildRGBA->setOpacity(getOpacity());
	}
}

void NFSpriteCluster::addChild(CCNode *pChild){
    CCSprite::addChild(pChild);
}

void NFSpriteCluster::addChild(CCNode *pChild, int zOrder){
    CCSprite::addChild(pChild, zOrder);
}

void NFSpriteCluster::addChild(CCNode *pChild, int zOrder, int tag){
	if( !isHandsOffChildProperty() )setChildStatus(pChild);
    
    CCSprite::addChild(pChild, zOrder, tag);
}

void NFSpriteCluster::stopAction(){
    stopAllActions();
    if( isHandsOffChildAction() ) return;
    if( this->getChildrenCount() > 0 ){
        CCObject* access;
        CCARRAY_FOREACH(getChildren(), access){            
            NFSpriteCluster* child = dynamic_cast<NFSpriteCluster*>(access);
            if( child != NULL ){
                if( !child->isAloneAction() )child->stopAction();
            }else{
                CCNode* node = dynamic_cast<CCNode*>(access);
                if( node != NULL ){
                    node->stopAllActions();
                }
            }
        }
    }
}

