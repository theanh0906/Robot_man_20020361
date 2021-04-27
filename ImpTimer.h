#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include "init.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "PlayerObject.h"

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    int Start();
    void Stop();
    void Pause();
    void Unpause();

    //ham nhan thoi gian
    int GetTick();

    bool Is_started();
    bool Is_paused();

private:
    //thoi diem
    //tick là thời gian
    int start_tick;
    int paused_tick;

    bool is_paused;
    bool is_started;
};









#endif // IMP_TIMER_H_

