#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include "init.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define BOSS_HEALTH 9
#define BOSS_G_SPEED 0.8

class BossObject:public BaseObject
{
public:
    BossObject();
    ~BossObject();

    enum Health
    {
        High=40,
        Medium=41,
        Low=42,
        Die=43,
    };

    bool LoadImg(string path,SDL_Renderer* screen);
    bool LoadImgPresent(SDL_Renderer* screen);


    void Show(SDL_Renderer* des);


    void CheckToMap(Map& map_data);


    void DoBoss(Map& map_data);


    void InitBullet1(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y);
    void InitBullet2(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y);
    void InitBullet3(BulletObject* t_bullet,SDL_Renderer* screen,int bullet_pos_x,int bullet_pos_y);

    void MakeBullet1(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect);
    void MakeBullet2(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect);
    void MakeBullet3(SDL_Renderer* screen,const int& x_limit,const int& y_limit,const float& x_rect,const float& y_rect);

    void RemoveAllBullet(const int& idx);

    void SetMapStartXY(const int& mp_x,const int& mp_y) { map_x=mp_x; map_y=mp_y;};


    void Set_x_pos(const float& _x_pos) {x_pos=_x_pos;}
    void Set_y_pos(const float& _y_pos) {y_pos=_y_pos;}


    void Set_y_val(const float& _y_val) {y_val=_y_val;}


    void SetOnGround(const bool& _on_ground) {on_ground=_on_ground;}


    void SetFramePresent(const int& _frame_present) {frame_present=_frame_present;}


    float Get_y_val() const {return y_val;}
    float Get_x_pos() const {return x_pos;}
    float Get_y_pos() const {return y_pos;}
    int Get_frame_fresent() const {return frame_present;}

    int GetNumberHealthOneFrame() const {return number_health_one_frame;}
    int SetNumberHealth() const {return number_health;}

    bool GetOnGround() {return on_ground;}
    vector<BulletObject*> GetBullet1() const {return bullet_list_1;}
    vector<BulletObject*> GetBullet2() const {return bullet_list_2;}
    vector<BulletObject*> GetBullet3() const {return bullet_list_3;}

    SDL_Rect GetRectFrame();

private:
    float x_pos;
    float y_pos;

    float y_val;

    int map_x;
    int map_y;

    bool on_ground;

    int frame_present;

    int number_health_one_frame;
    int number_health;

    vector<BulletObject*> bullet_list_1;
    vector<BulletObject*> bullet_list_2;
    vector<BulletObject*> bullet_list_3;
};




#endif // BOSS_OBJECT_H_
