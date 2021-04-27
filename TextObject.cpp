#include "TextObject.h"

TextObject::TextObject()
{
    texts_width=0;
    texts_height=0;

    texts_texture=NULL;

    texts_color.r=255;
    texts_color.g=255;
    texts_color.b=255;

}
TextObject::~TextObject()
{

}

bool TextObject::LoadFont(TTF_Font* font,SDL_Renderer* screen)
{
    SDL_Surface* text_surface=TTF_RenderText_Solid(font,texts.c_str(),texts_color);
    if(text_surface!=NULL)
    {
        texts_texture=SDL_CreateTextureFromSurface(screen,text_surface);
        texts_width=text_surface->w;
        texts_height=text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    return texts_texture!=NULL;
}

void TextObject::Frees()
{
    if(texts_texture!=NULL)
    {
        SDL_DestroyTexture(texts_texture);
        texts_texture=NULL;
    }
}

void TextObject::SetColorText(Uint8 red,Uint8 green,Uint8 blue)
{
    texts_color.r=red;
    texts_color.g=green;
    texts_color.b=blue;
}

void TextObject::SetColorText(const int& type)
{
    if(type==TEXT_RED)
    {
        SDL_Color color={255,0,0};
        texts_color=color;
    }
    else if(type==TEXT_WHITE)
    {
        SDL_Color color={255,255,255};
        texts_color=color;
    }
    else if(type==TEXT_BLACK)
    {
        SDL_Color color={0,0,0};
        texts_color=color;
    }
    else if(type==TEXT_YELLOW)
    {
        SDL_Color color={255,255,0};
        texts_color=color;
    }
}

void TextObject::RenderText(SDL_Renderer* screen,
                            int x_pos,int y_pos,
                            SDL_Rect* clip/*=NULL*/,
                            double angel/*=0.0*/,
                            SDL_Point* center/*=NULL*/,
                            SDL_RendererFlip flip/*=SDL_FLIP_NONE*/)
{
    SDL_Rect renderQuad={x_pos,y_pos,texts_width,texts_height};
    if(clip!=NULL)
    {
        renderQuad.w=clip->w;
        renderQuad.h=clip->h;
    }
    SDL_RenderCopyEx(screen,texts_texture,clip,&renderQuad,angel,center,flip);
}

