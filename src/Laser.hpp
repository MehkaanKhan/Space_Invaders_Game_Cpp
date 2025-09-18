#pragma once
#include <raylib.h>

class Laser{
    public:
        Laser(Vector2 position, int speed); //arguments set it's potiton and speed
        void Update(); //update the position of laser beam
        void Draw(); //draws laser beam onto the screen
        Rectangle getRect();
        bool active;
    private:
        Vector2 position; //position of laser
        int speed; //speed of laser
};