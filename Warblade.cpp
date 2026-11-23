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
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Texture/Sprite initializations ALWAYS goes AFTER window initialization
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

    Player player;
    const float playerAccel = 1.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
 	    //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) player.updateVelocity(playerAccel, 0.0f);
        if (IsKeyDown(KEY_LEFT)) player.updateVelocity(-playerAccel, 0.0f);
        if (IsKeyDown(KEY_UP)) player.updateVelocity(0.0f, -playerAccel);
        if (IsKeyDown(KEY_DOWN)) player.updateVelocity(0.0f, playerAccel);

        player.applyVelocity();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            player.Draw();
		EndDrawing();
        //----------------------------------------------------------------------------------
    }
    return 0;
}
