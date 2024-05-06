#pragma once
#include "raylib.h"
class Paddle {
public:
    float x, y;
    int speed_y;
    float width;
    float height;
    Paddle(float w, float h, int s)
        :
        width(w),
        height(h),
        speed_y(s)
    {
    }

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
        if (y + width >= GetScreenHeight())
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
        if (y + width >= GetScreenHeight())
        {
            y = GetScreenHeight() - width;
        }
    }
};