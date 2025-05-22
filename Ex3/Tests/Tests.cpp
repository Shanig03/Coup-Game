#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/Game.hpp"
#include "../src/Player.hpp"
#include "../src/Merchant.hpp"
#include "../src/Baron.hpp"

using namespace coup;

TEST_CASE("Tests for the Player class"){
    SUBCASE("Player Constructor and Basic Getters") {
        Game game;
        Player* p = new Player(game, "Alice", "Spy");    

        CHECK(p->getName() == "Alice");
        CHECK(p->getRole() == "Spy");
        CHECK(p->getAlive() == true);
        CHECK(p->getSan() == false);
        CHECK(p->coins() == 0);

        delete p;
    }

    SUBCASE("setAlive and getAlive") {
        Game game;
        Player* p = new Player(game, "Bob", "Judge");

        p->setAlive(false);
        CHECK_FALSE(p->getAlive());
        delete p;
    }

    SUBCASE("setUndoCoup and setAnotherTurn") {
        Game game;
        Player* p = new Player(game, "Cleo", "Governor");

        p->setUndoCoup(true);
        p->setAnotherTurn(true);

        CHECK(p->hasAnotherTurn());
        delete p;

    }

    SUBCASE("setArrested and getArrested") {
        Game game;
        Player* p = new Player(game, "Dina", "General");

        p->setArrested(true);
        CHECK(p->getArrested() == true);
        delete p;
    }

    SUBCASE("decreaseCoins") {
        Game game;
        Player* p = new Player(game, "Eli", "Spy");    
        game.addPlayer(p);
        game.startGame();
        std::cout << game.getCurrentPlayer()->getName() << std::endl;

        for (int i = 0; i < 5; ++i) {
            p->gather();
        }

        int prev = p->coins();
        p->decreaseCoins(2);

        std::cout << prev - 2 << std::endl;
        CHECK(p->coins() == prev - 2);
        delete p;
    }

    SUBCASE("Sanction action") {
        Game game;
        Player* p1 = new Player(game, "Sanctioner", "Spy");
        Player* p2 = new Player(game, "Target", "Baron");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        for (int i = 0; i < 3; ++i) {
            p1->gather();
            p2->gather();
        }

        p1->sanction(*p2);
        int p2_coins = p2->coins();
        CHECK(p2->getSan() == true);

        // After sanction the player cannot use tax and gather, so his coins should stay the same.
        p2->gather();
        p2->tax();
        CHECK(p2->coins() == p2_coins);
        delete p1;
        delete p2;
    }

    SUBCASE("Sanction action with less that 3 coins") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "target", "Spy");        
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        CHECK_THROWS_AS(p1->sanction(*p2), std::invalid_argument);
        delete p1;
        delete p2;
    }

    SUBCASE("Bribe action") {
        Game game;
        Player* p = new Player(game, "Briber", "Spy");
        game.addPlayer(p);
        game.startGame();

        for (int i = 0; i < 4; ++i) {
            p->gather();
        }

        CHECK_NOTHROW(p->bribe());
        CHECK(p->hasAnotherTurn() == true);

        p->tax();
        p->gather();

        // After 2 action AnotherTurn should be back to false.
        CHECK(p->hasAnotherTurn() == false); 
        delete p;
    }

    SUBCASE("Bribe action with less that 4 coins") {
        Game game;
        Player* p = new Player(game, "Briber", "Spy");
        game.addPlayer(p);
        game.startGame();

        CHECK_THROWS_AS(p->bribe(), std::invalid_argument);
        delete p;
    }

    SUBCASE("Tax action") {
        Game game;
        Player* p = new Player(game, "Taxer", "Spy");
        game.addPlayer(p);
        game.startGame();

        p->tax();
        CHECK(p->coins() == 2);
        delete p;
    }

    SUBCASE("Gather action") {
        Game game;
        Player* p = new Player(game, "Gatherer", "Spy");
        game.addPlayer(p);
        game.startGame();

        p->gather();
        CHECK(p->coins() == 1);
        delete p;
    }

    SUBCASE("Arrest action") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "target", "Spy");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        p1->gather();
        p2->gather();

        int p1_coins = p1->coins();
        int p2_coins = p2->coins();

        p1->arrest(*p2);

        CHECK(p1->coins() == p1_coins + 1);
        CHECK(p2->coins() == p2_coins - 1);
        delete p1;
        delete p2;
    }

    SUBCASE("Arrest action with arrested") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "target", "Spy");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        p1->gather();
        p2->gather();
        p2->setArrested(true);
        int p1_coins = p1->coins();
        int p2_coins = p2->coins();

        p1->arrest(*p2);

        CHECK(p1->coins() == p1_coins);
        CHECK(p2->coins() == p2_coins);
        delete p1;
        delete p2;
    }

    SUBCASE("Arrest action with arrestBlocked") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "target", "Spy");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        p1->gather();
        p2->gather();

        p1->setArrestBlocked(true);
        int p1_coins = p1->coins();
        int p2_coins = p2->coins();

        p1->arrest(*p2);

        CHECK(p1->coins() == p1_coins);
        CHECK(p2->coins() == p2_coins);
        delete p1;
        delete p2;
    }

    SUBCASE("Coup action with 7 coins") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "Merchant", "Merchant");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        for (int i = 0; i < 7; ++i) {
            p1->gather();
            p2->gather();
        }

        p1->coup(*p2);
        CHECK_FALSE(p2->getAlive());
        CHECK(p1->coins() == 0); 
        delete p1;
        delete p2;
    }

    SUBCASE("Coup action throws without enough coins") {
        Game game;
        Player* p1 = new Player(game, "LowCoins", "Spy");
        Player* p2 = new Player(game, "Target", "Merchant");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        // Each one of the players have 1 coin from the gather action.
        p1->gather();
        p2->gather();

        CHECK_THROWS_AS(p1->coup(*p2), std::invalid_argument);
        delete p1;
        delete p2;
    }

    SUBCASE("Coup action with undoCoup"){
        Game game;
        Player* p1 = new Player(game, "LowCoins", "Spy");
        Player* p2 = new Player(game, "Target", "Merchant");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        for (int i = 0; i < 8; i++){
            p1->gather();
            p2->gather();
        }

        p2->setUndoCoup(true);
        p1->coup(*p2);
        CHECK(p2->getAlive() == true);
        delete p1;
        delete p2;
    }

    SUBCASE("Arrest action sets target as arrested") {
        Game game;
        Player* p1 = new Player(game, "Arrester", "Spy");
        Player* p2 = new Player(game, "Target", "Spy");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        for (int i = 0; i < 2; ++i) {
            p1->gather();
            p2->gather();
        }

        p1->arrest(*p2);
        CHECK(p2->getArrested());
        delete p1;
        delete p2;
    }

    SUBCASE("startTurn throws if not player's turn") {
        Game game;
        Player* p1 = new Player(game, "A", "Spy");
        Player* p2 = new Player(game, "B", "Spy");
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        // Try to have p2 play when it’s p1’s turn
        CHECK_THROWS_AS(p2->startTurn(), std::runtime_error);
        delete p1;
        delete p2;
    }

    SUBCASE("startTurn throws if player has 10+ coins") {
        Game game;
        Player* p = new Player(game, "Richie", "Spy");
        game.addPlayer(p);
        game.startGame();

        for (int i = 0; i < 10; ++i) {
            p->gather();
        }

        CHECK_THROWS_AS(p->startTurn(), std::runtime_error);
        delete p;
    }
}
