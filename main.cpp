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
    ((float)WINDOW_WIDTH / 2.0f) - 64.0f,
    ((float)WINDOW_HEIGHT / 2.0f) - 64.0f,
    128.0f,
    128.0f
  };

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");

  float speed{8.0};
  bool characterIsMoving{false};
  float rightLeft{1.0f};

  Texture2D worldTexture{LoadTexture("levels-map/level-1.png")};
  Vector2 croppedWorldPosition{
    x: 0.0f,
    y: 0.0f,
  };

  Texture2D pinkManTexture_idle{LoadTexture("characters/Pink Man/Idle (32x32).png")};
  Texture2D pinkManTexture_running{LoadTexture("characters/Pink Man/Run (32x32).png")};

  Character mainPlayer{};
  mainPlayer.updateTime = 1.0f / 24.0f;
  mainPlayer.sprite = &pinkManTexture_idle;
  mainPlayer.center = {
    x: 32.0f,
    y: 32.0f
  };
  mainPlayer.spriteCropPosition.x = 0.0f;
  mainPlayer.spriteCropPosition.y = 0.0f;
  mainPlayer.spriteCropPosition.height = 32.0f;
  mainPlayer.spriteCropPosition.width = 32.0f;

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    float deltaTime{GetFrameTime()};
    BeginDrawing();
    ClearBackground(BLACK);

    // Keys control
    Vector2 direction{};

    if (IsKeyDown(KEY_LEFT)) {
      direction.x = -1.0f;
      rightLeft = -1.f;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      direction.x = 1.0f;
      rightLeft = 1.f;
    }
    if (IsKeyDown(KEY_DOWN)) direction.y = 1.0f;
    if (IsKeyDown(KEY_UP)) direction.y = -1.0f;

    characterIsMoving = Vector2Length(direction) > 0.0f;

    if (characterIsMoving) {
      croppedWorldPosition = Vector2Subtract(croppedWorldPosition,
      Vector2Scale(
        Vector2Normalize(direction),
        speed
      ));
      mainPlayer.sprite = &pinkManTexture_running;
    } else {
      mainPlayer.sprite = &pinkManTexture_idle;
    }

    // Animation
    mainPlayer.runningTime += deltaTime;
    if (mainPlayer.runningTime >= mainPlayer.updateTime) {
      mainPlayer.runningTime = 0.0f;
      mainPlayer.spriteCropPosition.x += 32.0f;
      if (mainPlayer.spriteCropPosition.x >= 32.0f * 11) {
        mainPlayer.spriteCropPosition.x = 0;
      }
    }

    // Drawing
    DrawTextureEx(worldTexture, croppedWorldPosition, 0.0f, 2, WHITE);
    DrawTexturePro(
      (*mainPlayer.sprite),
      Rectangle{
        mainPlayer.spriteCropPosition.x,
        mainPlayer.spriteCropPosition.y,
        mainPlayer.spriteCropPosition.width * rightLeft,
        mainPlayer.spriteCropPosition.height
      },
      mainPlayerDestination,
      mainPlayer.center,
      0.0f,
      WHITE
    );

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(worldTexture);
  UnloadTexture(pinkManTexture_idle);
  UnloadTexture(pinkManTexture_running);
}
