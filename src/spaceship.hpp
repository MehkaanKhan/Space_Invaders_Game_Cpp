#pragma once //an instruction that ensures this header file is ony included once in a compilation to avoid duplication definitions
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship{

    public:
        Spaceship(); //constructor
        ~Spaceship(); //distructor
        // Public methods so that other classes can call them
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle getRect();
        void Reset();
        std::vector<Laser> lasers; // a vector of type class Laser
    private:
    // Private members so that they can only be accessed within the class and no other can touch this
    Texture2D image; // Data Structure representing a 2D image --> used for rendering
    Vector2 position; // Data type representing a 2D point or vector with x and y componenets --> position of spaceship
    double lastFireTime; // This attribute will hold time in seconds 
    Sound laserSound;
};