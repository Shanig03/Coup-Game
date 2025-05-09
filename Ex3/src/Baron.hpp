#ifndef BARON_HPP
#define BARON_HPP

#include "Game.hpp"

namespace coup {
    class Baron : public Player{

        public:
        Baron(Game g, string name);

        void invest();
    };

}




#endif