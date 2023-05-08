#ifndef EXPLOSIONOBJECT_H
#define EXPLOSIONOBJECT_H

#include "Spine.h"
#include "AllFunc.h"

#define NUM_FRAME_EXP_h 6
#define NUM_FRAME_EXP_v 3

class ExplosionObject : public Spine
{
    public:
        ExplosionObject();
        ~ExplosionObject();

        void set_clip();
        void set_frame(const int& fr) {frame_ = fr;}
        virtual bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* screen);
        int get_frame_width() const {return frame_width_;}
        int get_frame_height() const {return frame_height_;}


    private:
        int frame_width_;
        int frame_height_;

        unsigned int frame_;
        SDL_Rect frame_clip_[NUM_FRAME_EXP_h*NUM_FRAME_EXP_v];
};

#endif // EXPLOSIONOBJECT_H
