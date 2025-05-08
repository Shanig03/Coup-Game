#include "GameGUI.hpp"
#include <iostream>

GameGUI::GameGUI() : window(sf::VideoMode(800, 600), "Coup Game") {
    if (!window.isOpen()) {
        std::cerr << "Error: Window failed to open!" << std::endl;
        exit(EXIT_FAILURE);
    }
    setupButtons();
}

void GameGUI::setupButtons() {
    // Define buttons with position, size, and label
    buttons.emplace_back(50, 500, 100, 40, "Income");
    buttons.emplace_back(170, 500, 100, 40, "Foreign Aid");
    buttons.emplace_back(290, 500, 100, 40, "Coup");
    buttons.emplace_back(410, 500, 100, 40, "Tax");
}

void GameGUI::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void GameGUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (auto& button : buttons) {
                if (button.isClicked(mousePos)) {
                    std::cout << "Button clicked: " << button.isClicked(mousePos) << "\n";
                    // Handle action here (e.g., trigger the corresponding game action)
                }
            }
        }
    }
}

void GameGUI::render() {
    window.clear(sf::Color(30, 30, 30));  // Dark background
    for (auto& button : buttons) {
        button.draw(window);  // Draw each button on the window
    }
    window.display();  // Display the window contents
}
