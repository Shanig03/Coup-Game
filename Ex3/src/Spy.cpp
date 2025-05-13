#include "Spy.hpp"

namespace coup {

    Spy::Spy(Game& g, const std::string& name): Player(g, name, "Spy"){}
    
    int Spy::showCoinsAmount(Player& p){
        if (!this->isAlive){
            throw std::runtime_error("This Spy is out of the game.");
        }
        if (!p.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        return p.coins();
    }

    void Spy::blockArrest(Player& p){

    }


} 
