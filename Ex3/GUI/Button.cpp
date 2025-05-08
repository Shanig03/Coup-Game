#include "Button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, const std::string& text) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(100, 100, 250));  // Default color

    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::Black);  // Visible on white
}

void Button::setFont(const sf::Font& newFont) {
    font = newFont;
    buttonText.setFont(font);

    // Center the text inside the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    sf::FloatRect shapeBounds = shape.getGlobalBounds();

    buttonText.setPosition(
        shapeBounds.left + (shapeBounds.width - textBounds.width) / 2 - textBounds.left,
        shapeBounds.top + (shapeBounds.height - textBounds.height) / 2 - textBounds.top
    );
}

void Button::setButtonColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}
