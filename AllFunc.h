#ifndef ALLFUNC_H_
#define ALLFUNC_H_

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "TextObject.h"


static SDL_Window* gameWindow = NULL;
static SDL_Renderer* gameRenderer = NULL;
static SDL_Event gameEvent;
static SDL_Renderer* g_img_menu = NULL;





//screen
const int FRAME_PER_SECOND = 40;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int colorkeyR = 167;
const int colorkeyG = 175;
const int colorkeyB = 180;


const int RenderColor = 0Xff;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define max_map_hor 401
#define max_map_ver 10

#define STATE_MONEY 4

typedef struct Input //xu li input di chuyen nvat
{
    int left_, right_, up_, down_, jump_;

};


typedef struct gMAP
{
    int start_x, start_y, max_x, max_y;
    //start là tọa độ, max là số ô, max=start/tile_size;


    int tile[max_map_ver][max_map_hor];
    char* file_name;

};


namespace SDLCommonFunc
{

    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Surface* des, TTF_Font* font);
}


#endif
