// Email: shanig7531@gmail.com

#include "Spy.hpp"

namespace coup {

    Spy::Spy(Game& g, const std::string& name): Player(g, name, "Spy"){}
    
    int Spy::showCoinsAmount(Player& p){
        // Checks if both of the players are alive.
        if (!this->isAlive){
            throw std::runtime_error("This Spy is out of the game.");
        }
        if (!p.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        return p.coins();
    }

    void Spy::blockArrest(Player& p){
        // Set the arrestBlocked of the other player to true.
        p.setArrestBlocked(true);
        std::cout << p.getName() << ", your arrest action is blocked until tour next turn." << std::endl;
    }


} 
