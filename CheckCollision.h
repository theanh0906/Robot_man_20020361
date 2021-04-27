#ifndef CHECK_COLLISION_H_
#define CHECK_COLLISION_H_

#include "init.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "PlayerObject.h"
#include "PlayerHealth.h"
#include "ExplosionObject.h"
#include "BossObject.h"
#include "CheckBossHp.h"
#include "Menu.h"

bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

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
                                          bool& out_game);


void ThreatCollisionBulletPlayer(SDL_Renderer* screen,
                                 PlayerObject& player_character,
                                 vector<BulletObject*>&player_bullet_list,
                                 ExplosionObject& exp_threat_die,
                                 vector<ThreatObject*>&list_threat,
                                 int& player_mark,Mix_Chunk* ex_sound[1]);

void BossCollisionBulletPlayer(SDL_Renderer* screen,
                               PlayerObject& player_character,
                               vector<BulletObject*>&player_bullet_list,
                               ExplosionObject& exp_threat_die,
                               BossObject& boss,
                               int& player_mark,
                               int& boss_hp,BossHp& boss_health
                               ,Mix_Chunk* ex_sound[1]);


void PlayerCollisionBossAndBulletBoss(SDL_Renderer* screen,
                                      BossObject& boss,
                                      PlayerObject& player_character,
                                      int& player_lifes,
                                      PlayerHealth& player_health,
                                      bool & quit,
                                      BaseObject& g_bg_replay,
                                      BaseObject& g_replay,
                                      BaseObject& g_exit,
                                      bool& out_game);



#endif // CHECK_COLLISION_H_
