#ifndef PLAYERPOWER_H
#define PLAYERPOWER_H


#include "AllFunc.h"
#include "Spine.h"

class PlayerPower : public Spine
{
    public:
        PlayerPower();
        ~PlayerPower();

        void SetNum(const int& num) {number_ = num;}
        void AddPos(const int& xPos);
        void Show(SDL_Renderer* screen);
        void Init(SDL_Renderer* screen);

        void InitCrease();
        void Decrease();

    private:
        int number_;
        std::vector <int> pos_list_; //3 sinh menh thi 3 vi tri

};

class PlayerMoney : public Spine
{
public:
    PlayerMoney();
    ~PlayerMoney();


    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos_ = x, y_pos_ = y;}
private:
    int x_pos_;
    int y_pos_;

};

#endif // PLAYERPOWER_H
