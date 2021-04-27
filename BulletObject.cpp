#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val=0;
    y_val=0;
    is_move=false;
    bullet_dir=0;
    bullet_type=0;
}

BulletObject::~BulletObject()
{
}

void BulletObject::CheckBulletMove(const int& x_border,const int& y_border)
{
    switch(bullet_dir)
    {
        case DirRight:
            base_x+=x_val;
            if(base_x>x_border)
                is_move=false;
            break;
        case DirLeft:
            base_x-=x_val;
            if(base_x<0)
                is_move=false;
            break;
        case DirUp:
            base_y-=y_val;
            if(base_y<0)
                is_move=false;
            break;
        case DirDown:
            base_y+=y_val;
            if(base_y>y_border)
                is_move=false;
            break;
    }
}
void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    if(bullet_type==PLAYER_BULLET)
        LoadImg("bullet//player.png",des);
    else if(bullet_type==THREAT_BULLET_1)
        LoadImg("bullet//threat_1.png",des);
    else if(bullet_type==THREAT_BULLET_2)
        LoadImg("bullet//threat_2.png",des);
    else if(bullet_type==THREAT_BULLET_3)
        LoadImg("bullet//threat_3.png",des);
}

SDL_Rect BulletObject::GetRectFrame()
{
    SDL_Rect rect_bullet;
    rect_bullet.x=GetBaseX();
    rect_bullet.y=GetBaseY();
    rect_bullet.h=GetBaseHeight();
    rect_bullet.w=GetBaseWidth();
    return rect_bullet;
}
