#include "Game.hpp"

namespace coup {

    Game::Game(){}

    void Game::addPlayer(const std::string name){
        if (std::find(this->playersList.begin(), this->playersList.end(), name) == this->playersList.end()) {
            this->playersList.push_back(name);
        } else {
            std::cout << "Player already exists." << std::endl;
        }
    }

    const std::vector<std::string> Game::players(){
        return this->playersList;
    }

    const std::string Game::turn(){
        return this->currPlayer;
    }

    int& Game::getJackpot(){
        return this->jackpot;
    }

    void Game::passTurns(){
        auto it = std::find(this->playersList.begin(), this->playersList.end(), this->currPlayer);

        if (it == this->playersList.end()) {
            // If current player is not set or not found, start with the first player
            if (!playersList.empty()) {
                this->currPlayer = playersList[0];
            }
        } else {
            // Move to the next player, wrap around if at the end
            size_t index = std::distance(playersList.begin(), it);
            this->currPlayer = playersList[(index + 1) % playersList.size()];
        }
    }


}