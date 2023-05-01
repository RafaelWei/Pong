#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include<GameState.h>
#include <Constants.h>

GameState::GameState()
    :running{true}, 
    turn{false},
    l_s{0},
    r_s{0},
    velX{},
    velY{},
    score{""}
{
    l_paddle.x = 32; 
    l_paddle.h=HEIGHT/4;
    l_paddle.y = (HEIGHT/2)-(l_paddle.h/2);
    l_paddle.w = 12;

    r_paddle = l_paddle;
    r_paddle.x = WIDTH - r_paddle.w -32;

    ball.x = ball.y = 0;
    ball.w = ball.h = SIZE;

    score = std::to_string(l_s) + " " + std::to_string(r_s);
}

const SDL_Rect& GameState::get_l_paddle() const
{
    return l_paddle;
}

const SDL_Rect& GameState::get_r_paddle() const
{
    return r_paddle;
}
    
const SDL_Rect& GameState::get_ball() const
{
    return ball;
}

const std::string& GameState::get_score() const
{
    return score;
}

bool GameState::isRunning()
{
    return running;
}

void GameState::stopRunning()
{
    running = false;
}

void GameState::input()
{
    SDL_Event e;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT) running = false;
    }
    if (keystates[SDL_SCANCODE_ESCAPE]) 
    {
        running = false;
    }
    if (keystates[SDL_SCANCODE_UP]) 
    {
        l_paddle.y -= SPEED;
    }
    if (keystates[SDL_SCANCODE_DOWN]) 
    {
        l_paddle.y += SPEED;
    }
}

void GameState::serve()
{
    r_paddle.y = l_paddle.y = (HEIGHT/2)-(l_paddle.h/2);
    if (turn)
    {
        ball.x = l_paddle.x + (l_paddle.w*4);
        velX = BALL_SPEED / 2;
    }
    else
    {
        ball.x = r_paddle.x - (r_paddle.w*4);    
        velX = -BALL_SPEED / 2;
    }
    ball.y = HEIGHT/2 - (SIZE/2);
    velY = 0;

    turn = !turn;
}

void GameState::update()
{
    input();

    // Limit the paddles to the edges of the screen
    if (l_paddle.y < 0) l_paddle.y=0;
    if (l_paddle.y + l_paddle.h > HEIGHT) l_paddle.y = HEIGHT-l_paddle.h;
    if (r_paddle.y < 0) r_paddle.y=0;
    if (r_paddle.y + r_paddle.h > HEIGHT) r_paddle.y = HEIGHT-r_paddle.h;

    // update the ball speed and location
    if (SDL_HasIntersection(&ball, &r_paddle))
    {
        double rel = (r_paddle.y + (r_paddle.h/2)) - (ball.y+(SIZE/2));
        double norm = rel/(r_paddle.h/2);
        double bounce = norm*(5*PI/12);
        velX = -BALL_SPEED*cos(bounce);
        velY = BALL_SPEED*(-sin(bounce));
    }
    if (SDL_HasIntersection(&ball, &l_paddle))
    {
        double rel = (l_paddle.y + (l_paddle.h/2)) - (ball.y+(SIZE/2));
        double norm = rel/(l_paddle.h/2);
        double bounce = norm*(5*PI/12);
        velX = BALL_SPEED*cos(bounce);
        velY = BALL_SPEED*(-sin(bounce));
    }

    if (ball.y > r_paddle.y + (r_paddle.h/2))
    {
        r_paddle.y += SPEED;
    }
    if (ball.y < r_paddle.y + (r_paddle.h/2))
    {
        r_paddle.y -= SPEED;
    }

    if (ball.x <= 0)
    {
        r_s++;
        serve();
    }
    if (ball.x + SIZE >= WIDTH)
    {
        l_s++;
        serve();
    }

    if (ball.y <= 0 || ball.y + SIZE >= HEIGHT) velY = -velY;

    ball.x += velX;
    ball.y += velY;

    score = std::to_string(l_s) + " " + std::to_string(r_s);
}

GameState operator*(const GameState& game_state, double d)
{
    GameState g {game_state};
    g.l_paddle.y *= d;
    g.r_paddle.y *= d;
    g.ball.x *= d;
    g.ball.y *= d;

    return g;
}

GameState operator*(double d, const GameState& game_state)
{
    return game_state * d;
}

GameState operator+(const GameState& game_state1, const GameState& game_state2)
{
    GameState g {game_state1};
    g.l_paddle.y += game_state2.l_paddle.y;
    g.r_paddle.y += game_state2.r_paddle.y;
    g.ball.x += game_state2.ball.x;
    g.ball.y += game_state2.ball.y;

    return g;
}
