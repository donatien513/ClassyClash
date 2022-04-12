#include <string>
#include "raylib.h"
#include "raymath.h"

class Character {
  private:
    Texture2D *sprite;
    bool isRunning;
    Rectangle charcaterPosition{};
    Vector2 charcaterCenter{Vector2{
      x: 32.0f,
      y: 32.0f
    }};
    float updateTime = 1.0f / 24.0f;
    float runningTime;
    float facingDirection = 1.0f;
    Rectangle spriteCropPosition{
      0.0f,
      0.0f,
      32.0f,
      32.0f
    };
    void setSprite(Texture2D* newSprite);
    void setIsRunning(bool newIsRunningStatus);
  public:
    Texture2D idleSprite{LoadTexture("characters/Virtual Guy/Idle (32x32).png")};
    Texture2D runningSprite{LoadTexture("characters/Virtual Guy/Run (32x32).png")};
    void move(std::string direction);
    void idle();
    void incrementRunningTime(float deltaTime);
    void setCharacterPosition(Rectangle newCharacterPosition);
    void draw();
    Character();
};
