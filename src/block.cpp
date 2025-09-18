#include "block.hpp"

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw(){
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255}); //a block of 3 by 3 pixels and yellow color
}

Rectangle Block::getRect()
{
    // since block is 3 x 3 pixels we'll assign values for return first
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3; // 3 pixels
    rect.height = 3; // 3 pixels 
    return rect;
}
