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

    std::string Game::winner(){
        std::string winnerName;
        int aliveCount = 0;

        for (Player* p : playersList) {
            if (p->getAlive()) {
                aliveCount++;
                winnerName = p->getName();
            }
        }

        if (aliveCount == 1) {
            return winnerName;
        }

        throw std::runtime_error("Game is not over yet. No winner.");
    
    }


    void Game::moveTurnTo(const std::string& role, Player& p) {
        std::string originalTurn = this->currPlayer;
        int originalIndex = -1;
    
        // Find the index of the original player
        for (size_t i = 0; i < playersList.size(); ++i) {
            if (playersList[i]->getName() == originalTurn) {
                originalIndex = static_cast<int>(i);
                break;
            }
        }
    
        if (originalIndex == -1) {
            throw std::runtime_error("Original player not found.");
        }
    
        bool undone = false;
    
        // Loop through players with the given role (excluding original actor)
        for (size_t i = 1; i < playersList.size(); ++i) {
            size_t idx = (originalIndex + i) % playersList.size();
            Player* candidate = playersList[idx];
    
            if (!candidate->getAlive() || candidate->getName() == originalTurn) {
                continue;
            }
    
            if (candidate->getRole() == role) {
                this->currPlayer = candidate->getName();  // Temporarily give them the turn
    
                // If the player decides to undo, stop
                if (candidate->undo(p)) {
                    undone = true;
                    break;
                }
            }
        }
    
        // Always return turn to next alive player after the original actor
        for (size_t i = 1; i <= playersList.size(); ++i) {
            size_t idx = (originalIndex + i) % playersList.size();
            if (playersList[idx]->getAlive()) {
                this->currPlayer = playersList[idx]->getName();
                return;
            }
        }
    
        throw std::runtime_error("No alive player to pass turn to.");
    }



}