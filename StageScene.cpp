#include "StageScene.h"
#include "GameScene.h"
#include "ModeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* StageScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StageScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StageScene::init()
{
	if(!Layer::init() )
	{
		return false;
	}

	initData();
	initStageBG();
	initBGM();
	initStage1();
	initStage2();
	initStage3();
	initStage4();
	initStage5();
	initMarin();
	
	return true;
}
void StageScene::initBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("stageScene.mp3");
}
void StageScene::initData()
{

	

	stage1=UserDefault::getInstance()->getBoolForKey("STAGE1", false);
	stage2=UserDefault::getInstance()->getBoolForKey("STAGE2", false);
	stage3=UserDefault::getInstance()->getBoolForKey("STAGE3", false);
	stage4=UserDefault::getInstance()->getBoolForKey("STAGE4", false);
	stage5=UserDefault::getInstance()->getBoolForKey("STAGE5", false);
}

void StageScene::initStageBG()
{
	
	auto spr = Sprite::create("GalaxyPangBG2.png");
	spr -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	
	this->addChild(spr);

	auto particle = ParticleMeteor::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/1.5, 
		Director::getInstance()->getWinSize().height/2.5);
	this->addChild(particle);
	
}

void StageScene::initStage1()
{
	auto sprAlien_1 = Sprite::create("Alien1.png");
	sprAlien_1->setScale(0.8);
	sprAlien_1->setPosition(Point(Director::getInstance()->getWinSize().width/4.7, Director::getInstance()->getWinSize().height/5.2));
	sprAlien_1->setTag(TAG_STAGE1);
	this->addChild(sprAlien_1);

	if(!stage1)
	{
		auto action1 = RotateBy::create(0.5, 20);
		auto action2 = action1->reverse();
		auto action3 = RotateBy::create(0.5, -20);
		auto action4 = action3->reverse();
		auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
		auto action6 = RepeatForever::create(action5);

		sprAlien_1->runAction(action6);
	}
	else
	{
		auto particle = ParticleFire::create();
		particle->setPosition(Director::getInstance()->getWinSize().width/4.7, Director::getInstance()->getWinSize().height/8);
		particle->setScaleY(0.4);
		this->addChild(particle);
	}
}

void StageScene::initStage2()
{
	auto sprAlien_2 = Sprite::create("Alien2.png");
	sprAlien_2->setScale(0.8);
	sprAlien_2->setPosition(Point(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/2.3));
	sprAlien_2->setTag(TAG_STAGE2);
	this->addChild(sprAlien_2);

	if(!stage2)
	{
		auto action1 = RotateBy::create(0.5, 20);
		auto action2 = action1->reverse();
		auto action3 = RotateBy::create(0.5, -20);
		auto action4 = action3->reverse();
		auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
		auto action6 = RepeatForever::create(action5);

		sprAlien_2->runAction(action6);
	}
	else
	{
		auto particle = ParticleFire::create();
		particle->setPosition(Director::getInstance()->getWinSize().width/4.7, Director::getInstance()->getWinSize().height/2.7);
		particle->setScaleY(0.4);
		this->addChild(particle);
	}

}

void StageScene::initStage3()
{
	auto sprAlien_3 = Sprite::create("Alien3.png");
	sprAlien_3->setScale(0.8);
	sprAlien_3->setPosition(Point(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/1.45));
	sprAlien_3->setTag(TAG_STAGE3);
	this->addChild(sprAlien_3);

	if(!stage3)
	{
		auto action1 = RotateBy::create(0.5, 20);
		auto action2 = action1->reverse();
		auto action3 = RotateBy::create(0.5, -20);
		auto action4 = action3->reverse();
		auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
		auto action6 = RepeatForever::create(action5);

		sprAlien_3->runAction(action6);
	}
	else
	{
		auto particle = ParticleFire::create();
		particle->setPosition(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/1.6);
		particle->setScaleY(0.4);
		this->addChild(particle);
	}
}

void StageScene::initStage4()
{
	auto sprAlien_4 = Sprite::create("Alien4.png");
	sprAlien_4->setScale(0.8);
	sprAlien_4->setPosition(Point(Director::getInstance()->getWinSize().width/2.5, Director::getInstance()->getWinSize().height/1.1));
	sprAlien_4->setTag(TAG_STAGE4);
	this->addChild(sprAlien_4);

	if(!stage4)
	{
		auto action1 = RotateBy::create(0.5, 20);
		auto action2 = action1->reverse();
		auto action3 = RotateBy::create(0.5, -20);
		auto action4 = action3->reverse();
		auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
		auto action6 = RepeatForever::create(action5);

		sprAlien_4->runAction(action6);
	}
	else
	{
		auto particle = ParticleFire::create();
		particle->setPosition(Director::getInstance()->getWinSize().width/2.5, Director::getInstance()->getWinSize().height/1.2);
		particle->setScaleY(0.4);
		this->addChild(particle);
	}

}

void StageScene::initStage5()
{
	auto sprAlien_5 = Sprite::create("Alien5.png");
	sprAlien_5->setScale(0.8);
	sprAlien_5->setPosition(Point(Director::getInstance()->getWinSize().width/1.24, Director::getInstance()->getWinSize().height/1.37));
	sprAlien_5->setTag(TAG_STAGE5);
	this->addChild(sprAlien_5);

	if(!stage5)
	{
		auto action1 = RotateBy::create(0.5, 20);
		auto action2 = action1->reverse();
		auto action3 = RotateBy::create(0.5, -20);
		auto action4 = action3->reverse();
		auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
		auto action6 = RepeatForever::create(action5);

		sprAlien_5->runAction(action6);
	}
	else
	{
		auto particle = ParticleFire::create();
		particle->setPosition(Director::getInstance()->getWinSize().width/1.24, Director::getInstance()->getWinSize().height/1.5);
		particle->setScaleY(0.4);
		this->addChild(particle);
	}

}

void StageScene::initMarin()
{
	auto sprMarin = Sprite::create("marin.png");
	sprMarin->setScale(0.9);
	sprMarin->setPosition(Point(Director::getInstance()->getWinSize().width/1.2, Director::getInstance()->getWinSize().height/6.5));
	this->addChild(sprMarin);

	auto action1 = Sequence::create(
													DelayTime::create(2),
													ScaleTo::create(1.5, 1.15),
													CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect1, this)),
													DelayTime::create(2),
													ScaleTo::create(1.5, 1),
													CallFunc::create(CC_CALLBACK_0(StageScene::initRoket, this)),
													NULL);
	sprMarin->runAction(action1);

}												
void StageScene::initRoket()
{
	auto sprRoket = Sprite::create("Roket.png");
	sprRoket->setPosition(Point(Director::getInstance()->getWinSize().width/1.7, Director::getInstance()->getWinSize().height/3.7));
	this->addChild(sprRoket);
	if(!stage1)
	{
		
		auto action1 = Sequence::create( 
														RotateBy::create(1.5, -40),
														CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect2, this)),
														MoveTo::create(2, Point(Director::getInstance()->getWinSize().width/4.7, Director::getInstance()->getWinSize().height/5.2)),
														CallFunc::create(CC_CALLBACK_0(StageScene::actionRoket1, this)),
														DelayTime::create(3),
														CallFunc::create(CC_CALLBACK_0(StageScene::changeScene, this)),
														NULL);
		sprRoket->runAction(action1);
	}
	
	else if(!stage2)
	{
		
		auto action1 = Sequence::create( 
														RotateBy::create(1.5, 30),
														CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect2, this)),
														MoveTo::create(2, Point(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/2.3)),
														CallFunc::create(CC_CALLBACK_0(StageScene::actionRoket2, this)),
														DelayTime::create(3),
														CallFunc::create(CC_CALLBACK_0(StageScene::changeScene, this)),
														NULL);
		sprRoket->runAction(action1);
	}
		
	else if(!stage3)
	{
		
		auto action1 = Sequence::create( 
														RotateBy::create(1.5, 55),
														CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect2, this)),
														MoveTo::create(2, Point(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/1.45)),
														CallFunc::create(CC_CALLBACK_0(StageScene::actionRoket3, this)),
														DelayTime::create(3),
														CallFunc::create(CC_CALLBACK_0(StageScene::changeScene, this)),
														NULL);
		sprRoket->runAction(action1);
	}
	
	else if(!stage4)
	{
		
		auto action1 = Sequence::create( 
														RotateBy::create(1.5, 60),
														CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect2, this)),
														MoveTo::create(2, Point(Director::getInstance()->getWinSize().width/2.5, Director::getInstance()->getWinSize().height/1.1)),
														CallFunc::create(CC_CALLBACK_0(StageScene::actionRoket4, this)),
														DelayTime::create(3),
														CallFunc::create(CC_CALLBACK_0(StageScene::changeScene, this)),
														NULL);
		sprRoket->runAction(action1);
	}

	else if(!stage5)
	{
		
		auto action1 = Sequence::create( 
														RotateBy::create(1.5, 100),
														CallFunc::create(CC_CALLBACK_0(StageScene::soundEffect2, this)),
														MoveTo::create(2, Point(Director::getInstance()->getWinSize().width/1.24, Director::getInstance()->getWinSize().height/1.4)),
														CallFunc::create(CC_CALLBACK_0(StageScene::actionRoket5, this)),
														DelayTime::create(3),
														CallFunc::create(CC_CALLBACK_0(StageScene::changeScene, this)),
														NULL);
		sprRoket->runAction(action1);
	}
	else 
	{
		sprRoket->setVisible(false);
		initRestart();

	}
}

void StageScene::actionRoket1()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/4.7, Director::getInstance()->getWinSize().height/5.9);
	particle->setScaleY(0.4);
	this->addChild(particle);
}

void StageScene::actionRoket2()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/2.7);
	particle->setScaleY(0.4);
	this->addChild(particle);
}

void StageScene::actionRoket3()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/4.8, Director::getInstance()->getWinSize().height/1.6);
	particle->setScaleY(0.4);
	this->addChild(particle);
}

void StageScene::actionRoket4()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/2.5, Director::getInstance()->getWinSize().height/1.2);
	particle->setScaleY(0.4);
	this->addChild(particle);
}

void StageScene::actionRoket5()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/1.24, Director::getInstance()->getWinSize().height/1.5);
	particle->setScaleY(0.4);
	this->addChild(particle);
}

void StageScene::changeScene()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto scene = TransitionFade::create(2.0, GameScene::createScene());
	Director::getInstance()->replaceScene(scene);
	
	
}

void StageScene::initRestart()
{
	auto restartLabel = Label::createWithTTF("RESTART", "Galaxy2.ttf", 30);
	
	auto item_0 = MenuItemLabel::create(restartLabel , 
		CC_CALLBACK_0(StageScene::reStart, this));
	
	
	auto menu = Menu::create(item_0, NULL);
	menu->setPosition(Point(getContentSize().width/1.25, getContentSize().height/2));
	menu->setAnchorPoint(Point::ZERO);
	menu->setScale(1);
	
	this->addChild(menu);

	auto action = Sequence::create(
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		NULL);
	auto action2 = RepeatForever::create(action);

	menu->runAction(action2);
	
}

void StageScene::reStart()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	UserDefault::getInstance()->setBoolForKey("STAGE1", false);
	UserDefault::getInstance()->setBoolForKey("STAGE2", false);
	UserDefault::getInstance()->setBoolForKey("STAGE3", false);
	UserDefault::getInstance()->setBoolForKey("STAGE4", false);
	UserDefault::getInstance()->setBoolForKey("STAGE5", false);

	
	auto scene = TransitionFade::create(2.0, ModeScene::createScene());
	Director::getInstance()->replaceScene(scene);
	
	
}

void StageScene::soundEffect1()
{
	SimpleAudioEngine::getInstance()->playEffect("shotgun pump.wav");
}

void StageScene::soundEffect2()
{
	SimpleAudioEngine::getInstance()->playEffect("boom.wav");
}

void StageScene::soundEffectCancle()
{
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}


