#include "BaseObject.h"

BaseObject::BaseObject()
{
    base_x=0;
    base_y=0;
    base_width=0;
    base_height=0;
    base_texture=NULL;
}

BaseObject::~BaseObject()
{
    frees();
}

bool BaseObject::LoadImg(const string path,SDL_Renderer* screen)
{
    frees();//giai phong bo nho

    bool success=true;

    SDL_Texture* new_texture=NULL;
    SDL_Surface* img=IMG_Load(path.c_str());

    if(img==NULL)
    {
        cout<<"path image error"<<IMG_GetError();
        success=false;
    }
    else
    {
        SDL_SetColorKey(img,SDL_TRUE,SDL_MapRGB(img->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B)); // những pixel true sẽ bị ẩn
        new_texture=SDL_CreateTextureFromSurface(screen,img);
        if(new_texture==NULL)
        {
            cout<<"create new tx error "<<SDL_GetError();
            success=false;
        }
        else
        {
            base_width=img->w;
            base_height=img->h;
        }
        base_texture=new_texture;
    }
    SDL_FreeSurface(img);
    return success;
}

void BaseObject::RenderOnScreen(SDL_Renderer* screen,SDL_Rect* clip)
{
    SDL_Rect rectQuad={base_x,base_y,base_width,base_height};
    SDL_RenderCopy(screen,base_texture,clip,&rectQuad);
}

void BaseObject::frees()
{
    if(base_texture!=NULL)
    {
        SDL_DestroyTexture(base_texture);
        base_texture=NULL;
        base_width=0;
        base_height=0;
    }
}



