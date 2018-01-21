
#include "GameScene.h"
#include "StageScene.h"
#include "GameCoin.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

int GameScene::adjCoin[BOARDX * BOARDY][TOTALADJCOIN] = { 
    {-1, -1,  1,  7,  6, -1},   // 0, line 1
    {-1, -1,  2,  8,  7,  0}, 
    {-1, -1,  3,  9,  8,  1}, 
    {-1, -1,  4, 10,  9,  2}, 
    {-1, -1,  5, 11, 10,  3}, 
    {-1, -1, -1, -1, 11,  4}, 
    {-1,  0,  7, 12, -1, -1},   // 6, line 2
    { 0,  1,  8, 13, 12,  6}, 
    { 1,  2,  9, 14, 13,  7}, 
    { 2,  3, 10, 15, 14,  8}, 
    { 3,  4, 11, 16, 15,  9}, 
    { 4,  5, -1, 17, 16, 10},
    { 6,  7, 13, 19, 18, -1},   // 12, line 3
    { 7,  8, 14, 20, 19, 12},
    { 8,  9, 15, 21, 20, 13},
    { 9, 10, 16, 22, 21, 14},
    {10, 11, 17, 23, 22, 15},
    {11, -1, -1, -1, 23, 16},
    {-1, 12, 19, 24, -1, -1},   // 18, line 4
    {12, 13, 20, 25, 24, 18},
    {13, 14, 21, 26, 25, 19},
    {14, 15, 22, 27, 26, 20},
    {15, 16, 23, 28, 27, 21},
    {16, 17, -1, 29, 28, 22},
    {18, 19, 25, 31, 30, -1},   // 24, line 5
    {19, 20, 26, 32, 31, 24},
    {20, 21, 27, 33, 32, 25},
    {21, 22, 28, 34, 33, 26},
    {22, 23, 29, 35, 34, 27},
    {23, -1, -1, -1, 35, 28},
    {-1, 24, 31, 36, -1, -1},   // 30, line 6
    {24, 25, 32, 37, 36, 30},
    {25, 26, 33, 38, 37, 31},
    {26, 27, 34, 39, 38, 32},
    {27, 28, 35, 40, 39, 33},
    {28, 29, -1, 41, 40, 34},
    {30, 31, 37, -1, -1, -1},   // 36, line 7
    {31, 32, 38, -1, -1, 36},
    {32, 33, 39, -1, -1, 37},
    {33, 34, 40, -1, -1, 38},
    {34, 35, 41, -1, -1, 39},
    {35, -1, -1, -1, -1, 40},
};

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	initBG();
	
	initData();
	initAnimation_1();
	initAnimation_2();
	initScore();
	initReady();
	initStart();
	initGameCoin();
	actionReady();

	return true;
}
GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_gameCoins);
	CC_SAFE_RELEASE(_selectCoins);
    CC_SAFE_RELEASE(_selectMask);
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void GameScene::initBG()
{
	auto sprBG = Sprite::create("GalaxyPangBG.png");
	sprBG -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	this->addChild(sprBG);

	
}
void GameScene::initBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("gameScene.mp3",true);
}

void GameScene::initAnimation_1()
{
	auto action1 = RotateBy::create(0.5, 20);
	auto action2 = action1->reverse();
	auto action3 = RotateBy::create(0.5, -20);
	auto action4 = action3->reverse();
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5);
	
	if(!stage1)
	{
		auto sprAlien_1 = Sprite::create("Alien1.png");
		sprAlien_1->setScale(0.9);
		sprAlien_1->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
		this->addChild(sprAlien_1);
		sprAlien_1->runAction(action6);
	}
	else if(!stage2)
	{
		auto sprAlien_2 = Sprite::create("Alien2.png");
		sprAlien_2->setScale(0.9);
		sprAlien_2->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
		this->addChild(sprAlien_2);
		sprAlien_2->runAction(action6);
	}
	else if(!stage3)
	{
		auto sprAlien_3 = Sprite::create("Alien3.png");
		sprAlien_3->setScale(0.9);
		sprAlien_3->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
		this->addChild(sprAlien_3);
		sprAlien_3->runAction(action6);
	}
	else if(!stage4)
	{
		auto sprAlien_4 = Sprite::create("Alien4.png");
		sprAlien_4->setScale(0.9);
		sprAlien_4->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
		this->addChild(sprAlien_4);
		sprAlien_4->runAction(action6);
	}
	else if(!stage5)
	{
		auto sprAlien_5 = Sprite::create("Alien5.png");
		sprAlien_5->setScale(0.9);
		sprAlien_5->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
		this->addChild(sprAlien_5);
		sprAlien_5->runAction(action6);
	}
}

void GameScene::initAnimation_2()
{
	auto sprMan = Sprite::create("marin.png");
	sprMan->setScale(0.8);
	sprMan->setPosition(Point(Director::getInstance()->getWinSize().width/3.8, Director::getInstance()->getWinSize().height/1.3));
	this->addChild(sprMan);

	auto action1 = RotateBy::create(0.5, 20);
	auto action2 = action1->reverse();
	auto action3 = RotateBy::create(0.5, -20);
	auto action4 = action3->reverse();
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5);

	sprMan->runAction(action6);
}

void GameScene::actionAnimation_1()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.4);
	particle->setTag(TAG_PARTICLE_FIRE);
	particle->setScale(0.5);
	this->addChild(particle);
	
	auto action = Sequence::create(
		DelayTime::create(2.5),
		Hide::create(),
		CallFunc::create(CC_CALLBACK_0(GameScene::actionAnimation_2, this)),
		NULL);
	
	particle->runAction(action);
}
void GameScene::actionAnimation_2()
{
	auto particle = this->getChildByTag(TAG_PARTICLE_FIRE); 
	this->removeChild(particle);
}

void GameScene::initData()
{
	
	isTouch = false;
	lastCoin = -1;
	selectCoinCount=0;
	score = 0;
	gameTime=60;

	stage1=UserDefault::getInstance()->getBoolForKey("STAGE1");
	stage2=UserDefault::getInstance()->getBoolForKey("STAGE2");
	stage3=UserDefault::getInstance()->getBoolForKey("STAGE3");
	stage4=UserDefault::getInstance()->getBoolForKey("STAGE4");
	stage5=UserDefault::getInstance()->getBoolForKey("STAGE5");

}
void GameScene::initScore()
{
	auto scoreFont = CCLabelBMFont::create("0", "font.fnt", Director::getInstance()->getWinSize().width * 0.3f);
	scoreFont->setTag(TAG_LABEL_SCORE);
    scoreFont->setAnchorPoint(Point(1, 0.5));
    scoreFont->setPosition(Point(Director::getInstance()->getWinSize().width * 0.65f, Director::getInstance()->getWinSize().height * 0.95f));
    scoreFont->setScale(0.8);
    this->addChild(scoreFont);
	
}
void GameScene::initTimer()
{

	CCSprite* timeBar = CCSprite::create("timebar.png");
    progressTimeBar = CCProgressTimer::create(timeBar);
    progressTimeBar->setPosition(Point(Director::getInstance()->getWinSize().width * 0.5f, 10));
    progressTimeBar->setPercentage(100.0f);
    progressTimeBar->setMidpoint(ccp(0, 0.5f));
    progressTimeBar->setBarChangeRate(ccp(1, 0));
    progressTimeBar->setType(kCCProgressTimerTypeBar);
 
    this->addChild(progressTimeBar);
 
    CCProgressFromTo* progressToZero = CCProgressFromTo::create(60, 100, 0);
    progressTimeBar->runAction(progressToZero);
 
    CCSprite* timeOutline = CCSprite::create("timeoutline.png");
    timeOutline->setPosition(Point(Director::getInstance()->getWinSize().width * 0.5f, 10));
    timeOutline->setVisible(true);
    this->addChild(timeOutline);
	this->schedule(schedule_selector(GameScene::timeCount), 1.0f);
}
void GameScene::initReady()
{
	auto readyLabel = Label::createWithTTF("READY", "Galaxy2.ttf", 50);
	readyLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	readyLabel->setTag(TAG_LABEL_READY);
	readyLabel->setColor(Color3B::WHITE);
	readyLabel->setScale(0.0);
	this->addChild(readyLabel, 10);
}

void GameScene::initStart()
{
	auto startLabel = Label::createWithTTF("START", "Galaxy2.ttf", 50);
	startLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	startLabel->setTag(TAG_LABEL_START);
	startLabel->setColor(Color3B::WHITE);
	startLabel->setScale(0.0);
	this->addChild(startLabel, 10);
}
void GameScene::initClear()
{
	auto clearLabel = Label::createWithTTF("CLEAR", "Galaxy2.ttf", 50);
	clearLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	clearLabel->setTag(TAG_LABEL_CLEAR);
	clearLabel->setColor(Color3B::WHITE);
	clearLabel->setScale(0.0);
	this->addChild(clearLabel, 10);

	auto actionClear = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::changeScene, this)),
		NULL);

	clearLabel->runAction(actionClear);
}

void GameScene::initGameOver()
{
	auto gameOverLabel = Label::createWithTTF("GAME OVER", "Galaxy2.ttf", 50);
	gameOverLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	gameOverLabel->setTag(TAG_LABEL_GAMEOVER);
	gameOverLabel->setColor(Color3B::WHITE);
	gameOverLabel->setScale(0.0);
	this->addChild(gameOverLabel, 10);

	auto actionGameOver = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::changeScene, this)),
		NULL);

	gameOverLabel->runAction(actionGameOver);
}

void GameScene::actionReady()
{
	auto actionReady = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::actionStart, this)),
		NULL);

	auto readyLabel = (Label*)this->getChildByTag(TAG_LABEL_READY);
	readyLabel->runAction(actionReady);
}

void GameScene::actionStart()
{
	auto actionStart = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::touchTrue, this)),
		CallFunc::create(CC_CALLBACK_0(GameScene::initTimer, this)),
		CallFunc::create(CC_CALLBACK_0(GameScene::initBGM, this)),
		NULL);

	auto startLabel = (Label*)this->getChildByTag(TAG_LABEL_START);
	startLabel->runAction(actionStart);
}

void GameScene::touchTrue()
{
	isTouch = TRUE;
}

void GameScene::initGameCoin()
{
	double coinXPos = 0;
    double coinYPos = 0;
  
	double diffX = 43.5;
    double diffY = 45;
    int initCoinXPos = 30; 
    int initCoinYPos = 292;

	srand(time(NULL));

    GameCoin* gameCoin;
 
    // init array
	
    _gameCoins = CCArray::createWithCapacity(BOARDX * BOARDY);
    _gameCoins->retain();
	
	_selectCoins = CCArray::createWithCapacity(BOARDX * BOARDY);
    _selectCoins->retain();
 
    _selectMask = CCArray::createWithCapacity(BOARDX * BOARDY);
    _selectMask->retain();
	


	

    // init gameCoin
    for(int xIndex = 0; xIndex < BOARDX; xIndex++) 
	{
        coinXPos = initCoinXPos + (xIndex * diffX);
        coinYPos = initCoinYPos;
        if(xIndex % 2 == 0)
            coinYPos -= diffY/2;
 
       for(int yIndex = 0; yIndex < BOARDY; yIndex++) 
	   {
            gameCoin = createGameCoin(ccp(coinXPos, coinYPos),
                            rand() % TOTALCOINTYPE + 1,
                            GameCoin::LIVE);
			
            _gameCoins->addObject(gameCoin);
			
            coinYPos -= diffY;
        }   
	}

	 // selectMask setup
    CCSprite* selectMask;
 
    for(int xIndex = 0; xIndex < BOARDX; xIndex++) 
	{
        coinXPos = initCoinXPos + (xIndex * diffX);
        coinYPos = initCoinYPos;
        if(xIndex % 2 == 0)
            coinYPos -= diffY/2;
 
        for(int yIndex = 0; yIndex < BOARDY; yIndex++) 
		{
            selectMask = CCSprite::create("selectTile1.png");
            selectMask->setVisible(false);
            selectMask->setPosition(ccp(coinXPos, coinYPos));
			selectMask->setOpacity(170);
            this->addChild(selectMask);
            _selectMask->addObject(selectMask);
 
            coinYPos -= diffY;
        }
    }
	
}

GameCoin* GameScene::createGameCoin(const CCPoint &pos, int type, int state)
{
    GameCoin* gameCoin;
    CCString* name;
 
    name = CCString::createWithFormat("coin_%i.png", type);
    gameCoin = GameCoin::spriteWithFile(name->getCString());
    gameCoin->setVisible(true);
    gameCoin->setPosition(pos);
    gameCoin->setState(state);
    gameCoin->setType(type);
 
    this->addChild(gameCoin);
 
    return gameCoin;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if(!isTouch)
		return false;

	Point location = touch->getLocation();
	lastCoin = checkPushGameCoin(location);
   
	if (lastCoin >= 0) 
        addSelectCoins(lastCoin);
		
	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	if(!isTouch)
		return;
	Point location = touch->getLocation();

	int newCoin = -1;
 
    if (inLastCoin(location) == false) 
	{
        newCoin = checkAdjacentCoin(location);
        if (compareCoinType(lastCoin, newCoin)) 
		{
            lastCoin = newCoin;
            addSelectCoins(lastCoin);
        }
    }
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	if(!isTouch)
		return;
	Point location = touch->getLocation();
	clearSelectCoin();
	moveUpDeadCoin();
	addNewCoin();
	
}

int GameScene::checkPushGameCoin(CCPoint &touchPos)
{   
    int index;
    GameCoin *tmpCoin;
     
    for (index = 0; index < _gameCoins->count(); index++) {
        tmpCoin = (GameCoin*)_gameCoins->objectAtIndex(index); 
        if (tmpCoin->boundingBox().containsPoint(touchPos) == true) {
           
     
            return index;
        }
    }

   
 
    return -1;
}

bool GameScene::inLastCoin(CCPoint &touchPos)
{
    if(lastCoin == -1) {
        return false;
    }
 
    GameCoin* _lastCoin = (GameCoin*)_gameCoins->objectAtIndex(lastCoin);
 
    if(_lastCoin->boundingBox().containsPoint(touchPos) == true) {
        return true;
    }
 
    return false;
}

int GameScene::checkAdjacentCoin(CCPoint &touchPos)
{
    int index;
    GameCoin* tmpCoin;
 
    if(lastCoin < 0)
        return -1;
 
    for(index = 0; index < 6; index++) {
        if(adjCoin[lastCoin][index] == -1) {
            continue;
        }
        tmpCoin = (GameCoin*)_gameCoins->objectAtIndex(adjCoin[lastCoin][index]);
 
        if(tmpCoin->boundingBox().containsPoint(touchPos) == true) {
            return adjCoin[lastCoin][index];
        }
    }
 
    return -1;
}

bool GameScene::compareCoinType(int index1, int index2)
{
    if (index1 < 0 || index2 < 0)
        return false;
 
    GameCoin* tmpCoin1 = (GameCoin*)_gameCoins->objectAtIndex(index1);
    GameCoin* tmpCoin2 = (GameCoin*)_gameCoins->objectAtIndex(index2);
 
    if(tmpCoin1->getType() == tmpCoin2->getType()) {
        return true;
    }
 
    return false;
}
int GameScene::addSelectCoins(int index)
{
    if(index < 0) {
        return -1;
    }
 
    GameCoin* tmpCoin = (GameCoin*)_gameCoins->objectAtIndex(index);
    CCSprite* selectMask = (CCSprite*)_selectMask->objectAtIndex(index);
 
    if(tmpCoin->getState() != GameCoin::SELECT) {
        tmpCoin->setState(GameCoin::SELECT);
        _selectCoins->addObject(tmpCoin);
 
        selectMask->setVisible(true);
    }
	selectCoinCount+=1;

    return 0;
}

void GameScene::clearSelectCoin()
{
    int index;
    GameCoin* tmpCoin;
 
    if(selectCoinCount >= 3) {
		soundEffect();
		addGameScore(selectCoinCount);
        for(index = 0; index < _selectCoins->count(); index++) {
            tmpCoin = (GameCoin*)_selectCoins->objectAtIndex(index);
            tmpCoin->setState(GameCoin::DEAD);
            tmpCoin->setVisible(false);
        }
    }
    else {
        for(index = 0; index < _selectCoins->count(); index++) {
            tmpCoin = (GameCoin*)_selectCoins->objectAtIndex(index);
            tmpCoin->setState(GameCoin::LIVE);
        }
    }
 
    resetSelectMask();
    resetGameInfo();
}

void GameScene::resetSelectMask()
{
    CCSprite* selectMask;
 
    for(int i = 0; i < _selectMask->count(); i++) {
        selectMask = (CCSprite*)_selectMask->objectAtIndex(i);
        selectMask->setVisible(false);
    }
}

void GameScene::resetGameInfo()
{
    selectCoinCount = 0;
    lastCoin = -1;
 
    _selectCoins->removeAllObjects();
}

void GameScene::moveUpDeadCoin()
{
	
    int deadCoinNum = 0;
    int bottomPos = 0;
    GameCoin* coin;
	
    for (int x = 0; x < BOARDX; x++) {
        bottomPos = ((x + 1) * BOARDY) - 1;
        deadCoinNum = 0;
 
        for (int y = bottomPos; y > bottomPos - BOARDY; y--) {
            coin = (GameCoin*)_gameCoins->objectAtIndex(y);
            if (coin->getState() == GameCoin::DEAD) {
                deadCoinNum++;
                continue;
            }
 
            if (deadCoinNum > 0)
                changeCoin(y, y + deadCoinNum);
        }
    }
}

void GameScene::changeCoin(int index1, int index2)
{
    CCPoint tmpPos;
    GameCoin* tmpCoin1 = (GameCoin*)_gameCoins->objectAtIndex(index1);
    GameCoin* tmpCoin2 = (GameCoin*)_gameCoins->objectAtIndex(index2);
 
    tmpPos = tmpCoin2->getPosition();
    tmpCoin2->setPosition(tmpCoin1->getPosition());
    
	
	moveCoin(tmpCoin1, tmpPos);
	actionAnimation_1();
    _gameCoins->exchangeObjectAtIndex(index1, index2);
}

void GameScene::moveCoin(GameCoin* coin, CCPoint& pos)
{
    float duration = 0.0f;
    float coinSpeed = 1000.0f;
    CCPoint prevPos = coin->getPosition();
    coin->setState(GameCoin::MOVE);
    coin->stopAllActions();

    duration = prevPos.getDistance(pos)*2 / coinSpeed;
 
    CCFiniteTimeAction* movePos = CCSequence::create(
            CCMoveTo::create(duration, pos),
            CCCallFuncN::create(this, callfuncN_selector(GameScene::coinMoveDone)),
			NULL);
 
    coin->runAction(movePos);
}

void GameScene::coinMoveDone(CCNode* pSender)
{
    GameCoin* coin = (GameCoin*)pSender;
 
    coin->stopAllActions();
    coin->setState(GameCoin::LIVE);
}

void GameScene::addNewCoin()
{
    GameCoin* coin;
    int line = 0;
 
    for (int i = 0; i < BOARDX; i++)
        lineDeadCoin[i] = 0;
 
    for (int i = 0; i < _gameCoins->count(); i++) {
        coin = (GameCoin*)_gameCoins->objectAtIndex(i);
 
        if (coin->getState() == GameCoin::DEAD) {
            line = (int)(i / BOARDY);
            lineDeadCoin[line] += 1;
 
            setNewCoin(coin);
        }
    }
    addNewCoinAction();
	
}

void GameScene::setNewCoin(GameCoin* coin)
{
    CCString* name;
    CCTexture2D* tex;
    int coinType = rand() % TOTALCOINTYPE + 1;
 
    name = CCString::createWithFormat("coin_%i.png", coinType);
    tex = CCTextureCache::sharedTextureCache()->addImage(name->getCString());
 
    coin->setTexture(tex);
    coin->setVisible(true);
    coin->setType(coinType);
    coin->setState(GameCoin::LIVE);
}

void GameScene::addNewCoinAction()
{
    GameCoin* coin;
    CCPoint pos;
    int startIndex;
    int diffY = 45;
 
    for (int i = 0; i < BOARDX; i++) 
	{
        if(lineDeadCoin[i] > 0) 
		{
            startIndex = i * BOARDY;
 
            for (int j = startIndex; j < startIndex + lineDeadCoin[i]; j++) 
			{
                coin = (GameCoin*)_gameCoins->objectAtIndex(j);
                pos = coin->getPosition();
                coin->setPosition(ccp(pos.x, pos.y + (lineDeadCoin[i] * diffY)));
 
                moveCoin(coin, pos);
            }   
        }   
    } 
	
}

void GameScene::addGameScore(int deadCoinNum)
{
    char score1[100] = {0,};
	auto scoreFont = (CCLabelBMFont*)this->getChildByTag(TAG_LABEL_SCORE);
    score += (deadCoinNum * 100);
 
    sprintf(score1, "%i", score);
    scoreFont->setString(score1);

	if(!stage1)
	{
		if(score>=5000)
		{
			isTouch=false;
			UserDefault::getInstance()->setBoolForKey("STAGE1", true);
			unscheduleAllSelectors();
			initClear();
		}
	}
	else if(!stage2)
	{
		if(score>=10000)
		{
			isTouch=false;
			UserDefault::getInstance()->setBoolForKey("STAGE2", true);
			unscheduleAllSelectors();
			initClear();
		}
	}
	else if(!stage3)
	{
		if(score>=12000)
		{
			isTouch=false;
			UserDefault::getInstance()->setBoolForKey("STAGE3", true);
			unscheduleAllSelectors();
			initClear();
		}
	}
	else if(!stage4)
	{
		if(score>=14000)
		{
			isTouch=false;
			UserDefault::getInstance()->setBoolForKey("STAGE4", true);
			unscheduleAllSelectors();
			initClear();
		}
	}
	else if(!stage5)
	{
		if(score>=15000)
		{
			isTouch=false;
			UserDefault::getInstance()->setBoolForKey("STAGE5", true);
			unscheduleAllSelectors();
			initClear();
		}
	}
}

void GameScene::timeCount(float delta)
{
    if (--gameTime == 0) {
       isTouch=false;
	   SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	   initGameOver();
    }
}

void GameScene::changeScene()
{
	auto scene = TransitionFade::create(2.0, StageScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void GameScene::soundEffect()
{
		SimpleAudioEngine::getInstance()->playEffect("Laser.wav");
}