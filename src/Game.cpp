#include "Game.hpp"
#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <string>

Game::Game()
{
    font = LoadFontEx("Font/monogram.ttf", 64, 0 ,0); // loads the font into GPU memory
    music = LoadMusicStream("Sounds/music.ogg"); //loading music file into music
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game(){
    Alien::UnloadImages(); // unload images as we close the game
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Update(){

    if (run) // game will run till run value is TRUE
    {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryshipSpawnInterval) // checks if the interval has passed --> update the attributes
        {
            mysteryShip.Spawn();
            timeLastSpawn = GetTime();
            mysteryshipSpawnInterval = GetRandomValue(10, 20);
        }

        for(auto& laser: spaceship.lasers) // Need to call Update method of each laser beam else it won't move -->  range based for loop
        {
            laser.Update();
        }
        MoveAliens();

        AlienShootLaser(); 
        for (auto& laser: alienLasers) //to update all of the lasers
        {
            laser.Update();
        }
        DeleteInactiveLaser();
        mysteryShip.Update();

        CheckForCollisions();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER)) //retstart when enter is pressed
        {
            Reset();
            InitGame();
        }
    }

}

void Game::Draw(){
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) // For every laser in the lasers vector we need to call the draw method -->  range based for loop
    {
        laser.Draw();
    }

    for(auto& obstacles: obstacles){
       obstacles.Draw(); 
    }

    for(auto& alien: aliens){
        alien.Draw();
    }

    for (auto& laser: alienLasers)
    {
        laser.Draw();
    }

    mysteryShip.Draw();
}

void Game::HandleInput(){
    if (run)
    {
        if(IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
        }
    }

}

void Game::DeleteInactiveLaser(){
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if (!it -> active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    // removing alien's laser with same process but with different vector
    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if (!it -> active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// grid[0].size() --> first row
std::vector<Obstacle> Game::CreateObstacles(){
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth; 
        // this line calculates the horizontal position of each obstacle by adding equal gap b/w them --> evenly spaced
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
} 

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens; //a temp vector to hold the aliens
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else 
            {
                alienType = 1;
            }
            float x = column * 55 + 75; // 55 pixels is the cell size which we hard-coded, 75 pixels is an offset to bring the grid to center
            float y = row * 55 + 110; // 110 pixels --> offset in y coordinate
            aliens.push_back(Alien(alienType, {x,y}));
        }
    }
    return aliens;
}

void Game::MoveAliens(){ // in this method we'll call all of the alien objects and pass alienDirection as an argument
    for(auto& alien : aliens){

        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        else if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }

}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
    // create a random number and use that for indexing vecctor containing all aliens
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& alien = aliens[randomIndex]; //gets random alien object
    alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2, 
                            alien.position.y + alien.alienImages[alien.type - 1].height}, 6)); // 6 --> +ve speed helps in shooting lasers down

    timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    // Spaceship Lasers
    for (auto& laser : spaceship.lasers)
    {
        auto it = aliens.begin(); // iterator that points to the beginning of alien vector
        while (it != aliens.end())
        {
            // check if laser collides with the alien the iterator is pointing to
            if (CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if (it -> type == 1)
                {
                    score += 100;
                }
                else if (it -> type == 2)
                {
                    score += 200;
                }
                else if (it -> type == 3)
                {
                    score += 300;
                }
                CheckForHighscore();
                it = aliens.erase(it);
                laser.active = false;
            }
            else
            {
                it++;
            }
        }

        // check collision between Spaceship Laser & Blocks
        for (auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs( it -> getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else // if no collision --> move to the next element
                {
                    it++;
                }
                
            }        
        }

        // check collision between Spaceship Laser & mystery ship
        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect()))
        {
            mysteryShip.alive = false;
            laser.active = false;
            score += 500;
            CheckForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Alien lasers
    for (auto& laser : alienLasers)
    {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            lives --;

            if (lives == 0)
            {
                GameOver();
            }
        }


        // copied the same obstacle code from above so that the lasers from aliens also erase parts of obstacles
         for (auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs( it -> getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else // if no collision --> move to the next element
                {
                    it++;
                }
                
            }        
        }
    }

    // Alien Collison with Obstacle
    for (auto& alien: aliens) 
    {
        //need to check for collision of every obstacles
        for (auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> getRect(), alien.getRect()))
                {
                    it = obstacle.blocks.erase(it); // we don't need to kill the alien if it hits an obstacle, kill obstacle --> done automatically by function
                }
                else
                {
                    it++;
                }
            }
        }

        // check if an alien sprite hits spaceship
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
           GameOver();
        }
    }
}

void Game::GameOver()
{
    std::cout<<"Game over"<<std::endl;
    run = false;
    saveScoreToFile(playerName, score);
}

void Game::InitGame()
{
    obstacles = CreateObstacles(); // Craeted a vector named Obstacle that holds 4 obstacle objects
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    mysteryshipSpawnInterval = GetRandomValue(10, 20);
}

void Game::CheckForHighscore() //This method will be called in the same areas where score is being added: alien hit and mystership hit
{
    if (score > highscore)
    {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

void Game::saveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");

    if (highscoreFile.is_open())
    {
        highscoreFile << highscore; // writes
        highscoreFile.close();
    }
    else
    {
        std:: cerr <<"Failed to save highscore to file" << std::endl; // cer -> standard error stream
    }

}

int Game::loadHighscoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");

    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore; // reads
        highscoreFile.close();
    }
    else
    {
        std:: cerr<<"Failed to laod the highscore from file" << std::endl;
    }

    return loadedHighscore;
}

void Game::saveScoreToFile(const std::string& playerName, int score)
{
    std::ofstream leaderboardFile("leaderboard.txt", std::ios::app); // Open in append mode
    if (!leaderboardFile.is_open()) {
        std::cerr << "Error: Could not open leaderboard.txt file." << std::endl;
        return;
    }

    leaderboardFile << playerName << " " << score << "\n"; // Save name and score in the file
    leaderboardFile.close();
}

void Game::loadScoreFromFile() {
    std::ifstream leaderboardFile("leaderboard.txt");
    if (!leaderboardFile.is_open()) {
        std::cerr << "Error: Could not open leaderboard.txt file." << std::endl;
        return;
    }

    std::string line;
    float y = 200.0f;  // Starting y-position for text
    const int fontSize = 34;  
    const int spacing = 50;  // Space between lines

    while (std::getline(leaderboardFile, line)) {
        // Draw each name and score on the leaderboard
        DrawTextEx(font, line.c_str(), {180.0f, y}, fontSize, 2, WHITE);
        y += spacing;
    }

    leaderboardFile.close();
}


void Game::enterPlayerName() {
    Color grey = {29, 29, 27, 255};
    while (isTyping) {
        BeginDrawing();
        ClearBackground(grey);
        DrawTextEx(font, "Enter your name:", {180, 150}, 34, 2, WHITE);
        DrawTextEx(font, playerName.c_str(), {180, 200}, 34, 2, WHITE); // Display typed name

        if (IsKeyPressed(KEY_ENTER)) {
            //saveScoreToFile(playerName, score);  // Save the score and name
            isTyping = false; // Stop typing after Enter key
        }

        if (IsKeyPressed(KEY_BACKSPACE) && playerName.length() > 0) {
            playerName.pop_back(); // Remove the last character
        }

        // Handle character input
        for (int key = 32; key < 128; key++) {
            if (IsKeyPressed(key)) {
                playerName.push_back((char)key); // Add the character to the player name
            }
        }

        EndDrawing();
    }
}


void Game::Reset() // This method will reset all of the elements to their original state
{
    spaceship.Reset();
    aliens.clear(); // delete all of the aliens
    alienLasers.clear(); // delete all of the lasers
    obstacles.clear(); // delete all of the obstacles
}
