#ifndef PLAYER_COIN_H_
#define PLAYER_COIN_H_

#include "init.h"
#include "BaseObject.h"

class PlayerCoin:public BaseObject
{
public:
    PlayerCoin();
    ~PlayerCoin();

    void LoadImgCoin(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetRect(const int& _x_pos,const int& _y_pos);


private:
    int x_pos;
    int y_pos;
};



#endif // PLAYER_COIN_H_


