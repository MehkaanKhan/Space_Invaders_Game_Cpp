#include "alien.hpp"

Texture2D Alien::alienImages[3] = {}; //initiaised it with zero values

Alien::Alien(int type, Vector2 position)
{
    // 'this' special pointer available within a class. It points to the current instance of the class. '->' expilicitly points to memeber variables
    this -> type = type; //local parameters passed to the function
    this -> position = position;

    if (alienImages[type - 1].id == 0) //'.id' internal identifier for the resource. Images are CPU-side data (not directly uploaded to the GPU).  
                                     // == 0 means image has not been loaded or initialized as a GPU texture. 
    {
    switch(type){
        case 1:
        {
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
        case 2:
        {
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        }
        case 3:
        {
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        }
        default:
        {
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
    }
}

void Alien::Draw(){ //Darw alien on screen
    DrawTextureV(alienImages[type - 1], position, WHITE); //DrawV function helps to draw the image on specified position on screen
}

int Alien::GetType(){
    return type;
}

void Alien::UnloadImages(){
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}

void Alien::Update(int direction){
    position.x += direction;
}