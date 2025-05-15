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
        bool isSanctioned; // Is plater got sanctioned
        bool isAlive; // Is plater "alive"
        bool anotherTurn; // Is player should get another turn
        bool undoCoup; // If General choose to undo a coup
        bool arrested; // Player who got arrested - stays true for the whole round
        bool arrestBlocked; // Player cant use the arrst action until his next turn

        public:
        Player(Game& game, const std::string& name, const std::string& role);
        //~Player(); // Not sure if needed

        virtual void gather();

        virtual void tax();

        int coins() const;

        virtual void bribe();

        virtual void arrest(Player& p);

        virtual void sanction(Player& p);

        virtual void coup(Player& player);

        bool getSan() const;

        bool getAlive() const;

        std::string getRole();

        std::string getName() const;
        
        void setAlive(bool aliveStatus);

        void decreaseCoins(int newAmount);

        virtual bool undo(Player& player);

        void setUndoCoup(bool undo);

        bool hasAnotherTurn();
        
        void setAnotherTurn(bool state);

        bool getArrested();
        void setArrested(bool state);

        bool getArrestBlocked();
        void setArrestBlocked(bool state);

    };

}

#endif