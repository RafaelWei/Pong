#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <GameState.h>

class RenderWindow
{
private:
    static constexpr int FONT_SIZE {32};

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect score_board;

    void write(const std::string& text, int x, int y);
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    int getRefreshRate();
    void render(const GameState& game);
    void cleanUp();
};
