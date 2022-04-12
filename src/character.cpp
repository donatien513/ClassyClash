#include "character.hpp"
#include <regex>

const std::regex directionMatcherRight{".*RIGHT.*"};
const std::regex directionMatcherLeft{".*LEFT.*"};


void Character::setSprite(Texture2D* newSprite) {
    sprite = newSprite;
};

void Character::move(std::string direction) {
    if (std::regex_match(direction, directionMatcherRight)) {
        facingDirection = 1.0f;
    } else if (std::regex_match(direction, directionMatcherLeft)) {
        facingDirection = -1.0f;
    }
    setIsRunning(true);
};

void Character::setIsRunning(bool newIsRunningStatus) {
    isRunning = newIsRunningStatus;
    if (isRunning) {
        setSprite(&runningSprite);
    } else {
        setSprite(&idleSprite);
    }
};

void Character::incrementRunningTime(float deltaTime) {
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
    runningTime = 0.0f;
    spriteCropPosition.x += 32.0f;
    if (spriteCropPosition.x >= 32.0f * 11) {
        spriteCropPosition.x = 0;
    }
    }
};

void Character::setCharacterPosition(Rectangle newCharacterPosition) {
    charcaterPosition = newCharacterPosition;
};

void Character::draw() {
    DrawTexturePro(
        *sprite,
        Rectangle{
            spriteCropPosition.x,
            spriteCropPosition.y,
            spriteCropPosition.width * facingDirection,
            spriteCropPosition.height
        },
        charcaterPosition,
        charcaterCenter,
        0.0f,
        WHITE
    );
};

void Character::idle() {
    setIsRunning(false);
}

Character::Character() {
    setSprite(&idleSprite);
};
