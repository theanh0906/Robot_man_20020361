#ifndef DRAW_H_
#define DRAW_H_

#include "init.h"

struct Rectangles
{
    Rectangles(const int& _x_pos,const int& _y_pos,const double& _width,const double& _height)
    {
        x_pos=_x_pos;
        y_pos=_y_pos;
        width=_width;
        height=_height;
    }
    int x_pos;
    int y_pos;
    double width;
    double height;
};

struct ColorRectangle
{
    ColorRectangle(const Uint8 _r,const Uint8 _g,const Uint8 _b) {r=_r, g=_g, b=_b; }

    Uint8 r;
    Uint8 g;
    Uint8 b;
};


void DrawRectangle(const Rectangles& mana,const ColorRectangle& color_mana,SDL_Renderer* screen);



#endif // DRAW_H_
