// Email: shanig7531@gmail.com

#include "General.hpp"

namespace coup {
    General::General(Game& g, const std::string& name) : Player(g, name, "General"){}

    bool General::undo(Player& player){
        if (!this->isAlive){
            throw std::runtime_error("General is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        if (this->coins() < 5){
            throw std::runtime_error("General doesnt have 5 coins to undo.");
        }
        
        this->decreaseCoins(5);
        player.setUndoCoup(true);
        return true;  // Indicates undo happened

    }



}