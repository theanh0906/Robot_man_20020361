#include "PlayerCoin.h"

PlayerCoin::PlayerCoin()
{
    x_pos=0;
    y_pos=0;
}
PlayerCoin::~PlayerCoin()
{

}
void PlayerCoin::LoadImgCoin(SDL_Renderer* screen)
{
    LoadImg("player_owned//money_img.png",screen);
}

void PlayerCoin::Show(SDL_Renderer* screen)
{
    base_x=x_pos;
    base_y=y_pos;
    RenderOnScreen(screen);
}

void PlayerCoin::SetRect(const int& _x_pos,const int& _y_pos)
{
    x_pos=_x_pos;
    y_pos=_y_pos;
}


