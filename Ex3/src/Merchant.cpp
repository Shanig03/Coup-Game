#include "Merchant.hpp"

namespace coup {
    Merchant::Merchant(Game& g, const std::string& name): Player(g, name, "Merchant"){}

    void Merchant::extraCoin(){
        if(this->coins() >= 3){
            this->coinsAmount++;
        }
    }

    void Merchant::merchantGotArrested(){
        this->decreaseCoins(2); // Pays 2 coins to the game instead of paying 1 to the player that arrested him
    }


}