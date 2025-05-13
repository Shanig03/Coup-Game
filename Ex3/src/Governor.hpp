#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Governor : public Player{

        public:
        Governor(Game& g, const std::string& name);

        void tax() override;

        bool undo(Player& player) override;
    };

}




#endif




