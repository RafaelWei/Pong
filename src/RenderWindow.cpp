#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.h"

void RenderWindow::write(const std::string& text, int x, int y)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t, color);
    if ( !surface ) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == nullptr) std::cout << "surface is NULL" << std::endl;
    std::cout << surface << std::endl; 
    score_board.w = surface->w;
    score_board.h = surface->h;
    score_board.x = x - score_board.w;
    score_board.y = x - score_board.h;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &score_board);
    SDL_DestroyTexture(texture);
}

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    : window{nullptr}, renderer{nullptr}, color{}, score_board{}
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        std::cerr << "Window failed to init. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if (renderer == nullptr)
        std::cerr << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;

    font = TTF_OpenFont("Peepo.ttf", FONT_SIZE); 
    if (font == NULL) 
    {
        std::cerr << "Font not found\n";
    }

    color.r = color.g = color.b = 255;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex {SDL_GetWindowDisplayIndex(window)};
    
    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::render(const GameState& game_state)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    const SDL_Rect& l_paddle =  game_state.get_l_paddle();
    const SDL_Rect& r_paddle =  game_state.get_r_paddle();
    const SDL_Rect& ball     =  game_state.get_ball();
    SDL_RenderFillRect(renderer, &l_paddle);
    SDL_RenderFillRect(renderer, &r_paddle);
    SDL_RenderFillRect(renderer, &ball);

    write(game_state.get_score(), GameState::WIDTH/2 + FONT_SIZE, FONT_SIZE*2);
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}
