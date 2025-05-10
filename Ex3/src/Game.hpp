#ifndef GAME_HPP
#define GAME_HPP
#include <vector>
#include <iostream>
#include <algorithm>

namespace coup {

    class Game {
        private:
        std::vector<std::string> playersList;
        std::string currPlayer;

        public:
        Game();

        const std::vector<std::string> players();

        const std::string turn();

        void passTurns();

        void addPlayer(std::string name);

        void removePlayer(std::string name);

        void startGame();
    };

}


#endif