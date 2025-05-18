#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/Game.hpp"
#include "../src/Player.hpp"
#include "../src/Merchant.hpp"
#include "../src/Baron.hpp"

using namespace coup;

TEST_CASE("Player Constructor and Basic Getters") {
    Game game;
    Player p(game, "Alice", "Spy");

    CHECK(p.getName() == "Alice");
    CHECK(p.getRole() == "Spy");
    CHECK(p.getAlive() == true);
    CHECK(p.getSan() == false);
    CHECK(p.coins() == 0);
}

TEST_CASE("setAlive and getAlive") {
    Game game;
    Player p(game, "Bob", "Judge");

    p.setAlive(false);
    CHECK_FALSE(p.getAlive());
}

TEST_CASE("setUndoCoup and setAnotherTurn") {
    Game game;
    Player p(game, "Cleo", "Governor");

    p.setUndoCoup(true);
    p.setAnotherTurn(true);

    CHECK(p.hasAnotherTurn());
}

TEST_CASE("setArrested and getArrested") {
    Game game;
    Player p(game, "Dina", "General");

    p.setArrested(true);
    CHECK(p.getArrested() == true);
}

TEST_CASE("decreaseCoins") {
    Game game;
    Player p(game, "Eli", "Spy");

    // manually increase coin amount for testing
    for (int i = 0; i < 5; ++i) {
        p.gather();
    }
    int prev = p.coins();
    p.decreaseCoins(2);
    CHECK(p.coins() == prev - 2);
}

TEST_CASE("Sanction action") {
    Game game;
    Player p1(game, "Sanctioner", "Spy");
    Player p2(game, "Target", "Baron");

    for (int i = 0; i < 3; ++i) {
        p1.gather();
    }

    // pass turn until p1's
    while (game.turn() != p1.getName()) {
        game.passTurns();
    }

    p1.sanction(p2);
    CHECK(p2.getSan() == true);
}

TEST_CASE("Bribe action") {
    Game game;
    Player p(game, "Briber", "Spy");

    for (int i = 0; i < 4; ++i) {
        p.gather();
    }

    while (game.turn() != p.getName()) {
        game.passTurns();
    }

    CHECK_NOTHROW(p.bribe());
    CHECK(p.hasAnotherTurn() == true);
}

TEST_CASE("Tax action") {
    Game game;
    Player p(game, "Taxer", "Spy");

    while (game.turn() != p.getName()) {
        game.passTurns();
    }

    p.tax();
    CHECK(p.coins() == 2);
}

TEST_CASE("Gather action") {
    Game game;
    Player p(game, "Gatherer", "Spy");

    while (game.turn() != p.getName()) {
        game.passTurns();
    }

    p.gather();
    CHECK(p.coins() == 1);
}

TEST_CASE("Coup action with 7 coins") {
    Game game;
    Player p1(game, "CoupMaker", "Spy");
    Player p2(game, "Target", "Merchant");

    for (int i = 0; i < 7; ++i) {
        p1.gather();
    }

    while (game.turn() != p1.getName()) {
        game.passTurns();
    }

    p1.coup(p2);
    CHECK_FALSE(p2.getAlive());
    CHECK(p1.coins() == 0); // if merchant, may be 1 from extraCoin
}

TEST_CASE("Coup action throws without enough coins") {
    Game game;
    Player p1(game, "LowCoins", "Spy");
    Player p2(game, "Target", "Merchant");

    p1.gather();

    while (game.turn() != p1.getName()) {
        game.passTurns();
    }

    CHECK_THROWS_AS(p1.coup(p2), std::invalid_argument);
}

TEST_CASE("Arrest action sets target as arrested") {
    Game game;
    Player p1(game, "Arrester", "Spy");
    Player p2(game, "Target", "Spy");

    for (int i = 0; i < 2; ++i) {
        p1.gather();
        game.passTurns();
        p2.gather();
        game.passTurns();
    }

    while (game.turn() != p1.getName()) {
        game.passTurns();
    }

    p1.arrest(p2);
    CHECK(p2.getArrested());
}

TEST_CASE("startTurn throws if not player's turn") {
    Game game;
    Player p1(game, "A", "Spy");
    Player p2(game, "B", "Spy");

    // Try to have p2 play when it’s p1’s turn
    CHECK_THROWS_AS(p2.startTurn(), std::runtime_error);
}

TEST_CASE("startTurn throws if player has 10+ coins") {
    Game game;
    Player p(game, "Richie", "Spy");

    for (int i = 0; i < 10; ++i) {
        p.gather();
        game.passTurns();
    }

    while (game.turn() != p.getName()) {
        game.passTurns();
    }

    CHECK_THROWS_AS(p.startTurn(), std::runtime_error);
}
