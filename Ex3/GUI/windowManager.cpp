#include "windowManager.hpp"
#include <iostream>

WindowManager::WindowManager(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {}

bool WindowManager::loadBackground(const std::string& filename) {
    if (!backgroundTexture.loadFromFile(filename)) {
        std::cerr << "Error loading background image!" << std::endl;
        return false;
    }
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
    return true;
}

bool WindowManager::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font!" << std::endl;
        return false;
    }
    return true;
}

void WindowManager::addButton(Button* button) {
    buttons.push_back(button);
}

void WindowManager::addText(sf::Text* text) {
    texts.push_back(text);
}

void WindowManager::addDrawable(sf::Drawable* drawable) {
    drawables.push_back(drawable);
}

void WindowManager::run(std::function<void(sf::Event&)> eventHandler,
                        std::function<void()> logicHandler,
                        std::function<void(sf::RenderWindow&)> customDraw) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            eventHandler(event);
        }

        logicHandler();

        window.clear();
        window.draw(background);
        for (auto& d : drawables) window.draw(*d);
        for (auto& t : texts) window.draw(*t);
        for (auto& b : buttons) b->draw(window);

        // 👇 Your custom drawing (e.g., player sf::Text objects)
        customDraw(window);

        window.display();
    }
}


sf::Font& WindowManager::getFont() {
    return font;
}

sf::RenderWindow& WindowManager::getWindow() {
    return window;
}
