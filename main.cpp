#include <string>
#include "raylib.h"
#include "raymath.h"
#include "src/character.hpp"
#include "src/world.hpp"

int main() {
  const int WINDOW_WIDTH{800};
  const int WINDOW_HEIGHT{800};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");

  float speed{8.0};
  bool characterIsMoving{false};
  float rightLeft{1.0f};

  Texture2D worldTexture{LoadTexture("levels-map/level-1.png")};
  Vector2 croppedWorldPosition{
    x: 0.0f,
    y: 0.0f,
  };

  // W.O.R.L.D.
  World world = World();

  // P.L.A.Y.E.R.
  Character mainPlayer = Character();
  mainPlayer.setCharacterPosition(Rectangle{
    ((float)WINDOW_WIDTH / 2.0f) - 64.0f,
    ((float)WINDOW_HEIGHT / 2.0f) - 64.0f,
    128.0f,
    128.0f
  });

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    float deltaTime{GetFrameTime()};
    BeginDrawing();
    ClearBackground(BLACK);

    // Keys control
    std::string direction = "";
  
    if (IsKeyDown(KEY_DOWN)) direction += "BOTTOM";
    if (IsKeyDown(KEY_UP)) direction += "TOP";
    if (IsKeyDown(KEY_LEFT)) direction += "LEFT";
    if (IsKeyDown(KEY_RIGHT)) direction += "RIGHT";

    if (direction == "") {
      mainPlayer.idle();
    } else {
      world.move(direction);
      mainPlayer.move(direction);
    }

    // Animation
    mainPlayer.incrementRunningTime(deltaTime);

    // Drawing
    world.draw();  
    mainPlayer.draw();

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(worldTexture);
  UnloadTexture(mainPlayer.idleSprite);
  UnloadTexture(mainPlayer.runningSprite);
}
