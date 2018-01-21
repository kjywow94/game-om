#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameCoin.h"

USING_NS_CC;
 

#define TAG_LABEL_READY			0
#define TAG_LABEL_START			1	
#define TAG_PARTICLE_FIRE			2
#define TAG_STAGE_1					3
#define TAG_STAGE_2					4
#define TAG_STAGE_3					5
#define TAG_STAGE_4					6
#define TAG_STAGE_5					7
#define TAG_STAGE_6					8
#define TAG_LABEL_CLEAR			9
#define TAG_LABEL_GAMEOVER	10
#define TAG_LABEL_SCORE			11

class GameScene: public Layer
{
private:
	enum
	{
		BOARDX = 7,
		BOARDY = 6,
		TOTALCOINTYPE = 4,
		TOTALADJCOIN = 6,
	};
	//CCSize* _screenSize;
	//CCAction* _treeMove;

	CCArray* _gameCoins;
	CCArray* _selectMask;                                                               
	CCArray* _selectCoins;
	

public:
	
	static Scene* createScene();

	bool stage1;
	bool stage2;
	bool stage3;
	bool stage4;
	bool stage5;
	bool isTouch;								//터치 가능여부
	int lastCoin;									//마지막 코인 위치
	int selectCoinCount;
	static int adjCoin[BOARDX * BOARDY][TOTALADJCOIN];
	int lineDeadCoin[BOARDX];
	int score;										//게임점수
	int gameTime;
	//CCLabelBMFont* scoreFont; 
	CCProgressTimer* progressTimeBar;		//타이머바

	virtual bool init();
	CREATE_FUNC(GameScene);

	~GameScene();							//소멸자
	void initBG();							//배경화면 초기화
	void initBGM();
	void initData();							//데이터 초기화
	void initAnimation_1();					//애니메이션 초기화
	void initAnimation_2();	
	void actionAnimation_1();				//애니메이션 액션
	void actionAnimation_2();
	void soundEffect();

	void initReady();						//Ready 라벨 생성
	void initStart();							//Start 라벨 생성
	void initClear();
	void initGameOver();

	void actionReady();					//Ready 액션 실행
	void actionStart();						//Start 액션 실행

	void touchTrue();						//터치 가능
	void initGameCoin();					//코인들 초기화
	void initScore();						//점수판
	void initTimer();						//타이머바

	GameCoin* createGameCoin(const CCPoint &pos, int type, int state);		//원하는 위치, 종류, 상태에 맞게 코인을 만들어주는 함수

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	int checkPushGameCoin(CCPoint &touchPos);
	
	int checkAdjacentCoin(CCPoint &touchPos);
    bool inLastCoin(CCPoint &touchPos);
    int addSelectCoins(int index);
    bool compareCoinType(int index1, int index2);
	
	void clearSelectCoin();
	void resetSelectMask();
    void resetGameInfo();

	void moveUpDeadCoin();
    void changeCoin(int index1, int index2);

	void moveCoin(GameCoin* coin, CCPoint& pos);
    void coinMoveDone(CCNode* pSender);

	void addNewCoin();
    void setNewCoin(GameCoin* coin);
    void addNewCoinAction();

	void addGameScore(int deadCoinNum);

	void timeCount(float delta);
    void changeScene();

	

};


#endif // __HELLOWORLD_SCENE_H__
