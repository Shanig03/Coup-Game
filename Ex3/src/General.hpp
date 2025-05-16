// Email: shanig7531@gmail.com

#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"


namespace coup {
    class General : public Player{

        public:
        General(Game& g, const std::string& name);

        bool undo(Player& player) override;

    };

}




#endif