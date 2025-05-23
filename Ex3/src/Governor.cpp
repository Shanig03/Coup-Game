// Email: shanig7531@gmail.com

#include "Governor.hpp"

namespace coup {


    Governor::Governor(Game& g, const std::string& name) : Player(g, name, "Governor"){}

    void Governor::tax(){
        this->startTurn();
    
        if(!this->isSanctioned){
            this->coinsAmount += 3; // Adds 3 coins to the Governor
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    
    }

    bool Governor::undo(Player& player){
        // Check if both players are alive.
        if (!this->isAlive){
            throw std::runtime_error("Governor is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        player.decreaseCoins(2);  // undo the other player tax action.
        return true; 
    }

}