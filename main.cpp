#include "raylib.h"
#include "raymath.h"

int main() {
  const int WINDOW_WIDTH{800};
  const int WINDOW_HEIGHT{800};


  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");
  float speed{8.0};

  Texture2D worldTexture{LoadTexture("levels-map/level-1.png")};
  Vector2 croppedWorldPosition{
    x: 0,
    y: 0,
  };

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

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
    DrawTextureEx(worldTexture, croppedWorldPosition, 0.0, 2, WHITE);

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(worldTexture);
}
