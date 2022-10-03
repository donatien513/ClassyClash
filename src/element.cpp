#include "element.hpp"
#include <regex>

const std::regex directionMatcherRight{".*RIGHT.*"};
const std::regex directionMatcherLeft{".*LEFT.*"};


void Element::setSprite(Texture2D* newSprite) {
    sprite = newSprite;
};

void Element::move(std::string direction) {
    if (std::regex_match(direction, directionMatcherRight)) {
        facingDirection = 1.0f;
    } else if (std::regex_match(direction, directionMatcherLeft)) {
        facingDirection = -1.0f;
    }
    setIsMoving(true);
};

void Element::setIsMoving(bool newIsMovingStatus) {
    if (newIsMovingStatus) {
        setSprite(&movingSprite);
    } else {
        setSprite(&idleSprite);
    }
};

void Element::incrementAnimationTime(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= updateTime) {
        animationTime = 0.0f;
        spriteCropPosition.x += 32.0f;
        if (spriteCropPosition.x >= 32.0f * 11) {
            spriteCropPosition.x = 0;
        }
    }
};

Element::Element(Rectangle newElementPosition) {
    charcaterPosition = newElementPosition;
    setSprite(&idleSprite);
};

void Element::unloadTexture() {
    UnloadTexture(idleSprite);
    UnloadTexture(movingSprite);
};

void Element::draw() {
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

void Element::idle() {
    setIsMoving(false);
}
