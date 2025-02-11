#include "PongGame.h"
#include "Paddle.h"

Paddle::Paddle()
{
    rect_color = ILI9341::ToColor(31, 31, 31);
}

void Paddle::Draw(const PongGame &pong)
{
    pong.GetScreen().DrawRect(posx, posy, rect_color, posx2, posy2);
}

void Paddle::Update(const PongGame &pong, PADDLE_DIRECTION direction)
{
    switch (direction)
    {
        case PADDLE_DIRECTION::NONE:
            break;
        case PADDLE_DIRECTION::DOWN:
            MoveDown(pong);
            break;
        case PADDLE_DIRECTION::UP:
            MoveUp(pong);
            break;
    }
}

void Paddle::ResetPosition()
{
    posx = ILI9341::display_width / 2 - 15;
    posx2 = ILI9341::display_width / 2 + 15; // 20 height
}

void Paddle::MoveUp(const PongGame& pong)
{    
    ILI9341& screen = pong.GetScreen();

    screen.DrawRect(posx2 - speed + 1, posy, 0, posx2 + 1, posy2);
    screen.DrawRect(posx - 1, posy, rect_color, posx - speed, posy2);
    posx -= speed;
    posx2 -= speed;
}

void Paddle::MoveDown(const PongGame& pong)
{
    ILI9341& screen = pong.GetScreen();

    screen.DrawRect(posx - 1, posy, 0, posx + speed - 1, posy2);
    screen.DrawRect(posx2 + 1, posy, rect_color, posx2 + speed, posy2);
    posx += speed;
    posx2 += speed;
}
    
