#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Coup Game");

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background_image.png")) {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load custom font (American Captain .otf)
    sf::Font font;
    if (!font.loadFromFile("AmericanCaptain-MdEY.otf")) {
        std::cerr << "Error loading custom font!" << std::endl;
        return -1;
    }

    // Input box
    sf::RectangleShape inputBox(sf::Vector2f(200, 40));
    inputBox.setFillColor(sf::Color(139, 69, 19));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(250, 180);

    // Input text
    sf::Text inputText("", font, 20);
    inputText.setPosition(260, 185);
    inputText.setFillColor(sf::Color::Black);

    std::string playerName = "";
    std::vector<std::string> players;
    std::vector<sf::Text> playerTexts;

    // Buttons
    Button addButton(460, 180, 100, 40, "Add");
    addButton.setButtonColor(sf::Color::White);
    addButton.setFont(font);

    Button startGameButton(350, 450, 100, 40, "Start Game");
    startGameButton.setButtonColor(sf::Color::White);
    startGameButton.setFont(font);

    // Label
    sf::Text label("Add Players", font, 50);
    label.setPosition(295, 60);
    label.setFillColor(sf::Color::White);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !playerName.empty()) {
                    playerName.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != 13) {
                    playerName += static_cast<char>(event.text.unicode);
                }
                inputText.setString(playerName);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (addButton.isClicked(mousePos) && !playerName.empty()) {
                    players.push_back(playerName);

                    sf::Text playerText(playerName, font, 24);
                    playerText.setFillColor(sf::Color::White);
                    playerText.setPosition(250, 240 + static_cast<int>(playerTexts.size()) * 30);
                    playerTexts.push_back(playerText);

                    playerName = "";
                    inputText.setString("");
                    std::cout << "Player added: " << players.back() << std::endl;
                }

                if (startGameButton.isClicked(mousePos)) {
                    std::cout << "Starting game with " << players.size() << " players." << std::endl;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(label);
        window.draw(inputBox);
        window.draw(inputText);
        addButton.draw(window);
        startGameButton.draw(window);
        for (const auto& playerText : playerTexts)
            window.draw(playerText);
        window.display();
    }

    return 0;
}
