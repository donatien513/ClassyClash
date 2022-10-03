#include <string>
#include "raylib.h"
#include "game-config.h"

class World {
  private:
    Vector2 worldPosition {
      x: 0.0f,
      y: 0.0f,
    };
    Vector2 cropPosition{
      x: 0.0f,
      y: 0.0f,
    };
    void moveWorldPosition(Vector2 nextCropUpdate);
    Texture2D texture{LoadTexture("levels-map/level-1.png")};
  public:
    void move(std::string direction);
    void draw();
    Texture2D* getTexture();
    Vector2* getWorldPosition();
    void unloadTexture();
};
