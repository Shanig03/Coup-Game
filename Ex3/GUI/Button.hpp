#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text);

    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePos);
    void setButtonColor(const sf::Color& color);  // Setter to change the button color
    void setFont(const sf::Font& newFont);


private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text buttonText;
};

#endif
