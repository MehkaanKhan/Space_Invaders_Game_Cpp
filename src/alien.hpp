#pragma once
#include "raylib.h"

class Alien{
    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int GetType(); //this method returns the type of alien
        static void UnloadImages(); //performs a task that doesn't depend on the state of any particular instance of the class
        Rectangle getRect();
        static Texture2D alienImages[3]; // this attribute will be common among all the objects and will be initialised only once
        int type; //display 3 different types of aliens --> 3 different images
        Vector2 position; //position of alien
    private:

};