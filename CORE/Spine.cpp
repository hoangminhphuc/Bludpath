#include <iostream>
#include "Spine.h"

Spine::Spine()
{
    gText = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    // tất cả các chỉ số ở trên là vị trí của 1 đối tượng hình ảnh, dùng cho tất cả các đối tượng sau này

}

Spine::~Spine()
{

}


bool Spine::LoadImg(std::string path, SDL_Renderer* screen)
{
    free();
    SDL_Texture* nTexture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str()); //lấy thông số của tấm ảnh vừa load
    if(load_surface != NULL){
            SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, colorkeyR, colorkeyG, colorkeyB));
            nTexture = SDL_CreateTextureFromSurface(screen, load_surface);
            if (nTexture != NULL){
                rect_.w = load_surface -> w;
                rect_.h = load_surface -> h;
                //lưu trữ chiều cao và chiều rộng của tấm ảnh vào ông rect_
            }

            SDL_FreeSurface(load_surface);


}

                gText = nTexture;
                return gText != NULL;
}



void Spine::Render(SDL_Renderer* x, SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(x, gText, clip, &renderquad); //blit a image, copy a texture to window
}



void Spine::free()
{
    if(gText!=NULL)
    {
        SDL_DestroyTexture(gText);
        gText = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
