// Email: shanig7531@gmail.com

#include "Judge.hpp"

namespace coup {
    Judge::Judge(Game& g, const std::string& name): Player(g, name, "Judge"){}


    bool Judge::undo(Player& player){
        if (!this->isAlive){
            throw std::runtime_error("Judge is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        // Need to make it fit the GUI
        std::cout << this->getName() << ", " << player.getName() << " performed a Bribe action. "
              << "Do you want to undo it? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            player.setAnotherTurn(false);  
            std::cout << player.getName() << " Bribe action was canceled. " << std::endl;
            return true;  // Indicates undo happened
        }
        
        return false;
    }

}