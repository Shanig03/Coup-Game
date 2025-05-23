// Email: shanig7531@gmail.com

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    /**
     * @class Governor
     * @brief Represents the Governor role in the Coup game.
     *
     * The Governor tax action gives him 3 coins instead of 2.
     * He can also undo other's players tax actions.
     *
     * @see Player
     */
    class Governor : public Player{

        public:

        /**
         * @brief Constructs a Governor player.
         * Initializes the player with role "Governor".
         *
         * @param g Reference to the game object this player belongs to.
         * @param name Name of the player.
         */
        Governor(Game& g, const std::string& name);

        /**
         * @brief Governor's special action: tax.
         * override the tax action from the player class.
         * If not sanctioned, adds 3 coins to the player and ends the turn.
         * This method checks if it's the player's turn and handles game progression.
         */
        void tax() override;

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
        bool undo(Player& player) override;

    };

}




#endif




