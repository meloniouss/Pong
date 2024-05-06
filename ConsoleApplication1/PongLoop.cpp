#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include <iostream>

//these are the collisions for the left and right paddles respectively with the ball

int main()
{

    //these are the paddle-ball collisions
    bool collision1 = false;
    bool collision2 = false;

    //these are the lose-condition collisions
    bool collisionBallWallLeft = false;
    bool collisionBallWallRight = false;

    InitWindow(1280, 800, "PONG 2024");
    int width = 1280;
    int length = 800;
    SetTargetFPS(165);

    //bouncy ball
    Ball ball(4, 4, 20);
    ball.x = width / 2;
    ball.y = length / 2;
   
    //left paddle
    Paddle pad1(120, 28, 4);
    pad1.x = 10;
    pad1.y = length / 2;

    //right paddle
    Paddle pad2(120, 28, 4);
    pad2.x = width-35;
    pad2.y = length / 2;

    Score leftScore(width / 4, length / 4);
    Score rightScore(width - width / 4, length / 4);
    
    //main game loop
    while (!WindowShouldClose())
    {   
       
        //update first, we to draw the updated version obviously.
        ball.Update();
        pad1.UpdateLeft();
        pad2.UpdateRight();
        //here we are checking collisions
        collision1 = CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.r, Rectangle{pad1.x, pad1.y, pad1.height+1, pad1.width+1});
        collision2 = CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.r, Rectangle{ pad2.x, pad2.y, pad2.height, pad2.width});
        
        //here every frame if the collision is true it will invert the x-axis speed of the ball
        if (collision1)
        {
            ball.speed_x *= -1;
        }
        if (collision2)
        {
            ball.speed_x *= -1;
        }

        if (ball.x + ball.r >= GetScreenWidth())
        {
            leftScore.value++;
            leftScore.Draw();
            ball.x = width / 2;
            ball.y = length / 2;
            ball.speed_x *= -1;
            ball.speed_y *= -1;
        };

        if (ball.x - ball.r <= 0)
        {
            rightScore.value++;
            rightScore.Draw();
            ball.x = width / 2;
            ball.y = length / 2;
            ball.speed_x *= -1;
            ball.speed_y *= -1;
        }
        // drawing all the shapes
        BeginDrawing();
        ClearBackground(BLACK);
        rightScore.Draw();
        leftScore.Draw();
        ball.Draw();
        pad1.Draw();
        pad2.Draw();
        DrawLine(width / 2, 0, width / 2, length, WHITE); // Middle line
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
    