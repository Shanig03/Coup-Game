#include "Player.hpp"

namespace coup {

    Player::Player(Game& game, const std::string name, std::string role) 
        : currGame(game), playerName(name) , role(role), coinsAmount(0) {
        game.addPlayer(name);
        isSanctioned = false;
    }


    void Player::gather(){
        if (this->currGame.turn() != this->playerName) {
            throw std::runtime_error("Action out of turn.");
        }

        if(!isSanctioned){
            this->coinsAmount++; // Adds 1 coin to the player
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    
    }

    void Player::tax(){
        if (this->currGame.turn() != this->playerName) {
            throw std::runtime_error("Action out of turn.");
        }
        if(!isSanctioned){
            this->coinsAmount += 2; // Adds 2 coins to the player
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    }

    void Player::arrest(Player& p){
        if (this->currGame.turn() != this->playerName) {
            throw std::runtime_error("Action out of turn.");
        }

        p.coinsAmount--;
        this->coinsAmount++;

        std::cout << "other player coins: " << p.coinsAmount << std::endl;
        std::cout << "this player coins: " << this->coinsAmount << std::endl;
        this->currGame.passTurns();

        this->isSanctioned = false;
    }

    int Player::coins(){
        return this->coinsAmount;
    }

    void Player::bribe(){
        if (this->coinsAmount < 4){
            throw std::invalid_argument("Player must have 4 coins to use the Bribe action.");
        }
    }

    void Player::sanction(Player& p){
        if (this->coinsAmount < 3){
            throw std::invalid_argument("Player must have 3 coins to use the Sanction action.");
        }

        this->coinsAmount -=3;
        p.isSanctioned = true;
    }


    void Player::coup(const Player& player){
        if (this->coinsAmount < 7){
            throw std::invalid_argument("Player must have 7 coins to use the Coup action.");
        }

        this->currGame.removePlayer(player.playerName); // Remove the player from the players list
        this->currGame.passTurns();

        this->isSanctioned = false;
    }


    bool Player::getSan(){
        return this->isSanctioned;
    }



}