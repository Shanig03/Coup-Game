#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Merchant : public Player{

        public:
        Merchant(Game& g, const std::string& name);

        void extraCoin();

        void merchantGotArrested();
    };

}




#endif