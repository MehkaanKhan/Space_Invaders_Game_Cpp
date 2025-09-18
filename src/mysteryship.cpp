#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

// position of mystery ship
void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1); //random position value of mystery ship --> return 0 (represents left-side) or 1 (represents right-side) 

    if (side == 0)
    {
        position.x = 25; // 25 pixels is the offset for moving ship due to the frame added
        speed = 3;
    }
    else // else we'll place the mysteryship at the right end of the screen --> Screen width - image.width()
    {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;

}

Rectangle MysteryShip::getRect()
{
    // alive means --> mystership is visible, so only collide with another element when it's visible/ alive
    if (alive)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {position.x, position.y, 0, 0};
    }

}
void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25)
        {
            alive = false;
        }
    }
}

void MysteryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}