#ifndef SPY_HPP
#define SPY_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Spy : public Player{

        public:
        Spy(Game& g, const std::string& name);

        int showCoinsAmount(Player& p);

        void blockArrest(Player& p);
    };

}

#endif