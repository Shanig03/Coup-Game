// Email: shanig7531@gmail.com

#include "Merchant.hpp"

namespace coup {
    
    // Constructor
    Merchant::Merchant(Game& g, const std::string& name): Player(g, name, "Merchant"){}

    /*
    If a merchant start his sturn with at least 3 coins, he gets extra 1 coin.
    */
    void Merchant::extraCoin(){
        if(this->coins() >= 3){
            this->coinsAmount++;
        }
    }

    /*
    When a merchant get arrested he pays 2 coins to the game
    instead of paying 1 to the player that arrested him.
    */
    void Merchant::merchantGotArrested(){
        this->decreaseCoins(2); 
    }
}