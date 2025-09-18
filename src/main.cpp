#include <raylib.h>
#include "Game.hpp"
#include "leaderboard.hpp"
#include "menu.hpp"
#include <string>

std::string FormatWithLeadingZeros(int number, int width) // a function that will take number and it's width as argument and return a string score with 0's
{
    std::string numberText = std::to_string(number);
    int leadingZero = width - numberText.length(); // number of leading 0
    return numberText = std::string(leadingZero, '0') + numberText;
        
}

int main() 
{
    //Game Window
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "PF Space Invaders!");
    InitAudioDevice(); //This function sets up audio system and prepares it to be used in game
    
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0 ,0); // loads the font into GPU memory
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    
    SetTargetFPS(60); //Game speed depends on these frame-rates else computer will run it as fast as possible
   
    Menu menu;
    Game game;
    MenuState currentState = MenuState::MAIN_MENU;

    //Game Loop
    while(WindowShouldClose() == false) //while  window is not closed
    {

        if (currentState == MenuState::MAIN_MENU) 
        {
            BeginDrawing();
            ClearBackground(grey);
            menu.Draw();
            currentState = menu.HandleInput();
            EndDrawing();
        }
        else if (currentState == MenuState::GAME) 
        {
            game.enterPlayerName();
            UpdateMusicStream(game.music);
            game.HandleInput();
            game.Update();
            BeginDrawing(); //Draws a blank canvas
            ClearBackground(grey); //Previous frame's graphics are wiped clean and new frame can be drawn
            DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
            DrawLineEx({25, 730}, {775, 730}, 3, yellow); // {}, {} --> strating point and ending point, 3 --> thickness
            if (game.run)
            {
                DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
            }
            else{
                DrawTextEx(font, "Game Over", {570, 740}, 34, 2, yellow);
            }

            float x = 50.0;
            for (int i = 0; i < game.lives; i++)
            {
                DrawTextureV(spaceshipImage, {x, 745}, WHITE); // x depends of image, if first --> 50 pixels, 2nd --> 100 pixels, 3rd --> 150
                x += 50;
            }

            DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
            std::string scoreText = FormatWithLeadingZeros(game.score, 5);
            DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow); // function expects a string we used c_str method coverts int -> string
            
            DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
            
            std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
            DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);
            game.Draw();
            EndDrawing(); //Ends the canvas

            if (!game.run){
                DrawText("Press Enter to play again", 50, 740, 15, WHITE);
                DrawText("Press backspace to return to Main Menu", 50, 760, 15, WHITE);
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    currentState = MenuState::MAIN_MENU;
                }
            }
        }
        else if (currentState == MenuState::LEADERBOARD) 
        {
            BeginDrawing();
            ClearBackground(grey);
            Leaderboard leaderboard;
            auto scores = leaderboard.GetScores();

            int textWidth = MeasureText("LEADER-BOARD", 34);

            DrawText("LEADER-BOARD", (GetScreenWidth() - textWidth) / 2, 150, 34, WHITE);
            game.loadScoreFromFile();
            DrawText("Press backspace to return to Main Menu", 180, 700, 20, WHITE);

            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                currentState = MenuState::MAIN_MENU;
            }
            EndDrawing();
        }
    }
   CloseWindow();
   CloseAudioDevice();
}