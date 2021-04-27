#include "PlayerHealth.h"

PlayerHealth::PlayerHealth()
{
    number_health=0;
}
PlayerHealth::~PlayerHealth()
{

}

void PlayerHealth::SetPos(const int& x_pos)
{
    img_health_pos_list.push_back(x_pos);
}

void PlayerHealth::LoadImgHealth(SDL_Renderer* screen)
{
    LoadImg("player_owned//player_pw.png",screen);
    number_health=PLAYER_LIFE;

    if(img_health_pos_list.size()>0)
    {
        img_health_pos_list.clear();
    }

    for(int i=0;i<number_health;i++)
    {
        int pos=30+i*40;
        SetPos(pos);
    }
}

void PlayerHealth::Show(SDL_Renderer* screen)
{
    for(int i=0;i<img_health_pos_list.size();i++)
    {
        base_x=img_health_pos_list.at(i);
        base_y=0;
        RenderOnScreen(screen);
    }
}

void PlayerHealth::IncreateHealth()
{
    number_health++;
    int last_pos=img_health_pos_list.back();
    last_pos+=40;
    img_health_pos_list.push_back(last_pos);
}

void PlayerHealth::DecreateHealth()
{
    number_health--;
    img_health_pos_list.pop_back();
}


