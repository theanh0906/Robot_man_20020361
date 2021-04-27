#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "init.h"

class BaseObject
{
    public:
        BaseObject();
        ~BaseObject();

        int GetBaseX()const {return base_x;}
        int GetBaseY() const {return base_y;}
        int GetBaseWidth() const {return base_width;}
        int GetBaseHeight() const {return base_height;}

        //set vị trí load ảnh
        void SetRect(const int& _x,const int& _y) {base_x=_x;base_y=_y;}

        virtual bool LoadImg(const string path,SDL_Renderer* screen);

        void RenderOnScreen(SDL_Renderer* screen,SDL_Rect* clip=NULL);

        void frees();

    protected:
        //vị trí load ảnh so voi man hinh
        int base_x;
        int base_y;

        //kích thước ảnh
        int base_width;
        int base_height;

        //ảnh
        SDL_Texture* base_texture;

};



#endif // BASE_OBJECT_H_
