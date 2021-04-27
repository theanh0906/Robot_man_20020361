#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "init.h"
#include "BaseObject.h"

#define MAX_TILE_MAP 20

//dữ liệu một ô ảnh
class TileMap:public BaseObject
{
public:
    TileMap(){;}
    ~TileMap(){;}
};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    //doc thong tin trong file
    void ReadFileMap(char* name);

    //load ảnh với tile tương ứng
    void LoadImageTilesMap(SDL_Renderer* screen);

    //vẽ ảnh lên màn hình
    void DrawMap(SDL_Renderer* screen);

    Map GetMap() const {return game_map;};
    void SetMap(Map& map_data) {game_map=map_data;};

private:
    //chua thong tin ban do
    Map game_map;

    //chua doi tuong hinh anh: dat,da
    TileMap tile_map[MAX_TILE_MAP];
};


#endif // GAME_MAP_H

