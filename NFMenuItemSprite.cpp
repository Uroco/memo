#import "CommonDefine.h"

#import "NFMenuItemSprite.h"
#import "SoundManager.h"

using namespace std;
using namespace cocos2d;

NFMenuItemSprite::NFMenuItemSprite() {
}

NFMenuItemSprite::~NFMenuItemSprite() {
}

NFMenuItemSprite* NFMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite,
										   CCObject* target, SEL_MenuHandler selector) {
	return NFMenuItemSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

NFMenuItemSprite* NFMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite,
										   CCObject* target, SEL_MenuHandler selector) {
	NFMenuItemSprite* instance = new NFMenuItemSprite();
	instance->autorelease();
	instance->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
	return instance;
}

void NFMenuItemSprite::selected() {
	CCMenuItemSprite::selected();
	playSoundEffect("LN_ninjase014.m4a");
}