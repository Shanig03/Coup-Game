// Email: shanig7531@gmail.com

#include "General.hpp"

namespace coup {

    /**
     * @brief Constructs a new General object.
     * Sets the role as "General" for identification in the game.
     *
     * @param g Reference to the current game instance.
     * @param name The name of the General player.
     */
    General::General(Game& g, const std::string& name) : Player(g, name, "General"){}


    /**
     * @brief Allows the General to undo a coup on a specific player.
     * This action costs the General 5 coins and only works if both players are alive (before coup).
     * The target player's undo flag is set to true upon success.
     *
     * @param player Reference to the player whose coup is being undone.
     * @return true if the undo was successful.
     * @throws std::runtime_error if the General or the target is not alive,
     *                            or if the General has fewer than 5 coins.
     */
    bool General::undo(Player& player){
        if (!this->isAlive){
            throw std::runtime_error("General is out of the game.");
        }
        if (!player.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        if (this->coins() < 5){
            throw std::runtime_error("General doesnt have 5 coins to undo.");
        }
        
        this->decreaseCoins(5);
        player.setUndoCoup(true);
        return true;  // Indicates undo happened

    }



}