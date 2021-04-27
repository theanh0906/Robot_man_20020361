#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
    frame_width=0;
    frame_height=0;
    frame_number=0;
}
ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::LoadImg(string path,SDL_Renderer* screen)
{
    bool check=BaseObject::LoadImg(path,screen);
    if(check)
    {
        frame_height=base_height;
        frame_width=base_width/8;
    }
    return check;
}

void ExplosionObject::SetClips()
{
    for(int i=0;i<8;i++)
    {
        frame_clip[i].x=i*frame_width;
        frame_clip[i].y=0;
        frame_clip[i].h=frame_height;
        frame_clip[i].w=frame_width;
    }
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip=&frame_clip[frame_number];
    SDL_Rect renderQuad={base_x,base_y,frame_width,frame_height};
    if(currentClip!=NULL)
    {
        renderQuad.w=currentClip->w;
        renderQuad.h=currentClip->h;
    }
    SDL_RenderCopy(screen,base_texture,currentClip,&renderQuad);
}

