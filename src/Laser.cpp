#include "Laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    // 'this' special pointer available within a class. It points to the current instance of the class. '->' expilicitly points to memeber variables
    this-> position = position; //local parameters passed to the function
    this-> speed = speed;
    active = true;
}

void Laser::Draw(){
    if (active)
    {
        DrawRectangle(position.x, position.y, 4, 15, {136, 8, 8, 255});
    }
    
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4; // 4 pixels wide
    rect.height = 15; // 15 pixels high
    return rect;
}

void Laser::Update(){
    position.y += speed;

    if (active)
    {
        if (position.y > GetScreenHeight() - 100|| position.y  < 25) //is the laser beam gets out of the screen
        {
            active = false;
        }
    }
}