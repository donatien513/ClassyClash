#include <string>
#include "raylib.h"
#include "raymath.h"

class Element {
  private:
    Texture2D *sprite;
    bool isMoving;
    Rectangle charcaterPosition{};
    Vector2 charcaterCenter{Vector2{
      x: 32.0f,
      y: 32.0f
    }};
    float updateTime = 1.0f / 24.0f;
    float animationTime;
    float facingDirection = 1.0f;
    Rectangle spriteCropPosition{
      0.0f,
      0.0f,
      32.0f,
      32.0f
    };
    void setSprite(Texture2D* newSprite);
    void setIsMoving(bool newIsMovingStatus);
    Texture2D idleSprite{LoadTexture("characters/Virtual Guy/Idle (32x32).png")};
    Texture2D movingSprite{LoadTexture("characters/Virtual Guy/Run (32x32).png")};
  public:
    void move(std::string direction);
    void idle();
    void incrementAnimationTime(float deltaTime);
    Element(Rectangle newElementPosition);
    void unloadTexture();
    void draw();
};
