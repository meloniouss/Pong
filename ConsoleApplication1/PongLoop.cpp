#include <iostream> 
#include <raylib.h>

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int r;
    void Draw()
    {
        DrawCircle(x, y, r, WHITE);
    };

    void Update()
    {
        ClearBackground(BLACK);
        x += speed_x;
        y += speed_y;
        if (y + r >= GetScreenHeight() || y - r <= 0)
        {
            speed_y *= -1;  // direction of y velocity flips when >= the screen height
        };
    };
};
class Paddle {
public:
    float x, y;
    int speed_y;
    float width;
    float height;
    void Draw()
    {
        DrawRectangle(x, y, height, width, WHITE);
    };
    void UpdateLeft()
    {
        if (IsKeyDown(KEY_W))
        {
            ClearBackground(BLACK);
            y -= speed_y;
        }
        if (IsKeyDown(KEY_S))
        {
            ClearBackground(BLACK);
            y += speed_y;
        }
        if (y <= 0)
        {
            y = 0;
        }
        if (y + width>= GetScreenHeight())
        {
            y = GetScreenHeight() - width;
        }
    };
    void UpdateRight()
    {
        if (IsKeyDown(KEY_UP))
        {
            ClearBackground(BLACK);
            y -= speed_y;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            ClearBackground(BLACK);
            y += speed_y;
        }
        if (y <= 0)
        {
            y = 0;
        }
        if (y + width>= GetScreenHeight())
        {
            y = GetScreenHeight() - width;
        }
    }
};
class Score {
public:
    
    int position_x;
    int position_y;
    int value = 0;
    void Draw()
    {
        DrawText(TextFormat("%i",value), position_x, position_y, 36, WHITE);
    }
};

// TODO: ADD WALL COLLISION FOR THE PADDLES, I.E. YOU CAN'T GO ABOVE OR BELOW THE WINDOW'S RESOLUTION
Ball ball;
Paddle pad1;
Paddle pad2;

Score leftScore;
Score rightScore;

//these are the collisions for the left and right paddles respectively with the ball
bool collision1;
bool collision2;
//collision ball wall is the lose-condition essentially
bool collisionBallWallLeft;
bool collisionBallWallRight;
int main()
{

    //these are the paddle-ball collisions
    collision1 = false;
    collision2 = false;

    //these are the lose-condition collisions
    collisionBallWallLeft = false;
    collisionBallWallRight = false;

    const int width = 1280;
    const int length = 800;
    InitWindow(width, length, "PONG 2024");
    SetTargetFPS(165);

    //bouncy ball
    ball.x = width / 2;
    ball.y = length / 2;
    ball.r = 20;
    ball.speed_x = 4;
    ball.speed_y = 4;
    //left paddle
    pad1.x = 10;
    pad1.y = length / 2;
    pad1.speed_y = 4;
    pad1.width = 120;
    pad1.height = 28;
    //right paddle
    pad2.x = width-35;
    pad2.y = length / 2;
    pad2.speed_y = 4;
    pad2.width = 120;
    pad2.height = 28;

    leftScore.position_x = width / 4;
    leftScore.position_y = length / 4;
    
    rightScore.position_x = width - width / 4;
    rightScore.position_y = length / 4;
    
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
        // drawing all the shapes n shit
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
    