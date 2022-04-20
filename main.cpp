#include <string>
#include "raylib.h"
#include "raymath.h"
#include "src/character.hpp"
#include "src/world.hpp"
#include "src/movement-control.hpp"

int main() {
  int WINDOW_WIDTH{800};
  int WINDOW_HEIGHT{800};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");

  float speed{8.0};

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
    ClearBackground(Color{
      30, 30, 30, 0
    });

    // Keys control
    std::string direction = getDirection(&WINDOW_WIDTH, &WINDOW_HEIGHT, &world.texture.width, &world.texture.height, world.getWorldPosition());
  
    if (direction != "") {
      world.move(direction);
      mainPlayer.move(direction);
    } else {
      mainPlayer.idle();
    }

    // Animation
    mainPlayer.incrementRunningTime(deltaTime);

    // Drawing
    world.draw();  
    mainPlayer.draw();

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(world.texture);
  UnloadTexture(mainPlayer.idleSprite);
  UnloadTexture(mainPlayer.runningSprite);
}
