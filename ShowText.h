#ifndef SHOW_TEXT_H_
#define SHOW_TEXT_H_

#include "init.h"
#include "TextObject.h"
#include "PlayerCoin.h"
#include "PlayerHealth.h"
#include "PlayerObject.h"
#include "Menu.h"
#include "GameMap.h"

void ShowAllText(SDL_Renderer* screen,
                 TTF_Font* font,
                 const Map& map_data,
                 PlayerObject& player_character,
                 bool& quit,double& time_run,
                 int& player_mark,
                 TextObject& time_game_text,
                 TextObject& coin_game_text,
                 TextObject& mark_game_text,
                 TextObject& mana_player_text,
                 TextObject& hp_player_text,
                 TextObject& name_boss_text,
                 BaseObject& g_bg_replay,
                 BaseObject& g_replay,
                 BaseObject& g_exit,
                 bool& out_game);




#endif // SHOW_TEXT_H_
