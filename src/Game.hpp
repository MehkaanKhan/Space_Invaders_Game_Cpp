#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include <raylib.h>
#include <fstream>
#include <sstream>

class Game
{
public:
    Game();
    ~Game();
    void Draw(); //Draw all of the game objects
    void Update(); //Update the position of all game objects
    void HandleInput(); //Handle player's input
    void saveScoreToFile(const std::string& playerName, int score);
    void loadScoreFromFile();
    void enterPlayerName();
    void Reset();
    bool run; //value TRUE if game runs, FALSE if game has stopped
    int lives;
    int score;
    int highscore;
    Music music;
    Font font;
    std::string playerName;
    bool isTyping;
private:
    void DeleteInactiveLaser();
    std::vector<Obstacle> CreateObstacles(); // this method will return a method of obstacles
    std::vector<Alien> CreateAliens(); //this method will create Aliens and return a vector of all aliens
    void MoveAliens(); //this method will invoke the 'update' method of alien class & provide it a direction parameter
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollisions(); // this method will check for collisions
    void GameOver();
    void InitGame(); //This method will initialize the game variables to intial values
    void CheckForHighscore(); //This method will check high-scores and if any greater than previous is recievced, copy and display that
    void saveHighscoreToFile(int highscore); // This method stores the highscore in a text file
    int loadHighscoreFromFile(); // This method loads the highscore from the file
    Spaceship spaceship; //a private attribute
    std::vector<Obstacle> obstacles; //a private attribute of vector that holds o4 obstacles
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers; //vector containing all of aliens
    int aliensDirection;
    constexpr static float alienLaserShootInterval = 0.35; //interval between each alien laser shoot, constexpr --> constant
    float timeLastAlienFired;
    MysteryShip mysteryShip;
    float mysteryshipSpawnInterval; // this attribute will at which mystery ship will appear --> won't be constant
    float timeLastSpawn;
    Sound explosionSound;
};
