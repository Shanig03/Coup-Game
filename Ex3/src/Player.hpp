#ifndef PLAYER_HPP
#define PLAYER_sHPP

#include "Game.hpp"
#include <iostream>
#include <stdexcept>

namespace coup {
    class Player {

        private:
        std::string playerName;
        int coinsAmount;
        std::string role;
        Game& currGame;
        bool isSanctioned;

        public:
        Player(Game& game, const std::string name, std::string role);
        //~Player(); // Not sure if needed

        void gather();

        void tax();

        int coins();

        void bribe();

        void arrest(Player& p);

        void sanction(Player& p);

        void coup(const Player& player);

        bool getSan();

    };

}



#endif