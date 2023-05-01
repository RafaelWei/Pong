#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.h"
#include "Utils.h"

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "Failed at SDL_Init(). Error: " << SDL_GetError() << std::endl;

    if (TTF_Init() < 0)
        std::cerr << "Failed at TTF_Init(). Error: " << TTF_GetError() << std::endl;

    RenderWindow window {"Pong", 720, 720};
    GameState game_state {};
    GameState previous_state {};

    std::cout << window.getRefreshRate() << std::endl;
    const double dt = 1.0 / 60;
    double accumulator = 0.0;
    double currentTime= utils::hireTimeInSeconds();


    while (game_state.isRunning())
    {

        int startTick = SDL_GetTicks();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            previous_state = game_state;
            game_state.update();
            accumulator -= dt;
            // t+=dt // Do we actually need the total time?
        }

        // We need to make the linear regression for a better interpolation
        const double alpha = accumulator / dt;
        window.render((game_state * alpha) + (previous_state * (1-alpha)));

        int frameTicks = SDL_GetTicks() - startTick;
        if (frameTicks < 1000 / window.getRefreshRate())
        {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
