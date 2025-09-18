#include "Menu.hpp"

Menu::Menu() {
    newButton = {250, 250, 250, 50};  // Position and size for "New" button
    leaderboardButton = {250, 350, 250, 50};  // Position and size for "Leaderboard" button
}

void Menu::Draw() {
    DrawText("PF Space Invaders!", 180, 150, 40, WHITE);
    DrawRectangleRec(newButton, DARKGRAY);
    DrawText("New", newButton.x + 90, newButton.y + 10, 30, WHITE);
    DrawRectangleRec(leaderboardButton, DARKGRAY);
    DrawText("Leaderboard", leaderboardButton.x + 50, leaderboardButton.y + 10, 20, WHITE);
}

MenuState Menu::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, newButton)) {
            return MenuState::GAME;
        } else if (CheckCollisionPointRec(mousePosition, leaderboardButton)) {
            return MenuState::LEADERBOARD;
        }
    }
    return MenuState::MAIN_MENU;
}
