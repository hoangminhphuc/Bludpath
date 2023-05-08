#ifndef THREATSOBJECT_H
#define THREATSOBJECT_H

#include <vector>
#include "AllFunc.h"
#include "Spine.h"
#include "BulletObject.h"

#define THREAT_FRAME_NUM_SLIME 7
#define THREAT_FRAME_NUM_TITAN 7
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
#define ANGEL_THREAT_SPEED 1
//1 = slime
//2 = bat
//3 = flying eye
//20 = titan
class ThreatsObject : public Spine
{
    public:
        ThreatsObject();
        ~ThreatsObject();

        enum TypeMove
        {
            STATIC_THREAT = 0,
            MOVE_IN_SPACE_THREAT = 1,
            FLYING_THREAT = 2,
        };



        void set_x_val(const int& xVal) {x_val_ = xVal;}
        void set_y_val(const int& yVal) {y_val_ = yVal;}

        void set_x_pos(const float &xp) {x_pos_ =xp;}
        void set_y_pos(const float &yp) {y_pos_ =yp;}

        float get_x_pos() const {return x_pos_;}
        float get_y_pos() const {return y_pos_;}

        void SetMapXY(const int&mp_x, const int &mp_y) {map_x_=mp_x; map_y_=mp_y;}

        void set_clips(int type_of_threats);
        bool LoadImg(std::string path, SDL_Renderer* screen, int type_of_threats);
        void Show(SDL_Renderer* des, int type_of_threats);
        int get_width_frame() const {return width_frame_;}
        int get_height_frame() const {return height_frame_;}

        void DoPlayer(gMAP& gMap);
        void CheckToMap(gMAP& gMap);
        void InitThreats();


        void set_type_move(const int& Typemove) {type_move_ = Typemove;}
        void SetAnimationPos(const int& pos_a, const int& pos_b)
        {animation_a_ = pos_a; animation_b_ = pos_b;}

        void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;};
        // de khi den gioi han thi set ipleft = 0 de cho con bot di ve huong left
        void ImpMoveType(SDL_Renderer* screen, int type_of_threat);

        std::vector <BulletObject*> get_bullet_list() const {return bullet_list_;}
        void set_bullet_list(std::vector <BulletObject*>& bl_list) {bullet_list_=bl_list;}
        SDL_Rect GetRectFrame();

        void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
        void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
        void RemoveBullet(const int& idx);
        int die;
        int threats_health;
        int get_type_move() const {return type_move_;}
    private:
        int map_x_;
        int map_y_;
        float x_val_;
        float y_val_;
        float x_pos_;
        float y_pos_; // vi tri cua con quai
        bool on_ground_;
        int come_back_time_;
        SDL_Rect frame_clip_[THREAT_FRAME_NUM_SLIME];
        //SDL_Rect frame_clip_t[THREAT_FRAME_NUM_TITAN];
        int frame_;
        int width_frame_;
        int height_frame_;

        int type_move_;
        int animation_a_; //gioi han phai de con bot di chuyen qua lai
        int animation_b_; //gioi han trai
        Input input_type_;


        std::vector <BulletObject*> bullet_list_;
};

#endif // THREATSOBJECT_H
