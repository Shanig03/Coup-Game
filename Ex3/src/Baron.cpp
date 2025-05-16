// Email: shanig7531@gmail.com

#include "Baron.hpp"

namespace coup {


    Baron::Baron(Game& g, const std::string& name) : Player(g, name, "Baron"){}


    void Baron::invest(){
        if (!this->isAlive){
            throw std::runtime_error("This Baron is out of the game.");
        }

        this->coinsAmount += 3; // Invest 3 coins and gets 6 coins -> overall gets 3 new coins
        std::cout << "The Baron invested 3 coins ang got 6 coins." << std::endl;
    }

    void Baron::compensation(){
        if (this->isSanctioned){
            this->coinsAmount++;
            std::cout << "The Baron got compensation for the sanction." << std::endl;
        }

    }

    
}
