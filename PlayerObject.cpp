#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
    frame_present=0;
    x_pos=0;
    y_pos=0;
    x_val=0;
    y_val=0;
    width_frame=0;
    height_frame=0;
    status=NONE;
    status_temp=NONE;
    input_type.left=0;
    input_type.right=0;
    input_type.down=0;
    input_type.up=0;
    input_type.jump=0;
    on_ground=false;
    map_x=0;
    map_y=0;
    time_comback=0;
    player_coin=0;
    number_gun_heat=0;
}

PlayerObject::~PlayerObject()
{

}


bool PlayerObject::LoadImg(const string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame=base_width/8;
        height_frame=base_height;
    }
    return ret;
}

void PlayerObject::SetClips()
{
    if(width_frame>0&&height_frame>0)
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

void PlayerObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if(on_ground==true)
    {
        if(status==LOOK_UP&&status_temp==WALK_RIGHT)
        {
            LoadImg("player_animation//player_look_up_right.png",des);
        }
        else if(status==LOOK_UP&&status_temp==WALK_LEFT)
        {
            LoadImg("player_animation//player_look_up_left.png",des);
        }
        else if(status==LOOK_DOWN&&status_temp==WALK_RIGHT)
        {
            LoadImg("player_animation//player_look_down_right.png",des);
        }
        else if(status==LOOK_DOWN&&status_temp==WALK_LEFT)
        {
            LoadImg("player_animation//player_look_down_left.png",des);
        }
        else if(status==WALK_RIGHT)
        {
            LoadImg("player_animation//player_right.png",des);
        }
        else if(status==WALK_LEFT)
        {
            LoadImg("player_animation//player_left.png",des);
        }
    }
    else
    {
        if(status==WALK_RIGHT)
        {
            LoadImg("player_animation//jum_right.png",des);
        }
        else if(status==WALK_LEFT)
        {
            LoadImg("player_animation//jum_left.png",des);
        }
        else if(status==LOOK_UP)
        {
            if(status_temp==WALK_RIGHT)
            {
                LoadImg("player_animation//jum_right.png",des);
            }
            else
            {
                LoadImg("player_animation//jum_left.png",des);
            }
        }
        else if(status==LOOK_DOWN)
        {
            if(status_temp==WALK_RIGHT)
            {
                LoadImg("player_animation//jum_right.png",des);
            }
            else
            {
                LoadImg("player_animation//jum_left.png",des);
            }
        }
    }
}



void PlayerObject::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);
    //khi ấn phím di chuyển thì left right =1
    if(input_type.left==1||input_type.right==1)
    {
        frame_present++;
    }
    else
    {
        frame_present=0;
    }

    if(frame_present>=8)
    {
        frame_present=0;
    }

    if(time_comback==0)
    {
        //set vi tri load anh o trong man hinh
        base_x=x_pos-map_x;
        base_y=y_pos-map_y;

        SDL_Rect* current_clip=&frame_clip[frame_present];// biến trạng thái hiện hành

        SDL_Rect renderQuad={base_x,base_y,width_frame,height_frame};

        SDL_RenderCopy(des,base_texture,current_clip,&renderQuad);
    }
}

void PlayerObject::HandelInputAction(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* bullet_sound[4],Mix_Chunk* bullet_player_skill[1])
{
    if(events.type==SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status=WALK_RIGHT;
                status_temp=status;
                input_type.right=1;
                input_type.left=0;
                UpdateImagePlayer(screen);
            }
            break;
        case SDLK_a:
            {
                status=WALK_LEFT;
                status_temp=status;
                input_type.left=1;
                input_type.right=0;
                UpdateImagePlayer(screen);
            }
            break;
        }
    }
    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                input_type.right=0;
            }
            break;
        case SDLK_a:
            {
                input_type.left=0;
            }
            break;
        }
    }

    if(events.type==SDL_KEYDOWN)
    {
        if(on_ground==true)
        {
            switch(events.key.keysym.sym)
            {
                case SDLK_k:
                    input_type.jump=1;
                    break;
                case SDLK_w:
                    status=LOOK_UP;
                    input_type.up=1;
                    input_type.down=0;
                    UpdateImagePlayer(screen);
                    break;
                case SDLK_s:
                    status=LOOK_DOWN;
                    input_type.up=0;
                    input_type.down=1;
                    UpdateImagePlayer(screen);
                    break;
            }
        }
    }

    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_w:
                input_type.up=0;
                status=status_temp;
                break;
            case SDLK_s:
                input_type.down=0;
                status=status_temp;
                break;
            case SDLK_k:
                input_type.jump=0;
                break;
        }
    }

    if(events.type==SDL_KEYDOWN&&time_comback==0)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_j:
            if(number_gun_heat<=3)
            {
                Mix_PlayChannel(-1,bullet_sound[0],0);

                number_gun_heat++;

                BulletObject* p_bullet=new BulletObject();
                p_bullet->SetBulletType(BulletObject::PLAYER_BULLET);
                p_bullet->LoadImgBullet(screen);
                if(status==LOOK_UP)
                {
                    p_bullet->SetBulletDir(BulletObject::DirUp);
                    p_bullet->SetRect(this->base_x+width_frame*0.4,base_y);
                }
                else if(status==LOOK_DOWN)
                {
                    p_bullet->SetBulletDir(BulletObject::DirDown);
                    p_bullet->SetRect(this->base_x+width_frame*0.4,base_y+height_frame);
                }
                else if(status==WALK_RIGHT)
                {
                    p_bullet->SetBulletDir(BulletObject::DirRight);
                    p_bullet->SetRect(this->base_x+width_frame-20,base_y+height_frame*0.25);
                }
                else if(status==WALK_LEFT)
                {
                    p_bullet->SetBulletDir(BulletObject::DirLeft);
                    p_bullet->SetRect(this->base_x,base_y+height_frame*0.25);
                }

                p_bullet->Set_x_val(BULLET_SPEED);
                p_bullet->Set_y_val(BULLET_SPEED);
                p_bullet->Set_is_move(true);

                p_bullet_list.push_back(p_bullet);
                break;
            }

        }
    }

    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_j:
            {
                number_gun_heat=0;
            }
            break;
        }
    }

    if(events.type==SDL_KEYDOWN&&time_comback==0)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_l:
            if(number_mana==500)
            {
                Mix_PlayChannel(-1,bullet_player_skill[0],0);

                number_mana=0;

                for(int i=0;i<5;i++)
                {
                    BulletObject* p_bullet=new BulletObject();
                    p_bullet->SetBulletType(BulletObject::PLAYER_BULLET);
                    p_bullet->LoadImgBullet(screen);

                    if(status==WALK_RIGHT)
                    {
                        p_bullet->SetBulletDir(BulletObject::DirRight);
                        p_bullet->SetRect(this->base_x+width_frame-20,base_y+height_frame*0.25-80+i*30);
                    }
                    else if(status==LOOK_UP)
                    {
                        p_bullet->SetBulletDir(BulletObject::DirUp);
                        p_bullet->SetRect(this->base_x+width_frame*0.25-80+i*30,base_y);
                    }
                    else if(status==LOOK_DOWN)
                    {
                        p_bullet->SetBulletDir(BulletObject::DirDown);
                        p_bullet->SetRect(this->base_x+width_frame*0.25-80+i*30,base_y);
                    }

                    else if(status==WALK_LEFT)
                    {
                        p_bullet->SetBulletDir(BulletObject::DirLeft);
                        p_bullet->SetRect(this->base_x+width_frame-20,base_y+height_frame*0.25-80+i*30);
                    }

                    p_bullet->Set_x_val(BULLET_SPEED+5);
                    p_bullet->Set_y_val(BULLET_SPEED+5);
                    p_bullet->Set_is_move(true);

                    p_bullet_list.push_back(p_bullet);
                }
                break;
            }

        }
    }

    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_l:
            {
            }
            break;
        }
    }

}

void PlayerObject::HandleBullet(SDL_Renderer* des)
{
    for(int i=0;i<p_bullet_list.size();i++)
    {
        BulletObject* p_bullet=p_bullet_list.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->Get_is_move()==true)
            {
                 p_bullet->CheckBulletMove(screen_width,screen_height);
                 p_bullet->RenderOnScreen(des);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin()+i);
                if(p_bullet!=NULL)
                {
                    delete p_bullet;
                    p_bullet=NULL;
                }
            }
        }
    }
}

void PlayerObject::DoPlayer(Map& map_data)
{
    if(time_comback==0)
    {
        x_val=0;
        y_val+=PLAYER_G_SPEED;

        if(input_type.jump==1)
        {
            if(on_ground==true)
            {
                y_val=-20;
            }
            on_ground=false;
            input_type.jump=0;
        }
        if(y_val>=PLAYER_MAX_G)
        {
            y_val=PLAYER_MAX_G;
        }
        if(input_type.left==1)
        {
            x_val-=PLAYER_SPEED;
        }
        else if(input_type.right==1)
        {
            x_val+=PLAYER_SPEED;
        }

        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }
    else
    {
        time_comback--;
        if(time_comback==0)
        {
            on_ground=false;
            status=NONE;
            if(x_pos>256)
            {
                x_pos-=256;
            }
            else
            {
                x_pos=0;
            }
            y_pos=0;
            x_val=0;
            y_val=0;
        }
    }
}


void PlayerObject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    int height_min=(height_frame<TILE_MAP_SIZE)?height_frame:TILE_MAP_SIZE;

    x1=(x_pos+x_val)/TILE_MAP_SIZE;
    x2=(x_pos+x_val+width_frame-1)/TILE_MAP_SIZE;

    y1=(y_pos)/TILE_MAP_SIZE;
    y2=(y_pos+height_min-1)/TILE_MAP_SIZE;

    if(x1>=0&&x2<=MAX_MAP_X&&y1>=0&&y2<=MAX_MAP_Y)
    {
        if(x_val>0) //di chuyển sang phải
        {
            if(map_data.tile[y1][x2]==COIN||map_data.tile[y2][x2]==COIN)
            {
                map_data.tile[y1][x2]=0;
                map_data.tile[y2][x2]=0;
                IncreaseCoin();
            }
            else if(map_data.tile[y1][x2]!=0||map_data.tile[y2][x2]!=0)
            {
                x_pos=x2*TILE_MAP_SIZE;
                x_pos-=(width_frame+1);
                x_val=0;
            }
        }
        else if(x_val<0)
        {
            if(map_data.tile[y1][x1]==COIN||map_data.tile[y2][x1]==COIN)
            {
                map_data.tile[y1][x1]=0;
                map_data.tile[y2][x1]=0;
                IncreaseCoin();
            }

            else if(map_data.tile[y1][x1]!=0||map_data.tile[y2][x1]!=0)
            {
                x_pos=(x1+1)*TILE_MAP_SIZE;
                x_val=0;
            }
        }

    }

    //check theo chieu doc

    int width_min=(width_frame<TILE_MAP_SIZE)?width_frame:TILE_MAP_SIZE;

    x1=(x_pos)/TILE_MAP_SIZE;
    x2=(x_pos+width_min-1)/TILE_MAP_SIZE;

    y1=(y_pos+y_val)/TILE_MAP_SIZE;
    y2=(y_pos+y_val+height_frame-1)/TILE_MAP_SIZE;

    if(x1>=0&&x2<=MAX_MAP_X&&y1>=0&&y2<=MAX_MAP_Y)
    {
        if(y_val>0)
        {
            if(status==NONE)
            {
                status=WALK_RIGHT;
            }
            if(map_data.tile[y2][x1]==COIN||map_data.tile[y2][x2]==COIN)
            {
                map_data.tile[y2][x1]=0;
                map_data.tile[y2][x2]=0;
                IncreaseCoin();
            }
            else if(map_data.tile[y2][x1]!=0||map_data.tile[y2][x2]!=0)
            {
                y_pos=y2*TILE_MAP_SIZE;
                y_pos-=(height_frame+1);
                y_val=0;
                on_ground=true;
            }
        }
        else if(y_val<0)
        {
            if(map_data.tile[y1][x1]==COIN||map_data.tile[y1][x2]==COIN)
            {
                map_data.tile[y1][x1]=0;
                map_data.tile[y1][x2]=0;
                IncreaseCoin();
            }

            else if(map_data.tile[y1][x1]!=0||map_data.tile[y1][x2]!=0)
            {
                y_pos=(y1+1)*TILE_MAP_SIZE;
                y_val=0;
            }
        }
    }

    x_pos+=x_val;
    y_pos+=y_val;

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
        time_comback=60;
    }
}

void PlayerObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x=x_pos-screen_width/3;
    if(map_data.start_x<0)
    {
        map_data.start_x=0;
    }
    else if((map_data.start_x+screen_width)>=map_data.max_map_x)
    {
        map_data.start_x=map_data.max_map_x-screen_width;
    }

    map_data.start_y=y_pos-screen_height/2;
    if(map_data.start_y<0)
    {
        map_data.start_y=0;
    }
    else if((map_data.start_y+screen_height)>=map_data.max_map_y)
    {
        map_data.start_y=map_data.max_map_y-screen_height;
    }
}




void PlayerObject::IncreaseCoin()
{
    player_coin++;
}

void PlayerObject::RemoveBullet(const int& bullet_number)
{
    int size_bullet_list=p_bullet_list.size();
    if(size_bullet_list>0&&bullet_number<size_bullet_list)
    {
        BulletObject* p_bullet=p_bullet_list.at(bullet_number);
        p_bullet_list.erase(p_bullet_list.begin()+bullet_number);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}

SDL_Rect PlayerObject::GetRectFrame()
{
    SDL_Rect rectQuad;
    rectQuad.x=base_x;
    rectQuad.y=base_y;
    rectQuad.h=height_frame;
    rectQuad.w=width_frame;
    return rectQuad;
}
