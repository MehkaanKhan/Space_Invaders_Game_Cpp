#pragma once
#include <raylib.h>

class Block{
    public:
        Block(Vector2 position); //teling constructor the coordinates at which the block will spawn so we use Vector2 position
        void Draw(); //function to draw the block
        Rectangle getRect();
    private:
        Vector2 position;
};