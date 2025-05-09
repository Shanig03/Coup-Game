#ifndef SPY_HPP
#define SPY_HPP

#include "Game.hpp"

namespace coup {
    class Spy : public Player{

        public:
        Spy(Game g, string name);
    };

}

#endif