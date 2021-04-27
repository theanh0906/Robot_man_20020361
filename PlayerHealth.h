#ifndef PLAYER_HEALTH_H_
#define PLAYER_HEALTH_H_

#include "init.h"
#include "BaseObject.h"
#include "PlayerObject.h"

class PlayerHealth:public BaseObject
{
public:
    PlayerHealth();
    ~PlayerHealth();

    void SetNumberHealth(const int& _number_health) {number_health=_number_health;};
    void SetPos(const int& x_pos);
    void Show(SDL_Renderer* screen);
    void LoadImgHealth(SDL_Renderer* screen);

    void IncreateHealth();
    void DecreateHealth();

private:
    int number_health;
    vector<int>img_health_pos_list;
};



#endif // PLAYER_HEALTH_H_


