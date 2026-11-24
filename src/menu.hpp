#pragma once
#include "raylib-cpp.hpp"
#include "time.hpp"
#include "animationHandler.hpp"
#include "doom.hpp"
#include <unordered_map>

enum visible {
    OFF,
    ON
};

enum selected {
    PLAY,
    SETTING,
    EXIT,
    UNKOWN
};

selected selectedButton = UNKOWN;
visible menuVisible = ON;

float alphaFade = 1.0f;
const float alphaSpeed = 0.005f; // how much per second will the alpha be reduced

float opacity = 0.0f;


// for fuck sakes I can't think of a better way to add a fadeIn animation
// With all blocking the opacity variable (Need to create an opacity variable for EACH element)

static float settingOpacity = 0.0f;
static float playOpacity = 0.0f;
static float exitOpacity = 0.0f;

static float settingGOpacity = 0.0f;
static float playGOpacity = 0.0f;
static float exitGOpacity = 0.0f;

float fadeSpeed = 0.125f;

static int selectedMenu = PLAY;
bool hasEnded = false;

const float btnFadeInSpeed = 15.0f;
const float glowSpeed = 0.2f;

spriteHandler tex;
timer timedt;

// Check out this wall of pain and if statements //
void checkOpacity() {

    if (alphaFade < 0.0f) {
        alphaFade = 0.0f;
    }

    if (opacity > 1.0f) {
        opacity = 1.0f;
    }
    if (settingOpacity > 1.0f) {
        settingOpacity = 1.0f;
    }

    if (settingGOpacity > 0.05f) {
        settingGOpacity = 0.05f;
    }

    if (exitOpacity > 1.0f) {
        exitOpacity = 1.0f;
    }

    if (exitGOpacity > 0.05f) {
        exitGOpacity = 0.05f;
    }

    if (playOpacity > 1.0f) {
        playOpacity = 1.0f;
    }

    if (playGOpacity > 0.05f) {
        playGOpacity = 0.05f;
    }
}

void menuInit() {

    checkOpacity();

    if (!hasEnded) {
        if (timedt.getDelta() >= 2.0f && timedt.getDelta() <= 3.5f) {
            DrawTextureEx(tex.loadSprite("warbladeWHITE.png", UI), { 750 , 180 }, 0.0f, 2.0f, Fade(WHITE, (timedt.getDelta() - (2.0f)) / 0.8f));
        }
        else if (timedt.getDelta() >= 3.5f && timedt.getDelta() <= 8.0f) {
            DrawTextureEx(tex.loadSprite("recreationWHITE.png", UI), { 580, 200 }, 0.0f, 2.0f, Fade(WHITE, (timedt.getDelta() - (3.5f)) / 1.2f));
            DrawTextureEx(tex.loadSprite("warbladeWHITE.png", UI), { 750, 180 }, 0.0f, 2.0f, WHITE);
        }
        else if (timedt.getDelta() >= 8.0f && timedt.getDelta() <= 18.0f) {
            DrawTextureEx(tex.loadSprite("title.png", UI), { 580, 200 }, 0.0f, 2.0f, Fade(WHITE, opacity += fadeSpeed));
            DrawTextureEx(tex.loadSprite("play.png", UI), { 400, 500 }, 0.0f, 2.0f, Fade(WHITE, opacity += fadeSpeed));
            DrawTextureEx(tex.loadSprite("setting.png", UI), { 1100, 500 }, 0.0f, 2.0f, Fade(WHITE, opacity += fadeSpeed));
            DrawTextureEx(tex.loadSprite("exit.png", UI), { 700, 700 }, 0.0f, 2.0f, Fade(WHITE, opacity += fadeSpeed));
            DrawRectangle(0, 0, virtualResolutions::VIRTUAL_WIDTH, virtualResolutions::VIRTUAL_HEIGHT, Fade(WHITE, alphaFade -= alphaSpeed * (timedt.getDelta() - (8.0f))));

        }
        else if (timedt.getDelta() >= 18.0f) {
            DrawTextureEx(tex.loadSprite("title.png", UI), { 580, 200 }, 0.0f, 2.0f, WHITE);
                DrawTextureEx(tex.loadSprite("playH.png", UI), { 400, 500 }, 0.0f, 2.0f, WHITE);
                DrawTextureEx(tex.loadSprite("setting.png", UI), { 1100, 500 }, 0.0f, 2.0f, WHITE);
                DrawTextureEx(tex.loadSprite("exit.png", UI), { 700, 700 }, 0.0f, 2.0f, WHITE);

            hasEnded = true;
        }
    }
    else {

        // Need to draw it twice to avoid flickering //
        DrawTextureEx(tex.loadSprite("title.png", UI), { 580, 200 }, 0.0f, 2.0f, WHITE);
        if (selectedButton == selected::UNKOWN) {
            DrawTextureEx(tex.loadSprite("play.png", UI), { 400, 500 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(tex.loadSprite("setting.png", UI), { 1100, 500 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(tex.loadSprite("exit.png", UI), { 700, 700 }, 0.0f, 2.0f, WHITE);

            // To make sure the player is not stuck when the menu starts //
            selectedButton = selected::PLAY;
        }

        if (IsKeyPressed(KEY_RIGHT) && (selectedButton == selected::PLAY || selectedButton == selected::EXIT)) {
            selectedButton = selected::SETTING;
        }
        else if (IsKeyPressed(KEY_LEFT) && (selectedButton == selected::SETTING || selectedButton == selected::EXIT)) {
            selectedButton = selected::PLAY;
        }
        else if (IsKeyPressed(KEY_UP) && selectedButton == selected::EXIT) {
            selectedButton = selected::PLAY;
        }
        else if (IsKeyPressed(KEY_DOWN) && (selectedButton == selected::PLAY || selectedButton == selected::SETTING)) {
            selectedButton = selected::EXIT;
        }

        if (selectedButton == selected::SETTING) {
            playOpacity = 0.0f;
            exitOpacity = 0.0f;

            playGOpacity = 0.0f;
            exitGOpacity = 0.0f;

            settingOpacity += GetFrameTime() * btnFadeInSpeed;
            settingGOpacity += GetFrameTime() * glowSpeed;

            checkOpacity();

            DrawTextureEx(tex.loadSprite("play.png", UI), { 400, 500 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(tex.loadSprite("exit.png", UI), { 700, 700 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(tex.loadSprite("black.png", UI), { 1100, 500 }, 0.0f, 2.0f, Fade(BLACK, settingGOpacity));
            DrawTextureEx(tex.loadSprite("settingH.png", UI), { 1100, 500 }, 0.0f, 2.0f, Fade(WHITE, settingOpacity));
        }

        if (selectedButton == selected::PLAY) {
            settingOpacity = 0.0f;
            exitOpacity = 0.0f;

            settingGOpacity = 0.0f;
            exitGOpacity = 0.0f;

            playOpacity += GetFrameTime() * btnFadeInSpeed;
            playGOpacity += GetFrameTime() * glowSpeed;

            checkOpacity();

            DrawTextureEx(tex.loadSprite("black.png", UI), { 400, 500 }, 0.0f, 2.0f, Fade(BLACK, playGOpacity));
            DrawTextureEx(tex.loadSprite("playH.png", UI), { 400, 500 }, 0.0f, 2.0f, Fade(WHITE, playOpacity));

            DrawTextureEx(tex.loadSprite("setting.png", UI), { 1100, 500 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(tex.loadSprite("exit.png", UI), { 700, 700 }, 0.0f, 2.0f, WHITE);

            if (IsKeyPressed(KEY_ENTER)) {
                menuVisible = visible::OFF;
            }
        }

        if (selectedButton == selected::EXIT) {
            settingOpacity = 0.0f;
            playOpacity = 0.0f;

            settingGOpacity = 0.0f;
            playGOpacity = 0.0f;

            exitOpacity += GetFrameTime() * btnFadeInSpeed;
            exitGOpacity += GetFrameTime() * glowSpeed;

            checkOpacity();

            DrawTextureEx(tex.loadSprite("play.png", UI), { 400, 500 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(tex.loadSprite("setting.png", UI), { 1100, 500 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(tex.loadSprite("black.png", UI), { 700, 700 }, 0.0f, 2.0f, Fade(BLACK, exitGOpacity));
            DrawTextureEx(tex.loadSprite("exitH.png", UI), { 700, 700 }, 0.0f, 2.0f, Fade(WHITE, exitOpacity));
        }
    }
}

void test() {
    DrawTextureEx(tex.loadSprite("supernova0.png", BACKGROUND), { 0, 0 }, 0.0f, 5.0f, WHITE);
}