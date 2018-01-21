#include "ModeScene.h"
#include "ClassicScene.h"
#include "ScoreScene.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ScoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
	if(!Layer::init() )
	{
		return false;
	}
	initBG();
	initScore();
	initMenu();
	
	return true;
}

void ScoreScene::initBG()
{
	auto spr = Sprite::create("ModeSceneBG.png");
	spr -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	
	this->addChild(spr);
}

void ScoreScene::initScore()
{
	int highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE");
	auto label = Label::createWithTTF(StringUtils::format("HIGH SCORE \n     %d", highScore), "Galaxy2.ttf", 50);
	label->setPosition(Point(getContentSize().width/2, getContentSize().height/1.7));
	this->addChild(label);
}

void ScoreScene::initMenu()
{
	auto label_1 = Label::createWithTTF("Wait a minute, go to the Mode Selection", "Galaxy2.ttf", 17);
	label_1->setPosition(Point(getContentSize().width/2, getContentSize().height/6));

	this->addChild(label_1);

	auto action = Sequence::create(
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		Show::create(),
		DelayTime::create(1),
		Hide::create(),
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(ScoreScene::changeScene, this)),
		NULL);

	label_1->runAction(action);

}

void ScoreScene::changeScene()
{
	auto scene = TransitionFade::create(2.0, ModeScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
