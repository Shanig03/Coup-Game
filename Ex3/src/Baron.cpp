// Email: shanig7531@gmail.com

#include "Baron.hpp"

namespace coup {

    /**
     * @brief Constructs a new Baron object.
     * Initializes the player with the role "Baron".
     *
     * @param g Reference to the game the player belongs to.
     * @param name Name of the player.
     */
    Baron::Baron(Game& g, const std::string& name) : Player(g, name, "Baron"){}


    /**
     * @brief Baron's special action: invest.
     * If the Baron has at least 3 coins and is alive, they can invest those coins,
     * and receive a total of 6 (i.e., gain 3 net coins).
     *
     * @throws std::runtime_error if the Baron is not alive.
     */
    void Baron::invest(){
        if (!this->isAlive){
            throw std::runtime_error("This Baron is out of the game.");
        }

        if (this->coins() >= 3){
            this->coinsAmount += 3; // Invest 3 coins and gets 6 coins -> overall gets 3 new coins
            std::cout << "The Baron invested 3 coins ang got 6 coins." << std::endl;
            this->currGame.passTurns();
        }
    }

    /**
     * @brief Baron's passive action: compensation.
     * If the Baron is get sanctioned, they receive 1 compensation coin.
     * Triggered by external code.
     */
    void Baron::compensation(){
        if (this->isSanctioned){
            this->coinsAmount++;
            std::cout << "The Baron got compensation for the sanction." << std::endl;
        }

    }

    
}
