#include "Player.hpp"

namespace coup {

    Player::Player(Game& game, const std::string name, std::string role) 
        : currGame(game), playerName(name) , role(role), coinsAmount(0) {

    }


    void Player::gather(){
        if(!isSanctioned){
            this->coinsAmount++; // Adds 1 coin to the player
            this->currGame.getJackpot()--; // Redoucing by 1 the game's jackpot
        }
    }

}