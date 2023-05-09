#include <iostream>
#include "AllFunc.h"
#include "Spine.h"
#include "game-map.h"
#include "maincharacter.h"
#include "Timer.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include <windows.h>
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"



Spine gameBackground;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_tuto = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) // ham sdl init tra ve 0 neu success va tra ve negative error neu fail
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //sdl_hint_render  de check xem texture dc tao chua, va se anh huong
    // den cai scale cua texture sau nay

    gameWindow = SDL_CreateWindow("BLUDPATH",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
    if (gameWindow == NULL)
    {
        success = false;
    }
    else
    {
        gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gameRenderer == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gameRenderer,
                                   RenderColor, RenderColor,
                                   RenderColor, RenderColor);
            int imgflag = IMG_INIT_PNG;
            if (!(IMG_Init(imgflag) && imgflag))
            {
                success = false;
            }
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_time = TTF_OpenFont("font//dlxfont.ttf", 15);
        font_menu = TTF_OpenFont("font//TheCen.ttf", 40);
        font_tuto = TTF_OpenFont("font//TheCen.ttf", 30);

        if (font_time == NULL || font_menu == NULL)
        {
            success = false;
        }

    }
    return success;
}



bool LoadBackground()
{
    bool ret1 = gameBackground.LoadImg("layers//far.png", gameRenderer);

    if(ret1 == false )
        return false;


    return true;
}


void close()
{
    gameBackground.free();

    SDL_DestroyRenderer(gameRenderer);

    gameRenderer = NULL;

    SDL_DestroyWindow(gameWindow);
    gameWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
std::vector<int> to;



std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    int rand_threats = 0;
    //threats di chuyển qua lại
    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 15; i++)
    {
        ThreatsObject* p_threat = dynamic_threats + i;
        if (p_threat != NULL)
        {
            rand_threats = rand() % 2 + 1;
            to.push_back(rand_threats);
            if (rand_threats == 1)
            {
                p_threat->LoadImg("layers//slimeleft.png", gameRenderer, 1);
            }
            else if(rand_threats == 2)
            {
                p_threat->LoadImg("layers//threat1_left.png", gameRenderer, 2);
            }
            p_threat->set_clips(rand_threats);
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - (rand() % 150 +20);
            int pos2 = p_threat->get_x_pos() + (rand() % 150 +20);
            //lay chinh vi tri cua bot roi cong them 1 luong phu hop la 60 nhu tren
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, gameRenderer);
            list_threats.push_back(p_threat);
        }
    }
    //threats bay trên trời
    ThreatsObject* flying_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = flying_threats + i;
        if (p_threat != NULL)
        {
            rand_threats = 3;
            to.push_back(rand_threats);
            p_threat->LoadImg("layers//angel_threat.png", gameRenderer, 3);
            p_threat->set_clips(rand_threats);
            p_threat->set_x_pos(700 + i*1200);
            p_threat->set_y_pos(100);
            p_threat->set_type_move(ThreatsObject::FLYING_THREAT);

            int pos1 = p_threat->get_x_pos() - (rand() % 150 +20);
            int pos2 = p_threat->get_x_pos() + (rand() % 150 +20);

            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, gameRenderer);

            list_threats.push_back(p_threat);
        }
    }


    //threats đứng yên 1 chỗ
    ThreatsObject* threats_objs = new ThreatsObject[20];


    for (int i = 0; i < 20; i++)
    {

        ThreatsObject* p_threat = threats_objs + i;
        if (p_threat != NULL)
        {
            rand_threats = 20;
            to.push_back(rand_threats);
            p_threat->LoadImg("layers//threat_level1.png", gameRenderer, 20);
            p_threat->set_clips(to[i]);
            p_threat->set_x_pos(700 + i*800);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, gameRenderer);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}



int main(int argc, char* argv[])
{
    Timer fps_timer;

    if (InitData()==false)
        return -1;

    if(LoadBackground()==false)
        return -1;


    GameMap GAME_MAP;
    GAME_MAP.loadmap("map/map01.dat");
    GAME_MAP.loadTiles(gameRenderer);


    maincharacter p_player;
    p_player.LoadImg("layers//pp_right.png", gameRenderer);
    p_player.set_clips();


    PlayerPower player_power;
    player_power.Init(gameRenderer);

    PlayerMoney player_money;
    player_money.Init(gameRenderer);
    player_money.SetPos(SCREEN_WIDTH*0.5 -300,8);

    std::vector <ThreatsObject*> threats_list = MakeThreadList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("layers//exp3.png", gameRenderer);
    if (tRet == false) return -1;
    exp_threat.set_clip();

    int num_die = 0; // chi so sinh menh


    //time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);


    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    int t = 1; // check trong vòng lặp để xem đã vào game chưa hay chỉ vào tutorial
    bool is_quit = false;
    int retMenu = Menu::ShowMenu(gameRenderer, font_menu);
    if (retMenu == 1)
    {
        is_quit = true;
    }
    else if(retMenu == 2)
    {
        while (t == 1)
        {
       int retTuto = Menu::ShowTuto(gameRenderer, font_tuto);
       if(retTuto == 0)
       {
            int retMenu1 = Menu::ShowMenu(gameRenderer, font_menu);
                if (retMenu1 == 1)
                {
                    is_quit = true;
                    t = 2;
                }
                else if(retMenu1 == 2)
                {
                    t = 1;
                }
                else t = 2; // ấn play game r thì thoát vòng lặp
       }
        }
    }


    while (!is_quit)
    {

        fps_timer.start();
        while (SDL_PollEvent(&gameEvent) != 0)
            //khi nó lôi ra 1 cái SDL_Event mà != 0
        {
            if (gameEvent.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(gameEvent, gameRenderer);
        }


        SDL_SetRenderDrawColor(gameRenderer, RenderColor,
                               RenderColor, RenderColor, RenderColor);
        SDL_RenderClear(gameRenderer);
        // clear cái renderer cũ bằng 1 màu để render frame mới

        gameBackground.Render(gameRenderer, NULL);
        GAME_MAP.Drawmap(gameRenderer);
        gMAP map_data = GAME_MAP.getMap();


        p_player.HandleBullet(gameRenderer);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.DoPlayer(map_data);
        p_player.Show(gameRenderer);

        GAME_MAP.SetMap(map_data);
        GAME_MAP.Drawmap(gameRenderer);

        //draw geometric
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 48);
        ColorData color_data(255, 255, 255);
        Geometric::RenderRectangle(rectangle_size, color_data, gameRenderer);


        GeometricFormat outLineSize(0, 0, SCREEN_WIDTH, 46);
        ColorData color_data2(24, 24, 41);
        Geometric::RenderOutline(outLineSize, color_data2, gameRenderer);




        player_power.Show(gameRenderer); // hinh anh tinh~
        player_money.Show(gameRenderer);

        for (int i = 0; i < threats_list.size(); i++)
        {

            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL && p_threat->die == 0)
            {
                p_threat->SetMapXY(map_data.start_x, map_data.start_y);

                p_threat->ImpMoveType(gameRenderer, to[i]);
                p_threat->DoPlayer(map_data);

                p_threat->MakeBullet(gameRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(gameRenderer, to[i]);

                // show tat ca cac doi tuong threat, xong kiem tra ban trung luon tai day
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); ++jj)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if(pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::
                            CheckCollision(pt_bullet->GetRect(), rect_player);
                        if(bCol1)
                        {
                            if(num_die > 3)
                            {
                            p_threat->RemoveBullet(jj);
                            break;
                            }
                        }
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if (bCol1 || bCol2 || p_player.die != 0)
                {

                    if (p_player.die != 0)
                    {
                        num_die += p_player.die;
                        p_player.die = 0;
                    }
                    else num_die++;
                    if(num_die < 3)
                    {
                        p_player.SetRect(0,0);
                        p_player.set_comeback_time(60);

                        SDL_Delay(1000);

                        player_power.Decrease();
                        player_power.Render(gameRenderer);
                        continue;
                    }
                    else
                    {
                      /* if (MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_threat->free();
                            close();
                            SDL_Quit();
                            return 0;
                        }*/
                        int retRestart = Menu::ShowRestart(gameRenderer, font_menu);
                        if (retRestart == 0)
                        {
                            is_quit = true;
                        }

                    }


                }
            }
        }


        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height= exp_threat.get_frame_height();


        std::vector <BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); ++r)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int  t= 0; t < threats_list.size(); ++t)
                {

                    ThreatsObject* obj_threat = threats_list.at(t);

                    if(obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();
                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if(bCol)
                        {
                            obj_threat->threats_health++;
                        }
                        if (bCol && obj_threat->die == 0)
                        {

                            for (int ex = 0; ex < 18; ex++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                                // để cho vụ nổ ở ngay tâm súng

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(gameRenderer);
                            }
                            p_player.RemoveBullet(r);
                            if(obj_threat->threats_health == 3 &&
                               obj_threat->get_type_move()== ThreatsObject::MOVE_IN_SPACE_THREAT)
                            {


                            mark_value++;
                           // p_player.RemoveBullet(r);
                            obj_threat->die = 1;
                            }
                            else if(obj_threat->threats_health == 8 &&
                               obj_threat->get_type_move()== ThreatsObject::STATIC_THREAT)
                            {


                            mark_value++;

                            obj_threat->die = 1;
                            }
                            else if(obj_threat->threats_health == 5 &&
                               obj_threat->get_type_move()== ThreatsObject::FLYING_THREAT)
                            {


                            mark_value++;

                            obj_threat->die = 1;
                            }

                            //obj_threat->free();
                            //threats_list.erase(threats_list.begin()+t);

                        }
                    }
                }
            }
        }


        // show game time

        std::string str_time = "TIME: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;

        if (val_time <= 0)
        {
            if (MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, gameRenderer);
             time_game.SetRect(SCREEN_WIDTH - 200 , 15);
            time_game.RenderText(gameRenderer);
        }


        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("MARK: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, gameRenderer);
        mark_game.SetRect(SCREEN_WIDTH*0.5-50 , 15);
        mark_game.RenderText(gameRenderer);

        int money_count = p_player.GetMoneyCount();
        std::string money_str = std::to_string(money_count);

        money_game.SetText(money_str);
        money_game.LoadFromRenderText(font_time, gameRenderer);
        money_game.SetRect(SCREEN_WIDTH*0.5-250 , 15);
        money_game.RenderText(gameRenderer);



        SDL_RenderPresent(gameRenderer);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //mili giay

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0) //delay_time ma cang cao thi ctrinh cang cham
            {


            SDL_Delay(delay_time);
            }
        }


    }


    //giai phong bo nho rac cua cac con bot khi thoat ctrinh
    for (int i = 0;i < threats_list.size();i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if(p_threat)
        {
            p_threat->free();
            p_threat = NULL;
        }
    }

    threats_list.clear();
    close();

    return 0;

}


