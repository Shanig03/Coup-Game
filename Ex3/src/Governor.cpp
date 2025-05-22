// Email: shanig7531@gmail.com

#include "Governor.hpp"

namespace coup {

    /**
     * @brief Constructs a Governor player.
     * Initializes the player with role "Governor".
     *
     * @param g Reference to the game object this player belongs to.
     * @param name Name of the player.
     */
    Governor::Governor(Game& g, const std::string& name) : Player(g, name, "Governor"){}

    /**
     * @brief Governor's special action: tax.
     * override the tax action from the player class.
     * If not sanctioned, adds 3 coins to the player and ends the turn.
     * This method checks if it's the player's turn and handles game progression.
     */
    void Governor::tax(){
        this->startTurn();
    
        if(!this->isSanctioned){
            this->coinsAmount += 3; // Adds 3 coins to the Governor
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    
    }

    /**
     * @brief Governor's undo ability.
     * Simulates undoing another player's tax action by deducting 2 coins.
     * Can only be used if both players are alive.
     *
     * @param player The player whose action is to be undone.
     * @return true if undo was successful.
     *
     * @throws std::runtime_error if the Governor or the target player is not alive.
     */
    bool Governor::undo(Player& player){
        if (!this->isAlive){
            throw std::runtime_error("Governor is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }

        player.decreaseCoins(2);  // or your actual undo logic
        return true;  // Indicates undo happened
    }

}