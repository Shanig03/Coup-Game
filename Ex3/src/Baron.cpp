// Email: shanig7531@gmail.com

#include "Baron.hpp"

namespace coup {


    Baron::Baron(Game& g, const std::string& name) : Player(g, name, "Baron"){}

    void Baron::invest(){
        // Check if the Baron is alive.
        if (!this->isAlive){
            throw std::runtime_error("This Baron is out of the game.");
        }

        // Must have at least 3 coins to invest 3 coins.
        if (this->coins() >= 3){
            this->coinsAmount += 3; // Invest 3 coins and gets 6 coins - overall gets 3 new coins
            std::cout << "The Baron invested 3 coins ang got 6 coins." << std::endl;
            this->currGame.passTurns(); // Count as a turn.
        }
    }

    void Baron::compensation(){
        // If this Baron got sanctioned.
        if (this->isSanctioned){
            this->coinsAmount++; // Gets 1 coin as a compensation.
            std::cout << "The Baron got compensation for the sanction." << std::endl;
        }

    }

}
