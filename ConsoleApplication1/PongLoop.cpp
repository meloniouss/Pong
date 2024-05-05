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
        if (x + r >= GetScreenWidth() || x - r <= 0)
        {
            //add collision here
            //we will probably need to add losing conditions, a lose message, etc.
            speed_x *= -1; // direction of x velocity flips when >= the screen width
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
        else if (IsKeyDown(KEY_S))
        {
            ClearBackground(BLACK);
            y += speed_y;
        }
    };
    void UpdateRight()
    {
        if (IsKeyDown(KEY_UP))
        {
            ClearBackground(BLACK);
            y -= speed_y;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            ClearBackground(BLACK);
            y += speed_y;
        }
    }
};


// TODO: ADD WALL COLLISION FOR THE PADDLES, I.E. YOU CAN'T GO ABOVE OR BELOW THE WINDOW'S RESOLUTION
Ball ball;
Paddle pad1;
Paddle pad2;

bool collision1;
bool collision2;

int main()
{
    collision1 = false;
    collision2 = false;
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

    //main game loop
    while (!WindowShouldClose())
    {   
        //update first, we to draw the updated version obviously.
        ball.Update();
        pad1.UpdateLeft();
        pad2.UpdateRight();

        //here we are checking collisions
        collision1 = CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.r, Rectangle{pad1.x, pad1.y, pad1.height, pad1.width});
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
        

        // drawing all the shapes n shit
        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        pad1.Draw();
        pad2.Draw();
        DrawLine(width / 2, 0, width / 2, length, WHITE); // Middle line
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
    