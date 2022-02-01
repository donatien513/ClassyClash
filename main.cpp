#include "raylib.h"

int main() {
  int WINDOW_WIDTH{800};
  int WINDOW_HEIGHT{800};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy clash");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
}
