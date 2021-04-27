#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_


#include "init.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "BulletObject.h"


#define THREAT_FRAME_NUMBER 8
#define THREAT_G_SPEED 0.8
#define THREAT_MAX_G 8
#define THREAT_SPEED 5

class ThreatObject:public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    enum TypeMove
    {
        STATIC=0,
        MOVE=1,
        FLY=2,
    };

    void Set_x_val(const float& _x_val){x_val=_x_val;}
    void Set_y_val(const float& _y_val){y_val=_y_val;}

    void Set_x_pos(const float& _x_pos){x_pos=_x_pos;}
    void Set_y_pos(const float& _y_pos){y_pos=_y_pos;}

    float Get_x_pos() const {return x_pos;}
    float Get_y_pos() const {return y_pos;}

    int GetWidthFrame() const {return width_frame;}
    int GetHeightFrame() const {return height_frame;}

    bool LoadImg(const string path,SDL_Renderer* screen);

    void SetClips();
    void Show(SDL_Renderer* des);

    void SetMapStartXY(const int& mp_x,const int& mp_y) {map_x=mp_x; map_y=mp_y;};
    void DoThreat(Map& map_data);

    void CheckToMap(Map& map_data);

    void SetTypeMove(const int& _type_move) {type_move=_type_move;}
    void SetSpaceMove(const int& _pos_a,const int& _pos_b) {animation_pos_a=_pos_a; animation_pos_b=_pos_b;}

    void SetInputLeft (const int& ipLeft) {input_type.left=ipLeft;} //set các trạng thái của threat động

    void LoadImpMoveType(SDL_Renderer* screen);


    void SetBulletList(const vector<BulletObject*>& _bullet_list) {bullet_list=_bullet_list;}
    vector<BulletObject*> GetBullet() const {return bullet_list;}

    void InitBullet(BulletObject* t_bullet,SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen,const int& x_limit,const int& y_limit);

    SDL_Rect GetRectFrame();

    void RemoveBullet(const int& bullet_number);

    void SetOnGround(const bool& _on_ground) {on_ground=_on_ground;}
    bool GetOnGround() {return on_ground;}

private:
    SDL_Rect frame_clip[THREAT_FRAME_NUMBER];

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;


    int map_x;
    int map_y;

    int width_frame;
    int height_frame;
    int frame;

    bool on_ground;
    int time_threat_comback;

    //threat động
    int type_move;
    //khoang di chuyen
    int animation_pos_a;
    int animation_pos_b;

    Input input_type;

    vector<BulletObject*> bullet_list;
};












#endif // THREAT_OBJECT_H_
