#ifndef BALL_H
#define BALL_H

#include "display/ILI9341.h"

#include "Types.h" 

class PongGame;

/// @brief 
/// 4x4 bouncing ball for pong 
class Ball
{
public:
    Ball();

public:
    friend class PongGame;

    /// @brief 
    /// Draws and updates bouncing ball.     
    /// @param screen 
    void Update(const PongGame& pong);

    /// @brief 
    /// Gets the top left position of the ball rect.
    /// @return Returns a vector2 of type float.
    Vec2f GetMin() const;

    /// @brief 
    /// Gets the bottom right position of the ball rect.
    /// @return Returns a vector2 of type float.
    Vec2f GetMax() const;

    /// @brief 
    /// Sets the ball position to starting position.
    void ResetPosition();
        
private:
    /// @brief true when we hit a left or right side behind a paddle
    bool hit_side = false;

    /// @brief starting the ball at top middle 
    float posx = 4;
    float posy = ILI9341::display_height / 2 - 2;    
    float posx2 = 8;
    float posy2 = ILI9341::display_height / 2 + 2;  

    /// @brief ball color 
    ILI9341::COLOR16 color = 0;

    /// @brief current ball velocity
    Vec2f velocity {1, 1};
};

#endif 