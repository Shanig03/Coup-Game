
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"


using namespace coup;

int main() {
    Game g;
    Player p(g, "shani", "spy");
    Player p2(g, "noa", "spy");

    g.addPlayer(&p);
    g.addPlayer(&p2);

    g.startGame();

    std::cout << "Before action, current player: " << g.turn() << std::endl;
    
    // gather test
    p.gather();   // shani
    std::cout << "After gather, current player: " << g.turn() << std::endl;

    p2.gather();  // noa
    p.gather();   // shani
    p2.gather();  // noa

    // tax test
    p.tax();      // shani

    // arrest test
    p2.gather();  // noa (coins = 3)
    p.arrest(p2); // shani steals 1 from p2

    std::cout << "Shani coins: " << p.coins() << std::endl;
    std::cout << "Noa coins: " << p2.coins() << std::endl;

    // sanction test (shani sanctions noa)
    p.sanction(p2);
    std::cout << "Shani sanctioned Noa." << std::endl;

    // try to gather with sanctioned player (should do nothing)
    try {
        p2.gather(); // Noa is sanctioned → no coin should be added
        std::cout << "Noa coins (should be unchanged): " << p2.coins() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // bribe test (fail: not enough coins)
    try {
        p2.bribe();  // Should throw since noa has <4 coins
    } catch (const std::exception& e) {
        std::cerr << "Bribe failed as expected: " << e.what() << std::endl;
    }

    // make sure turn rotation still works after sanction
    p2.gather();   // noa
    std::cout << "Noa coins (should be unchanged): " << p2.coins() << std::endl;
    std::cout << "Current player: " << g.turn() << std::endl;

    std::cout << "is sanctioned: " <<  p2.getSan() << std::endl;

    p2.arrest(p); // noa
    
    std::cout << "is sanctioned: " <<  p2.getSan() << std::endl;


    std::cout << "Current player: " << g.turn() << std::endl;

    p.gather(); // shani

    std::cout << "Current player: " << g.turn() << std::endl;

    p2.gather();

    p.gather(); // shani

    p2.gather();

    p.gather(); // shani

    p2.gather();

    p.gather(); // shani

    p2.gather();

    try {
        g.winner();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    

    std::cout << "is alive before coup: " << p.getAlive() << std::endl;
    
    try {
        p2.coup(p);
    } catch (const std::exception& e) {
        std::cerr << "Coup failed: " << e.what() << std::endl;
    }

    std::cout << "is alive after coup: " << p.getAlive() << std::endl;


    try {
        p.gather();
    } catch (const std::exception& e) {
        std::cerr << "Gather failed as expected: " << e.what() << std::endl;
    }

    std::cout << "The winner is: " << g.winner() << std::endl;


    return 0;
}
