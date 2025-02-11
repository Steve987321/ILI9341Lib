#include "PongGame.h"
#include "Ball.h"

Ball::Ball()
{
    color = ILI9341::ToColor(31, 31, 31);
}

void Ball::Update(const PongGame& pong)
{
    ILI9341& screen = pong.GetScreen();

    // check if bal is hitting bounds
    if (posx <= 2 || posx2 >= ILI9341::display_width - 2)
        velocity.x *= -1;

    if (posy <= 2 || posy2 >= ILI9341::display_height - 2)
    {
        velocity.y *= -1; 

        hit_side = true;
    }

    if (velocity.x > 0) // down 
    {
        screen.DrawRect((uint8_t)(posx), (uint16_t)(posy), pong.GetBGColor(), (uint8_t)(posx + velocity.x), (uint16_t)(posy2));
        screen.DrawRect((uint8_t)(posx2), (uint16_t)(posy), color, (uint8_t)(posx2 + velocity.x), (uint16_t)(posy2));
    }
    else // up 
    {
        screen.DrawRect((uint8_t)(posx2 + velocity.x), (uint16_t)(posy), pong.GetBGColor(), (uint8_t)(posx2), (uint16_t)(posy2));
        screen.DrawRect((uint8_t)(posx + velocity.x), (uint16_t)(posy), color, (uint8_t)(posx), (uint16_t)(posy2));
    }

    posx += velocity.x;
    posx2 += velocity.x;

    if (velocity.y > 0) // left
    {
        screen.DrawRect((uint8_t)(posx), (uint16_t)(posy), pong.GetBGColor(), (uint8_t)(posx2), (uint16_t)(posy + velocity.y));
        screen.DrawRect((uint8_t)(posx), (uint16_t)(posy2), color, (uint8_t)(posx2), (uint16_t)(posy2 + velocity.y));
    }
    else // right 
    {
        screen.DrawRect((uint8_t)(posx), (uint16_t)(posy2 + velocity.y), pong.GetBGColor(), (uint8_t)(posx2), (uint16_t)(posy2));
        screen.DrawRect((uint8_t)(posx), (uint16_t)(posy + velocity.y), color, (uint8_t)(posx2), (uint16_t)(posy));
    }

    posy += velocity.y;
    posy2 += velocity.y;
}

Vec2f Ball::GetMin() const
{
    return Vec2f(posx, posy);
}

Vec2f Ball::GetMax() const
{
    return Vec2f(posx2, posy2);
}

void Ball::ResetPosition()
{
    posx = 4;
    posy = ILI9341::display_height / 2 - 2;    
    posx2 = 8;
    posy2 = ILI9341::display_height / 2 + 2;
}
