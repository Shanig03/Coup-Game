// Email: shanig7531@gmail.com

#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    /**
     * @class Merchant
     * @brief Represents the Merchant role in the Coup game.
     *
     * The Merchant earns extra coin for each turn he start with at least 3 coins 
     * and whe get arrested he pays 2 coins to the game instead of 1 to the player that arrested him.
     *
     * @see Player
     */
    class Merchant : public Player{

        public:

        /**
         * @brief Constructs a Merchant player and registers their role in the game.
         * 
         * @param g Reference to the current Game instance.
         * @param name The name of the player.
         */
        Merchant(Game& g, const std::string& name);

        /** 
         * @brief Grants the Merchant an additional coin if they start their turn with at least 3 coins.
         *
         * This method checks the current coin count. If the Merchant has 3 or more coins,
         * they receive 1 bonus coin.
         */
        void extraCoin();

        /**
         * @brief Handles the arrest scenario for the Merchant.
         *
         * Instead of paying 1 coin to the arresting player, the Merchant pays 2 coins directly to the game.
         */
        void merchantGotArrested();
    };

}

#endif