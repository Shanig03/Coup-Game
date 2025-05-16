// Email: shanig7531@gmail.com

#include "Spy.hpp"

namespace coup {

    Spy::Spy(Game& g, const std::string& name): Player(g, name, "Spy"){}
    
    /*
    This function shows the coins of the other player.
    @param p the other player.
    */
    int Spy::showCoinsAmount(Player& p){
        if (!this->isAlive){
            throw std::runtime_error("This Spy is out of the game.");
        }
        if (!p.getAlive()){
            throw std::runtime_error("Target player is out of the game.");
        }
        return p.coins();
    }

    /*
    This function block the arrest action for the other player.
    @param p the other player.
    */
    void Spy::blockArrest(Player& p){
        p.setArrestBlocked(true);
        std::cout << p.getName() << ", your arrest action is blocked until tour next turn." << std::endl;
    }


} 
