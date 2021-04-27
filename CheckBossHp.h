#ifndef CHECK_BOSS_HP
#define CHECK_BOSS_HP

#include "init.h"
#include "BaseObject.h"
#include "BossObject.h"

class BossHp:public BaseObject
{
public:
    BossHp();
    ~BossHp();

    void SetNumberHp(const int& _number_hp_boss) {number_hp_boss=_number_hp_boss;}

    void SetPos(const int& x_pos);

    void Show(SDL_Renderer* screen);
    void LoadImgHp(SDL_Renderer* screen);

    void DecreateHp();

private:
    int number_hp_boss;
    vector<int>img_health_pos_list;
};




#endif // CHECK_BOSS_HP
