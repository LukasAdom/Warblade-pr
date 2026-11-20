#pragma once
#include "raylib-cpp.hpp"

// Base object for further structs such as Player, Enemy etc.
struct Entity
{
    raylib::Texture sprite;
    raylib::Rectangle hitBox;
    raylib::Vector2 pos{0, 0};
    raylib::Vector2 velocity{0, 0};
    float rotation = 0.0f; // In radians
};

struct Player : Entity
{
    Player(){
        // Hard coded location of the players sprite
        // TODO: Get an actually trasnparant PNG and resize to appropriate size or get a smaller PNG
        sprite.Load("media/textures/player.png");
    }

    void Draw(){
        sprite.Draw(pos);
    }
};

//struct Enemy : Entity {
    // Empty...
//};

//struct Projectile : Entity {

//};