#include "Button.hpp"
#include <iostream>
#include <cmath>  // for std::round

Button::Button(float x, float y, float width, float height, const std::string& text){
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(100, 100, 250));  // Default color

    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::Black);  // Visible on white

    centerText();
}

void Button::setFont(const sf::Font& newFont) {
    buttonText.setFont(newFont);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::Black);

    centerText();
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

std::string Button::getText() const {
    return buttonText.getString();
}

void Button::centerText() {
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    sf::FloatRect shapeBounds = shape.getGlobalBounds();

    float posX = std::round(shapeBounds.left + (shapeBounds.width - textBounds.width) / 2.f - textBounds.left);
    float posY = std::round(shapeBounds.top + (shapeBounds.height - textBounds.height) / 2.f - textBounds.top);

    buttonText.setPosition(posX, posY);
}

/*
void Button::setEnabled(bool e) {
    enabled = e;
    if (enabled)
        setButtonColor(sf::Color::White);       // enabled color
    else
        setButtonColor(sf::Color(150, 150, 150)); // disabled color
}


bool Button::isEnabled() const {
    return enabled;
}
*/