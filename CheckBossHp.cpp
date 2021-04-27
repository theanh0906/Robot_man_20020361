#include "CheckBossHp.h"

BossHp::BossHp()
{
    number_hp_boss=0;
}
BossHp::~BossHp()
{

}

void BossHp::SetPos(const int& x_pos)
{
    img_health_pos_list.push_back(x_pos);
}

void BossHp::LoadImgHp(SDL_Renderer* screen)
{
    LoadImg("boss//hp_boss.png",screen);
    number_hp_boss=BOSS_HEALTH;

    if(img_health_pos_list.size()>0)
    {
        img_health_pos_list.clear();
    }

    for(int i=0;i<number_hp_boss;i++)
    {
        int pos=400+i*60;
        SetPos(pos);
    }
}

void BossHp::Show(SDL_Renderer* screen)
{
    for(int i=0;i<img_health_pos_list.size();i++)
    {
        base_x=img_health_pos_list.at(i);
        base_y=100;
        RenderOnScreen(screen);
    }
}


void BossHp::DecreateHp()
{
    number_hp_boss--;
    img_health_pos_list.pop_back();
}



