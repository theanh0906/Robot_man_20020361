#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "init.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define PLAYER_G_SPEED 1 //trọng lực
#define PLAYER_MAX_G 10
#define PLAYER_SPEED 20
#define BULLET_SPEED 25
#define PLAYER_LIFE 3

class PlayerObject:public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    // các trạng thái
    enum WalkType
    {
        NONE=0,
        WALK_RIGHT=1,
        WALK_LEFT=2,
        LOOK_UP=3,
        LOOK_DOWN=4,
    };

    bool LoadImg(const string path,SDL_Renderer* screen);

    //show nhân vật khi di chuyển
    void Show(SDL_Renderer* des);

    void HandelInputAction(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* bullet_sound[4],Mix_Chunk* bullet_player_skill[1]);

    //hàm tạo hiệu ứng di chuyển
    void SetClips();


    void DoPlayer(Map& map_data); //biến map để lấy dữ liệu của bản đồ tránh nhân vật đi ra ngoài

    //hàm lấy giá trị start x, start y của map
    void SetMapStartXY(const int& _map_x,const int& _map_y) {map_x=_map_x; map_y=_map_y;}

    //hàm kiểm tra map để nhân vật va chạm
    void CheckToMap(Map& map_data);

    //hàm tính vị trí hiển thị của map khi nhân vật di chuyển
    //center.... hình ảnh trung tâm trên bản đồ
    void CenterEntityOnMap(Map& map_data);

    //cập nhật hình ảnh khi nhân vật di chuyển
    void UpdateImagePlayer(SDL_Renderer* des);

    //đạn nhân vật
    void SetBulletList(vector<BulletObject*>_p_bullet_list) {p_bullet_list=_p_bullet_list;}
    vector<BulletObject*>GetBulletList() const {return p_bullet_list;}


    //đạn di chuyển
    void HandleBullet(SDL_Renderer* des);

    //vàng của nhân vật
    void IncreaseCoin();
    int GetPlayerCoin() const {return player_coin;}


    //hàm xoá đạn khi bắn trúng threat
   void RemoveBullet(const int& bullet_number);

   //hàm lấy giá trị của frame hiện tại khi nhân vật di chuyển..
   SDL_Rect GetRectFrame();

   //hàm set thời gian quay lại khi nhân vật chết
   void SetTimeComeBack(const int& _time_comback) {time_comback=_time_comback;}

   float GetYPos() const {return y_pos;};

   void SetNumberGunHeat(const int& _number_gun_heat) {number_gun_heat=_number_gun_heat;};

   int GetNumberGunHeat() const {return number_gun_heat;};

   void SetNumberMana(const int& _number_mana) {number_mana=_number_mana;};

   int GetNumberPlayerSkill() const {return number_mana;};

private:
    //giá trị khi nhấn phím
    float x_val;
    float y_val;

    // vị trí hiện tại của nhân vật
    float x_pos;
    float y_pos;

    //giá trị hình ảnh hiện tại(vì hình ảnh di chuyển là một chuỗi)
    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];

    //biến lưu trạng thái nhân vật
    Input input_type;

    //biến lưu chỉ số của frame hien tai
    int frame_present;

    //biến cho biết sử dụng hình ảnh trạng thái di chuyển sang trái hay phải
    int status;
    int status_temp;

    //kiem tra nhan vat co o tren mat dat hay khog
    bool on_ground;

    //mép bản đồ bên trai khi nhân vật di chuyển
    int map_x;
    int map_y;

    int time_comback;

    //vector cho băng đạn
    vector<BulletObject*>p_bullet_list;

    int player_coin;

    int number_gun_heat;

    int number_mana;

};






#endif // PLAYER_OBJECT_H_



