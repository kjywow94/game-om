
#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
#define TAG_MENU									19
#define TAG_MENUITEM_RESTART			20
#define TAG_MENUITEM_CHANGEMODE		21



class ScoreScene: public Layer
{
public:
	
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(ScoreScene);
	
	void initBG();
	void initScore();
	void initMenu();
	void menuCallback();
	void changeScene();
};

#endif 
