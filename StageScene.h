
#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_MENUITEM_PLAY		0
#define TAG_STAGE1						1
#define TAG_STAGE2						2
#define TAG_STAGE3						3
#define TAG_STAGE4						4
#define TAG_STAGE5						5





class StageScene: public Layer
{
public:
	
	bool stage1;
	bool stage2;
	bool stage3;
	bool stage4;
	bool stage5;

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(StageScene);

	void initBGM();
	void initData();
	void initStageBG();
	void initStage1();
	void initStage2();
	void initStage3();
	void initStage4();
	void initStage5();

	void initMarin();
	void initRoket();
	void actionRoket1();
	void actionRoket2();
	void actionRoket3();
	void actionRoket4();
	void actionRoket5();

	void changeScene();
	void initRestart();
	void reStart();
	void soundEffect1();
	void soundEffect2();
	void soundEffectCancle();
	
	
};

#endif 
