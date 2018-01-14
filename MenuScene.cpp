#include "MenuScene.h"
#include "ModeScene.h"
#include "StageScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;


USING_NS_CC;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	if(!Layer::init() )
	{
		return false;
	}

	initBG();
	initBGM();
	initMenu();
	//initData();
	
	
	return true;
}

void MenuScene::initData()
{
	UserDefault::getInstance()->setBoolForKey("STAGE1", true);
	UserDefault::getInstance()->setBoolForKey("STAGE2", true);
	UserDefault::getInstance()->setBoolForKey("STAGE3", true);
	UserDefault::getInstance()->setBoolForKey("STAGE4", true);
	UserDefault::getInstance()->setBoolForKey("STAGE5", true);

}
void MenuScene::initBG()
{
	
	auto spr = Sprite::create("GalaxyPangMainBG.png");
	spr -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	
	this->addChild(spr);

	auto particle = ParticleGalaxy::create();
	this->addChild(particle);
	
}
void MenuScene::initMenu()
{
	auto label_1 = Label::createWithTTF("Press to Start", "Galaxy2.ttf", 30);
	
	auto item_0 = MenuItemLabel::create(label_1, 
		CC_CALLBACK_1(MenuScene::menuCallback, this));
	
	item_0->setTag(TAG_MENUITEM_PLAY);


	auto menu = Menu::create(item_0, NULL);
	menu->setPosition(Point(getContentSize().width/2, getContentSize().height/5));
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

void MenuScene::menuCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	switch (item->getTag())
	{
		case TAG_MENUITEM_PLAY:
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			auto scene = TransitionFade::create(2.0, ModeScene::createScene());
			Director::getInstance()->replaceScene(scene);
		}
		break;
		
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
		#endif
				break;
			default:
				break;
	}

}

void MenuScene::initBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("mainScene.mp3");
}