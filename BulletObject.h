#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "init.h"
#include "BaseObject.h"

class BulletObject:public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DirRight=20,
        DirLeft=21,
        DirUp=22,
        DirDown=23,
    };

    enum BulletType
    {
        PLAYER_BULLET=50,
        THREAT_BULLET_1=51,
        THREAT_BULLET_2=52,
        THREAT_BULLET_3=53,
    };

    void Set_x_val(const int& _x_val){x_val=_x_val;}
    void Set_y_val(const int& _y_val){y_val=_y_val;}

    int Get_x_val() const {return x_val;}
    int Get_y_val() const {return y_val;}

    void Set_is_move(const bool& _is_move){is_move=_is_move;}
    bool Get_is_move() const {return is_move;}

    void SetBulletDir(const int _bullet_dir) {bullet_dir=_bullet_dir;}
    int GetBulletDir() const {return bullet_dir;}

    void SetBulletType(const int _bullet_type) {bullet_type=_bullet_type;}
    int GetBulletType() {return bullet_type;}

    //hàm check viên đạn ở trong map
    void CheckBulletMove(const int& x_border,const int& y_border);

    void LoadImgBullet(SDL_Renderer* des);

    SDL_Rect GetRectFrame();

private:
    int x_val;
    int y_val;

    bool is_move;

    int bullet_dir;//hướng đạn

    //loai dan
    int bullet_type;
};





#endif // BULLET_OBJECT_H_
