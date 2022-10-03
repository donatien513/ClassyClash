#include <string>
#include "raylib.h"
#include "raymath.h"
#include "src/hero.hpp"
#include "src/world.hpp"
#include "src/movement-control.hpp"

int main() {
  int WINDOW_WIDTH{400};
  int WINDOW_HEIGHT{400};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");

  float speed{8.0};

  // W.O.R.L.D.
  World world = World();

  // P.L.A.Y.E.R.
  Hero mainPlayer = Hero(Rectangle{
    (static_cast<float>(WINDOW_WIDTH) / 2.0f) - 64.0f,
    (static_cast<float>(WINDOW_HEIGHT) / 2.0f) - 64.0f,
    64.0f,
    64.0f
  });

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    float deltaTime{GetFrameTime()};
    BeginDrawing();
    ClearBackground(Color{
      30, 30, 30, 0
    });



    // Keys control
    std::string direction = getDirection(&WINDOW_WIDTH, &WINDOW_HEIGHT, world.getTexture(), world.getWorldPosition());
  
    if (direction != "") {
      world.move(direction);
      mainPlayer.move(direction);
    } else {
      mainPlayer.idle();
    }

    // Animation
    mainPlayer.incrementAnimationTime(deltaTime);

    // Drawing
    world.draw();  
    mainPlayer.draw();

    EndDrawing();
  }
  world.unloadTexture();
  mainPlayer.unloadTexture();
  CloseWindow();
}
