#include "init.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "InitThreats.h"
#include "BossObject.h"
#include "CheckCollision.h"
#include "ImpTimer.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerHealth.h"
#include "PlayerCoin.h"
#include "ShowText.h"
#include "draw.h"
#include "Menu.h"
#include "CheckBossHp.h"

SDL_Window* g_window=NULL;
SDL_Renderer* g_screen=NULL;

TTF_Font* g_font=NULL;

Mix_Chunk* g_sound_bullet[4];
Mix_Chunk* g_sound_exp[1];
Mix_Chunk* g_sound_boss[1];
Mix_Chunk* g_sound_player_skill[1];

bool CreatesWindow()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"sdl_init error "<<SDL_GetError()<<endl;
        success=false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout<<"SDL error "<<endl;
		}

        g_window=SDL_CreateWindow("Robot Man",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
                                ,screen_width,screen_height,SDL_WINDOW_SHOWN);
        if(g_window==NULL)
        {
            cout<<"create window error "<<SDL_GetError()<<endl;
            success=false;
        }
        else
        {
            g_screen=SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
            if(g_screen==NULL)
            {
                cout<<"create renderer error "<<SDL_GetError();
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(g_screen,0xFF,0xFF,0xFF,0xFF);
                int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout<<"create renderer error 2 "<<IMG_GetError();
					success = false;
				}

                if(TTF_Init()==-1)
                {
                    success=false;
                }

                g_font=TTF_OpenFont("font_text//dlxfont_.ttf",15);

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError();
                    success = false;
                }

                g_sound_bullet[0]=Mix_LoadWAV("music//player_bullet.wav");
                g_sound_bullet[1]=Mix_LoadWAV("music//Laser.wav");
                g_sound_bullet[2]=Mix_LoadWAV("music//static.wav");
                g_sound_bullet[3]=Mix_LoadWAV("music//fly.wav");

                g_sound_exp[0]=Mix_LoadWAV("music//ex.wav");
                g_sound_boss[0]=Mix_LoadWAV("music//Bomb1.wav");
                g_sound_player_skill[0]=Mix_LoadWAV("music//explosion.wav");

            }
        }
    }
    return success;
}

void Close()
{
    SDL_DestroyRenderer(g_screen);
    SDL_DestroyWindow(g_window);
    g_screen=NULL;
    g_window=NULL;

    IMG_Quit();
    SDL_Quit();
}


int main(int argc,char* argv[])
{
    BaseObject background;
    BaseObject bg_menu;
    BaseObject bg_replay;
    BaseObject bg_continue;
    BaseObject start;
    BaseObject exit;
    BaseObject pause;
    BaseObject replay;
    BaseObject win_game;

    SDL_Event event;

    if(CreatesWindow()&&background.LoadImg("map//bg.png",g_screen))
    {
        bool out_game=false;
        while(!out_game)
        {
            ImpTimer time_game;
            double time_run=0.0;

            //MAP
            GameMap game_map;
            game_map.ReadFileMap("map//map01.dat");
            game_map.LoadImageTilesMap(g_screen);


            //PLAYER
            PlayerObject player_character;
            player_character.LoadImg("player_animation//player_right.png",g_screen);
            player_character.SetClips();

            int player_lifes=PLAYER_LIFE;
            int player_mark=0;
            int check_fall_player=0;  // check player ngã
            int mana_player=0;

            //show health and coin of player
            PlayerHealth player_health;
            player_health.LoadImgHealth(g_screen);

            PlayerCoin player_coin;
            player_coin.LoadImgCoin(g_screen);
            player_coin.SetRect(screen_width-580,10);


            //THREATS
            vector<ThreatObject*>list_threat=MakeListThreat(g_screen);  //lay het va load tung threat mot

            ExplosionObject exp_threat_die;
            bool check_exp=exp_threat_die.LoadImg("map//explosion.png",g_screen);
            exp_threat_die.SetClips();

            //BOSS
            BossObject boss;
            int boss_hp=BOSS_HEALTH;

            BossHp boss_health;
            boss_health.LoadImgHp(g_screen);

            CreateBoss(g_screen,boss);

            //text
            TextObject time_game_text;
            time_game_text.SetColorText(TextObject::TEXT_YELLOW);

            TextObject mark_game_text;
            mark_game_text.SetColorText(TextObject::TEXT_YELLOW);

            TextObject coin_game_text;
            coin_game_text.SetColorText(TextObject::TEXT_YELLOW);

            TextObject mana_player_text;
            mana_player_text.SetColorText(TextObject::TEXT_RED);

            TextObject hp_player_text;
            hp_player_text.SetColorText(TextObject::TEXT_RED);

            TextObject name_boss_text;
            name_boss_text.SetColorText(TextObject::TEXT_RED);


            pause.LoadImg("menu//pause.png",g_screen);
            pause.SetRect(300,0);

            win_game.LoadImg("menu//win_page.png",g_screen);

            bg_replay.LoadImg("menu//bg_replay.png",g_screen);

            bool quit_loop_main=false;

            int menu_chose_number=CreateMenuGame(g_screen,bg_menu,start,exit);

            if(menu_chose_number==0)
            {
                quit_loop_main=true;
                out_game=true;
            }


            //loop main
            while(!quit_loop_main)
            {
                time_game.Start();

                while(SDL_PollEvent(&event)!=0)
                {
                    if(event.type==SDL_QUIT)
                    {
                        quit_loop_main=true;
                        out_game=true;
                    }
                    player_character.HandelInputAction(event,g_screen,g_sound_bullet,g_sound_player_skill);
                    CreatePause(g_screen,pause,time_game,event);
                }


                SDL_SetRenderDrawColor(g_screen,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(g_screen);
                background.RenderOnScreen(g_screen,NULL);

                Map map_data=game_map.GetMap();

                if(time_game.Is_paused())
                {
                    int continue_number=CreateMenuContinue(g_screen,bg_continue,start,exit);
                    if(continue_number==0)
                    {
                        quit_loop_main=true;
                        out_game=true;
                    }
                    else if(continue_number==1)
                    {
                        time_game.Unpause();
                    }
                }

                else if(!time_game.Is_paused())
                {

                    if(boss_hp<=0)
                    {

                        int win_chose_number=CreateMenuReplay(g_screen,win_game,replay,exit);
                        if(win_chose_number==0)
                        {
                            quit_loop_main=true;
                            out_game=true;
                        }
                        else if(win_chose_number==1)
                        {
                            quit_loop_main=true;
                            out_game=false;
                        }
                    }

                    pause.RenderOnScreen(g_screen);

                    player_character.SetMapStartXY(map_data.start_x,map_data.start_y);
                    player_character.DoPlayer(map_data);
                    player_character.Show(g_screen);
                    player_character.HandleBullet(g_screen);

                    if(mana_player<500)
                        mana_player++;
                    if(mana_player==500&&player_character.GetNumberPlayerSkill()==0)
                    {
                        mana_player=0;
                    }

                    //draw mana
                    Rectangles mana_player_rect(50,50,mana_player/2.0,20.0);
                    ColorRectangle mana_player_color(0,0,255);

                    DrawRectangle(mana_player_rect,mana_player_color,g_screen);

                    player_character.SetNumberMana(mana_player);

                    game_map.SetMap(map_data);
                    game_map.DrawMap(g_screen);

                    player_health.Show(g_screen);
                    player_coin.Show(g_screen);

                    if(map_data.start_x+screen_width>=map_data.max_map_x-700)
                    {
                        boss_health.Show(g_screen);
                    }

                    for(int i=0;i<list_threat.size();i++)
                    {
                        ThreatObject* one_threat=list_threat.at(i);

                        if(one_threat!=NULL)
                        {
                            one_threat->SetMapStartXY(map_data.start_x,map_data.start_y);
                            one_threat->LoadImpMoveType(g_screen);
                            one_threat->DoThreat(map_data);

                            one_threat->Show(g_screen);
                        }
                    }

                    boss.SetMapStartXY(map_data.start_x,map_data.start_y);
                    boss.DoBoss(map_data);
                    boss.Show(g_screen);


                    vector<BulletObject*>player_bullet_list=player_character.GetBulletList();

                    if(time_run>=1.0)
                    {
                        PlayerCollisionThreatAndBulletThreat(g_screen,list_threat,player_character,player_lifes,
                                                             player_health,quit_loop_main,check_fall_player,g_sound_bullet,bg_replay,replay,exit,out_game);
                        ThreatCollisionBulletPlayer(g_screen,player_character,player_bullet_list,exp_threat_die,list_threat,player_mark,g_sound_exp);
                        if(boss_hp>0)
                        {
                            BossCollisionBulletPlayer(g_screen,player_character,player_bullet_list,exp_threat_die,boss,player_mark,boss_hp,boss_health,g_sound_exp);
                        }
                        PlayerCollisionBossAndBulletBoss(g_screen,boss,player_character,player_lifes,player_health,quit_loop_main,bg_replay,replay,exit,out_game);
                    }


                    boss.LoadImgPresent(g_screen);


                    ShowAllText(g_screen,g_font,map_data,player_character,quit_loop_main,time_run,player_mark,time_game_text,
                                coin_game_text,mark_game_text,mana_player_text,hp_player_text,name_boss_text,bg_replay,replay,exit,out_game);


                    SDL_RenderPresent(g_screen);

                    int real_time_run=time_game.GetTick();

                    int time_one_frame=1000/FPS; //thoi gian mot hinh anh chay /*ms*/
                    if(real_time_run<time_one_frame)
                    {
                        int delay_time=time_one_frame-real_time_run;
                        SDL_Delay(delay_time);
                    }

                    time_run+=(double)time_game.GetTick()/1000;
                }
            }
                 ClearListThreat(list_threat);
        }
    }
    Close();
    return 0;
}

