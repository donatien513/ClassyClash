#include <string>
#include "world.hpp"

void World::moveWorldCropPosition(Vector2 nextCropUpdate) {
    cropPosition = Vector2Subtract(cropPosition,
        Vector2Scale(
            Vector2Normalize(nextCropUpdate),
            speed
        )
    );
};

void World::move(std::string direction) {
    Vector2 nextCropUpdate{};

    if (direction == "TOP") nextCropUpdate = { x: 0.0f, y: -1.0f };
    if (direction == "TOPRIGHT") nextCropUpdate = { x: 1.0f, y: -1.0f };
    if (direction == "RIGHT") nextCropUpdate = { x: 1.0f, y: 0.0f };
    if (direction == "BOTTOMRIGHT") nextCropUpdate = { x: 1.0f, y: 1.0f };
    if (direction == "BOTTOM") nextCropUpdate = { x: 0.0f, y: 1.0f };
    if (direction == "BOTTOMLEFT") nextCropUpdate = { x: -1.0f, y: 1.0f };
    if (direction == "LEFT") nextCropUpdate = { x: -1.0f, y: 0.0f };
    if (direction == "TOPLEFT") nextCropUpdate = { x: -1.0f, y: -1.0f };

    moveWorldCropPosition(nextCropUpdate);
};

void World::draw() {
    DrawTextureEx(texture, cropPosition, 0.0f, 2, WHITE);
};
