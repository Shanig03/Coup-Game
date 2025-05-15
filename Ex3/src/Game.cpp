#include "Game.hpp"
#include <random>
#include <ctime>

//#include "Governor.hpp"
//#include "Baron.hpp"
//#include "Spy.hpp"


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

    /*
    A function to pass the turnes by the order of the players list 
    only for players that are still in the game
    */
    void Game::passTurns(){
        // Find current player's index
        size_t index = 0;
        Player* current = nullptr;

        for (size_t i = 0; i < playersList.size(); ++i) {
            if (playersList[i]->getName() == currPlayer) {
                index = i;
                current = playersList[i];
                break;
            }
        }

        if (current == nullptr) {
            throw std::runtime_error("Current player not found.");
        }
        
        // Check if current player has anotherTurn flag set
        if (current->hasAnotherTurn()) {
            std::cout << "Player " << current->getName() << " has another turn.\n";
            current->setAnotherTurn(false);
            return; // Don't change turn
        }

        // Normal turn passing
        size_t total = playersList.size();
        for (size_t offset = 1; offset <= total; ++offset) {
            Player* nextPlayer = playersList[(index + offset) % total];
            std::cout << "Checking player: " << nextPlayer->getName()
                    << ", alive? " << nextPlayer->getAlive() << std::endl;

            if (nextPlayer->getAlive()) {
                // In the start of each row the arrested bool will go back to false, so they can be arrested again.
                if (((index + offset) % total) < index){
                    for (size_t i = 0; i < playersList.size(); ++i) {
                        playersList[i]->setArrested(false); // Reset to false
                        
                    }
                }
                
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

        for (Player* candidate : playersList) {
            if (!candidate->getAlive() || candidate->getName() == originalTurn) {
                continue;
            }

            if (candidate->getRole() == role) {
                bool result = candidate->undo(p);  // ask the player if they want to undo
                if (result) {
                    break;  // only break if someone actually undoes
                }
            }
        }
    }


    

/* 
    std::string Game::getCurrPlayer(){
        return this->currPlayer;
    }

    std::vector<Player*> Game::assignRandomRoles(const std::vector<std::string>& playerNames) {        
        std::vector<Player*> players;
        std::vector<std::string> roles = {"Spy", "Judge", "Baron", "General", "Merchant", "Governor"};
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        for (const std::string& name : playerNames) {
            std::string role = roles[std::rand() % roles.size()];

            if (role == "Spy") {
                players.push_back(Spy(*this, name));
            } else if (role == "Judge") {
                players.push_back(Judge(*this, name));
            } else if (role == "Baron") {
                players.push_back(Baron(*this, name));
            } else if (role == "General") {
                players.push_back(General(*this, name));
            } else if (role == "Merchant") {
                players.push_back(Merchant(*this, name));
            } else if (role == "Governor") {
                players.push_back(Governor(*this, name));
            }
        }

        return players;
    }
*/

}