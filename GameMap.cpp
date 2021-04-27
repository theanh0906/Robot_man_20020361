#include "GameMap.h"

void GameMap::ReadFileMap(char* name)
{
    FILE* fp=NULL;
    fopen_s(&fp,name,"rb");

    if(fp==NULL)
        return ;

    game_map.max_map_x=0;
    game_map.max_map_y=0;

    for(int i=0;i<MAX_MAP_Y;i++)
    {
        for(int j=0;j<MAX_MAP_X;j++)
        {
            fscanf(fp,"%d",&game_map.tile[i][j]);
            int val=game_map.tile[i][j];
            if(val>0)
            {
                if(j>game_map.max_map_x)
                    game_map.max_map_x=j;
                if(i>game_map.max_map_y)
                    game_map.max_map_y=i;
            }
        }
    }

    //sau khi load xong ,o vi tri toi da
    game_map.max_map_x=(game_map.max_map_x+1)*TILE_MAP_SIZE;
    game_map.max_map_y=(game_map.max_map_y+1)*TILE_MAP_SIZE;

    game_map.start_x=0;
    game_map.start_y=0;

    game_map.file=name;
    fclose(fp);
}

void GameMap::LoadImageTilesMap(SDL_Renderer* screen)
{
    char file_img[22];
    FILE* file_names=NULL;
    for(int i=0;i<MAX_TILE_MAP;i++)
    {
        sprintf_s(file_img,"map//%d.png",i);

        fopen_s(&file_names,file_img,"rb");

        if(file_names==NULL)
        {
            continue;
        }
        fclose(file_names);

        tile_map[i].LoadImg(file_img,screen);
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    //vị trí của ảnh
    int map_x=0;
    int map_y=0;

    map_x=game_map.start_x/TILE_MAP_SIZE;

    // % vị trí load bắt đầu từ phần dư
    x1=(game_map.start_x % TILE_MAP_SIZE)*-1;
    x2=x1+screen_width+(x1==0?0:TILE_MAP_SIZE);


    map_y=game_map.start_y/TILE_MAP_SIZE;

    y1=(game_map.start_y%TILE_MAP_SIZE)*-1;
    y2=y1+screen_height+(y1==0?0:TILE_MAP_SIZE);


    for(int i=y1;i<y2;i+=TILE_MAP_SIZE)
    {
        map_x=game_map.start_x/TILE_MAP_SIZE;
        for(int j=x1;j<x2;j+=TILE_MAP_SIZE)
        {
            int val=game_map.tile[map_y][map_x];
            if(val>0)
            {
                tile_map[val].SetRect(j,i);
                tile_map[val].RenderOnScreen(screen);
            }
            map_x++;
        }
        map_y++;
    }
}

