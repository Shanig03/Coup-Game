// Email: shanig7531@gmail.com

#ifndef SPY_HPP
#define SPY_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    
    /**
     * @class Spy
     * @brief Represents the Spy role in the Coup game.
     * 
     * The Spy can reveal another player's coin count and block arrest actions.
     * Inherits from Player and defines the Spy's unique actions.
     * 
     * @see Player
     */
    class Spy : public Player{

        public:
        /**
         * @brief Constructs a Spy player with the specified name and links them to the game.
         * 
         * @param g Reference to the game the player belongs to.
         * @param name Name of the player.
         */
        Spy(Game& g, const std::string& name);

        /**
         * @brief Reveals the number of coins the target player currently has.
         * 
         * This action does not affect gameplay but provides useful information about another player's coin status.
         * 
         * @param p Reference to the target player whose coins are being revealed.
         * @return The number of coins the target player currently holds.
         * 
         * @throws std::runtime_error if the Spy is not alive.
         * @throws std::runtime_error if the target player is not alive.
         */
        int showCoinsAmount(Player& p); 

        /**
         * @brief Blocks the arrest action of the target player.
         * 
         * This prevents the target player from performing an arrest action until their next turn.
         * 
         * @param p Reference to the player whose arrest action is being blocked.
         */
        void blockArrest(Player& p); 
    };

}

#endif