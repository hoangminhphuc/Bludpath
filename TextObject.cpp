#include "TextObject.h"


TextObject::TextObject()
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

TextObject::~TextObject()
{
    //dtor
}


bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
//nhan text vào và convert sang texture
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
    if (text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
        rect.w = text_surface->w;
         rect.h = text_surface->h;

        SDL_FreeSurface(text_surface);
    }


    return texture_ != NULL;
}


void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}


void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;

}


void TextObject::SetColor(int type)
{
   if (type == RED_TEXT)
   {
       SDL_Color color = {255, 0, 0};
       text_color_ = color;

   }
   else if (type == WHITE_TEXT)
   {
       SDL_Color color = {255, 255, 255};
       text_color_ = color;
   }
   else if (type == BLACK_TEXT)
   {
       SDL_Color color = {0, 0, 0};
       text_color_ = color;
   }
}


void TextObject::RenderText(SDL_Renderer* screen,/* int xp,
                             int yp, */SDL_Rect* clip ,
                         double angle , SDL_Point* center ,
                         SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {rect.x, rect.y , rect.w , rect.h};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;

    }

    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);

}


Spine gMenu;


int Menu::ShowMenu(SDL_Renderer* des, TTF_Font* font) {
    if (gMenu.LoadImg("layers//17350.png", des) == 0) {
        return 1;
    }

    const int MenuItemNum = 3;
    SDL_Rect posArr[MenuItemNum];
    posArr[0].x = SCREEN_WIDTH*0.5 - 120;
    posArr[0].y = SCREEN_HEIGHT*0.5;

    posArr[1].x = SCREEN_WIDTH*0.5 - 75 - 60;
    posArr[1].y = SCREEN_HEIGHT*0.5 + 60;

    posArr[2].x = SCREEN_WIDTH*0.5 - 50;
    posArr[2].y = SCREEN_HEIGHT*0.5 + 120;

    TextObject textMenu[MenuItemNum];
    textMenu[0].SetText("Play Game");
    textMenu[0].SetColor(TextObject::WHITE_TEXT);
    textMenu[0].SetRect(posArr[0].x, posArr[0].y);

    textMenu[2].SetText("How to play");
    textMenu[2].SetColor(TextObject::WHITE_TEXT);
    textMenu[2].SetRect(posArr[1].x, posArr[1].y);

    textMenu[1].SetText("Exit");
    textMenu[1].SetColor(TextObject::WHITE_TEXT);
    textMenu[1].SetRect(posArr[2].x, posArr[2].y);

    bool selected[MenuItemNum] = {0, 0, 0};
    int xm = 0;
    int ym = 0;
    SDL_Event mEvent;
    while (true) {
        gMenu.Render(des);
        for (int i = 0; i < MenuItemNum; i++) {
            textMenu[i].LoadFromRenderText(font, des);
            textMenu[i].RenderText(des);
            // textMenu[i].CreateGameText(font, des);
        }

        while (SDL_PollEvent(&mEvent)) {
            switch (mEvent.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                xm = mEvent.motion.x;
                ym = mEvent.motion.y;

                for (int i = 0; i < MenuItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        if (selected[i] == false) {
                            selected[i] = true;
                            textMenu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = false;
                            textMenu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                xm = mEvent.button.x;
                ym = mEvent.button.y;
                for (int i = 0; i < MenuItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        return i; // nếu i =1 thì trong hàm main is_quit = true để thoát ctrinh
                        //còn i != 1 thì hàm main tiếp tục chạy và bỏ qua menu để render cái khác
                    }
                }

            case SDL_KEYDOWN:
                if (mEvent.key.keysym.sym == SDLK_ESCAPE) {
                    return 1;
                }

            default:
                break;
            }

        }
        SDL_RenderPresent(des);
    }

    return 1;
}

Spine gRestart;
int Menu::ShowRestart(SDL_Renderer* des, TTF_Font* font) {
    if (gRestart.LoadImg("layers//17350.png", des) == 0) {
        return 1;
    }

    const int RestartItemNum = 1;
    SDL_Rect posArr[RestartItemNum];

    posArr[0].x = SCREEN_WIDTH*0.5 - 40;
    posArr[0].y = SCREEN_HEIGHT*0.5 + 20;




    TextObject textMenu[RestartItemNum];
    textMenu[0].SetText("EXIT");
    textMenu[0].SetColor(TextObject::WHITE_TEXT);
    textMenu[0].SetRect(posArr[0].x, posArr[0].y);




    bool selected[RestartItemNum] = {0};
    int xm = 0;
    int ym = 0;
    SDL_Event mEvent;
    while (true) {
        gRestart.Render(des);
        for (int i = 0; i < RestartItemNum; i++) {
            textMenu[i].LoadFromRenderText(font, des);
            textMenu[i].RenderText(des);
            // textMenu[i].CreateGameText(font, des);
        }

        while (SDL_PollEvent(&mEvent)) {
            switch (mEvent.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                xm = mEvent.motion.x;
                ym = mEvent.motion.y;

                for (int i = 0; i < RestartItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        if (selected[i] == false) {
                            selected[i] = true;
                            textMenu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = false;
                            textMenu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                xm = mEvent.button.x;
                ym = mEvent.button.y;
                for (int i = 0; i < RestartItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        return i;
                    }
                }

            case SDL_KEYDOWN:
                if (mEvent.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }

            default:
                break;
            }

        }
        SDL_RenderPresent(des);
    }

    return 1;
}

Spine tutorial;

int Menu::ShowTuto(SDL_Renderer* des, TTF_Font* font)
{
     if (tutorial.LoadImg("layers//tuto.jpg", des) == 0)
     {
        return 1;
     }

    const int RestartItemNum = 1;
    SDL_Rect posArr[RestartItemNum];


    posArr[0].x = 10;
    posArr[0].y = 10;

    TextObject textMenu[RestartItemNum];
    textMenu[0].SetText("BACK");
    textMenu[0].SetColor(TextObject::WHITE_TEXT);
    textMenu[0].SetRect(posArr[0].x, posArr[0].y);

    const int line = 4;
     SDL_Rect posguide[line];
     posguide[0].x = 40;
     posguide[0].y = 150;

     posguide[1].x = 40;
     posguide[1].y = 250;

     posguide[2].x = 40;
     posguide[2].y = 350;

     posguide[3].x = 40;
     posguide[3].y = 400;

     TextObject guide[line];
     guide[0].SetText("Press UP, LEFT, RIGHT to move");
     guide[0].SetColor(TextObject::WHITE_TEXT);
     guide[0].SetRect(posguide[0].x, posguide[0].y);

     guide[1].SetText("Press A or F to shoot");
     guide[1].SetColor(TextObject::WHITE_TEXT);
     guide[1].SetRect(posguide[1].x, posguide[1].y);

     guide[2].SetText("Beware!!!");
     guide[2].SetColor(TextObject::WHITE_TEXT);
     guide[2].SetRect(posguide[2].x, posguide[2].y);

     guide[3].SetText("Threats have multiple health and you only have 3. Be cafeful!");
     guide[3].SetColor(TextObject::WHITE_TEXT);
     guide[3].SetRect(posguide[3].x, posguide[3].y);



     bool selected[RestartItemNum] = {0};
    int xm = 0;
    int ym = 0;
    SDL_Event mEvent;
    while (true) {
        tutorial.Render(des);
        for (int i = 0; i < RestartItemNum; i++) {
            textMenu[i].LoadFromRenderText(font, des);
            textMenu[i].RenderText(des);
            // textMenu[i].CreateGameText(font, des);
        }
        for (int i = 0; i < line; i++) {
            guide[i].LoadFromRenderText(font, des);
            guide[i].RenderText(des);
        }
        while (SDL_PollEvent(&mEvent)) {
            switch (mEvent.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                xm = mEvent.motion.x;
                ym = mEvent.motion.y;

                for (int i = 0; i < RestartItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        if (selected[i] == false) {
                            selected[i] = true;
                            textMenu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = false;
                            textMenu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                xm = mEvent.button.x;
                ym = mEvent.button.y;
                for (int i = 0; i < RestartItemNum; i++) {
                    if (SDLCommonFunc::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        return i;
                    }
                }

            default:
                break;
            }

        }

    SDL_RenderPresent(des);
    }
    return 1;
}
