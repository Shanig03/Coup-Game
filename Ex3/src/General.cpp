// Email: shanig7531@gmail.com

#include "General.hpp"

namespace coup {

    
    General::General(Game& g, const std::string& name) : Player(g, name, "General"){}

    bool General::undo(Player& player){
        // Check if both of the players alive.
        if (!this->isAlive){
            throw std::runtime_error("General is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        // Check that he have at least 5 coins so he can use the undo.
        if (this->coins() < 5){
            throw std::runtime_error("General doesnt have 5 coins to undo.");
        }
        
        this->decreaseCoins(5); // The action cost 5 coins.
        player.setUndoCoup(true); // Set the undoCoup flag of the player to true.
        return true;
    }
}