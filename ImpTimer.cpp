#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick=0;
    paused_tick=0;
    is_paused=false;
    is_started=false;
}

ImpTimer::~ImpTimer()
{

}

int ImpTimer::Start()
{
    is_started=true;
    is_paused=false;
    start_tick=SDL_GetTicks();
    return start_tick;
}

void ImpTimer::Stop()
{
    is_paused=false;
    is_started=false;
}

void ImpTimer::Pause()
{
    if(is_started==true&&is_paused==false)
    {
        is_paused=true;
        paused_tick=SDL_GetTicks()-start_tick;
    }
}

void ImpTimer::Unpause()
{
    if(is_paused==true)
    {
        is_paused=false;
        start_tick=SDL_GetTicks()-paused_tick;
        paused_tick=0;
    }
}

int ImpTimer::GetTick()
{
    if(is_started==true)
    {
        if(is_paused==true)
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks()-start_tick;
        }
    }
    return 0;
}

bool ImpTimer::Is_started()
{
    return is_started;
}
bool ImpTimer::Is_paused()
{
    return is_paused;
}

