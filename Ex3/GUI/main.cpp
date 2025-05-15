#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.hpp"
#include "windowManager.hpp"

int main() {

    WindowManager wm(800, 600, "Coup Game");

    if (!wm.loadBackground("background_image.png") || !wm.loadFont("AmericanCaptain-MdEY.otf"))
        return -1;

    std::string playerName;
    std::vector<std::string> players;
    std::vector<sf::Text*> playerTexts;

    // Input box and input text
    sf::RectangleShape inputBox(sf::Vector2f(200, 40));
    inputBox.setFillColor(sf::Color(139, 69, 19));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(250, 180);

    sf::Text inputText("", wm.getFont(), 20);
    inputText.setPosition(260, 185);
    inputText.setFillColor(sf::Color::Black);

    // Label
    sf::Text* label = new sf::Text("Add Players", wm.getFont(), 50);
    label->setPosition(295, 60);
    label->setFillColor(sf::Color::White);

    // Buttons
    Button* addButton = new Button(460, 180, 100, 40, "Add");
    addButton->setButtonColor(sf::Color::White);
    addButton->setFont(wm.getFont());

    Button* startGameButton = new Button(350, 450, 100, 40, "Start Game");
    startGameButton->setButtonColor(sf::Color::White);
    startGameButton->setFont(wm.getFont());

    wm.addDrawable(&inputBox);
    wm.addText(&inputText);
    wm.addText(label);
    wm.addButton(addButton);
    wm.addButton(startGameButton);

    wm.run(
        [&](sf::Event& event) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !playerName.empty()) {
                    playerName.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != 13) {
                    playerName += static_cast<char>(event.text.unicode);
                }
                inputText.setString(playerName);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = wm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(wm.getWindow()));

                if (addButton->isClicked(mousePos) && !playerName.empty()) {
                    players.push_back(playerName);

                    sf::Text* playerText = new sf::Text(playerName, wm.getFont(), 24);
                    playerText->setFillColor(sf::Color::White);
                    playerText->setPosition(250, 240 + static_cast<int>(playerTexts.size()) * 30);
                    playerTexts.push_back(playerText);
                    wm.addText(playerText);

                    playerName = "";
                    inputText.setString("");
                    std::cout << "Player added: " << players.back() << std::endl;
                }

                if (startGameButton->isClicked(mousePos)) {
                    std::cout << "Starting game with " << players.size() << " players." << std::endl;
                }
            }
        },
        []() {
            // Optional logic updates
        }
    );

    return 0;
}
