#ifndef MENU_H_
#define MENU_H_
#include "init.h"
#include "BaseObject.h"
#include "InitWindow.h"
#include "ImpTimer.h"


int CreateMenuGame(SDL_Renderer* screen,BaseObject& g_bg_menu,
                   BaseObject& g_start,
                   BaseObject& g_exit);

int CreateMenuReplay(SDL_Renderer* screen,BaseObject& g_bg_replay,
                     BaseObject& g_replay,
                     BaseObject& g_exit);

bool CheckMouseFocus(const int& x,const int& y,const SDL_Rect& rect);

void CreatePause(SDL_Renderer* screen,BaseObject& g_pause,ImpTimer& fps_time,SDL_Event event);

int CreateMenuContinue(SDL_Renderer* screen,
                   BaseObject& g_bg_continue,
                   BaseObject& g_start,
                   BaseObject& g_exit);

#endif // MENU_H_
