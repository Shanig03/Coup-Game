#ifndef BARON_HPP
#define BARON_HPP

#include "Game.hpp"

namespace coup {
    class Baron : public Player{

        public:
        Baron(Game& g, const std::string& name);

        void invest();

        void compensation(); // Compensation for sanction
    };

}




#endif