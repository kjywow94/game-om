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
	bool isTouch;								//��ġ ���ɿ���
	int lastCoin;									//������ ���� ��ġ
	int selectCoinCount;
	static int adjCoin[BOARDX * BOARDY][TOTALADJCOIN];
	int lineDeadCoin[BOARDX];
	int score;										//��������
	int gameTime;
	//CCLabelBMFont* scoreFont; 
	CCProgressTimer* progressTimeBar;		//Ÿ�̸ӹ�

	virtual bool init();
	CREATE_FUNC(GameScene);

	~GameScene();							//�Ҹ���
	void initBG();							//���ȭ�� �ʱ�ȭ
	void initBGM();
	void initData();							//������ �ʱ�ȭ
	void initAnimation_1();					//�ִϸ��̼� �ʱ�ȭ
	void initAnimation_2();	
	void actionAnimation_1();				//�ִϸ��̼� �׼�
	void actionAnimation_2();
	void soundEffect();

	void initReady();						//Ready �� ����
	void initStart();							//Start �� ����
	void initClear();
	void initGameOver();

	void actionReady();					//Ready �׼� ����
	void actionStart();						//Start �׼� ����

	void touchTrue();						//��ġ ����
	void initGameCoin();					//���ε� �ʱ�ȭ
	void initScore();						//������
	void initTimer();						//Ÿ�̸ӹ�

	GameCoin* createGameCoin(const CCPoint &pos, int type, int state);		//���ϴ� ��ġ, ����, ���¿� �°� ������ ������ִ� �Լ�

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
