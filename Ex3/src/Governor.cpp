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
        if (!this->isAlive){
            throw std::runtime_error("Governor is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        // Need to make it fit the GUI
        std::cout << this->getName() << ", " << player.getName() << " performed a tax action. "
              << "Do you want to undo it? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            player.decreaseCoins(2);  // or your actual undo logic
            return true;  // Indicates undo happened
        }
        
        return false;
    }

    /*
    bool Governor::undo(Player& player) {
    if (!this->isAlive) {
        throw std::runtime_error("Governor is out of the game.");
    }
    if (!player.getAlive()) {
        throw std::runtime_error("Target player is out of the game.");
    }

    if (!hasAnsweredUndo()) {
        // Wait for GUI to provide an answer
        return false; // Not ready yet
    }

    if (wantsToUndo()) {
        player.decreaseCoins(2); // Perform the undo
    }

    resetUndoState();  // Prepare for next time
    return true; // Finished the undo phase
}
    */

}