#ifndef INIT_H_
#define INIT_H_

#include<windows.h>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include<cmath>
#include<math.h>
#include<cstdlib>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<time.h>


#define FPS 20
#define TILE_MAP_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define COIN 4
#define TIME_PLAY 200.0


using namespace std;


//screen
const int screen_width=1280;
const int screen_height=640;

//color
const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;

const int COLOR_DRAW=0xFF;


//doi tuong du lieu cua mot o

struct Map
{
  //vi tri bat dau cua map hien thi len man hinh
  int start_x;
  int start_y;

  // vị trí tối đa của bản đồ
  int max_map_x;
  int max_map_y;

  //mang luu tru du lieu map
  int tile[MAX_MAP_Y][MAX_MAP_X];

  char* file;
};

//trạng thái di chuyển của nhân vật
struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};



#endif // INIT_H_


