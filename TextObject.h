#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "init.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        TEXT_RED=60,
        TEXT_WHITE=61,
        TEXT_BLACK=62,
        TEXT_YELLOW=63,
    };

    bool LoadFont(TTF_Font* font,SDL_Renderer* screen);
    void Frees();

    void SetColorText(Uint8 red,Uint8 green,Uint8 blue);
    void SetColorText(const int& type);

    void RenderText(SDL_Renderer* screen,
                    int x_pos,int y_pos,
                    SDL_Rect* clip=NULL,
                    double angel=0.0,//goc nghieng
                    SDL_Point* center=NULL,
                    SDL_RendererFlip flip=SDL_FLIP_NONE);

    int GetWidthText() const {return texts_width;}
    int GetHeightText() const {return texts_height;}

    void SetTexts(const string& _texts) {texts=_texts;}
    string GetTexts() const {return texts;}

private:
    string texts;

    SDL_Color texts_color;

    SDL_Texture* texts_texture;

    //kich thuoc
    int texts_height;
    int texts_width;

};






#endif // TEXT_OBJECT_H_


