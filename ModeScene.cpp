#include "ModeScene.h"
#include "ClassicScene.h"
#include "StageScene.h"

USING_NS_CC;

Scene* ModeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ModeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ModeScene::init()
{
	if(!Layer::init() )
	{
		return false;
	}
	initBG();
	initMenu();
	
	
	return true;
}

void ModeScene::initBG()
{
	auto spr = Sprite::create("ModeSceneBG.png");
	spr -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	
	this->addChild(spr);
}

void ModeScene::initMenu()
{
	auto label_1 = Label::createWithTTF("CLASSIC MODE", "Galaxy2.ttf", 37);
	auto label_2 = Label::createWithTTF("STAGE MODE", "Galaxy2.ttf", 40);

	auto item_0 = MenuItemLabel::create(label_1, 
		CC_CALLBACK_1(ModeScene::menuCallback, this));
	item_0->setTag(TAG_MENUITEM_CLASSIC);

	auto item_1 = MenuItemLabel::create(label_2, 
		CC_CALLBACK_1(ModeScene::menuCallback, this));
	item_1->setTag(TAG_MENUITEM_STAGE);


	auto menu = Menu::create(item_0, item_1, NULL);
	menu->setPosition(Point(getContentSize().width/2, getContentSize().height/2));
	menu->setAnchorPoint(Point::ZERO);
	menu->setScale(1);
	menu->alignItemsVerticallyWithPadding(50);
	
	this->addChild(menu);

	
	
}


void ModeScene::menuCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	switch (item->getTag())
	{
	case TAG_MENUITEM_CLASSIC:
		{
			auto scene = TransitionFade::create(2.0, ClassicScene::createScene());
			Director::getInstance()->replaceScene(scene);
		}
		break;
	case TAG_MENUITEM_STAGE:
		{
			auto scene = TransitionFade::create(2.0, StageScene::createScene());
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