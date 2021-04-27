#include "draw.h"

void DrawRectangle(const Rectangles& mana,const ColorRectangle& color_mana,SDL_Renderer* screen)
{
    SDL_Rect mana_rect={mana.x_pos,mana.y_pos,mana.width,mana.height};
    SDL_SetRenderDrawColor(screen,color_mana.r,color_mana.g,color_mana.b,0xFF);

    SDL_RenderFillRect(screen,&mana_rect);
}
