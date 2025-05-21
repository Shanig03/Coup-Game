// Email: shanig7531@gmail.com

#include "Player.hpp"
#include "Game.hpp"

#include "Baron.hpp"
#include "Merchant.hpp"

namespace coup {

    // Constructor
    Player::Player(Game& game, const std::string& name, const std::string& role): 
    currGame(game), playerName(name), role(role), coinsAmount(0), isSanctioned(false), 
    isAlive(true), anotherTurn(false), undoCoup(false) {}


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

    
    /*
    This function implement the gather action in the Coup game. 
    Each player who choose this action gets 1 coin.
    */
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

    /*
    This function implement the tax action in the Coup game. 
    Each player who choose this action gets 2 coin, Except for the Governor who gets 3 coins.
    */
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

    /*
    This function implement the arrest action in the Coup game. 
    The Player choose another player and arrest him - takes 1 coin from him. 
    This action cant be played on the same player twice in a row.
    @param p the player who got arrested.
    */
    void Player::arrest(Player& p){
        startTurn();
        if (!p.getAlive()){throw std::runtime_error("The player on whom the action is preformed is out of the game.");}

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
            if (Merchant* m = dynamic_cast<Merchant*>(this)){
                m->extraCoin();
                m->merchantGotArrested();

            } else if (p.getRole() != "Merchant"){
                p.coinsAmount--;
                this->coinsAmount++; 
            }            
            p.setArrested(true); // Track players who got arrested.
        }

        this->isSanctioned = false;

        this->currGame.passTurns();
    }

    /*
    Returns the coins amount of the player.
    */
    int Player::coins() const{
        return this->coinsAmount;
    }

    /*
    This function implement the bribe action in the Coup game. 
    The Player pays 4 coins and in return he gets 2 turns in a row.
    */
    void Player::bribe(){
        startTurn();

        // check if the player have enough coins.
        if (this->coinsAmount < 4){
            throw std::invalid_argument("Player must have 4 coins to use the Bribe action.");
        }

        this->coinsAmount -= 4;
        this->anotherTurn = true; // Truck who should get anither turn.
        this->arrestBlocked = false;
        this->currGame.moveTurnTo("Judge", *this);

        // No need to passTurns() because the player have 2 more action, 
        // and only at the seconed one the turn will pass to the next player.
    
    }

    /*
    This function implement the sanction action in the Coup game. 
    The Player choose another player and sanction him - Prevent him from using tax and gather
    actions until his next turn.
    This action costs 3 coins.
    @param p the player who got sanctioned.
    */
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

    /*
    This function implement the coup action in the Coup game. 
    The Player choose another player and coup him - kick him out of the game.
    This action costs 7 coins.
    @param p the player who got couped.
    */
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

    /*
    Returns the sanctioned state of the player.
    */
    bool Player::getSan() const{
        return this->isSanctioned;
    }

    /*
    Returns the state of the player.
    */
    bool Player::getAlive() const {
        return this->isAlive;
    }

    /*
    Returns the name of the player.
    */
    std::string Player::getName() const{
        return this->playerName;
    }

    /*
    Set the state of the player.
    @param aliveStatus the new status.
    */
    void Player::setAlive(bool aliveStatus) {
        this->isAlive = aliveStatus;
    }
    
    /*
    Returns the role of the player.
    */
    std::string Player::getRole(){
        return this->role;
    }

    /*
    Decrease the coins amount of the player.
    @param newAmount the amount to deducte.
    */
    void Player::decreaseCoins(int newAmount){
        this->coinsAmount -= newAmount;
    }

    
    bool Player::undo(Player& player){
        return false;
    }
    

    /*
    Set the undoCoup state of the player.
    @param undo new state.
    */
    void Player::setUndoCoup(bool undo){
        this->undoCoup = undo;
    }

    /*
    Returns the anotherTurn state of the player.
    */
    bool Player::hasAnotherTurn(){
        return this->anotherTurn;
    }

    /*
    Set the anotherTurn state of the player.
    @param state new state.
    */
    void Player::setAnotherTurn(bool state){
        this->anotherTurn = state;
    }

    /*
    Returns the arrested state of the player.
    */
    bool Player::getArrested(){
        return this->arrested;
    }

    /*
    Set the arrested state of the player.
    @param state new state.
    */
    void Player::setArrested(bool state){
        this->arrested = state;
    }

    /*
    Set the arrestBlocked state of the player.
    @param state new state.
    */
    void Player::setArrestBlocked(bool state){
        this->arrestBlocked = state;
    }
}