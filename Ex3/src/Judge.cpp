// Email: shanig7531@gmail.com

#include "Judge.hpp"

namespace coup {

    Judge::Judge(Game& g, const std::string& name): Player(g, name, "Judge"){}

    bool Judge::undo(Player& player){
        // Check if both players are alive.
        if (!this->isAlive){
            throw std::runtime_error("Judge is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        player.setAnotherTurn(false); // Set the anotherTurn flag of the other player to false.
        std::cout << player.getName() << " Bribe action was canceled. " << std::endl;
        return true; 
        
    }

}