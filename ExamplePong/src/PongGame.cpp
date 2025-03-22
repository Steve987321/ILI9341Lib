#include "PongGame.h"

PongGame::PongGame()
{
    text_col = ILI9341::ToColor(31, 31, 31);
}

void PongGame::Init()
{
    screen.Init();
    ts.begin();

    // background
    screen.DrawRect(0, 0, game_bg_col, ILI9341::display_width, ILI9341::display_height);

    // starting scores 
    UpdateScore();

    paddleright.posy = 30;
    paddleright.posy2 = 32;

    // draw paddles 
    paddleleft.Draw(*this);
    paddleright.Draw(*this);
}

void PongGame::UpdateScore()
{
    // int to string
    char left_score_buffer[3];
    char right_score_buffer[3];

    itoa(paddleleft.score, left_score_buffer, 10);
    itoa(paddleright.score, right_score_buffer, 10);
    
    screen.SetRotation(ILI9341::ROTATION_FLAGS::YMIRRORED);

    // clear first 
    screen.DrawRect(ILI9341::display_width - 15, 100, game_bg_col, ILI9341::display_width - 5, 240);  

    // draw score 
    screen.DrawString(100, 6, left_score_buffer, strlen(left_score_buffer), text_col, 1.2f); 
    screen.DrawString(220, 6, right_score_buffer, strlen(right_score_buffer), text_col, 1.2f); 
    
    screen.ResetRotation();
}

void PongGame::CheckCollision()
{
    if (ball.posy2 >= paddleleft.posy && ball.posy <= paddleleft.posy)
    {
        uint8_t check_x = (uint8_t)ball.posx + 2; // middle of ball

        // check for hit 
        if (ball.posx < paddleleft.posx2 && ball.posx2 > paddleleft.posx)
        {
            if (check_x > (paddleleft.posx + paddleleft.posx2) / 2)
            {
                // down (hit lower part of paddle)
                ball.velocity.x = ball_speed;
            }
            else
            {
                // up (hit upper part of paddle)
                ball.velocity.x = -ball_speed;
            }
            ball_speed += 0.1f;
            ball.velocity.y = -1;
        }
    }
    else if (ball.posy <= paddleright.posy2 && ball.posy2 <= paddleleft.posy2)
    {
        uint8_t check_x = (uint8_t)ball.posx + 2; // middle of ball

        // check for hit 
        if (ball.posx < paddleright.posx2 && ball.posx2 > paddleright.posx)
        {
            if (check_x > (paddleright.posx + paddleright.posx2) / 2)
            {
                // down 
                ball.velocity.x = ball_speed;
            }
            else
            {
                // up 
                ball.velocity.x = -ball_speed;
            }

            ball_speed += 0.1f;
            ball.velocity.y = 1;
        }
    }

}

void PongGame::Reset()
{
    ball_speed = 1;

    screen.DrawRect(0, 0, game_bg_col, ILI9341::display_width, ILI9341::display_height);
    
    ball.ResetPosition();
    paddleleft.ResetPosition();
    paddleright.ResetPosition();

    UpdateScore();

    // draw paddles 
    paddleleft.Draw(*this);
    paddleright.Draw(*this);

    delay(500);
}

void PongGame::Update()
{
    auto player_direction = Paddle::PADDLE_DIRECTION::NONE;

    if (ts.touched())
    {
        if (ts.getPoint().y > 2000)
            player_direction = Paddle::PADDLE_DIRECTION::DOWN;
        else
            player_direction = Paddle::PADDLE_DIRECTION::UP;
    }

    paddleleft.Update(*this, player_direction);

    if (paddleright.posx > ball.posx)
        paddleright.Update(*this, Paddle::PADDLE_DIRECTION::UP);
    else 
        paddleright.Update(*this, Paddle::PADDLE_DIRECTION::DOWN);

    ball.Update(*this);

    // solve ball collision and cause a bounce back
    CheckCollision();

    if (ball.hit_side)
    {
        if (ball.posy <= 5)
            paddleright.score++;
        else
            paddleleft.score++;

        Reset();

        ball.hit_side = false;
    }
}

ILI9341 &PongGame::GetScreen()
{
    return screen;
}

ILI9341::COLOR16 PongGame::GetBGColor() const
{
    return game_bg_col;
}
