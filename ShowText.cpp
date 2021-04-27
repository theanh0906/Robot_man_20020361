#include "ShowText.h"


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
                 bool& out_game)
{
    //show game time
    string str_time="Time: ";
    double time_rest=TIME_PLAY-time_run; //time con lai

    if(time_rest<=0.0)
    {
        quit=true;
        if(!CreateMenuReplay(screen,g_bg_replay,g_replay,g_exit))
                out_game=true;
        else
                out_game=false;
    }
    else if(time_rest>0.0)
    {
        string str_time_rest=to_string(time_rest);
        str_time+=str_time_rest;

        time_game_text.SetTexts(str_time);
        time_game_text.LoadFont(font,screen);
        time_game_text.RenderText(screen,screen_width-200,15);
    }

    string str_mark="Mark: ";

    string to_str_mark=to_string(player_mark);
    str_mark+=to_str_mark;

    mark_game_text.SetTexts(str_mark);
    mark_game_text.LoadFont(font,screen);
    mark_game_text.RenderText(screen,screen_width-400,15);


    string to_str_coin=to_string(player_character.GetPlayerCoin());
    coin_game_text.SetTexts(to_str_coin);
    coin_game_text.LoadFont(font,screen);
    coin_game_text.RenderText(screen,screen_width-550,15);


    mana_player_text.SetTexts("Mana: ");
    mana_player_text.LoadFont(font,screen);
    mana_player_text.RenderText(screen,0,50);

    hp_player_text.SetTexts("HP:");
    hp_player_text.LoadFont(font,screen);
    hp_player_text.RenderText(screen,0,0);

    if(map_data.start_x+screen_width>=map_data.max_map_x-700)
    {
        name_boss_text.SetTexts("Boss: ");
        name_boss_text.LoadFont(font,screen);
        name_boss_text.RenderText(screen,300,100);
    }


}
