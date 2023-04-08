#ifndef SPINE_H_
#define SPINE_H_

#include <../AllFunc.h>
class Spine{
    public:
        Spine();
        ~Spine();
        void SetRect(const int& x, const int& y){
            rect_.x = x;
            rect_.y = y;
        }
        SDL_Rect GetRect(){
            return rect_;
        }
        SDL_Texture* GetText(){
            return gText;
        }

        virtual bool LoadImg(std::string path, SDL_Renderer* screen);
        void Render(SDL_Renderer* x, SDL_Rect* clip = NULL);
        void free();

    protected:
        SDL_Texture* gText;
        SDL_Rect rect_; //



};

#endif
