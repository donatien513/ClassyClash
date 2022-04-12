#include <string>
#include "raylib.h"
#include "raymath.h"

class World {
  private:
    float speed{8.0f};
    Texture2D texture{LoadTexture("levels-map/level-1.png")};
    Vector2 cropPosition{
      x: 0.0f,
      y: 0.0f,
    };
    void moveWorldCropPosition(Vector2 nextCropUpdate);
  public:
    void move(std::string direction);
    void draw();
};
