#ifndef PLAYER_HPP
#define PLAYER_sHPP

#include "Game.hpp"
#include <iostream>

namespace coup {
    class Player {

        private:
        std::string playerName;
        int coinsAmount;
        std::string role;
        Game currGame;
        bool isSanctioned;

        public:
        Player(Game& game, const std::string name, std::string role);
        ~Player();

        void gather();

        void tax();

        int& coins();

        void bribe();

        void arrest();

        void sanction();

        void coup(const Player& player);

    };

}



#endif