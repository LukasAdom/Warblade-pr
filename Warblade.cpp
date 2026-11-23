#include "raylib-cpp.hpp"
#include "src/entity.hpp"
#include "src/tools.hpp"
#include <vector>
#include "src/level_loader.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    const float playerAccel = 1.0f;

    // Texture/Sprite initializations ALWAYS goes AFTER window initialization
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

    Player player;
    // TODO: create a global entity vector with type unique_ptr for easier application of .applyVelocity() and .Draw()
    // it would be able to store every polymorth of entity such as player, enemy, projectile etc. in 1 vector


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.updateVelocity(playerAccel, 0.0f);
        if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) player.updateVelocity(-playerAccel, 0.0f);
        if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) player.updateVelocity(0.0f, -playerAccel);
        if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) player.updateVelocity(0.0f, playerAccel);

        player.applyVelocity();

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            player.Draw();
		EndDrawing();
    }
    return 0;
}
