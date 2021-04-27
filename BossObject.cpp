#include "BossObject.h"

BossObject::BossObject()
{
    x_pos=0.0;
    y_pos=0.0;
    frame_present=High;
    number_health=0;
    number_health_one_frame=0;
    on_ground=false;
    y_val=0.0;
    map_x=0;
    map_y=0;
}

BossObject::~BossObject()
{
    ;
}

bool BossObject::LoadImg(string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path.c_str(),screen);
    return ret;
}

bool BossObject::LoadImgPresent(SDL_Renderer* screen)
{
    bool ret=true;
    if(frame_present==High)
    {
        ret=LoadImg("boss//boss_high.png",screen);
    }
    else if(frame_present==Medium)
    {
        ret=LoadImg("boss//boss_medium.png",screen);
    }
    else if(frame_present==Low)
    {
        ret=LoadImg("boss//boss_low.png",screen);
    }
    else if(frame_present==Die)
    {
        RemoveAllBullet(1);
        frees();
    }

    return ret;
}

void BossObject::Show(SDL_Renderer* des)
{
    base_x=x_pos-map_x;
    base_y=y_pos-map_y;
    SDL_Rect renderQuad={base_x,base_y,base_width,base_height};
    SDL_RenderCopy(des,base_texture,NULL,&renderQuad);
}

void BossObject::DoBoss(Map& map_data)
{
    y_val+=BOSS_G_SPEED;
    CheckToMap(map_data);
}

void BossObject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    //check theo chieu doc

    int width_min=(base_width<TILE_MAP_SIZE)?base_width:TILE_MAP_SIZE;//???

    y1=(y_pos+y_val)/TILE_MAP_SIZE;
    y2=(y_pos+y_val+base_height-1)/TILE_MAP_SIZE;

    if(x1>=0&&x2<=MAX_MAP_X&&y1>=0&&y2<=MAX_MAP_Y)
    {
        if(y_val>0)
        {
            if((map_data.tile[y2-2][x1]!=0&&map_data.tile[y2][x1]!=COIN)
               ||(map_data.tile[y2-2][x2]!=0&&map_data.tile[y2][x2]!=COIN))
            {
                y_pos=y2*TILE_MAP_SIZE;
                y_pos-=(base_height+1);
                y_val=0;
                on_ground=true;
            }
        }
    }

    y_pos+=y_val;
}


void BossObject::InitBullet1(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y)
{
    if(t_bullet!=NULL)
    {
        t_bullet->SetBulletType(BulletObject::THREAT_BULLET_1);
        t_bullet->SetBulletDir(BulletObject::DirLeft);

        t_bullet->SetRect(bullet_pos_x,bullet_pos_y);


        t_bullet->LoadImgBullet(screen);
        t_bullet->Set_is_move(true);
        t_bullet->Set_x_val(15);
        bullet_list_1.push_back(t_bullet);
    }
}

void BossObject::InitBullet2(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y)
{
    if(t_bullet!=NULL)
    {
        t_bullet->SetBulletType(BulletObject::THREAT_BULLET_1);
        t_bullet->SetBulletDir(BulletObject::DirLeft);

        t_bullet->SetRect(bullet_pos_x,bullet_pos_y);


        t_bullet->LoadImgBullet(screen);
        t_bullet->Set_is_move(true);
        t_bullet->Set_x_val(15);
        bullet_list_2.push_back(t_bullet);
    }
}

void BossObject::InitBullet3(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y)
{
    if(t_bullet!=NULL)
    {
        t_bullet->SetBulletType(BulletObject::THREAT_BULLET_1);
        t_bullet->SetBulletDir(BulletObject::DirLeft);

        t_bullet->SetRect(bullet_pos_x,bullet_pos_y);


        t_bullet->LoadImgBullet(screen);
        t_bullet->Set_is_move(true);
        t_bullet->Set_x_val(15);
        bullet_list_3.push_back(t_bullet);
    }
}

void BossObject::MakeBullet1(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect)
{
    for(int i=0;i<bullet_list_1.size();i++)
    {
        BulletObject* t_bullet=bullet_list_1.at(i);

        if(t_bullet!=NULL)
        {
            t_bullet->CheckBulletMove(screen_width,screen_height);
            if(t_bullet->Get_is_move())
            {
                int bullet_space=base_x+base_width-t_bullet->GetBaseX()/*vi tri vien dan*/;
                if(bullet_space<600&&bullet_space>0)
                {
                    t_bullet->CheckBulletMove(x_limit,y_limit);
                    t_bullet->RenderOnScreen(screen);
                }
                else
                {
                    t_bullet->Set_is_move(false);
                }
            }
            else if(t_bullet->Get_is_move()==false)
            {
                t_bullet->Set_is_move(true);
                t_bullet->SetRect(x_rect,y_rect);
            }
        }
    }
}

void BossObject::MakeBullet2(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect)
{
    for(int i=0;i<bullet_list_2.size();i++)
    {
        BulletObject* t_bullet=bullet_list_2.at(i);

        if(t_bullet!=NULL)
        {
            t_bullet->CheckBulletMove(screen_width,screen_height);
            if(t_bullet->Get_is_move())
            {
                int bullet_space=base_x+base_width-t_bullet->GetBaseX()/*vi tri vien dan*/;
                if(bullet_space<600&&bullet_space>0)
                {
                    t_bullet->CheckBulletMove(x_limit,y_limit);
                    t_bullet->RenderOnScreen(screen);
                }
                else
                {
                    t_bullet->Set_is_move(false);
                }
            }
            else if(t_bullet->Get_is_move()==false)
            {
                t_bullet->Set_is_move(true);
                t_bullet->SetRect(x_rect,y_rect);
            }
        }
    }
}

void BossObject::MakeBullet3(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect)
{
    for(int i=0;i<bullet_list_3.size();i++)
    {
        BulletObject* t_bullet=bullet_list_3.at(i);

        if(t_bullet!=NULL)
        {
            t_bullet->CheckBulletMove(screen_width,screen_height);
            if(t_bullet->Get_is_move())
            {
                int bullet_space=base_x+base_width-t_bullet->GetBaseX()/*vi tri vien dan*/;
                if(bullet_space<600&&bullet_space>0)
                {
                    t_bullet->CheckBulletMove(x_limit,y_limit);
                    t_bullet->RenderOnScreen(screen);
                }
                else
                {
                    t_bullet->Set_is_move(false);
                }
            }
            else if(t_bullet->Get_is_move()==false)
            {
                t_bullet->Set_is_move(true);
                t_bullet->SetRect(x_rect,y_rect);
            }
        }
    }
}

void BossObject::RemoveAllBullet(const int& idx)
{
    int size1=bullet_list_1.size();
    if(size1>0&&idx<size1)
    {
        BulletObject* p_bullet=bullet_list_1.at(idx);
        bullet_list_1.erase(bullet_list_1.begin()+idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
    int size2=bullet_list_2.size();
    if(size2>0&&idx<size2)
    {
        BulletObject* p_bullet=bullet_list_2.at(idx);
        bullet_list_2.erase(bullet_list_2.begin()+idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
    int size3=bullet_list_3.size();
    if(size3>0&&idx<size3)
    {
        BulletObject* p_bullet=bullet_list_3.at(idx);
        bullet_list_3.erase(bullet_list_3.begin()+idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}


SDL_Rect BossObject::GetRectFrame()
{
    SDL_Rect rectQuad;
    rectQuad.x=base_x;
    rectQuad.y=base_y;
    rectQuad.h=base_height;
    rectQuad.w=base_width;
    return rectQuad;
}



