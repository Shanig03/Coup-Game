// Email: shanig7531@gmail.com

#ifndef BARON_HPP
#define BARON_HPP

#include "Game.hpp"

namespace coup {
    /**
    * @class Baron
    * @brief Represents the Baron role in the Coup game.
    *
    * The Baron can invest 3 coins and get 6 in return. 
    * Also, if he get sanctioned he gets 1 coin as a compensation.
    *
    * @see Player
    */
    class Baron : public Player{

        public:

        /**
         * @brief Constructs a new Baron object.
         * Initializes the player with the role "Baron".
         *
         * @param g Reference to the game the player belongs to.
         * @param name Name of the player.
         */
        Baron(Game& g, const std::string& name);

        /**
         * @brief Baron's special action: invest.
         * If the Baron has at least 3 coins and is alive, they can invest those coins,
         * and receive a total of 6 (i.e., gain 3 net coins).
         *
         * @throws std::runtime_error if the Baron is not alive.
         */
        void invest();

        /**
         * @brief Baron's passive action: compensation.
         * If the Baron is get sanctioned, they receive 1 compensation coin.
         * Triggered by external code.
         */
        void compensation();
    };

}




#endif