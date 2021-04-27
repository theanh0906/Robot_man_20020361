#include "CheckCollision.h"


bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
      int left_a = object1.x;
      int right_a = object1.x + object1.w;
      int top_a = object1.y;
      int bottom_a = object1.y + object1.h;

      int left_b = object2.x;
      int right_b = object2.x + object2.w;
      int top_b = object2.y;
      int bottom_b = object2.y + object2.h;


      // Case 1: size object 1 < size object 2
      if (left_a > left_b && left_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (left_a > left_b && left_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      // Case 2: size object 1 < size object 2
      if (left_b > left_a && left_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (left_b > left_a && left_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

       // Case 3: size object 1 = size object 2
      if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
      {
        return true;
      }

      return false;

}


void PlayerCollisionThreatAndBulletThreat(SDL_Renderer* screen,
                                          vector<ThreatObject*>&list_threat,
                                          PlayerObject& player_character,
                                          int& player_lifes,
                                          PlayerHealth& player_health,
                                          bool & quit,int& check_fall_player,
                                          Mix_Chunk* sound_bullet[4],
                                          BaseObject& g_bg_replay,
                                          BaseObject& g_replay,
                                          BaseObject& g_exit,
                                          bool& out_game)
{
    for(int i=0;i<list_threat.size();i++)
    {
        ThreatObject* one_threat=list_threat.at(i);

        if(one_threat!=NULL)
        {
            one_threat->MakeBullet(screen,screen_width,screen_height);

            SDL_Rect rect_frame_threat=one_threat->GetRectFrame();

            SDL_Rect rect_frame_player=player_character.GetRectFrame();

            vector<BulletObject*> threat_bullet_list=one_threat->GetBullet();

            bool collision_test_1=false;

        for(int j=0;j<threat_bullet_list.size();j++)
        {
            BulletObject* one_bullet_threat=threat_bullet_list.at(j);

            SDL_Rect rect_one_bullet_threat;
            rect_one_bullet_threat=one_bullet_threat->GetRectFrame();

            if(one_bullet_threat!=NULL)
             {
                collision_test_1=CheckCollision(rect_one_bullet_threat,rect_frame_player);

                if(collision_test_1)
                {
                    one_threat->RemoveBullet(j);
                    break; //khong xet vien dan khac nua
                }
             }
        }

            bool collision_test_2=CheckCollision(rect_frame_player,rect_frame_threat);

            bool collision_test_3=false;

           if(player_character.GetYPos()>=640.0&&check_fall_player==0)
            {
               collision_test_3=true;
               check_fall_player++;

            }
            else if(player_character.GetYPos()<640.0&&check_fall_player==1)
            {
              collision_test_3=false;
              check_fall_player=0;
            }



            //gặp lỗi collision test 1 =true khi bat dau
            if(collision_test_1||collision_test_2||collision_test_3) //gap 1 trong 2 se chet
            {

                player_lifes--;
                if(player_lifes>0)
                {
                        player_character.SetRect(0,0);
                        player_character.SetTimeComeBack(60);
                        SDL_Delay(100);

                        player_health.DecreateHealth();
                        player_health.RenderOnScreen(screen);

                        continue;
                }
                    else if(player_lifes==0)
                    {
                        quit=true;

                        if(!CreateMenuReplay(screen,g_bg_replay,g_replay,g_exit))
                            out_game=true;
                        else
                            out_game=false;
                    }
            }
        }
    }

}


void ThreatCollisionBulletPlayer(SDL_Renderer* screen,
                                 PlayerObject& player_character,
                                 vector<BulletObject*>&player_bullet_list,
                                 ExplosionObject& exp_threat_die,
                                 vector<ThreatObject*>&list_threat,
                                 int& player_mark,Mix_Chunk* ex_sound[1])
{
    for(int i=0;i<player_bullet_list.size();i++)
    {
        BulletObject* one_player_bullet=player_bullet_list.at(i);

        int frame_width_exp=exp_threat_die.GetFrameWidth();
        int frame_height_exp=exp_threat_die.GetFrameHeight();

        if(one_player_bullet!=NULL)
        {
            for(int j=0;j<list_threat.size();j++)
            {
                    ThreatObject* threat_monster=list_threat.at(j);
                    if(threat_monster!=NULL)
                    {
                        SDL_Rect threat_rect=threat_monster->GetRectFrame();

                        SDL_Rect one_player_bullet_rect;
                        one_player_bullet_rect=one_player_bullet->GetRectFrame();

                        bool collision_test=CheckCollision(one_player_bullet_rect,threat_rect);

                        if(collision_test==true)
                        {
                            player_mark+=1;

                            Mix_PlayChannel(-1,ex_sound[0],0);
                            for(int ex_number=0;ex_number<8;ex_number++)
                            {
                                int exp_x_pos=one_player_bullet->GetBaseX()-frame_width_exp*0.5;
                                int exp_y_pos=one_player_bullet->GetBaseY()-frame_height_exp*0.5;

                                exp_threat_die.SetFrameNumber(ex_number);
                                exp_threat_die.SetRect(exp_x_pos,exp_y_pos);
                                exp_threat_die.Show(screen);
                            }

                                player_character.RemoveBullet(i);
                                threat_monster->frees();
                                list_threat.erase(list_threat.begin()+j);
                        }

                    }
                }
            }
    }
}

void BossCollisionBulletPlayer(SDL_Renderer* screen,
                               PlayerObject& player_character,
                               vector<BulletObject*>&player_bullet_list,
                               ExplosionObject& exp_threat_die,
                               BossObject& boss,
                               int& player_mark,
                               int& boss_hp,BossHp& boss_health
                               ,Mix_Chunk* ex_sound[1])
{
    for(int i=0;i<player_bullet_list.size();i++)
    {
        BulletObject* one_player_bullet=player_bullet_list.at(i);

        int frame_width_exp=exp_threat_die.GetFrameWidth();
        int frame_height_exp=exp_threat_die.GetFrameHeight();

        if(one_player_bullet!=NULL)
        {

            SDL_Rect boss_rect=boss.GetRectFrame();

            SDL_Rect one_player_bullet_rect;
            one_player_bullet_rect=one_player_bullet->GetRectFrame();

            bool collision_test=CheckCollision(one_player_bullet_rect,boss_rect);

            if(collision_test==true)
            {
                Mix_PlayChannel(-1,ex_sound[0],0);
                player_mark+=10;
                boss_hp--;
                if(boss_hp<=0)
                    boss_hp=0;
                for(int ex_number=0;ex_number<8;ex_number++)
                {

                        int exp_x_pos=one_player_bullet->GetBaseX()-frame_width_exp*0.5;
                        int exp_y_pos=one_player_bullet->GetBaseY()-frame_height_exp*0.5;

                        exp_threat_die.SetFrameNumber(ex_number);
                        exp_threat_die.SetRect(exp_x_pos,exp_y_pos);
                        exp_threat_die.Show(screen);
                }

                boss_health.DecreateHp();
                boss_health.RenderOnScreen(screen);

                if(boss_hp>=7)
                {
                    boss.SetFramePresent(BossObject::High);
                }
                else if(boss_hp>=4)
                {
                    boss.SetFramePresent(BossObject::Medium);
                }
                else if(boss_hp>=1)
                {
                    boss.SetFramePresent(BossObject::Low);
                }
                else
                {
                    boss.SetFramePresent(BossObject::Die);
                }

                player_character.RemoveBullet(i);

            }
        }
    }
}

void PlayerCollisionBossAndBulletBoss(SDL_Renderer* screen,
                                      BossObject& boss,
                                      PlayerObject& player_character,
                                      int& player_lifes,
                                      PlayerHealth& player_health,
                                      bool & quit,
                                      BaseObject& g_bg_replay,
                                      BaseObject& g_replay,
                                      BaseObject& g_exit,
                                      bool& out_game)
{
        boss.MakeBullet1(screen,screen_width,screen_height,boss.GetBaseX()+30,boss.GetBaseY()+20);
        boss.MakeBullet2(screen,screen_width,screen_height,boss.GetBaseX()+60,boss.GetBaseY()+60);
        boss.MakeBullet3(screen,screen_width,screen_height,boss.GetBaseX()+90,boss.GetBaseY()+90);

        SDL_Rect rect_frame_boss=boss.GetRectFrame();

        SDL_Rect rect_frame_player=player_character.GetRectFrame();

        vector<BulletObject*> boss_bullet_list_1=boss.GetBullet1();
        vector<BulletObject*> boss_bullet_list_2=boss.GetBullet2();
        vector<BulletObject*> boss_bullet_list_3=boss.GetBullet3();

        bool collision_test_1=false;
        bool collision_test_2=false;
        bool collision_test_3=false;

        for(int j=0;j<boss_bullet_list_3.size();j++)
        {
            BulletObject* one_bullet_boss_3=boss_bullet_list_3.at(j);

            SDL_Rect rect_one_bullet_boss_3;
            rect_one_bullet_boss_3=one_bullet_boss_3->GetRectFrame();

            if(one_bullet_boss_3!=NULL)
             {
                collision_test_3=CheckCollision(rect_one_bullet_boss_3,rect_frame_player);

                if(collision_test_3)
                {
                    break; //khong xet vien dan khac nua
                }
             }
        }

        for(int j=0;j<boss_bullet_list_1.size();j++)
        {
            BulletObject* one_bullet_boss_1=boss_bullet_list_1.at(j);

            SDL_Rect rect_one_bullet_boss_1;
            rect_one_bullet_boss_1=one_bullet_boss_1->GetRectFrame();

            if(one_bullet_boss_1!=NULL)
             {
                collision_test_1=CheckCollision(rect_frame_player,rect_one_bullet_boss_1);

                if(collision_test_1)
                {
                    break; //khong xet vien dan khac nua
                }
             }
        }

        for(int j=0;j<boss_bullet_list_2.size();j++)
        {
            BulletObject* one_bullet_boss_2=boss_bullet_list_2.at(j);

            SDL_Rect rect_one_bullet_boss_2;
            rect_one_bullet_boss_2=one_bullet_boss_2->GetRectFrame();

            if(one_bullet_boss_2!=NULL)
             {
                collision_test_2=CheckCollision(rect_frame_player,rect_one_bullet_boss_2);

                if(collision_test_2)
                {
                    break; //khong xet vien dan khac nua
                }
             }
        }

            bool collision_test_4=CheckCollision(rect_frame_player,rect_frame_boss);


            if(collision_test_1||collision_test_2||collision_test_3||collision_test_4)
            {
                player_lifes--;
                if(player_lifes>0)
                {
                        player_character.SetRect(0,0);
                        player_character.SetTimeComeBack(60);
                        SDL_Delay(100);

                        player_health.DecreateHealth();
                        player_health.RenderOnScreen(screen);

                }
                else if(player_lifes==0)
                {
                    quit=true;
                    if(!CreateMenuReplay(screen,g_bg_replay,g_replay,g_exit))
                        out_game=true;
                    else
                        out_game=false;
                }
            }
            else
                return;
}

