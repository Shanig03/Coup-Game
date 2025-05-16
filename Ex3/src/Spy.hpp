// Email: shanig7531@gmail.com

#ifndef SPY_HPP
#define SPY_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Spy : public Player{

        public:
        Spy(Game& g, const std::string& name);

        int showCoinsAmount(Player& p); // Shows the coins of the other player.

        void blockArrest(Player& p); // Block the arrest action for the other player.
    };

}

#endif