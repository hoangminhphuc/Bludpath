
//#include "CommonFunc.h"
#include "BaseObject.h"
#include <iostream>
#include "game_map.h"
#include "MainObject.h"
BaseObject g_background ;

using namespace std;

bool InitData ()
{
    bool success = true;
    int ret = SDL_Init (SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //tao cua so
    g_window = SDL_CreateWindow ("Game cua Shiba Inu " , SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED ,
                                                        SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer (g_window , -1 , SDL_RENDERER_ACCELERATED);
        if ( g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor (g_screen , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR ,
                                    RENDER_DRAW_COLOR , RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}

bool LoadBackground ()
{
    bool ret = g_background.LoadImg ("layers//far.png" , g_screen);
    if (ret == false)
        return false;

    return true;

}

void close ()
{
    g_background.Free();

    SDL_DestroyRenderer (g_screen);
    g_screen = NULL;

    SDL_DestroyWindow (g_window);
    g_window = NULL;

    IMG_Quit ();
    SDL_Quit ();
}

int main(int argc, char* argv[])
{
    if (InitData() == false)
        return -1;

    if (LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat"); //truyen file luu trang thai cua 1 o
    game_map.LoadTiles (g_screen);



    MainObject p_player;
    p_player.LoadImg ("layers//pp.png" , g_screen);
    p_player.set_clips();


    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent (&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event , g_screen );
        }
        SDL_SetRenderDrawColor (g_screen , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR ,
                                    RENDER_DRAW_COLOR , RENDER_DRAW_COLOR);
        SDL_RenderClear (g_screen);

        g_background.Render(g_screen , NULL); //render background
        game_map.DrawMap (g_screen); // ve cac o
        Map map_data = game_map.getMap();

        p_player.DoPlayer(map_data);
        p_player.Show (g_screen);

        SDL_RenderPresent (g_screen);
    }

    close();
    return 0;
}
