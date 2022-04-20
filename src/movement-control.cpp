#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "game-config.h"

std::string getDirection(int* windowWidth, int* windowHeight, int* mapWidth, int* mapHeight, Vector2* worldPosition) {
    std::string direction = "";
    if (IsKeyDown(KEY_UP) && static_cast<float>((*worldPosition).y) >= 0.0f) direction += "TOP";
    if (IsKeyDown(KEY_DOWN) && static_cast<float>(*windowHeight) + (static_cast<float>((*worldPosition).y)) <= (static_cast<float>(*mapHeight * WORLD_SCALE))) direction += "BOTTOM";
    if (IsKeyDown(KEY_LEFT) && static_cast<float>((*worldPosition).x) >= 0.0f) direction += "LEFT";
    if (IsKeyDown(KEY_RIGHT) && static_cast<float>(*windowWidth) + (static_cast<float>((*worldPosition).x)) <= (static_cast<float>(*mapWidth * WORLD_SCALE))) direction += "RIGHT";
    return direction;
};