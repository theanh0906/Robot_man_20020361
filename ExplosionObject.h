#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "init.h"
#include "BaseObject.h"

class ExplosionObject:public BaseObject
{
public:

    ExplosionObject();
    ~ExplosionObject();

    void SetClips();
    void SetFrameNumber(const int& _frame_number) {frame_number=_frame_number;}

    bool LoadImg(string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);

    int GetFrameWidth() const {return frame_width;}
    int GetFrameHeight() const {return frame_height;}

private:
    int frame_number;

    int frame_width;
    int frame_height;

    SDL_Rect frame_clip[8];

};








#endif // EXPLOSION_OBJECT_H__

