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

        // Need to make it fit the GUI
        std::cout << this->getName() << ", " << player.getName() << " got Couped. "
              << "Do you want to undo it? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            this->decreaseCoins(5);
            player.setUndoCoup(true);
            return true;  // Indicates undo happened
        }
        
        return false;

    }



}