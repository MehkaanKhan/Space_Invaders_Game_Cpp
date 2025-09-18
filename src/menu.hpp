#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>

enum class MenuState { // representing a collection of values
    MAIN_MENU, //enumerator polluting the global namespace, making the code more organized 
            //and reducing the chance of naming conflicts
    GAME,
    LEADERBOARD
};

class Menu {
public:
    Menu();
    void Draw();
    MenuState HandleInput();
private:
    Rectangle newButton;
    Rectangle leaderboardButton;
};

#endif
