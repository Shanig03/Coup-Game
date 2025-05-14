#include "Player.hpp"
#include "Game.hpp"

#include "Baron.hpp"
#include "Merchant.hpp"

namespace coup {

    // Constructor definition in Player.cpp
    Player::Player(Game& game, const std::string& name, const std::string& role): 
    currGame(game), playerName(name), role(role), coinsAmount(0), isSanctioned(false), 
    isAlive(true), anotherTurn(false), undoCoup(false) {}


    void Player::gather(){
        if (!this->isAlive){
            throw std::runtime_error("Player is out of the game.");
        }

        if (this->currGame.turn() != this->playerName) {
            throw std::runtime_error("Action out of turn.");
        }

        if(!isSanctioned){
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
            }
            
            this->coinsAmount++; // Adds 1 coin to the player
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    
    }

    void Player::tax(){
        if (!this->isAlive){
            throw std::runtime_error("Player is out of the game.");
        }
        if (this->currGame.turn() != this->playerName) {
            throw std::runtime_error("Action out of turn.");
        }
        if(!isSanctioned){
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
            }
            this->coinsAmount += 2; // Adds 2 coins to the player
            this->currGame.moveTurnTo("Governor", *this);
            std::cout << coinsAmount << std::endl;
            this->currGame.passTurns();
        }
    }

    void Player::arrest(Player& p){
        if (!this->isAlive){ throw std::runtime_error("Player is out of the game.");}
        if (this->currGame.turn() != this->playerName) {throw std::runtime_error("Action out of turn.");}
        if (p.getRole() != "General"){
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
                m->merchantGotArrested();
            } else if (p.getRole() != "Merchant"){
                p.coinsAmount--;
                this->coinsAmount++; 
            }            
                       
        }
        this->isSanctioned = false;

        this->currGame.passTurns();

    }

    int Player::coins() const{
        return this->coinsAmount;
    }

    void Player::bribe(){
        if (!this->isAlive){
            throw std::runtime_error("Player is out of the game.");
        }
        if (this->coinsAmount < 4){
            throw std::invalid_argument("Player must have 4 coins to use the Bribe action.");
        }
        this->coinsAmount -= 4;
        this->anotherTurn = true;

        // No need to passTurns() because the player have 2 more action, 
        // and only at the seconed one the turn will pass to the next player.
    
    }

    void Player::sanction(Player& p){
        if (!this->isAlive){
            throw std::runtime_error("Player is out of the game.");
        }
        if (this->coinsAmount < 3){
            throw std::invalid_argument("Player must have 3 coins to use the Sanction action.");
        }

        if (Merchant* m = dynamic_cast<Merchant*>(&p)){
            m->extraCoin();
        }        
        this->coinsAmount -=3;
        p.isSanctioned = true;
        
        if (p.getRole() == "Judge"){
            this->coinsAmount--;
        }

        if (Baron* b = dynamic_cast<Baron*>(&p)){
            b->compensation();
        }
        this->currGame.passTurns();

    }


    void Player::coup(Player& player) {
        // Check if the player and target player are alive
        if (!this->isAlive || !player.getAlive()) {
            throw std::runtime_error("One of the players is out of the game.");
        }

        // Ensure that the player performing the coup has enough coins
        if (this->coins() < 7) {
            throw std::invalid_argument("Player must have 7 coins to use the Coup action.");
        }

        // Execute the coup action by removing the player and passing turns
        this->coinsAmount -= 7; 
        if (Merchant* m = dynamic_cast<Merchant*>(this)){
            m->extraCoin();
        }

        this->currGame.moveTurnTo("General", player);
        if (!player.undoCoup){
            this->currGame.removePlayer(player.playerName);  
            // Mark the player as dead
            player.isAlive = false;

        }
        this->currGame.passTurns();

        std::cout << "Turn passed after coup." << std::endl;

        this->isSanctioned = false;
    }


    bool Player::getSan() const{
        return this->isSanctioned;
    }


    bool Player::getAlive() const {
        return this->isAlive;
    }

    
    std::string Player::getName() const{
        return this->playerName;
    }

    void Player::setAlive(bool aliveStatus) {
        this->isAlive = aliveStatus;
    }
    

    std::string Player::getRole(){
        return this->role;
    }

    void Player::decreaseCoins(int newAmount){
        this->coinsAmount -= newAmount;
    }


    bool Player::undo(Player& player){
        return false;
    }

    void Player::setUndoCoup(bool undo){
        this->undoCoup = undo;
    }

    bool Player::hasAnotherTurn(){
        return this->anotherTurn;
    }

    void Player::setAnotherTurn(bool state){
        this->anotherTurn = state;
    }


}