
#include "ClassicScene.h"
#include "ModeScene.h"
#include "GameCoin.h"
#include "ScoreScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

int ClassicScene::adjCoin[BOARDX * BOARDY][TOTALADJCOIN] = { 
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

Scene* ClassicScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ClassicScene::create();
	scene->addChild(layer);

	return scene;
}

bool ClassicScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClassicScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ClassicScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ClassicScene::onTouchEnded, this);
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
ClassicScene::~ClassicScene()
{
	CC_SAFE_RELEASE(_gameCoins);
	CC_SAFE_RELEASE(_selectCoins);
    CC_SAFE_RELEASE(_selectMask);
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void ClassicScene::initBG()
{
	auto sprBG = Sprite::create("GalaxyPangBG.png");
	sprBG -> setPosition(Point(Director::getInstance()->getWinSize().width/2, 
		Director::getInstance()->getWinSize().height/2));
	this->addChild(sprBG);

	
}
void ClassicScene::initBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("gameScene.mp3",true);
}

void ClassicScene::initAnimation_1()
{
	auto action1 = RotateBy::create(0.5, 20);
	auto action2 = action1->reverse();
	auto action3 = RotateBy::create(0.5, -20);
	auto action4 = action3->reverse();
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5);
	
	auto sprAlien_5 = Sprite::create("Alien5.png");
	sprAlien_5->setScale(0.9);
	sprAlien_5->setPosition(Point(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.3));
	this->addChild(sprAlien_5);
	sprAlien_5->runAction(action6);
	
}

void ClassicScene::initAnimation_2()
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

void ClassicScene::actionAnimation_1()
{
	auto particle = ParticleFire::create();
	particle->setPosition(Director::getInstance()->getWinSize().width/1.3, Director::getInstance()->getWinSize().height/1.4);
	particle->setTag(TAG_PARTICLE_FIRE);
	particle->setScale(0.5);
	this->addChild(particle);
	
	auto action = Sequence::create(
		DelayTime::create(2.5),
		Hide::create(),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::actionAnimation_2, this)),
		NULL);
	
	particle->runAction(action);
}
void ClassicScene::actionAnimation_2()
{
	auto particle = this->getChildByTag(TAG_PARTICLE_FIRE); 
	this->removeChild(particle);
}

void ClassicScene::initData()
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
void ClassicScene::initScore()
{
	auto scoreFont = CCLabelBMFont::create("0", "font.fnt", Director::getInstance()->getWinSize().width * 0.3f);
	scoreFont->setTag(TAG_LABEL_SCORE);
    scoreFont->setAnchorPoint(Point(1, 0.5));
    scoreFont->setPosition(Point(Director::getInstance()->getWinSize().width * 0.65f, Director::getInstance()->getWinSize().height * 0.95f));
    scoreFont->setScale(0.8);
    this->addChild(scoreFont);
	
}
void ClassicScene::initTimer()
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
	this->schedule(schedule_selector(ClassicScene::timeCount), 1.0f);
}
void ClassicScene::initReady()
{
	auto readyLabel = Label::createWithTTF("READY", "Galaxy2.ttf", 50);
	readyLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	readyLabel->setTag(TAG_LABEL_READY);
	readyLabel->setColor(Color3B::WHITE);
	readyLabel->setScale(0.0);
	this->addChild(readyLabel, 10);
}

void ClassicScene::initStart()
{
	auto startLabel = Label::createWithTTF("START", "Galaxy2.ttf", 50);
	startLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	startLabel->setTag(TAG_LABEL_START);
	startLabel->setColor(Color3B::WHITE);
	startLabel->setScale(0.0);
	this->addChild(startLabel, 10);
}


void ClassicScene::initTimeOver()
{
	auto gameOverLabel = Label::createWithTTF("TIME OVER", "Galaxy2.ttf", 50);
	gameOverLabel->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	gameOverLabel->setTag(TAG_LABEL_GAMEOVER);
	gameOverLabel->setColor(Color3B::WHITE);
	gameOverLabel->setScale(0.0);
	this->addChild(gameOverLabel, 10);

	auto actionGameOver = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::changeScene, this)),
		NULL);

	gameOverLabel->runAction(actionGameOver);
}

void ClassicScene::actionReady()
{
	auto actionReady = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::actionStart, this)),
		NULL);

	auto readyLabel = (Label*)this->getChildByTag(TAG_LABEL_READY);
	readyLabel->runAction(actionReady);
}

void ClassicScene::actionStart()
{
	auto actionStart = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::touchTrue, this)),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::initTimer, this)),
		CallFunc::create(CC_CALLBACK_0(ClassicScene::initBGM, this)),
		NULL);

	auto startLabel = (Label*)this->getChildByTag(TAG_LABEL_START);
	startLabel->runAction(actionStart);
}

void ClassicScene::touchTrue()
{
	isTouch = TRUE;
}

void ClassicScene::initGameCoin()
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

GameCoin* ClassicScene::createGameCoin(const CCPoint &pos, int type, int state)
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

bool ClassicScene::onTouchBegan(Touch* touch, Event* event)
{
	if(!isTouch)
		return false;

	Point location = touch->getLocation();
	lastCoin = checkPushGameCoin(location);
   
	if (lastCoin >= 0) 
        addSelectCoins(lastCoin);
		
	return true;
}

void ClassicScene::onTouchMoved(Touch* touch, Event* event)
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

void ClassicScene::onTouchEnded(Touch* touch, Event* event)
{
	if(!isTouch)
		return;
	Point location = touch->getLocation();
	clearSelectCoin();
	moveUpDeadCoin();
	addNewCoin();
	
}

int ClassicScene::checkPushGameCoin(CCPoint &touchPos)
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

bool ClassicScene::inLastCoin(CCPoint &touchPos)
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

int ClassicScene::checkAdjacentCoin(CCPoint &touchPos)
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

bool ClassicScene::compareCoinType(int index1, int index2)
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
int ClassicScene::addSelectCoins(int index)
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

void ClassicScene::clearSelectCoin()
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

void ClassicScene::resetSelectMask()
{
    CCSprite* selectMask;
 
    for(int i = 0; i < _selectMask->count(); i++) {
        selectMask = (CCSprite*)_selectMask->objectAtIndex(i);
        selectMask->setVisible(false);
    }
}

void ClassicScene::resetGameInfo()
{
    selectCoinCount = 0;
    lastCoin = -1;
 
    _selectCoins->removeAllObjects();
}

void ClassicScene::moveUpDeadCoin()
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

void ClassicScene::changeCoin(int index1, int index2)
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

void ClassicScene::moveCoin(GameCoin* coin, CCPoint& pos)
{
    float duration = 0.0f;
    float coinSpeed = 1000.0f;
    CCPoint prevPos = coin->getPosition();
    coin->setState(GameCoin::MOVE);
    coin->stopAllActions();

    duration = prevPos.getDistance(pos)*2 / coinSpeed;
 
    CCFiniteTimeAction* movePos = CCSequence::create(
            CCMoveTo::create(duration, pos),
            CCCallFuncN::create(this, callfuncN_selector(ClassicScene::coinMoveDone)),
			NULL);
 
    coin->runAction(movePos);
}

void ClassicScene::coinMoveDone(CCNode* pSender)
{
    GameCoin* coin = (GameCoin*)pSender;
 
    coin->stopAllActions();
    coin->setState(GameCoin::LIVE);
}

void ClassicScene::addNewCoin()
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

void ClassicScene::setNewCoin(GameCoin* coin)
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

void ClassicScene::addNewCoinAction()
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

void ClassicScene::addGameScore(int deadCoinNum)
{
    char score1[100] = {0,};
	auto scoreFont = (CCLabelBMFont*)this->getChildByTag(TAG_LABEL_SCORE);
    score += (deadCoinNum * 100);
 
    sprintf(score1, "%i", score);
    scoreFont->setString(score1);

	
}

void ClassicScene::timeCount(float delta)
{
	int scoreTemp = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE",0);

	if(score>scoreTemp)
		UserDefault::getInstance()->setIntegerForKey("HIGHSCORE", score);
    if (--gameTime == 0) {
       isTouch=false;
	   SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	   initTimeOver();
    }
}

void ClassicScene::changeScene()
{
	auto scene = TransitionFade::create(2.0, ScoreScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void ClassicScene::soundEffect()
{
		SimpleAudioEngine::getInstance()->playEffect("Laser.wav");
}