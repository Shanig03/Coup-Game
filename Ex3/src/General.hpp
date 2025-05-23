// Email: shanig7531@gmail.com

#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"


namespace coup {

    /**
     * @class General
     * @brief Represents the General role in the Coup game.
     *
     * The General can undo the coup action, that cost him 5 coins.
     * Also, if he get arrested he get his coin back.
     *
     * @see Player
     */
    class General : public Player{

        public:

        /**
         * @brief Constructs a new General object.
        * Sets the role as "General" for identification in the game.
        *
        * @param g Reference to the current game instance.
        * @param name The name of the General player.
        */
        General(Game& g, const std::string& name);


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
        bool undo(Player& player) override;

    };

}




#endif