#pragma once
#include "raylib-cpp.hpp"
#include "tools.hpp"

// Base object for further structs such as Player, Enemy etc.
struct Entity
{
    raylib::Texture sprite;
    raylib::Rectangle hitBox;
    raylib::Vector2 pos{0, 0};
    raylib::Vector2 velocity{0.0f, 0.0f};
    float rotation = 0.0f; // In radians
    const float dragScaler = 0.2f;
    const raylib::Vector2 maxVelocity = {10.0f, 10.0f};
    const raylib::Vector2 minVelocity = -maxVelocity;

    void setPos(float a, float b){
        this->pos = raylib::Vector2{a, b};
    }

    void setPos(raylib::Vector2 vec2)
    {
        this->pos = vec2;
    }

    void setVelocity(float a, float b){
        this->velocity = raylib::Vector2{a, b};
    }

    void setVelocity(raylib::Vector2 vec2)
    {
        this->velocity = vec2;
    }

    void updateVelocity(float a, float b){
        this->velocity += raylib::Vector2{a, b};
        this->velocity = this->velocity.Clamp(minVelocity, maxVelocity);
    }

    void updateVelocity(raylib::Vector2 vec2)
    {
        this->velocity += vec2;
        this->velocity = this->velocity.Clamp(minVelocity, maxVelocity);
    }

    raylib::Vector2 operator+=(raylib::Vector2 &vec2)
    {
        this->updateVelocity(vec2);
        return this->velocity;
    }

    // without a constant source of velocity the entity will eventually reach 0 velocity
    raylib::Vector2 applyDrag()
    {
        const float speed = this->velocity.Length();

        if (speed <= dragScaler) {
            this->velocity = raylib::Vector2{0.0f, 0.0f};
        } else {
            const float remainingSpeed = speed - dragScaler;
            this->velocity *= remainingSpeed / speed;
        }

        return this->velocity;
    }

    // This needs to be called if you want the entity to move
    // (Doesn't implement delta time...)
    raylib::Vector2 applyVelocity(bool applyDrag = true)
    {
        if(applyDrag) this->applyDrag();
        raylib::Vector2 futurePosition = this->pos + this->velocity;

        // Bounds check
        // TODO: Make it account for size of sprite and maybe find a less glitchy implementation
        if (futurePosition.x < GetScreenWidth() 
            && futurePosition.x >= 0 
            && futurePosition.y < GetScreenHeight()
            && futurePosition.y >= 0){
            this->setPos(futurePosition);
            return this->pos;
        }
        
        return this->pos;
    }

    // Call this to display said entity
    void Draw()
    {
        // Raylib throws an exception and dumps the core when the texture isn't correctly loaded
        // so I'm not sure if this check is neccesary
        if (IsTextureValid(sprite)) sprite.Draw(pos);
    }
};

struct Player : Entity{
    Player(){

        // TODO: Get an actually trasnparant PNG
        Image ico = LoadImage("media/textures/player.png");
        ImageResize(&ico, 50, 50); // From what I can tell textures can't be resized or edited after being loaded. Consider declaring sprite as image?
        sprite = LoadTextureFromImage(ico);
        UnloadImage(ico);
    }
};

struct Enemy : Entity {
    // Empty...
};

struct Projectile : Entity {

};