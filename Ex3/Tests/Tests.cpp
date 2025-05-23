#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/Game.hpp"
#include "../src/Player.hpp"
#include "../src/Merchant.hpp"
#include "../src/Baron.hpp"
#include "../src/Spy.hpp"
#include "../src/General.hpp"
#include "../src/Judge.hpp"
#include "../src/Governor.hpp"

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

    }

    SUBCASE("Sanction action with less that 3 coins") {
        Game game;
        Player* p1 = new Player(game, "CoupMaker", "Spy");
        Player* p2 = new Player(game, "target", "Spy");        
        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        CHECK_THROWS_AS(p1->sanction(*p2), std::invalid_argument);

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

    }

    SUBCASE("Bribe action with less that 4 coins") {
        Game game;
        Player* p = new Player(game, "Briber", "Spy");
        game.addPlayer(p);
        game.startGame();

        CHECK_THROWS_AS(p->bribe(), std::invalid_argument);
    }

    SUBCASE("Tax action") {
        Game game;
        Player* p = new Player(game, "Taxer", "Spy");
        game.addPlayer(p);
        game.startGame();

        p->tax();
        CHECK(p->coins() == 2);
    }

    SUBCASE("Gather action") {
        Game game;
        Player* p = new Player(game, "Gatherer", "Spy");
        game.addPlayer(p);
        game.startGame();

        p->gather();
        CHECK(p->coins() == 1);
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

    }
}

TEST_CASE("Tests for the Spy class") {
    SUBCASE("Spy constructor and inheritance from Player") {
        coup::Game game;
        coup::Spy* s = new coup::Spy(game, "Shadow");
        game.addPlayer(s);
        game.startGame();

        CHECK(s->getName() == "Shadow");
        CHECK(s->getRole() == "Spy");
        CHECK(s->getAlive());
        CHECK(s->coins() == 0);
    }

    SUBCASE("Spy showCoinsAmount returns correct value") {
        coup::Game game;
        coup::Spy* spy = new coup::Spy(game, "Spy");
        coup::Player* target = new coup::Player(game, "Target", "Spy");
        game.addPlayer(spy);
        game.addPlayer(target);
        game.startGame();

        for (int i = 0; i < 3; ++i) {
            spy->gather();
            target->gather();
        }

        CHECK(spy->showCoinsAmount(*target) == 3);
    }

    SUBCASE("Spy showCoinsAmount throws if Spy is dead") {
        coup::Game game;
        coup::Spy* spy = new coup::Spy(game, "Spy");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(spy);
        game.addPlayer(target);
        game.startGame();

        spy->setAlive(false);
        CHECK_THROWS_AS(spy->showCoinsAmount(*target), std::runtime_error);

    }

    SUBCASE("Spy showCoinsAmount throws if target is dead") {
        coup::Game game;
        coup::Spy* spy = new coup::Spy(game, "Spy");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(spy);
        game.addPlayer(target);
        game.startGame();

        target->setAlive(false);
        CHECK_THROWS_AS(spy->showCoinsAmount(*target), std::runtime_error);

    }

    SUBCASE("Spy blockArrest") {
        coup::Game game;
        coup::Spy* spy = new coup::Spy(game, "Spy");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(spy);
        game.addPlayer(target);
        game.startGame();

        spy->blockArrest(*target);
        CHECK(target->getArrestBlocked());

        // Checking that the block arrest doesnt let him usr the arrest action in his turn.
        spy->gather();
        target->arrest(*spy);
        CHECK(target->getArrestBlocked());
        target->gather();
        CHECK(!target->getArrestBlocked());
    }
}

TEST_CASE("Tests for the Governor class") {
    SUBCASE("Governor constructor sets role correctly") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        game.addPlayer(gov);
        game.startGame();

        CHECK(gov->getName() == "Greg");
        CHECK(gov->getRole() == "Governor");
        CHECK(gov->getAlive() == true);
    }

    SUBCASE("Governor tax adds 3 coins when not sanctioned") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* dummy = new coup::Player(game, "Dummy", "Spy");

        game.addPlayer(gov);
        game.addPlayer(dummy);
        game.startGame();

        gov->tax();  // Governor's turn
        CHECK(gov->coins() == 3);

        dummy->gather(); // Dummy's turn
    }

    SUBCASE("Governor tax does nothing if sanctioned") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* dummy = new coup::Player(game, "Dummy", "Spy");

        game.addPlayer(gov);
        game.addPlayer(dummy);
        game.startGame();

        for (int i = 0; i < 3; ++i){
            gov->gather();
            dummy->gather();
        }

        gov->sanction(*dummy);
        dummy->tax();  // Should not add coins due to sanction

        CHECK(dummy->coins() == 3);
        dummy->gather(); // Complete dummy's turn
    }

    SUBCASE("Governor undo reduces player's coins by 2") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(gov);
        game.addPlayer(target);
        game.startGame();

        // Ensure target has coins
        gov->gather();
        target->gather(); 
        gov->gather();

        target->gather(); 
        int before = target->coins(); // Should be 2

        bool result = gov->undo(*target);
        CHECK(result == true);
        CHECK(target->coins() == before - 2);
    }

    SUBCASE("Undo throws if Governor is not alive") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(gov);
        game.addPlayer(target);
        game.startGame();

        gov->setAlive(false);

        CHECK_THROWS_WITH(gov->undo(*target), "Governor is out of the game.");
    }

    SUBCASE("Undo throws if target player is not alive") {
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* target = new coup::Player(game, "Target", "Spy");

        game.addPlayer(gov);
        game.addPlayer(target);
        game.startGame();

        target->setAlive(false);

        CHECK_THROWS_WITH(gov->undo(*target), "Target player is out of the game.");
    }

    SUBCASE("Governor gets 3 coins instead of 3 in Tax action"){
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");

        game.addPlayer(gov);
        game.startGame();

        gov->tax();
        CHECK(gov->coins() == 3);
    }

    SUBCASE("Governor can undo the Tax action of other players"){
        coup::Game game;
        coup::Governor* gov = new coup::Governor(game, "Greg");
        coup::Player* target = new coup::Player(game, "Target", "Spy");
        game.addPlayer(target);
        game.addPlayer(gov);
        game.startGame();

        target->tax();
        gov->undo(*target);

        CHECK(target->coins() == 0);
    }
}

TEST_CASE("Tests for the Baron class") {
    SUBCASE("Constructor sets correct name and role") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        CHECK(baron->getName() == "Ron");
        CHECK(baron->getRole() == "Baron");
    }

    SUBCASE("Invest increases coins correctly if 3 or more coins") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        game.addPlayer(baron);
        game.startGame();

        game.addPlayer(baron);
        baron->gather();
        baron->gather();
        baron->gather();
        CHECK(baron->coins() == 3);

        // Perform invest
        baron->invest();

        // Should now have 6 coins
        CHECK(baron->coins() == 6);
    }

    SUBCASE("Invest does nothing if coins < 3") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        game.addPlayer(baron);
        game.startGame();
        CHECK(baron->coins() == 0);

        // Should not throw or change anything
        baron->invest();
        CHECK(baron->coins() == 0);  // Still 2
    }

    SUBCASE("Invest throws if Baron is not alive") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        baron->setAlive(false);  // Simulate death
        CHECK_THROWS_WITH(baron->invest(), "This Baron is out of the game.");
    }

    SUBCASE("Compensation gives coin if sanctioned") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        Baron* baron2 = new Baron(game, "Dan");
        game.addPlayer(baron);
        game.addPlayer(baron2);
        game.startGame();

        for (int i = 0; i < 3; ++i){
            baron->gather();
            baron2->gather();
        }

        baron->sanction(*baron2);
        CHECK(baron2->coins() ==  4);
    }

    SUBCASE("Multiple invest calls accumulate coins") {
        Game game;
        Baron* baron = new Baron(game, "Ron");
        game.addPlayer(baron);
        game.startGame();

        for (int i = 0; i < 3; ++i){
            baron->gather();
        }
        
        baron->invest();  // +3 , now 6
        CHECK(baron->coins() == 6);

        baron->invest();  // +3 again, now 12
        CHECK(baron->coins() == 9);
    }
}


TEST_CASE("Tests for the General class") {
    SUBCASE("Constructor sets correct name and role") {
        Game game;
        General* general = new General(game, "Commander");
        game.addPlayer(general);
        game.startGame();

        CHECK(general->getName() == "Commander");
        CHECK(general->getRole() == "General");
    }

    SUBCASE("Undo works correctly with valid conditions") {
        Game game;
        General* general = new General(game, "Commander");
        General* general2 = new General(game, "noa");
        General* general3 = new General(game, "shani");
        game.addPlayer(general);
        game.addPlayer(general2);
        game.addPlayer(general3);
        game.startGame();

        for (int i = 0; i < 7; i++){
            general->gather();
            general2->gather();
            general3->gather();
        }
        CHECK(general->coins() == 7);
        
        general3->undo(*general2);
        CHECK(general3->coins() == 2);  // Should have spent 5 coins for undo

        general->coup(*general2);
        CHECK(general->coins() == 0);  // Should have spent 7 coins for coup
        CHECK(general2->getAlive()); // Should be true
    }

    SUBCASE("Undo fails if General is dead") {
        Game game;
        General* general = new General(game, "Commander");
        General* general2 = new General(game, "noa");
        game.addPlayer(general);
        game.addPlayer(general2);
        game.startGame();
        general->setAlive(false);
        CHECK_THROWS_WITH(general->undo(*general2), "General is out of the game.");
    }

    SUBCASE("Undo fails if target player is dead") {
        Game game;
        General* general = new General(game, "Commander");
        General* general2 = new General(game, "noa");
        game.addPlayer(general);
        game.addPlayer(general2);
        game.startGame();

        general2->setAlive(false);

        for (int i = 0; i < 5; i++){
            general->gather();
        }
        CHECK_THROWS_WITH(general->undo(*general2), "Target player is out of the game.");
    }

    SUBCASE("Undo fails if General has fewer than 5 coins") {
        Game game;
        General* general = new General(game, "Commander");
        General* general2 = new General(game, "noa");
        game.addPlayer(general);
        game.addPlayer(general2);
        game.startGame();

        general->gather();
        general2->gather();
        
        CHECK(general->coins() == 1);
        CHECK_THROWS_WITH(general->undo(*general2), "General doesnt have 5 coins to undo.");
    }
}


TEST_CASE("Tests for the Judge class") {
    
    SUBCASE("Constructor sets correct name and role") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        game.addPlayer(judge);
        game.startGame();

        CHECK(judge->getName() == "Dan");
        CHECK(judge->getRole() == "Judge");
    }

    SUBCASE("Undo works correctly with valid conditions") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        Judge* target = new Judge(game, "Roni");
        Judge* extra = new Judge(game, "Maya");

        game.addPlayer(judge);
        game.addPlayer(target);
        game.addPlayer(extra);
        game.startGame();

        target->setAnotherTurn(true);
        CHECK(target->hasAnotherTurn() == true);

        bool result = judge->undo(*target);
        CHECK(result == true);
        CHECK(target->hasAnotherTurn() == false);
    }

    SUBCASE("Undo fails if Judge is dead") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        Judge* target = new Judge(game, "Maya");

        game.addPlayer(judge);
        game.addPlayer(target);
        game.startGame();

        judge->setAlive(false);

        CHECK_THROWS_WITH(judge->undo(*target), "Judge is out of the game.");
    }

    SUBCASE("Undo fails if target player is dead") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        Judge* target = new Judge(game, "Roni");

        game.addPlayer(judge);
        game.addPlayer(target);
        game.startGame();

        target->setAlive(false);

        CHECK_THROWS_WITH(judge->undo(*target), "Target player is out of the game.");
    }

    SUBCASE("Undo works even if target never had another turn") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        Judge* target = new Judge(game, "Maya");

        game.addPlayer(judge);
        game.addPlayer(target);
        game.startGame();

        CHECK(target->hasAnotherTurn() == false); 
        bool result = judge->undo(*target);
        CHECK(result == true);
        CHECK(target->hasAnotherTurn() == false);
    }

    SUBCASE("Undo does not affect other players") {
        Game game;
        Judge* judge = new Judge(game, "Dan");
        Judge* target = new Judge(game, "Maya");
        Judge* other = new Judge(game, "Roni");

        game.addPlayer(judge);
        game.addPlayer(target);
        game.addPlayer(other);
        game.startGame();

        target->setAnotherTurn(true);
        other->setAnotherTurn(true);

        judge->undo(*target);
        CHECK(target->hasAnotherTurn() == false);
        CHECK(other->hasAnotherTurn() == true); 
    }
}

TEST_CASE("Tests for the Merchant class") {

    SUBCASE("Constructor sets correct name and role") {
        Game game;
        Merchant* merchant = new Merchant(game, "Dan");
        game.addPlayer(merchant);
        game.startGame();

        CHECK(merchant->getName() == "Dan");
        CHECK(merchant->getRole() == "Merchant");
    }

    SUBCASE("extraCoin does not add coin if Merchant has less than 3 coins") {
        Game game;
        Merchant* merchant = new Merchant(game, "Dan");
        Merchant* p2 = new Merchant(game, "Maya");

        game.addPlayer(merchant);
        game.addPlayer(p2);
        game.startGame();

        merchant->gather(); // 1 coin
        CHECK(merchant->coins() == 1);
        // Try again to call extraCoin() (its called inside gather too)
        merchant->extraCoin(); // should not add anything
        CHECK(merchant->coins() == 1);
    }

    SUBCASE("extraCoin adds one coin if Merchant has at least 3 coins") {
        Game game;
        Merchant* merchant = new Merchant(game, "Ali Baba");
        Spy* p2 = new Spy(game, "Marco Polo");

        game.addPlayer(merchant);
        game.addPlayer(p2);
        game.startGame();

        for (int i = 0; i < 4; i++) {
            merchant->gather();  
            p2->gather();
        }
        
        CHECK(merchant->coins() == 5);
        CHECK(p2->coins() == 4);
    }

    SUBCASE("merchantGotArrested reduces coins by 2") {
        Game game;
        Merchant* merchant = new Merchant(game, "Dan");
        Spy* p2 = new Spy(game, "Maya");
        
        game.addPlayer(p2);
        game.addPlayer(merchant);
        game.startGame();

        for (int i = 0; i < 5; i++) {
            p2->gather();
            merchant->gather();
        }

        CHECK(merchant->coins() == 7);

        p2->arrest(*merchant);
        CHECK(merchant->coins() == 5);
    }
}

TEST_CASE("Game class tests") {
    Game game;

    SUBCASE("Add players and get player names") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);

        auto names = game.players();
        CHECK_EQ(names.size(), 2);
        CHECK_EQ(names[0], "Alice");
        CHECK_EQ(names[1], "Bob");

        SUBCASE("Duplicate name ignored") {
            Governor* dup = new Governor(game, "Alice");
            game.addPlayer(dup);
            CHECK_EQ(game.players().size(), 2); // no new player added
            delete dup;
        }

        SUBCASE("Too many players throws") {
            for (int i = 0; i < 4; i++) {
                game.addPlayer(new Governor(game, "P" + std::to_string(i)));
            }
            CHECK_THROWS_AS(game.addPlayer(new Governor(game, "Overflow")), std::runtime_error);
        }
    }

    SUBCASE("Start game sets first alive player") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        CHECK_EQ(game.turn(), "Alice");
    }

    SUBCASE("Turn passing works and skips dead players") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");
        Governor* p3 = new Governor(game, "Charlie");

        game.addPlayer(p1);
        game.addPlayer(p2);
        game.addPlayer(p3);
        game.startGame();  // Should be Alice

        CHECK_EQ(game.turn(), "Alice");
        game.passTurns(); // Should go to Bob
        CHECK_EQ(game.turn(), "Bob");

        p3->setAlive(false); // Charlie is dead
        game.passTurns(); // Should go to Alice (wrap around)
        CHECK_EQ(game.turn(), "Alice");
    }

    SUBCASE("Remove player marks them dead") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);

        game.removePlayer("Alice");
        CHECK_FALSE(p1->getAlive());
        CHECK(p2->getAlive());
    }

    SUBCASE("Winner only declared when one player alive") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);

        game.removePlayer("Bob");
        CHECK_EQ(game.winner(), "Alice");

        SUBCASE("Calling winner too early throws") {
            game.addPlayer(new Governor(game, "Charlie"));
            CHECK_THROWS_AS(game.winner(), std::runtime_error);
        }
    }

    SUBCASE("Role list returns correct players") {
        Governor* p1 = new Governor(game, "Alice");
        Baron* p2 = new Baron(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);

        auto govs = game.roleList("Governor");
        auto barons = game.roleList("Baron");
        auto generals = game.roleList("General");

        CHECK_EQ(govs.size(), 1);
        CHECK_EQ(barons.size(), 1);
        CHECK_EQ(generals.size(), 0);
    }

    SUBCASE("Assign random roles and all added") {
        std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
        game.assignRandomRoles(names);

        CHECK_EQ(game.getPlayers().size(), 3);
        auto all = game.players();
        CHECK_EQ(all.size(), 3);
    }

    SUBCASE("Get current player returns correct object") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);
        game.startGame();

        Player* current = game.getCurrentPlayer();
        CHECK(current != nullptr);
        CHECK_EQ(current->getName(), game.turn());
    }

    SUBCASE("Get all players returns correct list") {
        Governor* p1 = new Governor(game, "Alice");
        Governor* p2 = new Governor(game, "Bob");

        game.addPlayer(p1);
        game.addPlayer(p2);
        CHECK_EQ(game.getPlayers().size(), 2);
    }
}


