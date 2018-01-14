
#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_MENUITEM_PLAY		0



class MenuScene: public Layer
{
public:
	
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(MenuScene);
	
	void initBG();
	void initBGM();
	void initData();
	void initMenu();
	void menuCallback(Ref *sender);

};

#endif // __MENU_SCENE_H__
