#include "Game.hpp"


namespace coup {

    Game::Game(){}

    void Game::addPlayer(Player* p){
        if (playersList.size() >= 6) {
            throw std::runtime_error("Can't add more than 6 players.");
        }

        // Check for duplicate by name
        for (Player* existing : playersList) {
            if (existing->getName() == p->getName()) {
                std::cout << "Player already exists." << std::endl;
                return;
            }
        }

        this->playersList.push_back(p);
    }

    const std::vector<std::string> Game::players(){

        std::vector<std::string> playersNames;

        for (Player* p : playersList) {
            if (p->getAlive()) {
                playersNames.push_back(p->getName());
            }
        }

        return playersNames;
    }

    const std::string Game::turn(){
        return this->currPlayer;
    }

    void Game::passTurns(){
        // Find current player's index
        size_t index = 0;
        for (size_t i = 0; i < playersList.size(); ++i) {
            if (playersList[i]->getName() == currPlayer) {
                index = i;
                break;
            }
        }

        size_t total = playersList.size();
        for (size_t offset = 1; offset <= total; ++offset) {
            Player* nextPlayer = playersList[(index + offset) % total];
            if (nextPlayer->getAlive()) {
                currPlayer = nextPlayer->getName();
                return;
            }
        }

        throw std::runtime_error("No alive players to pass turn to.");
    }

    void Game::startGame(){
        for (Player* p : playersList) {
            if (p->getAlive()) {
                this->currPlayer = p->getName();
                return;
            }
        }
        throw std::runtime_error("No active players to start the game.");
    }

    void Game::removePlayer(std::string name){
        for (Player* p : playersList) {
            if (p->getName() == name) {
                p->setAlive(false);
                std::cout << "Eliminated: " << name << std::endl;
                return;
            }
        }
        std::cout << "Player not found: " << name << std::endl;
    }



}