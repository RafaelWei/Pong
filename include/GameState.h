#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GameState
{
private:
    bool running;                // true while the game is running
    bool turn;                   // whose turn is it
    int l_s, r_s;                // left score and right score
    double velX, velY;           // speed of the ball
    std::string score;           // score in string format 
    SDL_Rect l_paddle, r_paddle; 
    SDL_Rect ball;               

    void input();

public:
    GameState();

    static constexpr int WIDTH {720};
    static constexpr int HEIGHT {720};
    static constexpr int BALL_SPEED {16};
    static constexpr int SPEED {9};
    static constexpr int SIZE {16};
    static constexpr double PI {3.14159265358979323846}; 

    const SDL_Rect& get_l_paddle() const;
    const SDL_Rect& get_r_paddle() const;
    const SDL_Rect& get_ball() const;
    const std::string& get_score() const;

    bool isRunning();
    void stopRunning();
    void serve();
    void update();

    friend GameState operator*(double d, const GameState& game_state);
    friend GameState operator*(const GameState& game_state, double d);
    friend GameState operator+(const GameState& game_state1, const GameState& game_state2);
};
