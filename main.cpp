#include "raylib.h"
#include "raymath.h"

struct Character {
  Texture2D *sprite;
  Rectangle spriteCropPosition;
  Vector2 center;
  float updateTime;
  float runningTime;
};

int main() {
  const int WINDOW_WIDTH{800};
  const int WINDOW_HEIGHT{800};

  const Rectangle mainPlayerDestination{
    (WINDOW_WIDTH / 2.0) - 64.0,
    (WINDOW_HEIGHT / 2.0) - 64.0,
    128.0,
    128.0
  };

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");
  float speed{8.0};

  Texture2D worldTexture{LoadTexture("levels-map/level-1.png")};
  Vector2 croppedWorldPosition{
    x: 0,
    y: 0,
  };

  Texture2D pinkManTexture{LoadTexture("characters/Pink Man/Idle (32x32).png")};

  Character mainPlayer{};
  mainPlayer.updateTime = 1.0 / 24.0;
  mainPlayer.sprite = &pinkManTexture;
  mainPlayer.center = {
    x: 32.0,
    y: 32.0
  };
  mainPlayer.spriteCropPosition.x = 0.0;
  mainPlayer.spriteCropPosition.y = 0.0;
  mainPlayer.spriteCropPosition.height = 32.0;
  mainPlayer.spriteCropPosition.width = 32.0;

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    float deltaTime{GetFrameTime()};
    BeginDrawing();
    ClearBackground(BLACK);

    // Keys control
    Vector2 direction{};

    if (IsKeyDown(KEY_LEFT)) direction.x = -1.0;
    if (IsKeyDown(KEY_RIGHT)) direction.x = 1.0;
    if (IsKeyDown(KEY_DOWN)) direction.y = 1.0;
    if (IsKeyDown(KEY_UP)) direction.y = -1.0;
    if (Vector2Length(direction)) {
      croppedWorldPosition = Vector2Subtract(croppedWorldPosition,
      Vector2Scale(
        Vector2Normalize(direction),
        speed
      ));
    }

    // Animation
    mainPlayer.runningTime += deltaTime;
    if (mainPlayer.runningTime >= mainPlayer.updateTime) {
      mainPlayer.runningTime = 0.0;
      mainPlayer.spriteCropPosition.x += 32.0;
      if (mainPlayer.spriteCropPosition.x >= 32.0 * 11) {
        mainPlayer.spriteCropPosition.x = 0;
      }
    }

    // Drawing
    DrawTextureEx(worldTexture, croppedWorldPosition, 0.0, 2, WHITE);
    DrawTexturePro(
      (*mainPlayer.sprite),
      mainPlayer.spriteCropPosition,
      mainPlayerDestination,
      mainPlayer.center,
      0.0,
      WHITE
    );

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(worldTexture);
}
