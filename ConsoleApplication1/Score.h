#pragma once
#pragma once
#include "raylib.h"
class Score {
public:

    int position_x;
    int position_y;
    int value = 0;
    Score(int x, int y)
        :
        position_x(x),
        position_y(y)
        {
        }
    void Draw()
    {
        DrawText(TextFormat("%i", value), position_x, position_y, 36, WHITE);
    }
};