#include "InitThreats.h"

vector<ThreatObject*> MakeListThreat(SDL_Renderer* screen)
{
    vector<ThreatObject*>list_threat;

    ThreatObject* move_threat=new ThreatObject[10];
    for(int i=0;i<10;i++)
    {
        ThreatObject* m_threat=(move_threat+i);
        if(m_threat!=NULL)
        {
            m_threat->SetTypeMove(ThreatObject::MOVE);

            m_threat->LoadImg("threat//threat_left.png",screen);

            m_threat->SetClips();
            m_threat->Set_x_pos(2000+i*1500);
            m_threat->Set_y_pos(500);
            m_threat->SetInputLeft(1);


            int pos_a=m_threat->Get_x_pos()-100;
            int pos_b=m_threat->Get_x_pos()+100;

            m_threat->SetSpaceMove(pos_a,pos_b);
            BulletObject* m_bullet=new BulletObject();
            m_threat->InitBullet(m_bullet,screen);

            list_threat.push_back(m_threat);
        }
    }

    ThreatObject* fly_threat=new ThreatObject[10];
    for(int i=0;i<10;i++)
    {
        ThreatObject* m_threat=(fly_threat+i);
        if(m_threat!=NULL)
        {
            m_threat->SetOnGround(true);
            m_threat->SetTypeMove(ThreatObject::FLY);

            m_threat->LoadImg("threat//threat_fly_left.png",screen);

            m_threat->SetClips();
            m_threat->Set_x_pos(4000+i*1200);
            m_threat->Set_y_pos(100);

            m_threat->SetInputLeft(1);


            int pos_a=m_threat->Get_x_pos()-100;
            int pos_b=m_threat->Get_x_pos()+100;

            m_threat->SetSpaceMove(pos_a,pos_b);
            BulletObject* m_bullet=new BulletObject();
            m_threat->InitBullet(m_bullet,screen);
            list_threat.push_back(m_threat);
        }
    }

    ThreatObject* static_threats=new ThreatObject[10];
    for(int i=0;i<10;i++)
    {
        ThreatObject* m_threat=(static_threats+i);//thay doi toi dia chi
        if(m_threat!=NULL)
        {
            m_threat->SetTypeMove(ThreatObject::STATIC);
            m_threat->LoadImg("threat//threat_level.png",screen);
            m_threat->SetClips();
            m_threat->Set_x_pos(900+i*1470);
            m_threat->Set_y_pos(250);
            m_threat->SetInputLeft(0);

            BulletObject* m_bullet=new BulletObject();
            m_threat->InitBullet(m_bullet,screen);

            list_threat.push_back(m_threat);
        }
    }
    return list_threat;
}

void ClearListThreat(vector<ThreatObject*>&list_threat)
{
    for(int i=0;i<list_threat.size();i++)
    {
        ThreatObject* one_threat=list_threat.at(i);
        if(one_threat)
        {
            one_threat->frees();
            one_threat=NULL;
        }
    }
    list_threat.clear();
}

void CreateBoss(SDL_Renderer* screen,BossObject& boss)
{
    boss.Set_x_pos(25600-500);
    boss.Set_y_pos(screen_height-600);

    BulletObject* boss_bullet_1=new BulletObject();
    BulletObject* boss_bullet_2=new BulletObject();
    BulletObject* boss_bullet_3=new BulletObject();

    boss.InitBullet1(boss_bullet_1,screen,boss.GetBaseX()+30,boss.GetBaseY()+10);
    boss.InitBullet2(boss_bullet_2,screen,boss.GetBaseX()+60,boss.GetBaseY()+60);
    boss.InitBullet3(boss_bullet_3,screen,boss.GetBaseX()+90,boss.GetBaseY()+90);

    return;
}
