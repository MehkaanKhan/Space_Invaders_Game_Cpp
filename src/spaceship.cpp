#include "spaceship.hpp"

Spaceship::Spaceship() //constructor
{
    image = LoadTexture("Graphics/spaceship.png"); //visual representation of our spaceship which is loaded from image and asigned to image attribute
    position.x = (GetScreenWidth() - image.width)/2; //since we're drawing image from top-left corner we need to include image width as well
    position.y = (GetScreenHeight() - image.height - 100);
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg");
}
Spaceship::~Spaceship(){
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::Draw() {//function to draw the spaceship
    DrawTextureV(image, position, WHITE); //A function that draws a Texture2D with position defined as Vector2, exactly what we need

}

void Spaceship::MoveLeft(){
    position.x -= 7; //move left by 7 pixels
    if (position.x < 25)
    {
        position.x = 25;
    }

}

void Spaceship::MoveRight(){
    position.x += 7; //move right by 7 pixels
    if (position.x > (GetScreenWidth() - image.width - 25))
    {
        position.x = (GetScreenWidth() - image.width - 25);
    }
}

void Spaceship::FireLaser(){

    if (GetTime() - lastFireTime >= 0.35){ //GetTime() function tells the time that has passed since game started
    lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6)); // a new laser beam is created and added to the vector
    // since we draw everything from left corner position.x + image.width/2 --> center
    // however since laser itself is 4 pixels wide, we subtract 2 to get exact center
    // -6 represents speed
    lastFireTime = GetTime();
    PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    // returning a rectangle that will be positioned at the position of the spacership
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
