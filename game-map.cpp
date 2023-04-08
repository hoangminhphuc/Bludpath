#include "game-map.h"
#include <iostream>



void GameMap::loadmap(char* nam)
{
    FILE* fp = NULL;
    fopen_s(&fp, nam, "rb");//truyền con trỏ, tên dường dẫn file, ở chế độ read
    if (fp == NULL)
    {
        return;
    }

    game_map.max_x = 0;
    game_map.max_y = 0;
    for (int i = 0; i < max_map_ver; i++)
    {
        for (int j = 0; j < max_map_hor; j++)
        {
            fscanf(fp,"%d", &game_map.tile[i][j]); //đọc theo chiều ngang file text
            int val = game_map.tile[i][j]; // lưu vào tile của game_map để sử dụng
            if ( val > 0) // nếu giá trị của ô này khác ô trong suốt (=0 trong file text)
            {
                if ( j > game_map.max_x)
                {
                    game_map.max_x = j; // tịnh tiến theo chiều ngang
                }
                if ( i > game_map.max_y)
                {
                    game_map.max_y = i; // tịnh tiến theo chiều dọc
                }
            }
        }
    }

    game_map.max_x = (game_map.max_x +1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE; // chuyển từ số ô sang tọa độ

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = nam;
    fclose(fp);

}

void GameMap::loadTiles(SDL_Renderer* screen)
{
    char file_img[30]; // có bao nhiêu kí tự trong đường dẫn file
    FILE* fp = NULL;

    for (int i = 0; i < TILEMAX; i++) // TILEMAX là số kiểu ô tối đa
    {
        sprintf_s(file_img, "map/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if ( fp == NULL)
        {
            continue;
        }

        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen);
         //load cái ảnh có số như lưu trong file map vào cái mảng để sau dùng
    }
}

void GameMap::Drawmap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    // tọa độ ảnh


    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/TILE_SIZE;
    map_y = game_map.start_y/TILE_SIZE;
    // tọa độ số bao nhiêu
    x1 = (game_map.start_x%TILE_SIZE)*(-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (game_map.start_y%TILE_SIZE)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i =y1; i < y2; i+=TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE;
        for (int j = x1; j < x2; j+=TILE_SIZE)
        {
            int val = game_map.tile[map_y][map_x];
            if (val > 0)//nếu ô đấy kh phải ô trong suốt
            {
                tile_mat[val].SetRect(j, i);
                //set vị trí của ô tileset
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }


}
