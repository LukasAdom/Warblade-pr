#pragma once
#include "raylib-cpp.hpp"
#include "time.hpp"
#include <unordered_map>

enum visible {
    OFF = 0,
    ON = 1
};

float alphaFade = 1.0f;
const float alphaSpeed = 0.005f; // how much per second will the alpha be reduced

float opacity = 0.0f;
float fadeSpeed = 0.125f;

float offset = 12.0f;

spriteHandler tex;
timer timedt;

void menuInit() {

    if (alphaFade < 0.0f) {
        alphaFade = 0.0f;
    }

    if (opacity > 1.0f)
        opacity = 1.0f;

    if (timedt.getDelta() >= 2.0f + offset && timedt.getDelta() <= 3.5f + offset) {
        DrawTextureEx(tex.loadSprite("warbladeWHITE.png", UI), { 750 , 180 }, 0.0f, 2.0f, Fade(WHITE, (timedt.getDelta() - (2.0f + offset)) / 0.8f));
    }
    else if (timedt.getDelta() >= 3.5f + offset && timedt.getDelta() <= 8.0f + offset) {
        DrawTextureEx(tex.loadSprite("recreationWHITE.png", UI), { 580, 200 }, 0.0f, 2.0f, Fade(WHITE, (timedt.getDelta() - (3.5f + offset)) / 1.2f));
        DrawTextureEx(tex.loadSprite("warbladeWHITE.png", UI), { 750, 180 }, 0.0f, 2.0f, WHITE);
    }
    else if (timedt.getDelta() >= 8.0f + offset) {
        DrawTextureEx(tex.loadSprite("title.png", UI), { 580, 200 }, 0.0f, 2.0f, Fade(WHITE, opacity += fadeSpeed));
        DrawRectangle(0, 0, virtualResolutions::VIRTUAL_WIDTH, virtualResolutions::VIRTUAL_HEIGHT, Fade(WHITE, alphaFade -= alphaSpeed * (timedt.getDelta() - (8.0f + offset))));
    }
}