// Email: shanig7531@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <functional> 


#include "Player.hpp"
#include "Governor.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Merchant.hpp"
#include "Judge.hpp"
#include "Spy.hpp"

namespace coup {
    class Player;

    /**
     * @brief Manages the overall state of the Coup game including players, turns, and victory conditions.
     * 
     * Responsibilities:
     * - Adding players and managing turn order
     * - Assigning random roles to players
     * - Keeping track of the current turn
     * - Handling player elimination
     * - Determining the game winner
     * 
     * @throws std::runtime_error on errors like exceeding player count, passing turns when no alive players exist, etc.
     */
    class Game {
        private:
        std::vector<Player*> playersList; // List of all players in the game
        std::string currPlayer; // The name of the player whose turn it is

        public:
        
        Game(); // Constructor
        ~Game(); // Distructor

        /**
         * @brief Returns the names of all players.
         * @return Vector of player names.
         */
        const std::vector<std::string> players();

        /**
         * @brief Returns the name of the current player.
         * @return Name of current player.
         */
        const std::string turn();

        /**
         * @brief Advances the turn to the next alive player.
         * @throws std::runtime_error if the current player is not found or no players are alive.
         */
        void passTurns();

        /**
         * @brief Adds a new player to the game.
         * @param p Pointer to a Player object.
         * @throws std::runtime_error if more than 6 players are added.
         */
        void addPlayer(Player* p);


        /**
         * @brief Marks a player as eliminated by name.
         * @param name Name of the player to eliminate.
         */
        void removePlayer(std::string name);

        /**
         * @brief Starts the game by setting the first alive player as the current player.
         * @throws std::runtime_error if no alive players exist.
         */
        void startGame();

        /**
         * @brief Returns the name of the last player alive.
         * @throws std::runtime_error if more than one player is still alive.
         * @return Name of the winner.
         */
        std::string winner();

        //void moveTurnTo(const std::string& role, Player& p);

        /**
         * @brief Assigns a random role to each player name provided.
         * @param playerNames List of player names.
         */
        void assignRandomRoles(const std::vector<std::string>& playerNames);

        /**
         * @brief Returns a pointer to the current player.
         * @return Pointer to Player object.
         */
        Player* getCurrentPlayer();

        /**
         * @brief Returns all players (alive and dead).
         * @return Vector of Player pointers.
         */
        std::vector<Player*> getPlayers();

        /**
         * @brief Returns all players with the asked role.
         * @return Vector of Player pointers.
         */
        std::vector<Player*> roleList(const std::string& role);

    };

}


#endif