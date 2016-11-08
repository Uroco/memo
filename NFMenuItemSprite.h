#include "cocos2d.h"

class NFMenuItemSprite : public cocos2d::CCMenuItemSprite
{
public:
	NFMenuItemSprite();
	~NFMenuItemSprite();
	static NFMenuItemSprite* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,
									cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
	static NFMenuItemSprite* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,
									cocos2d::CCNode* disabledSprite = NULL,
									cocos2d::CCObject* target = NULL, cocos2d::SEL_MenuHandler selector = NULL);
	void selected();
};