#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdexcept>

namespace coup {
    class Game;
    
    class Player {

        protected:
        std::string playerName;
        int coinsAmount;
        std::string role;
        Game& currGame;
        bool isSanctioned;
        bool isAlive;

        public:
        Player(Game& game, const std::string& name, const std::string& role);
        //~Player(); // Not sure if needed

        virtual void gather();

        virtual void tax();

        virtual int coins() const;

        virtual void bribe();

        virtual void arrest(Player& p);

        virtual void sanction(Player& p);

        virtual void coup(Player& player);

        virtual bool getSan() const;

        virtual bool getAlive() const;

        virtual std::string getRole();

        virtual std::string getName() const;
        
        virtual void setAlive(bool aliveStatus);

        virtual void decreaseCoins(int newAmount);

        virtual bool undo(Player& player);


    };

}

#endif