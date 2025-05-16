// Email: shanig7531@gmail.com

#ifndef JUDGE_HPP
#define JUDGE_HPP

#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Judge : public Player{

        public:
        Judge(Game& g, const std::string& name);
        bool undo(Player& player) override;
    };

}

#endif