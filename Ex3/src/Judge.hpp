#ifndef JUDGE_HPP
#define JUDGE_HPP

#include "Game.hpp"

namespace coup {
    class Judge : public Player{

        public:
        Judge(Game g, string name);
        void undo(Player& player);
    };

}




#endif