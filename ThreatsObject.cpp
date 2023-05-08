#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    come_back_time_ = 0;
    on_ground_ = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_THREAT;
    die = 0;
    threats_health = 0;

}

ThreatsObject::~ThreatsObject()
{
    //dtor
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen, int type_of_threats)
{
     bool ret = Spine::LoadImg(path, screen);
    if (ret == true)
    {
        if(type_of_threats == 1 || type_of_threats == 3)
        {
            width_frame_ = rect_.w/THREAT_FRAME_NUM_SLIME;
            height_frame_ = rect_.h;
        }
        else if(type_of_threats == 2)
        {
            width_frame_ = rect_.w/THREAT_FRAME_NUM_SLIME;
            height_frame_ = rect_.h;
        }
        else if (type_of_threats == 20)
        {
            width_frame_ = rect_.w/THREAT_FRAME_NUM_TITAN;
            height_frame_ = rect_.h;
        }

    }

    return ret;
}

void ThreatsObject::set_clips(int type_of_threats)
{
   if (width_frame_ > 0 && height_frame_ > 0)
   {
       if(type_of_threats == 1 || type_of_threats == 3)
       {
           for(int i = 0; i < THREAT_FRAME_NUM_SLIME; i++)
           {
                frame_clip_[i].x = width_frame_*i;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
           }
       }
       else if (type_of_threats == 2)
       {
           for(int i = 0; i < THREAT_FRAME_NUM_TITAN; i++)
           {
                frame_clip_[i].x = width_frame_*i;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
           }
       }
       else if (type_of_threats == 20)
       {

           for(int i = 0; i < THREAT_FRAME_NUM_TITAN; i++)
           {
                frame_clip_[i].x = width_frame_*i;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
           }
       }

   }
}


void ThreatsObject::Show(SDL_Renderer* des, int type_of_threats)
{
    if (come_back_time_ == 0 && die == 0)
    {
        rect_.x =x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;

        if(type_of_threats == 1 || type_of_threats == 3)
        {
            if (frame_ >= 7)
            {
                frame_ = 0;

            }

        }
        else if (type_of_threats == 20)
        {
            if (frame_ >= 7)
            {
                frame_ = 0;

            }

        }
        else if (type_of_threats == 2)
        {
            if (frame_ >= 7)
            {
                frame_ = 0;

            }

        }

        SDL_Rect* current_clip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, gText, current_clip, &renderQuad);
    }
}


void ThreatsObject::DoPlayer(gMAP& gMap)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
         y_val_ += THREAT_GRAVITY_SPEED;

         if(y_val_ >= THREAT_MAX_FALL_SPEED)
        {
            y_val_ = THREAT_MAX_FALL_SPEED;
        }

        if(input_type_.left_ == 1)
        {
            if(type_move_ != FLYING_THREAT)
            {
                x_val_ -=THREAT_SPEED;
            }
            else
            {
                x_val_ -=ANGEL_THREAT_SPEED;
            }
        }
        else if (input_type_.right_ == 1)
        {
            if(type_move_ != FLYING_THREAT)
            {
                x_val_ +=THREAT_SPEED; // khi cong mai ma gap animation_a_ thi se doi chieu, lien tuc nhu vay
            }
            else
            {
                x_val_ +=ANGEL_THREAT_SPEED;
            }
        }



        CheckToMap(gMap);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if(come_back_time_ == 0)
        {
            InitThreats();
        }
    }
}

void ThreatsObject::InitThreats()
{
    x_val_ = 0;
    y_val_ = 0;
            if(x_pos_ > 256)
            {


                x_pos_-=256; // 4tile map
                animation_a_ -=256;
                animation_b_ -=256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            come_back_time_ = 0;
            input_type_.left_ = 1;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}


void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin()+idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void ThreatsObject::CheckToMap(gMAP& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //CHECK HORIZONTAL
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE; //true thi lay ve trc
    x1 = (x_pos_ + x_val_) / TILE_SIZE; //ktra nvat dang dung o o bnhieu
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1>=0 && x2<max_map_hor && y1 >= 0 && y2 < max_map_ver)
    {
        if(x_val_ > 0) // nvat dang di chuyen ve ben phai
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];


                if((val1 != BLANK_TILE && val1 != STATE_MONEY) ||
                   (val2 != BLANK_TILE&& val2 != STATE_MONEY))// roi trung dong tien thi bo qua
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;
                }




        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];


                if((val1 != BLANK_TILE && val1 != STATE_MONEY) ||
                   (val2 != BLANK_TILE&& val2 != STATE_MONEY))
                {
                    x_pos_ = (x1+1)*TILE_SIZE;
                    x_val_ = 0;
                }



        }
    }



    //CHECK VERTICAL
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ +y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if (x1>=0 && x2<max_map_hor && y1 >= 0 && y2 < max_map_ver)
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

                if((val1 != BLANK_TILE && val1 != STATE_MONEY) ||
                   (val2 != BLANK_TILE&& val2 != STATE_MONEY))
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= (height_frame_ + 1); // day la khi nhan vat dung tren mat dat, cham o TILE MAP
                    y_val_ = 0;
                    on_ground_ = true; // gan bien cham mat dat cho on_ground de sau nay dung`

                }


        }
        else if(y_val_ < 0)
        {

            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

                 if((val1 != BLANK_TILE && val1 != STATE_MONEY) ||
                   (val2 != BLANK_TILE&& val2 != STATE_MONEY))
                    {
                    y_pos_ = (y1+1)*TILE_SIZE;
                    y_val_ = 0;
                    }


        }
    }

    x_pos_ +=x_val_;
    if(type_move_ != FLYING_THREAT)
    {
        y_pos_ +=y_val_;
    }
    //không va chạm thì cứ đi bình thường

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x) //vi tri cua nvat + chieu rong nvat > max chieu rong
    {
        x_pos_ = map_data.max_x - width_frame_ - 1;
    }

    if(y_pos_ > map_data.max_y)
    {
        come_back_time_ = 60;
    }
}




void ThreatsObject::ImpMoveType(SDL_Renderer* screen, int type_of_threat)
{
    if (type_move_ == STATIC_THREAT)
    {

    }
    else if(type_move_ == MOVE_IN_SPACE_THREAT)
    {
        if(on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                if(type_of_threat == 1)
                {
                    LoadImg("layers//slimeleft.png", screen, 1);
                }
                else if (type_of_threat == 2)
                {
                    LoadImg("layers//threat1_left.png", screen, 2);
                }
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                if(type_of_threat == 1)
                {


                LoadImg("layers//slimeright.png", screen, 1);
                }
                else if (type_of_threat == 2)
                {
                    LoadImg("layers//threat1_right.png", screen, 2);
                }
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                if(type_of_threat == 1)
                {
                    LoadImg("layers//slimeleft.png", screen, 1);
                }
                else if (type_of_threat == 2)
                {
                    LoadImg("layers//threat1_left.png", screen, 2);
                }
            }
        }
    }
    else if (type_move_ == FLYING_THREAT)
    {
        if (x_pos_ > animation_b_)
        {
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            if(type_of_threat == 3)
            {
                LoadImg("layers//angel_threat.png", screen, 3);
            }

        }
        else if (x_pos_ < animation_a_)
        {
            input_type_.left_ = 0;
            input_type_.right_ = 1;
            if(type_of_threat == 3)
            {
                LoadImg("layers//angel_threat.png", screen, 3);
            }

        }

        else
        {
            if (input_type_.left_ == 1)
            {
                if(type_of_threat == 3)
                {
                    LoadImg("layers//angel_threat.png", screen, 3);
                }

            }
        }
    }
}



void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {

        if(type_move_ ==STATIC_THREAT)
        {
             p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
            bool ret = p_bullet->LoadImgBullet(screen);
            if (ret)
            {
                p_bullet->set_is_move(true);
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet->SetRect(rect_.x +5, rect_.y + 10);
                p_bullet->set_x_val(15); //tốc độ bắn
                bullet_list_.push_back(p_bullet);
            }
        }
        else if(type_move_ == FLYING_THREAT)
        {
            p_bullet->set_bullet_type(BulletObject::LIGHTNING_BULLET);
            bool ret = p_bullet->LoadImgBullet(screen);
            if (ret)
            {
                p_bullet->set_is_move(true);
                p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
                p_bullet->SetRect(rect_.x - 100, rect_.y + SCREEN_HEIGHT);
                p_bullet->set_y_val(15);
                bullet_list_.push_back(p_bullet);
            }
        }


    }
}


void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i<bullet_list_.size();i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {

                int bullet_distance_x = rect_.x + width_frame_ - p_bullet->GetRect().x;
                if(type_move_ == STATIC_THREAT)
                {
                    if (bullet_distance_x < 300 && bullet_distance_x > 0)
                    {
                        p_bullet->HandleMove(x_limit, y_limit);
                        p_bullet->Render(screen);
                    }
                    else
                    {
                        p_bullet->set_is_move(false); // qua 300 se dung lai kh ban nua
                    }
                }
                else if (type_move_ == FLYING_THREAT )
                {
                    if (1)
                    {
                        p_bullet->HandleMove(x_limit, y_limit);
                        p_bullet->Render(screen);
                    }
                    else
                    {
                        p_bullet->set_is_move(false);
                    }
                }
            }
            else
            {
                p_bullet->set_is_move(true);
                if(type_move_ == STATIC_THREAT)
                {
                    p_bullet->SetRect(rect_.x +5, rect_.y + 10);
                }
                else if (type_move_ == FLYING_THREAT)
                {
                    p_bullet->SetRect(rect_.x + 50 , rect_.y + 50);
                }

            }
        }
    }
}



