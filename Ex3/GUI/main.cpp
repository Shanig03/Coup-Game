#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Button.hpp"
#include "windowManager.hpp"

#include "../src/Game.hpp"
#include "../src/Player.hpp"
#include "../src/Governor.hpp"
#include "../src/Baron.hpp"
#include "../src/General.hpp"
#include "../src/Merchant.hpp"
#include "../src/Judge.hpp"
#include "../src/Spy.hpp"

void updatePlayerStatusTexts(
    const std::vector<coup::Player*>& players,
    sf::Font& font,
    const std::string& currentTurnPlayerName,
    bool isSpyTurn,
    std::vector<sf::Text*>& playerStatusTexts,
    float windowWidth) {

    for (auto txt : playerStatusTexts) delete txt;
    playerStatusTexts.clear();

    float startY = 120.f;
    float spacingY = 50.f;
    unsigned int fontSize = 30;

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& p = players[i];
        std::string coinsStr = isSpyTurn || currentTurnPlayerName == p->getName()
                               ? std::to_string(p->coins())
                               : "hidden";

        std::string line = p->getName() + " | " + p->getRole() + " | Coins: " + coinsStr;

        sf::Text* text = new sf::Text(line, font, fontSize);
        text->setFillColor(p->getName() == currentTurnPlayerName ? sf::Color::Yellow : sf::Color::White);
        text->setStyle(p->getName() == currentTurnPlayerName ? sf::Text::Bold : sf::Text::Regular);

        sf::FloatRect textBounds = text->getLocalBounds();
        float originX = std::round(textBounds.left + textBounds.width / 2.f);
        float originY = std::round(textBounds.top + textBounds.height / 2.f);
        text->setOrigin(originX, originY);
        float posX = std::round(windowWidth / 2.f);
        float posY = std::round(startY + i * spacingY);
        text->setPosition(posX, posY);

        playerStatusTexts.push_back(text);
    }
}

void showArrestPopup(sf::Font& font, coup::Player* currentPlayer, const std::vector<coup::Player*>& players) {
    // Increased height from 300 to 420 to fit 6 buttons comfortably (6 * 60 = 360 + extra for title)
    sf::RenderWindow popup(sf::VideoMode(300, 420), "Choose Player to Arrest", sf::Style::Titlebar | sf::Style::Close);

    std::vector<Button> playerButtons;
    float x = 50.f;
    float y = 60.f;  // start a bit lower to leave space for title
    float buttonHeight = 40.f;
    float buttonSpacing = 60.f;

    for (coup::Player* p : players) {
        if (p != currentPlayer && p->getAlive()) {
            Button b(x, y, 200.f, buttonHeight, p->getName());  
            b.setFont(font);
            playerButtons.push_back(b);
            y += buttonSpacing;  
        }
    }

    sf::Text title("Choose a player to arrest", font, 24);
    title.setFillColor(sf::Color::White);

    // Center the title horizontally
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(popup.getSize().x / 2.f, 25.f);  // Top middle with some margin

    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = popup.mapPixelToCoords(sf::Mouse::getPosition(popup));
                for (auto& btn : playerButtons) {
                    if (btn.isClicked(mousePos)) {
                        std::string selectedName = btn.getText();

                        // Find the player with this name
                        for (coup::Player* target : players) {
                            if (target->getName() == selectedName) {
                                currentPlayer->arrest(*target);
                                break;
                            }
                        }

                        popup.close(); // Close after selecting
                        break;
                    }
                }
            }
        }

        popup.clear(sf::Color(50, 50, 50));
        popup.draw(title);
        for (auto& btn : playerButtons) {
            btn.draw(popup);
        }
        popup.display();
    }
}

void showSanctionPopup(sf::Font& font, coup::Player* currentPlayer, const std::vector<coup::Player*>& players) {
    // Increased height from 300 to 420 to fit 6 buttons comfortably (6 * 60 = 360 + extra for title)
    sf::RenderWindow popup(sf::VideoMode(300, 420), "Choose Player to Sanction", sf::Style::Titlebar | sf::Style::Close);

    std::vector<Button> playerButtons;
    float x = 50.f;
    float y = 60.f;  
    float buttonHeight = 40.f;
    float buttonSpacing = 60.f;

    for (coup::Player* p : players) {
        if (p != currentPlayer && p->getAlive()) {
            Button b(x, y, 200.f, buttonHeight, p->getName());  
            b.setFont(font);
            playerButtons.push_back(b);
            y += buttonSpacing;  
        }
    }

    sf::Text title("Choose a player to Sanction", font, 24);
    title.setFillColor(sf::Color::White);

    // Center the title horizontally
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(popup.getSize().x / 2.f, 25.f);  // Top middle with some margin

    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = popup.mapPixelToCoords(sf::Mouse::getPosition(popup));
                for (auto& btn : playerButtons) {
                    if (btn.isClicked(mousePos)) {
                        std::string selectedName = btn.getText();

                        // Find the player with this name
                        for (coup::Player* target : players) {
                            if (target->getName() == selectedName) {
                                try{
                                    currentPlayer->sanction(*target);
                                }
                                catch(const std::exception& e){
                                    std::cerr << e.what() << '\n';
                                }
                                break;
                            }
                        }

                        popup.close(); // Close after selecting
                        break;
                    }
                }
            }
        }

        popup.clear(sf::Color(50, 50, 50));
        popup.draw(title);
        for (auto& btn : playerButtons) {
            btn.draw(popup);
        }
        popup.display();
    }
}

void showCoupPopup(sf::Font& font, coup::Player* currentPlayer, const std::vector<coup::Player*>& players) {
    // Increased height from 300 to 420 to fit 6 buttons comfortably (6 * 60 = 360 + extra for title)
    sf::RenderWindow popup(sf::VideoMode(300, 420), "Choose Player to Coup", sf::Style::Titlebar | sf::Style::Close);

    std::vector<Button> playerButtons;
    float x = 50.f;
    float y = 60.f;  
    float buttonHeight = 40.f;
    float buttonSpacing = 60.f;

    for (coup::Player* p : players) {
        if (p != currentPlayer && p->getAlive()) {
            Button b(x, y, 200.f, buttonHeight, p->getName());  
            b.setFont(font);
            playerButtons.push_back(b);
            y += buttonSpacing;  
        }
    }

    sf::Text title("Choose a player to Coup", font, 24);
    title.setFillColor(sf::Color::White);

    // Center the title horizontally
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(popup.getSize().x / 2.f, 25.f);  // Top middle with some margin

    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = popup.mapPixelToCoords(sf::Mouse::getPosition(popup));
                for (auto& btn : playerButtons) {
                    if (btn.isClicked(mousePos)) {
                        std::string selectedName = btn.getText();

                        // Find the player with this name
                        for (coup::Player* target : players) {
                            if (target->getName() == selectedName) {
                                try{
                                    currentPlayer->coup(*target);
                                }
                                catch(const std::exception& e){
                                    std::cerr << e.what() << '\n';
                                }
                                break;
                            }
                        }

                        popup.close(); // Close after selecting
                        break;
                    }
                }
            }
        }

        popup.clear(sf::Color(50, 50, 50));
        popup.draw(title);
        for (auto& btn : playerButtons) {
            btn.draw(popup);
        }
        popup.display();
    }
}


int main() {
    coup::Game game1;
    WindowManager wm(800, 600, "Coup Game");

    if (!wm.loadBackground("background_image.png") || !wm.loadFont("AmericanCaptain-MdEY.otf"))
        return -1;

    std::string playerName;
    std::vector<std::string> players;
    std::vector<sf::Text*> playerTexts;

    sf::RectangleShape inputBox(sf::Vector2f(200, 40));
    inputBox.setFillColor(sf::Color(139, 69, 19));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(250, 180);

    sf::Text inputText("", wm.getFont(), 20);
    inputText.setPosition(260, 185);
    inputText.setFillColor(sf::Color::Black);

    sf::Text* label = new sf::Text("Add Players", wm.getFont(), 50);
    label->setPosition(295, 60);
    label->setFillColor(sf::Color::White);

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

    bool startGameNow = false;

    wm.run(
        [&](sf::Event& event) {
            if (event.type == sf::Event::Closed)
                wm.getWindow().close();

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
                    if (std::find(players.begin(), players.end(), playerName) == players.end()) {
                        players.push_back(playerName);
                        sf::Text* playerText = new sf::Text(playerName, wm.getFont(), 24);
                        playerText->setFillColor(sf::Color::White);
                        playerText->setPosition(250, 240 + playerTexts.size() * 30);
                        playerTexts.push_back(playerText);
                        wm.addText(playerText);
                        std::cout << "Player added: " << playerName << std::endl;
                    }
                    playerName = "";
                    inputText.setString("");
                }

                if (startGameButton->isClicked(mousePos)) {
                    std::cout << "Starting game with " << players.size() << " players.\n";
                    game1.assignRandomRoles(players);
                    game1.startGame();
                    startGameNow = true;
                    wm.getWindow().close();
                }
            }
        },
        []() {},
        [](sf::RenderWindow&) {}
    );

    for (auto pt : playerTexts) delete pt;
    delete label;
    delete addButton;
    delete startGameButton;

    if (startGameNow) {
        WindowManager gameWindow(800, 600, "Coup Game");

        if (!gameWindow.loadBackground("background_image.png") || !gameWindow.loadFont("AmericanCaptain-MdEY.otf"))
            return -1;

        std::vector<Button*> actionButtons;
        std::vector<std::string> actions = {"Gather", "Tax", "Arrest", "Bribe", "Sanction", "Coup"};

        float buttonWidth = 100, buttonHeight = 40, spacingX = 40, spacingY = 30;
        float startX = (gameWindow.getWindow().getSize().x - (3 * buttonWidth + 2 * spacingX)) / 2;
        float startY = 400;

        for (size_t i = 0; i < actions.size(); ++i) {
            int x = static_cast<int>(startX + (i % 3) * (buttonWidth + spacingX));
            int y = static_cast<int>(startY + (i / 3) * (buttonHeight + spacingY));

            Button* actionBtn = new Button(x, y, buttonWidth, buttonHeight, actions[i]);
            actionBtn->setButtonColor(sf::Color::White);
            actionBtn->setFont(gameWindow.getFont());
            gameWindow.addButton(actionBtn);
            actionButtons.push_back(actionBtn);
        }

        sf::Text turnLabel;
        turnLabel.setFont(gameWindow.getFont());
        turnLabel.setCharacterSize(24);
        turnLabel.setFillColor(sf::Color::White);
        turnLabel.setString("Current turn: None");
        sf::FloatRect textRect = turnLabel.getLocalBounds();
        turnLabel.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        turnLabel.setPosition(gameWindow.getWindow().getSize().x / 2.f, 50);
        gameWindow.addText(&turnLabel);

        std::vector<sf::Text*> playerStatusTexts;

        gameWindow.run(
            [&](sf::Event& event) {
                if (event.type == sf::Event::Closed)
                    gameWindow.getWindow().close();

                if (event.type == sf::Event::MouseButtonPressed) {
                    auto mousePos = gameWindow.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameWindow.getWindow()));
                    for (size_t i = 0; i < actionButtons.size(); ++i) {
                        if (actionButtons[i]->isClicked(mousePos)) {
                            std::string action = actions[i];
                            std::cout << "Action chosen: " << action << std::endl;

                            coup::Player* currentPlayer = game1.getCurrentPlayer();
                            if (currentPlayer != nullptr) {
                                if (action == "Gather") {
                                    currentPlayer->gather();
                                }
                                if (action == "Tax") { // Not working perfect
                                    currentPlayer->tax(); 
                                }
                                if (action == "Bribe") { // Not working perfect
                                    try{
                                        currentPlayer->bribe();
                                    }
                                    catch(const std::exception& e){
                                        std::cerr << e.what() << '\n';
                                    }
                                }
                                if (action == "Arrest") {
                                    std::vector<coup::Player*> players = game1.getPlayers();
                                    showArrestPopup(gameWindow.getFont(), currentPlayer, players);
                                }
                                if (action == "Sanction") {
                                    std::vector<coup::Player*> players = game1.getPlayers();
                                    showSanctionPopup(gameWindow.getFont(), currentPlayer, players);
                                }
                                if (action == "Coup") {
                                    currentPlayer->gather();
                                    std::vector<coup::Player*> players = game1.getPlayers();
                                    showCoupPopup(gameWindow.getFont(), currentPlayer, players);
                                }
                            }

                        }
                    }
                }

            },
            [&]() {
                std::string currentPlayer = game1.turn();
                std::string turnText = "Current turn: " + currentPlayer;
                turnLabel.setString(turnText);

                sf::FloatRect textRect = turnLabel.getLocalBounds();
                turnLabel.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
                turnLabel.setPosition(gameWindow.getWindow().getSize().x / 2.f, 50);

                bool isSpyTurn = (game1.getCurrentPlayer()->getRole() == "Spy");

                updatePlayerStatusTexts(game1.getPlayers(), gameWindow.getFont(),
                        currentPlayer, isSpyTurn, playerStatusTexts,
                        static_cast<float>(gameWindow.getWindow().getSize().x));

            },
            [&](sf::RenderWindow& win) {
                for (auto txt : playerStatusTexts) {
                    win.draw(*txt);
                }
            }
        );

        for (auto btn : actionButtons) delete btn;
        for (auto txt : playerStatusTexts) delete txt;
    }

    return 0;
}
