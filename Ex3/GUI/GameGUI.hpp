#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"

class GameGUI {
public:
    GameGUI();
    void run();

private:
    sf::RenderWindow window;
    std::vector<Button> buttons;

    void handleEvents();
    void render();
    void setupButtons();
};

#endif
