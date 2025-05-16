#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "Button.hpp"

class WindowManager {
public:
    WindowManager(unsigned int width, unsigned int height, const std::string& title);

    bool loadBackground(const std::string& filename);
    bool loadFont(const std::string& fontPath);

    void addButton(Button* button);
    void addText(sf::Text* text);
    void addDrawable(sf::Drawable* drawable);
    
    void run(std::function<void(sf::Event&)> eventHandler,
            std::function<void()> logicHandler,
            std::function<void(sf::RenderWindow&)> customDraw);
    
    sf::Font& getFont();
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Font font;

    std::vector<Button*> buttons;
    std::vector<sf::Text*> texts;
    std::vector<sf::Drawable*> drawables;
};

#endif
