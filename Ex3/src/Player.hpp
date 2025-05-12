#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdexcept>

namespace coup {
    class Game;
    
    class Player {

        private:
        std::string playerName;
        int coinsAmount;
        std::string role;
        Game& currGame;
        bool isSanctioned;
        bool isAlive;

        public:
        Player(Game& game, const std::string& name, const std::string& role);
        //~Player(); // Not sure if needed

        void gather();

        void tax();

        int coins() const;

        void bribe();

        void arrest(Player& p);

        void sanction(Player& p);

        void coup(Player& player);

        bool getSan() const;

        bool getAlive() const;

        std::string getName() const;
        
        void setAlive(bool aliveStatus);



    };

}



#endif