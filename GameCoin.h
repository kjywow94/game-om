#ifndef __POCOPANG_GAMECOIN_H__
#define __POCOPANG_GAMECOIN_H__
 
#include "cocos2d.h"
 
using namespace cocos2d;
 
class GameCoin : public CCSprite
{
private:
 
public:
    enum gameState {
        LIVE,
        DEAD,
        SELECT,
		MOVE,
    };  
 
    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(int, _state, State);
 
    static GameCoin* spriteWithFile(const char* pszFileName);
 
    GameCoin(); 
    ~GameCoin();
};
 
#endif // __POCOPANG_GAMECOIN_H__
