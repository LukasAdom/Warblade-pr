#include "raylib-cpp.hpp"
#include "src/entity.hpp"
#include "src/tools.hpp"
#include "src/menu.hpp"
#include "src/doom.hpp"
#include "src/time.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

enum class Scene
{
    MAIN_MENU,
    GAME
};

static void toggleFullSceenWindow(int windowW, int windowH) {
    if (!IsWindowFullscreen()) {
        int monitor = GetCurrentMonitor();

        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else {
        ToggleFullscreen();
        SetWindowSize(windowW, windowH);
    }
}

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

    Scene currentScene = Scene::MAIN_MENU;
    Dmelt doomTransition;

    // Don't be a dumbass like me and put the background or ANY initializations before the window initialization...
    RenderTexture2D bgRender = LoadRenderTexture(
        virtualResolutions::VIRTUAL_WIDTH,
        virtualResolutions::VIRTUAL_HEIGHT
    );

    doomTransition.init(virtualResolutions::VIRTUAL_WIDTH, virtualResolutions::VIRTUAL_HEIGHT);

    //toggleFullSceenWindow(screenWidth, screenHeight);

    Player player;
    const float playerAccel = 1.0f;

    timer timedt;

    //Texture2D bg = LoadTexture("media/textures/background/space0.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        float scale = std::min(
            (float)GetScreenWidth() / virtualResolutions::VIRTUAL_WIDTH,
            (float)GetScreenHeight() / virtualResolutions::VIRTUAL_HEIGHT
        );

        int scaledWidth = virtualResolutions::VIRTUAL_WIDTH * scale;
        int scaledHeight = virtualResolutions::VIRTUAL_HEIGHT * scale;

        int offsetX = (GetScreenWidth() - scaledWidth) / 2;
        int offsetY = (GetScreenHeight() - scaledHeight) / 2;


        if (IsKeyPressed(KEY_F11)) {
            toggleFullSceenWindow(screenWidth, screenHeight);
        }

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

        ClearBackground(BLACK);

        if (currentScene == Scene::MAIN_MENU &&
            menuVisible == visible::OFF)
        {
            doomTransition.start(
                [&]()
                {
                    DrawTextureEx(
                        tex.loadSprite("space0.png", BACKGROUND),
                        { 0, 0 },
                        0.0f,
                        3.0f,
                        WHITE
                    );

                    menuInit();
                },

                [&]()
                {
                    test();
                    player.Draw();
                }
            );

            currentScene = Scene::GAME;
        }

        BeginTextureMode(bgRender);

        ClearBackground(BLACK);

        if (doomTransition.isActive())
        {
            doomTransition.update(GetFrameTime());
            doomTransition.draw();
        }
        else
        {
            switch (currentScene)
            {
            case Scene::MAIN_MENU:

                DrawTextureEx(
                    tex.loadSprite("space0.png", BACKGROUND),
                    { 0, 0 },
                    0.0f,
                    3.0f,
                    WHITE
                );

                menuInit();
                break;

            case Scene::GAME:

                test();
                player.Draw();
                break;
            }
        }

        EndTextureMode();

        Rectangle source = {
            0.0f,
            0.0f,
            (float)virtualResolutions::VIRTUAL_WIDTH,
            -(float)virtualResolutions::VIRTUAL_HEIGHT
        };

        Rectangle dest = {
            (float)offsetX,
            (float)offsetY,
            (float)scaledWidth,
            (float)scaledHeight
        };

        DrawTexturePro(
            bgRender.texture,
            source,
            dest,
            { 0, 0 },
            0.0f,
            WHITE
        );

        EndDrawing();

        //----------------------------------------------------------------------------------
    }
    return 0;
}
