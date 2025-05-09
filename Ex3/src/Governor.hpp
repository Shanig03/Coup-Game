#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include "Game.hpp"

namespace coup {
    class Governor : public Player{

        public:
        Governor(Game g, string name);

        void undo(Player& player);
    };

}




#endif




