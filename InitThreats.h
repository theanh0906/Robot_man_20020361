#ifndef INIT_TWO_H_
#define INIT_TWO_H_

#include "init.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "BossObject.h"


vector<ThreatObject*> MakeListThreat(SDL_Renderer* screen);

void ClearListThreat(vector<ThreatObject*>&list_threat);

void CreateBoss(SDL_Renderer* screen,BossObject& boss);

#endif // INIT_TWO_H_

