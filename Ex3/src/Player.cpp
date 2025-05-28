// Email: shanig7531@gmail.com

#include "Player.hpp"
#include "Game.hpp"

#include "Baron.hpp"
#include "Merchant.hpp"

namespace coup {

    // Constructor
    Player::Player(Game& game, const std::string& name, const std::string& role): 
    playerName(name),  coinsAmount(0), role(role), currGame(game), isSanctioned(false), 
    isAlive(true), anotherTurn(false), undoCoup(false), arrested(false), arrestBlocked(false) {}

    void Player::startTurn(){
        // Check if a player has 10 coins or more.
        if (this->coinsAmount >= 10){
            throw std::runtime_error("Player has 10 or more coins, must use coup action.");
        }

        // Checks if the player who plays is alive.
        if (!this->isAlive){ throw std::runtime_error("Player is out of the game."); }

        // Checks if the current turn is the player who tries to plays.
        if (this->currGame.turn() != this->playerName) {throw std::runtime_error("Action out of turn.");}

    }


    void Player::gather(){
        startTurn();
    
        // If the Player is sanctioned, he cant use the gather action. 
        if(!isSanctioned){
            // Merchant gets an extra coin if they start their turn with at least 3 coins.
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
            }
            
            this->coinsAmount++; // Adds 1 coin to the player
            std::cout << coinsAmount << std::endl;
            this->arrestBlocked = false;
            this->currGame.passTurns();
        }
    
    }

    void Player::tax(){
        startTurn();

        // If the Player is sanctioned, he cant use the tax action. 
        if(!isSanctioned){

            // Merchant gets an extra coin if they start their turn with at least 3 coins.
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
            }
            
            this->coinsAmount += 2; // Adds 2 coins to the player.

            // Ask all the Governors if they wants to undo this tax action.
            //this->currGame.moveTurnTo("Governor", *this);
            std::cout << coinsAmount << std::endl; // Delete this
            this->arrestBlocked = false;
            this->currGame.passTurns();
        }
    }


    void Player::arrest(Player& p){
        startTurn();
        if (!p.getAlive()){throw std::runtime_error("The player on whom the action is preformed is out of the game.");}

        if (p.coins() < 1){throw std::runtime_error("The player on whom the action is preformed dosent have at least 1 coin.");}
        // Prevent from the same player to be arrested twice.
        if (p.getArrested()){ 
            std::cout << "Can't arrest the same player more then once in a row." << std::endl;
            return;
        }

        // Prevent from a player who got blocked to use the arrest action by the Spy.
        if (this->arrestBlocked){ 
            std::cout << "Arrest action blocked by the Spy, try again in your next turn." << std::endl;
            return;
        }
        
        // General gets back the coin if got arrested.
        if (p.getRole() != "General"){

            // Merchant pays 2 coins to the game instead of the player that arrested him.
            if (Merchant* m = dynamic_cast<Merchant*>(&p)){
                m->merchantGotArrested();

            } else if (p.getRole() != "Merchant"){
                p.coinsAmount--;
                this->coinsAmount++; 
            }   
            
            if (Merchant* m = dynamic_cast<Merchant*>(this)){ m->extraCoin();}
            
            p.setArrested(true); // Track players who got arrested.
        }

        this->isSanctioned = false;

        this->currGame.passTurns();
    }

    int Player::coins() const{
        return this->coinsAmount;
    }

    void Player::bribe(){
        startTurn();

        // check if the player have enough coins.
        if (this->coinsAmount < 4){
            throw std::invalid_argument("Player must have 4 coins to use the Bribe action.");
        }

        this->coinsAmount -= 4;
        this->anotherTurn = true; // Truck who should get another turn.
        this->arrestBlocked = false;
        //this->currGame.moveTurnTo("Judge", *this);

        // No need to passTurns() because the player have 2 more action, 
        // and only at the seconed one the turn will pass to the next player.
    
    }

    void Player::sanction(Player& p){
        startTurn();
        if (!p.getAlive()){throw std::runtime_error("The player on whom the action is preformed is out of the game.");}

        if (this->coinsAmount < 3){
            throw std::invalid_argument("Player must have 3 coins to use the Sanction action.");
        }

        // Extra coin for merchant.
        if (Merchant* m = dynamic_cast<Merchant*>(this)){m->extraCoin();}     

        this->coinsAmount -=3;
        p.isSanctioned = true;
        
        // The player that sanctioned the judge need to pay another coin to the game.
        if (p.getRole() == "Judge"){this->coinsAmount--;}

        // Baron gets 1 coin for compensation.
        if (Baron* b = dynamic_cast<Baron*>(&p)){b->compensation();}

        this->arrestBlocked = false;
        this->currGame.passTurns();

    }


    void Player::coup(Player& player) {
        // Checks if the player who plays is alive.
        if (!this->isAlive){ throw std::runtime_error("Player is out of the game."); }

        // Checks if the current turn is the player who tries to plays.
        if (this->currGame.turn() != this->playerName) {throw std::runtime_error("Action out of turn.");}


        if (!player.getAlive()){throw std::runtime_error("The player on whom the action is preformed is out of the game.");}
        
        // Ensure that the player performing the coup has enough coins.
        if (this->coins() < 7) {
            throw std::invalid_argument("Player must have 7 coins to use the Coup action.");
        }

        this->coinsAmount -= 7; 
        if (Merchant* m = dynamic_cast<Merchant*>(this)){m->extraCoin();}

        // Ask all the Generals if they wants to undo this coup action.
        //this->currGame.moveTurnTo("General", player); 

        // Checks if any of the General wants to undo the coup.
        if (!player.undoCoup){
            this->currGame.removePlayer(player.playerName);  
            player.isAlive = false;

        }
        this->currGame.passTurns();

        std::cout << "Turn passed after coup." << std::endl;
        this->arrestBlocked = false;
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

    bool Player::getArrested(){
        return this->arrested;
    }

    void Player::setArrested(bool state){
        this->arrested = state;
    }

    void Player::setArrestBlocked(bool state){
        this->arrestBlocked = state;
    }

    bool Player::getArrestBlocked(){
        return this->arrestBlocked;
    }

}