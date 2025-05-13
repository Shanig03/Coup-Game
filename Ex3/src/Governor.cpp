#include "Governor.hpp"

namespace coup {

    Governor::Governor(Game& g, const std::string& name) : Player(g, name, "Governor"){}

    void Governor::tax(){
        if (!this->isAlive){
            throw std::runtime_error("Player is out of the game.");
        }
        if (this->currGame.turn() != this->getName()){
            throw std::runtime_error("Can't play out of your turn.");
        }
        if(!this->isSanctioned){
            this->coinsAmount += 3; // Adds 3 coins to the Governor
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    
    }

    bool Governor::undo(Player& player){
        if (!this->isAlive){
            throw std::runtime_error("Governor is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        // Need to add the option to choose if to undo tax action
        player.decreaseCoins(2);

        return true;
    }

}