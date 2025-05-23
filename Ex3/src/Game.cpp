// Email: shanig7531@gmail.com

#include "Game.hpp"
#include <random>
#include <ctime>


namespace coup {

    Game::Game(){
        this->currPlayer = "";
        this->playersList = std::vector<Player*>();
    }

    Game::~Game() {
        // Delete all th eplayers in the game.
        for (Player* p : playersList) {
            delete p;
        }
        playersList.clear(); 
    }

    void Game::addPlayer(Player* p){
        // Check that there are no more that 6 players.
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
        Player* current = nullptr;

        // Finds the current player in the players list.
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

        // Turn passing
        size_t total = playersList.size();
        for (size_t offset = 1; offset <= total; ++offset) {
            Player* nextPlayer = playersList[(index + offset) % total]; // Going in a loop.
            std::cout << "Checking player: " << nextPlayer->getName()
                    << ", alive? " << nextPlayer->getAlive() << std::endl;

            if (nextPlayer->getAlive()) {
                // In the start of each row the arrested bool will go back to false, so they can be arrested again.
                if (((index + offset) % total) < index){
                    for (size_t i = 0; i < playersList.size(); ++i) {
                        playersList[i]->setArrested(false); // Reset to false
                        
                    }
                }
                // Passing the turn to the next alive player that was found.
                currPlayer = nextPlayer->getName();
                return;
            }
        }

        throw std::runtime_error("No alive players to pass turn to.");
    }

    void Game::startGame(){
        // Set the current player to be the first in the list so the game can start.
        for (Player* p : playersList) {
            if (p->getAlive()) {
                this->currPlayer = p->getName();
                return;
            }
        }
        throw std::runtime_error("No active players to start the game.");
    }

    void Game::removePlayer(std::string name){
        // Looks for the name in the players list and set his alive status to false.
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

        // Count how many "alive" players are in the list.
        for (Player* p : playersList) {
            if (p->getAlive()) {
                aliveCount++;
                winnerName = p->getName();
            }
        }

        // If there is only one- he is the winner.
        if (aliveCount == 1) {
            return winnerName;
        }

        throw std::runtime_error("Game is not over yet. No winner.");
    }


    /*
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
    */

    std::vector<Player*> Game::roleList(const std::string& role) {
        std::vector<Player*> pList;

        // Look for all the players with the asked role and add them to a list.
        for (Player* candidate : playersList) {
            if (!candidate->getAlive()) {
                continue;
            }

            if (candidate->getRole() == role) {
                pList.push_back(candidate);
            }
        }
        return pList;
    }

    void Game::assignRandomRoles(const std::vector<std::string>& playerNames) {
        std::vector<std::string> roles = {"Governor", "Baron", "General", "Merchant", "Judge", "Spy"};

        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed 

        // Each name in the list gets a role and that its getting initiated as the role they got. 
        for (const std::string& name : playerNames) {
            std::string role = roles[std::rand() % roles.size()];
            Player* p = nullptr;

            if (role == "Governor") {
                p = new Governor(*this, name);
            } else if (role == "Baron") {
                p = new Baron(*this, name);
            } else if (role == "General") {
                p = new General(*this, name);
            } else if (role == "Merchant") {
                p = new Merchant(*this, name);
            } else if (role == "Judge") {
                p = new Judge(*this, name);
            } else if (role == "Spy") {
                p = new Spy(*this, name);
            }

            if (p != nullptr) {
                this->addPlayer(p);
                std::cout << "Assigned role " << role << " to player " << name << std::endl;
            }
        }
    }

    Player* Game::getCurrentPlayer(){
        Player* curr;
        // Looks for the current player by his name in the players list.
        for (int i = 0; i < this->playersList.size(); i++){
            if (playersList[i]->getName() == this->currPlayer){
                curr = playersList[i];
            }
        }
        return curr;
    }

    std::vector<Player*> Game::getPlayers(){
        return this->playersList;
    }


}