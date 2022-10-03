#include <string>
#include "raylib.h"
#include "raymath.h"
#include "world.hpp"

void World::moveWorldPosition(Vector2 nextWorldPositionUpdate) {
    worldPosition = Vector2Add(worldPosition, nextWorldPositionUpdate);
    cropPosition = Vector2Subtract(cropPosition, nextWorldPositionUpdate);
};

void World::move(std::string direction) {
    Vector2 nextWorldPositionUpdate{};

    if (direction == "TOP") nextWorldPositionUpdate = { x: 0.0f, y: -1.0f };
    if (direction == "TOPRIGHT") nextWorldPositionUpdate = { x: 1.0f, y: -1.0f };
    if (direction == "RIGHT") nextWorldPositionUpdate = { x: 1.0f, y: 0.0f };
    if (direction == "BOTTOMRIGHT") nextWorldPositionUpdate = { x: 1.0f, y: 1.0f };
    if (direction == "BOTTOM") nextWorldPositionUpdate = { x: 0.0f, y: 1.0f };
    if (direction == "BOTTOMLEFT") nextWorldPositionUpdate = { x: -1.0f, y: 1.0f };
    if (direction == "LEFT") nextWorldPositionUpdate = { x: -1.0f, y: 0.0f };
    if (direction == "TOPLEFT") nextWorldPositionUpdate = { x: -1.0f, y: -1.0f };

    moveWorldPosition(Vector2Scale(
        Vector2Normalize(nextWorldPositionUpdate),
        speed
    ));
};

Vector2* World::getWorldPosition() {
    return &worldPosition;
}

void World::draw() {
    DrawTextureEx(texture, cropPosition, 0.0f, WORLD_SCALE, WHITE);
};

Texture2D* World::getTexture() {
    return &texture;
}

void World::unloadTexture() {
    UnloadTexture(texture);
};
