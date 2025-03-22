#ifndef PADDLE_H 
#define PADDLE_H

#include "display/ILI9341.h"

class PongGame;

/// @brief 
/// Pong player movable paddle rect.
class Paddle
{
public:
    Paddle();

public:
    friend class PongGame;

    enum class PADDLE_DIRECTION : uint8_t
    {
        NONE,
        DOWN,
        UP,
    };

    /// @brief 
    /// Draws the paddle at its current position
    /// @param pong Game context instance.
    void Draw(const PongGame& pong);

    /// @brief 
    /// Draws the movement of the paddle given the direction.
    /// @param pong Game context instance.
    /// @param direction What direction the paddle should be moved to.
    void Update(const PongGame& pong, PADDLE_DIRECTION direction);

    /// @brief 
    /// Sets the paddle position to the starting position.
    void ResetPosition();

private:
    /// @brief 
    /// Moves the paddle up 
    /// @param pong Game context instance.
    void MoveUp(const PongGame& pong);

    /// @brief 
    /// Moves the paddle down
    /// @param pong Game context instance.
    void MoveDown(const PongGame& pong);

private:
    /// @brief paddle color
    ILI9341::COLOR16 rect_color; 
    uint8_t score = 0;

    const uint8_t speed = 1; 
    
    /// @brief 
    /// paddle starting coordinates 
    uint8_t posx = ILI9341::display_width / 2 - 15;
    uint8_t posx2 = ILI9341::display_width / 2 + 15; // 20 height
    uint16_t posy = ILI9341::display_height - 32;
    uint16_t posy2 = ILI9341::display_height - 30; // 2 width
};
#endif 