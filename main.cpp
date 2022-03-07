#include "raylib.h"
#include "raymath.h"

class Character {
  private:
    Texture2D *sprite;
    Texture2D *idleSprite;
    Texture2D *runningSprite;
    bool isRunning;
    Rectangle charcaterPosition;
    Vector2 charcaterCenter;
    float updateTime = 1.0f / 24.0f;
    float runningTime;
    float facingDirection = 1.0f;
    Rectangle spriteCropPosition{
      0.0f,
      0.0f,
      32.0f,
      32.0f
    };
    void setSprite(Texture2D* newSprite) {
      sprite = newSprite;
    }
  public:
    void faceRight() {
      facingDirection = 1.0f;
    }
    void faceLeft() {
      facingDirection = -1.0f;
    }
    void setIdleSprite(Texture2D* newIdleSprite) {
      idleSprite = newIdleSprite;
    }
    void setRunningSprite(Texture2D* newRunningSprite) {
      runningSprite = newRunningSprite;
    }
    void setIsRunning(bool newIsRunningStatus) {
      isRunning = newIsRunningStatus;
      if (isRunning) {
        setSprite(runningSprite);
      } else {
        setSprite(idleSprite);
      }
    }
    void incrementRunningTime(float deltaTime) {
      runningTime += deltaTime;
      if (runningTime >= updateTime) {
        runningTime = 0.0f;
        spriteCropPosition.x += 32.0f;
        if (spriteCropPosition.x >= 32.0f * 11) {
          spriteCropPosition.x = 0;
        }
      }
    }
    void setCharacterPosition(Rectangle newCharacterPosition) {
      charcaterPosition = newCharacterPosition;
    }
    void setCharacterCenter(Vector2 newCharcaterCenter) {
      charcaterCenter = newCharcaterCenter;
    }
    void draw() {
      DrawTexturePro(
        *sprite,
        Rectangle{
          spriteCropPosition.x,
          spriteCropPosition.y,
          spriteCropPosition.width * facingDirection,
          spriteCropPosition.height
        },
        charcaterPosition,
        charcaterCenter,
        0.0f,
        WHITE
      );
    }
};

class World {
  private:
    float speed{8.0f};
    Texture2D *texture;
    Vector2 cropPosition{
      x: 0.0f,
      y: 0.0f,
    };
    Vector2 nextCropUpdate{
      x: 0.0f,
      y: 0.0f,
    };
    void moveWorldCropPosition() {
      cropPosition = Vector2Subtract(cropPosition,
      Vector2Scale(
        Vector2Normalize(nextCropUpdate),
        speed
      ));
    }
  public:
    void setTexture(Texture2D* newTexture) {
      texture = newTexture;
    }
    void prepareScrollUp() {
      nextCropUpdate.y = -1.0f;
    }
    void prepareScrollDown() {
      nextCropUpdate.y = 1.0f;
    }
    void prepareScrollLeft() {
      nextCropUpdate.x = -1.0f;
    }
    void prepareScrollRight() {
      nextCropUpdate.x = 1.0f;
    }
    void applyScrollAndReset() {
      moveWorldCropPosition();
      nextCropUpdate = {
        x: 0.0f,
        y: 0.0f,
      };
    }
    void draw() {
      DrawTextureEx(*texture, cropPosition, 0.0f, 2, WHITE);
    }
};

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

  Texture2D pinkManTexture_idle{LoadTexture("characters/Pink Man/Idle (32x32).png")};
  Texture2D pinkManTexture_running{LoadTexture("characters/Pink Man/Run (32x32).png")};

  // W.O.R.L.D.
  World world;
  world.setTexture(&worldTexture);

  // P.L.A.Y.E.R.
  Character mainPlayer = Character();

  mainPlayer.setIdleSprite(&pinkManTexture_idle);
  mainPlayer.setRunningSprite(&pinkManTexture_running);

  mainPlayer.setCharacterPosition(Rectangle{
    ((float)WINDOW_WIDTH / 2.0f) - 64.0f,
    ((float)WINDOW_HEIGHT / 2.0f) - 64.0f,
    128.0f,
    128.0f
  });
  mainPlayer.setCharacterCenter(Vector2{
    x: 32.0f,
    y: 32.0f
  });

  SetTargetFPS(60);
  
  while (!WindowShouldClose()) {
    float deltaTime{GetFrameTime()};
    BeginDrawing();
    ClearBackground(BLACK);

    // Keys control
    Vector2 direction{};
    bool characterIsMoving{false};

    if (IsKeyDown(KEY_LEFT)) {
      world.prepareScrollLeft();
      characterIsMoving = true;
      mainPlayer.faceLeft();
    }
    if (IsKeyDown(KEY_RIGHT)) {
      world.prepareScrollRight();
      characterIsMoving = true;
      mainPlayer.faceRight();
    }
    if (IsKeyDown(KEY_DOWN)) {
      world.prepareScrollDown();
      characterIsMoving = true;
    }
    if (IsKeyDown(KEY_UP)) {
      world.prepareScrollUp();
      characterIsMoving = true;
    }

    mainPlayer.setIsRunning(characterIsMoving);

    // Animation
    mainPlayer.incrementRunningTime(deltaTime);

    // Drawing
    world.applyScrollAndReset();
    world.draw();  
    mainPlayer.draw();

    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(worldTexture);
  UnloadTexture(pinkManTexture_idle);
  UnloadTexture(pinkManTexture_running);
}
