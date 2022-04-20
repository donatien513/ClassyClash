#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "game-config.h"

std::string getDirection(int* windowWidth, int* windowHeight, int* mapWidth, int* mapHeight, Vector2* worldPosition) {
    std::string direction = "";
    if (IsKeyDown(KEY_UP) && ((float)(*worldPosition).y) >= 0.0f) direction += "TOP";
    if (IsKeyDown(KEY_DOWN) && ((float)*windowHeight + ((float)(*worldPosition).y)) <= ((float)*mapHeight * WORLD_SCALE)) direction += "BOTTOM";
    if (IsKeyDown(KEY_LEFT) && ((float)(*worldPosition).x >= 0.0f)) direction += "LEFT";
    if (IsKeyDown(KEY_RIGHT) && ((float)*windowWidth + ((float)(*worldPosition).x)) <= ((float)*mapWidth * WORLD_SCALE)) direction += "RIGHT";
    return direction;
};