#ifndef GAME-MAP_H
#define GAME-MAP_H


#include "Spine.h"

#define TILEMAX 20
class Tile : public Spine
{
public:
    Tile(){;}
    ~Tile(){;}
};


class GameMap
{
    public:
         GameMap(){;}
         ~GameMap(){;}

        void loadmap(char* nam); //load con số từ file text
        void loadTiles(SDL_Renderer* screen);
        //load hình ảnh của tile vào file text nhưng kh biết ở đâu
        void Drawmap(SDL_Renderer* screen);// truyền ảnh vào đúng cái số
        gMAP getMap() const {return game_map;};
        void SetMap(gMAP& map_data) {game_map = map_data;};
    private:
        gMAP game_map;//lưu giữ các ô
        Tile tile_mat[TILEMAX];// lưu 20 cái loại ảnh của map


};



#endif // GAME-MAP_H
