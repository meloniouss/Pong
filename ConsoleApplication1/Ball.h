#pragma once
#include "raylib.h"
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int r;
    Ball(int sx, int sy, int r)
        :
        speed_x(sx),
        speed_y(sy),
        r(r) {}

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