
#ifndef __MODE_SCENE_H__
#define __MODE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
#define TAG_MENUITEM_CLASSIC		0
#define TAG_MENUITEM_STAGE 		1


class ModeScene: public Layer
{
public:
	
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(ModeScene);
	
	void initBG();
	void initMenu();
	void menuCallback(Ref *sender);
	
};

#endif // __MENU_SCENE_H__
