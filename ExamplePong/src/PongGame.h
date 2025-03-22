#ifndef PONGGAME_H
#define PONGGAME_H

// Controls 
#include "display/ILI9341.h"
#include "touch/XPT2046_Touchscreen.h"

// Pong  
#include "Ball.h"
#include "Paddle.h"

/// @brief 
/// Handles a game of pong against a simple bot. 
///
/// The 'bot' follows the ball position, it doesn't do any predictions.
class PongGame
{
public:
    PongGame();

public:
    /// @brief 
    /// Initializes display touchscreen and sets up the game for pong.
    void Init();  

    /// @brief
    /// Pong main loop.
    void Update();

public: 
    ILI9341& GetScreen();
    ILI9341::COLOR16 GetBGColor() const;

private:
    /// @brief 
    /// (Re)Draws the score of the paddles.
    void UpdateScore();

    /// @brief 
    /// Checks for collision and solves it.
    void CheckCollision();

    /// @brief 
    /// Prepares for anohter round of pong, doesn't reset scores.
    void Reset();

private:
    ILI9341 screen{10, 9, 8};
    XPT2046_Touchscreen ts{7};

    ILI9341::COLOR16 game_bg_col = 0;
    ILI9341::COLOR16 text_col = 0;

    Paddle paddleleft; // bottom 
    Paddle paddleright; // top
    
    Ball ball; 

    // ball speed that increases per bounce
    float ball_speed = 1.f;
};
#endif