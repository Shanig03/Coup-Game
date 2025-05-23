// Email: shanig7531@gmail.com

#include "Merchant.hpp"

namespace coup {
    

    Merchant::Merchant(Game& g, const std::string& name): Player(g, name, "Merchant"){}


    void Merchant::extraCoin(){
        // If player has at least 3 coins.
        if(this->coins() >= 3){
            this->coinsAmount++;
        }
    }

    void Merchant::merchantGotArrested(){
        // Decreasing the coins of the player by 2.
        this->decreaseCoins(2); 
    }
}