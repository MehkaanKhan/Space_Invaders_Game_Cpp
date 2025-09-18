#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Obstacle{
    public:
        Obstacle(Vector2 position);
        void Draw();
        Vector2 position;
        std::vector<Block> blocks;// need to access this vector by other classes so we'll make it public
        static std::vector<std::vector<int>> grid; //vector of a vector named grid  --> static so that we can access it withtou cretaing an object
    private:

};