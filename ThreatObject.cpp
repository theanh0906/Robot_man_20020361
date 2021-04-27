#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    x_pos=0.0;
    y_pos=0.0;
    x_val=0.0;
    y_val=0.0;
    map_x=0;
    map_y=0;
    width_frame=0;
    height_frame=0;
    frame=0;
    on_ground=false;
    time_threat_comback=0;
    animation_pos_a=0;
    animation_pos_b=0;
    input_type.left=0;
    input_type.right=0;
    type_move=STATIC;
}
ThreatObject::~ThreatObject()
{
    ;
}

bool ThreatObject::LoadImg(const string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret&&type_move==MOVE)
    {
        width_frame=base_width/8;
        height_frame=base_height;
    }
    else if(ret&&type_move==FLY)
    {
        width_frame=base_width/8;
        height_frame=base_height;
    }
    else if(ret&&type_move==STATIC)
    {
        width_frame=base_width/6;
        height_frame=base_height;
    }
    return ret;
}

void ThreatObject::SetClips()
{
    if(width_frame>0&&height_frame>0)
    {
        if(type_move==STATIC)
        {
            for(int i=0;i<6;i++)
            {
                frame_clip[i].x=i*width_frame;
                frame_clip[i].y=0;
                frame_clip[i].w=width_frame;
                frame_clip[i].h=height_frame;
            }
        }
        else if(type_move==MOVE)
        {
            for(int i=0;i<8;i++)
            {
                frame_clip[i].x=i*width_frame;
                frame_clip[i].y=0;
                frame_clip[i].w=width_frame;
                frame_clip[i].h=height_frame;
            }
        }
         else if(type_move==FLY)
        {
            for(int i=0;i<8;i++)
            {
                frame_clip[i].x=i*width_frame;
                frame_clip[i].y=0;
                frame_clip[i].w=width_frame;
                frame_clip[i].h=height_frame;
            }
        }
    }
}

void ThreatObject::Show(SDL_Renderer* des)
{
    if(time_threat_comback==0)
    {
        base_x=x_pos-map_x;
        base_y=y_pos-map_y;
        frame++;
        if(frame>=8&&type_move==MOVE)
        {
            frame=0;
        }
        else if(frame>=8&&type_move==FLY)
        {
            frame=0;
        }
        else if(frame>=6&&type_move==STATIC)
        {
            frame=0;
        }
        SDL_Rect* currentClip=&frame_clip[frame];//clip hien hanh
        SDL_Rect renderQuad= {base_x,base_y,width_frame,height_frame};
        SDL_RenderCopy(des,base_texture,currentClip,&renderQuad);
    }
}

void ThreatObject::DoThreat(Map& map_data)
{
    if(time_threat_comback==0)
    {
        x_val=0;
        y_val+=THREAT_G_SPEED;
        if(y_val>=THREAT_MAX_G)
        {
            y_val=THREAT_MAX_G;
        }
        if(input_type.left==1)
        {
            x_val-=THREAT_SPEED;
        }
        else if(input_type.right==1)
        {
            x_val+=THREAT_SPEED;
        }
        else
        {
           ;
        }
        CheckToMap(map_data);
    }
    else if(time_threat_comback>0)
    {
        time_threat_comback--;
        if(time_threat_comback==0)
        {
            on_ground=false;
            x_val=0;
            y_val=0;
            if(x_pos>256)
             {
                 x_pos-=256;
                 animation_pos_a-=256;
                 animation_pos_b-=256;
             }
            else
            {
                x_pos=0;
            }
            y_pos=0;
            input_type.left=1;
        }
    }
 }

void ThreatObject::CheckToMap(Map& map_data)
{
    // vị trí quai vat
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    int height_min=(height_frame<TILE_MAP_SIZE)?height_frame:TILE_MAP_SIZE;//???

    x1=(x_pos+x_val)/TILE_MAP_SIZE;
    x2=(x_pos+x_val+width_frame-1)/TILE_MAP_SIZE;

    y1=(y_pos)/TILE_MAP_SIZE;
    y2=(y_pos+height_min-1)/TILE_MAP_SIZE;

    if(x1>=0&&x2<=MAX_MAP_X&&y1>=0&&y2<=MAX_MAP_Y)
    {
        if(x_val>0)
        {
            if((map_data.tile[y1][x2]!=0&&map_data.tile[y1][x2]!=COIN)
               ||(map_data.tile[y2][x2]!=0&&map_data.tile[y2][x2]!=COIN))
            {
                x_pos=x2*TILE_MAP_SIZE;
                x_pos-=(width_frame+1);
                if(on_ground==true&&type_move==MOVE)
                    y_pos-=70; // để cho threat nhảy lên
                x_val=0;
            }
        }
        else if(x_val<0)
        {
            if((map_data.tile[y1][x1]!=0&&map_data.tile[y1][x1]!=COIN)
               ||(map_data.tile[y2][x1]!=0&&map_data.tile[y2][x1]!=COIN))
            {
                x_pos=(x1+1)*TILE_MAP_SIZE;
                if(on_ground==true&&type_move==MOVE)
                    y_pos-=70;
                x_val=0;
            }
        }

    }
    //check theo chieu doc

    int width_min=(width_frame<TILE_MAP_SIZE)?width_frame:TILE_MAP_SIZE;//???

    x1=(x_pos)/TILE_MAP_SIZE;
    x2=(x_pos+width_min-1)/TILE_MAP_SIZE;

    y1=(y_pos+y_val)/TILE_MAP_SIZE;
    y2=(y_pos+y_val+height_frame-1)/TILE_MAP_SIZE;

    if(x1>=0&&x2<=MAX_MAP_X&&y1>=0&&y2<=MAX_MAP_Y)
    {
        if(y_val>0)
        {
            if((map_data.tile[y2][x1]!=0&&map_data.tile[y2][x1]!=COIN)
               ||(map_data.tile[y2][x2]!=0&&map_data.tile[y2][x2]!=COIN))
            {
                y_pos=y2*TILE_MAP_SIZE;
                y_pos-=(height_frame+1);
                y_val=0;
                on_ground=true;
            }
            else if(type_move==STATIC||type_move==MOVE)
                on_ground=false;
            else
                on_ground=true;
        }
        else if(y_val<0)
        {
            if((map_data.tile[y1][x1]!=0&&map_data.tile[y1][x1]!=COIN)
               ||(map_data.tile[y1][x2]!=0&&map_data.tile[y1][x2]!=COIN))
            {
                y_pos=(y1+1)*TILE_MAP_SIZE;
                y_val=0;
            }
        }
    }

    x_pos+=x_val;

    if(on_ground==false)
    {
        y_pos+=y_val;
    }
    else if(on_ground==true)
    {
        y_pos=y_pos;
    }

    if(x_pos<0)
    {
        x_pos=0;
    }
    else if(x_pos+width_frame>map_data.max_map_x)
    {
        x_pos=map_data.max_map_x-width_frame-1;
    }
    if(y_pos>map_data.max_map_y)
    {
        time_threat_comback=50;
    }
}

void ThreatObject::LoadImpMoveType(SDL_Renderer* screen)
{
    if(type_move==STATIC) ;
    else if(type_move==MOVE)
    {
        if(on_ground==true)
        {
            if(x_pos>animation_pos_b)
            {
                input_type.left=1;
                input_type.right=0;
                LoadImg("threat//threat_left.png",screen);
            }
            else if(x_pos<animation_pos_a)
            {
                input_type.left=0;
                input_type.right=1;
                LoadImg("threat//threat_right.png",screen);
            }
        }
        else
        {
            if(input_type.left==1)
            {
                LoadImg("threat//threat_left.png",screen);
            }
        }
    }

    else if(type_move==FLY)
    {
        if(x_pos>animation_pos_b)
        {
            input_type.left=1;
            input_type.right=0;
            LoadImg("threat//threat_fly_left.png",screen);
        }
        else if(x_pos<animation_pos_a)
        {
            input_type.left=0;
            input_type.right=1;
            LoadImg("threat//threat_fly_right.png",screen);
        }
    }
}

void ThreatObject::InitBullet(BulletObject* t_bullet,SDL_Renderer* screen)
{
    if(t_bullet!=NULL)
    {
        if(type_move==STATIC)
        {
            t_bullet->SetBulletType(BulletObject::THREAT_BULLET_2);
            t_bullet->SetBulletDir(BulletObject::DirLeft);
            t_bullet->SetRect(base_x+5,base_y+40);
        }
        else if(type_move==MOVE)
        {
            t_bullet->SetBulletType(BulletObject::THREAT_BULLET_1);
            if(input_type.left==1)
            {
                t_bullet->SetBulletDir(BulletObject::DirLeft);
                t_bullet->SetRect(base_x,base_y+20);
            }
        }
        else if(type_move==FLY)
        {
            t_bullet->SetBulletType(BulletObject::THREAT_BULLET_3);
            t_bullet->SetBulletDir(BulletObject::DirLeft);
            t_bullet->SetRect(base_x+5,base_y+20);
        }
        t_bullet->LoadImgBullet(screen);
        t_bullet->Set_is_move(true);
        t_bullet->Set_x_val(15);
        bullet_list.push_back(t_bullet);
    }
}

void ThreatObject::MakeBullet(SDL_Renderer* screen,const int& x_limit,const int& y_limit)
{
    for(int i=0;i<bullet_list.size();i++)
    {
        BulletObject* t_bullet=bullet_list.at(i);

        if(t_bullet!=NULL)
        {
            t_bullet->CheckBulletMove(screen_width,screen_height);
            if(type_move==MOVE||type_move==FLY)
            {
                if(input_type.left==1)
                {
                    t_bullet->SetBulletDir(BulletObject::DirLeft);
                }
                else if(input_type.right==1)
                {
                    t_bullet->SetBulletDir(BulletObject::DirRight);
                }
            }
            if(t_bullet->Get_is_move())
            {
                if(type_move==STATIC)
                {
                    int bullet_space=base_x+width_frame-t_bullet->GetBaseX()/*vi tri vien dan*/;
                    if(bullet_space<400&&bullet_space>0)
                    {

                        t_bullet->CheckBulletMove(x_limit,y_limit);
                        t_bullet->RenderOnScreen(screen);
                    }
                    else
                    {
                        t_bullet->Set_is_move(false);
                    }
                }
                else if(type_move==MOVE||type_move==FLY)
                {
                    if(input_type.left==1)
                    {
                        int bullet_space=base_x+width_frame-t_bullet->GetBaseX()/*vi tri vien dan*/;
                        if(bullet_space<400&&bullet_space>0)
                        {
                            t_bullet->CheckBulletMove(x_limit,y_limit);
                            t_bullet->RenderOnScreen(screen);
                        }
                        else
                        {
                            t_bullet->Set_is_move(false);
                        }
                    }
                    else if(input_type.right==1)
                    {
                        int bullet_space=t_bullet->GetBaseX()-base_x;
                        if(bullet_space<400&&bullet_space>0)
                        {
                            t_bullet->CheckBulletMove(x_limit,y_limit);
                            t_bullet->RenderOnScreen(screen);
                        }
                        else
                        {
                            t_bullet->Set_is_move(false);
                        }
                    }
                }

            }
            else if(t_bullet->Get_is_move()==false)
            {
                t_bullet->Set_is_move(true);
                if(type_move==STATIC)
                {
                    t_bullet->SetRect(base_x+5,base_y+35);
                }
                else if(type_move==MOVE)
                {
                    t_bullet->SetRect(base_x,base_y+20);
                }
                else if(type_move==FLY)
                {
                    t_bullet->SetRect(base_x,base_y+15);
                }
            }
        }
    }
}

SDL_Rect ThreatObject::GetRectFrame()
{
    SDL_Rect rectQuad;
    rectQuad.x=base_x;
    rectQuad.y=base_y;
    rectQuad.h=height_frame;
    rectQuad.w=width_frame;
    return rectQuad;
}

void ThreatObject::RemoveBullet(const int& bullet_number)
{
    int size_bullet_list=bullet_list.size();
    if(size_bullet_list>0&&bullet_number<size_bullet_list)
    {
        BulletObject* t_bullet=bullet_list.at(bullet_number);
        t_bullet->Set_is_move(false);
    }
}

