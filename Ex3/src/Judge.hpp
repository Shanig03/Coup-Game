// Email: shanig7531@gmail.com

#ifndef JUDGE_HPP
#define JUDGE_HPP

#include "Game.hpp"
#include "Player.hpp"

namespace coup {

    /**
     * @class Judge
     * @brief Represents the Judge role in the Coup game.
     *
     * The Judge can undo the Bribe action 
     * and if another player sanction him, he have to pat another coin to the game.
     *
     * @see Player
     */
    class Judge : public Player{

        public:

        /**
         * @brief Constructs a new Judge object.
         * Inherits from Player and sets the role to "Judge".
         *
         * @param g Reference to the current game instance.
         * @param name The name of the Judge player.
         */
        Judge(Game& g, const std::string& name);

        /**
         * @brief Undoes a Bribe action on the target player.
         * This function disables the target player's extra turn gained from the bribe.
         *
         * @param player Reference to the target player.
         * @return true if the undo was successful.
         * @throws std::runtime_error if either the Judge or the target player is no longer alive.
         */
        bool undo(Player& player) override;
    };

}

#endif