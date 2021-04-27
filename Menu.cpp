#include "Menu.h"

bool CheckMouseFocus(const int& x,const int& y,const SDL_Rect& rect)
{
    bool success=false;
    if(x>=rect.x&&x<=(rect.x+rect.w)&&
       y>=rect.y&&y<=(rect.x+rect.h))
        success=true;
    return success;
}

int CreateMenuGame(SDL_Renderer* screen,BaseObject& g_bg_menu,
                   BaseObject& g_start,
                   BaseObject& g_exit)
{
    g_bg_menu.LoadImg("menu//bg_menu.png",screen);
    g_start.LoadImg("menu//start.png",screen);
    g_exit.LoadImg("menu//exit.png",screen);


    g_start.SetRect(500,220);
    g_exit.SetRect(500,300);


    SDL_Event m_event;
    int x_mouse=0;
    int y_mouse=0;

    SDL_Rect start_rect;
    start_rect.x=g_start.GetBaseX();
    start_rect.y=g_start.GetBaseY();
    start_rect.h=g_start.GetBaseHeight();
    start_rect.w=g_start.GetBaseWidth();

    SDL_Rect exit_rect;
    exit_rect.x=g_exit.GetBaseX();
    exit_rect.y=g_exit.GetBaseY();
    exit_rect.h=g_exit.GetBaseHeight();
    exit_rect.w=g_exit.GetBaseWidth();

    while(true)
    {
        g_bg_menu.RenderOnScreen(screen);
        g_start.RenderOnScreen(screen);
        g_exit.RenderOnScreen(screen);

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                {
                    x_mouse=m_event.motion.x;
                    y_mouse=m_event.motion.y;

                    CheckMouseFocus(x_mouse,y_mouse,start_rect);
                    CheckMouseFocus(x_mouse,y_mouse,exit_rect);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    x_mouse=m_event.button.x;
                    y_mouse=m_event.button.y;
                    if(CheckMouseFocus(x_mouse,y_mouse,exit_rect))
                    {
                        return 0;
                    }
                    if(CheckMouseFocus(x_mouse,y_mouse,start_rect))
                    {
                        return 1;
                    }

                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(screen);

    }

    return 0;
}

int CreateMenuReplay(SDL_Renderer* screen,BaseObject& g_bg_replay,
                     BaseObject& g_replay,
                     BaseObject& g_exit)
{
    g_replay.LoadImg("menu//replay.png",screen);

    g_replay.SetRect(600,500);
    g_exit.SetRect(600,580);


    SDL_Event m_event;
    int x_mouse=0;
    int y_mouse=0;

    SDL_Rect replay_rect;
    replay_rect.x=g_replay.GetBaseX();
    replay_rect.y=g_replay.GetBaseY();
    replay_rect.h=g_replay.GetBaseHeight();
    replay_rect.w=g_replay.GetBaseWidth();

    SDL_Rect exit_rect;
    exit_rect.x=g_exit.GetBaseX();
    exit_rect.y=g_exit.GetBaseY();
    exit_rect.h=g_exit.GetBaseHeight();
    exit_rect.w=g_exit.GetBaseWidth();

    while(true)
    {
        g_bg_replay.RenderOnScreen(screen);
        g_replay.RenderOnScreen(screen);
        g_exit.RenderOnScreen(screen);

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                {
                    x_mouse=m_event.motion.x;
                    y_mouse=m_event.motion.y;

                    CheckMouseFocus(x_mouse,y_mouse,replay_rect);
                    CheckMouseFocus(x_mouse,y_mouse,exit_rect);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    x_mouse=m_event.button.x;
                    y_mouse=m_event.button.y;
                    if(CheckMouseFocus(x_mouse,y_mouse,exit_rect))
                    {
                        return 0;
                    }
                    if(CheckMouseFocus(x_mouse,y_mouse,replay_rect))
                    {
                        return 1;
                    }

                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(screen);
    }

    return 0;
}

void CreatePause(SDL_Renderer* screen,BaseObject& g_pause,ImpTimer& fps_time,SDL_Event event)
{
    int x_mouse=0;
    int y_mouse=0;

    SDL_Rect pause_rect;
    pause_rect.x=g_pause.GetBaseX();
    pause_rect.y=g_pause.GetBaseY();
    pause_rect.h=g_pause.GetBaseHeight();
    pause_rect.w=g_pause.GetBaseWidth();

    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            x_mouse=event.button.x;
            y_mouse=event.button.y;
            if(CheckMouseFocus(x_mouse,y_mouse,pause_rect))
            {
                fps_time.Pause();
                return;
            }
            break;
        }
            default:
                break;

    }
    SDL_RenderPresent(screen);
}

int CreateMenuContinue(SDL_Renderer* screen,
                   BaseObject& g_bg_continue,
                   BaseObject& g_start,
                   BaseObject& g_exit)
{
    g_bg_continue.LoadImg("menu//bg_menu.png",screen);
    g_start.LoadImg("menu//start.png",screen);
    g_exit.LoadImg("menu//exit.png",screen);

    g_start.SetRect(500,220);
    g_exit.SetRect(500,300);


    SDL_Event m_event;
    int x_mouse=0;
    int y_mouse=0;

    SDL_Rect start_rect;
    start_rect.x=g_start.GetBaseX();
    start_rect.y=g_start.GetBaseY();
    start_rect.h=g_start.GetBaseHeight();
    start_rect.w=g_start.GetBaseWidth();

    SDL_Rect exit_rect;
    exit_rect.x=g_exit.GetBaseX();
    exit_rect.y=g_exit.GetBaseY();
    exit_rect.h=g_exit.GetBaseHeight();
    exit_rect.w=g_exit.GetBaseWidth();

    while(true)
    {
        g_bg_continue.RenderOnScreen(screen);
        g_start.RenderOnScreen(screen);
        g_exit.RenderOnScreen(screen);

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                {
                    x_mouse=m_event.motion.x;
                    y_mouse=m_event.motion.y;

                    CheckMouseFocus(x_mouse,y_mouse,start_rect);
                    CheckMouseFocus(x_mouse,y_mouse,exit_rect);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    x_mouse=m_event.button.x;
                    y_mouse=m_event.button.y;
                    if(CheckMouseFocus(x_mouse,y_mouse,exit_rect))
                    {
                        return 0;
                    }
                    if(CheckMouseFocus(x_mouse,y_mouse,start_rect))
                    {
                        return 1;
                    }

                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(screen);

    }
    return 0;
}


