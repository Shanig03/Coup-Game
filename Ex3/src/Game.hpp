// Email: shanig7531@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <functional> 


#include "Player.hpp"

namespace coup {
    class Player;

    class Game {
        private:
        std::vector<Player*> playersList;
        std::string currPlayer;

        public:
        Game();

        const std::vector<std::string> players();

        const std::string turn();

        void passTurns();

        void addPlayer(Player* p);

        void removePlayer(std::string name);

        void startGame();

        std::string winner();

        void moveTurnTo(const std::string& role, Player& p);

        std::vector<Player*> assignRandomRoles(const std::vector<std::string>& playerNames);

    };

}


#endif