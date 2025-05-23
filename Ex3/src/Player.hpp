// Email: shanig7531@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdexcept>

namespace coup {
    class Game;

    /**
     * @class Player
     * @brief Represents a player in the Coup game.
     * 
     * This class encapsulates all the actions a player can perform (e.g., gather, tax, coup),
     * and holds information like coin count, role, status, and turn behavior. It interacts closely
     * with the Game class to control game flow and enforce rules.
     */
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
        /**
         * @brief Constructs a new Player object.
         * 
         * @param game Reference to the Game object the player participates in.
         * @param name The player's name.
         * @param role The role type assigned to the player.
         */
        Player(Game& game, const std::string& name, const std::string& role);

        virtual ~Player();
        
        /**
         * @brief Executes the gather action, giving the player 1 coin.
         */
        void gather();

        /**
         * @brief Executes the tax action, giving 2 coins to the player.
         */
        virtual void tax();

        /**
         * @brief Gets the player's current coin count.
         * 
         * @return int The number of coins.
         */
        int coins() const;

        /**
         * @brief Executes the bribe action, giving the player 2 turns at a cost of 4 coins.
         * 
         * @throws std::invalid_argument If the player has fewer than 4 coins.
         */
        virtual void bribe();

        /**
         * @brief Executes the arrest action on another player.
         * 
         * @param p The target player to arrest.
         * @throws std::runtime_error If the target or acting player is not in a valid state.
         */
        virtual void arrest(Player& p);

        /**
         * @brief Executes the sanction action on another player.
         * 
         * @param p The player to be sanctioned.
         * @throws std::runtime_error If the player is not alive.
         * @throws std::invalid_argument If the player has fewer than 3 coins.
         */
        void sanction(Player& p);

        /**
         * @brief Executes the coup action on another player, costs 7 coins.
         * 
         * @param player The target player to be removed from the game.
         * @throws std::runtime_error If the player is not alive or it's not their turn.
         * @throws std::invalid_argument If the acting player has fewer than 7 coins.
         */
        void coup(Player& player);

        /**
         * @brief Validates if the player can start a turn.
         * 
         * @throws std::runtime_error If the player is not alive or it's not their turn.
         */
        void startTurn();

        /**
         * @brief Placeholder for undoing an action.
         * 
         * @param player The player involved in the undo.
         * @return false Always returns false by default.
         */
        virtual bool undo(Player& player); // "Abstract" function



    // --- Accessors & Mutators ---

        /**
         * @brief Gets the player's sanction status.
         * 
         * @return true if sanctioned, false otherwise.
         */
        bool getSan() const;

        /**
         * @brief Gets the player's alive status.
         * 
         * @return true if alive, false otherwise.
         */
        bool getAlive() const;

        /**
         * @brief Gets the player's role.
         * 
         * @return std::string The role.
         */
        std::string getRole();

        /**
         * @brief Gets the player's name.
         * 
         * @return std::string The name.
         */
        std::string getName() const;
        
        /**
         * @brief Sets the player's alive status.
         * 
         * @param aliveStatus The new alive state.
         */
        void setAlive(bool aliveStatus);

        /**
         * @brief Decreases the player's coins.
         * 
         * @param newAmount The amount to subtract.
         */
        void decreaseCoins(int newAmount);

        /**
         * @brief Sets whether a player has opted to undo a coup.
         * 
         * @param undo The new state.
         */
        void setUndoCoup(bool undo);

        /**
         * @brief Checks if the player has an extra turn.
         * 
         * @return true if has another turn, false otherwise.
         */
        bool hasAnotherTurn();
        
        /**
         * @brief Sets the player's extra turn state.
         * 
         * @param state The new state.
         */
        void setAnotherTurn(bool state);

        /**
         * @brief Gets whether the player has been arrested.
         * 
         * @return true if arrested, false otherwise.
         */
        bool getArrested();

        /**
         * @brief Sets the arrested state.
         * 
         * @param state The new state.
         */
        void setArrested(bool state);
        
        /**
         * @brief Sets whether the arrest action is blocked for the player.
         * 
         * @param state The new blocked state.
         */
        void setArrestBlocked(bool state);

        /**
         * @brief Gets whether the player's arrest action is blocked.
         * 
         * @return true if blocked, false otherwise.
         */
        bool getArrestBlocked();

    };

}

#endif