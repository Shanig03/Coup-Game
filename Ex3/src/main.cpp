
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Baron.hpp"


using namespace coup;

int main() {
    Game g;
    //Player p(g, "shani", "spy");
    //Player bar(g, "noa", "spy");

    Governor gov(g,"shani");
    Baron bar(g, "noa");



    g.addPlayer(&gov);
    g.addPlayer(&bar);

    g.startGame();

    std::cout << "Before action, current player: " << g.turn() << std::endl;
    
    // gather test
    gov.gather();   // shani
    std::cout << "After gather, current player: " << g.turn() << std::endl;

    bar.gather();  // noa

    gov.gather();   // shani
    bar.gather();  // noa

    std::cout << "Befor tax, coins: " << gov.coins() << std::endl;
    // tax test
    gov.tax();      // shani
    std::cout << "After tax, coins: " << gov.coins() << std::endl;

    // arrest test
    bar.gather();  // noa (coins = 3)
    gov.arrest(bar); // shani steals 1 from p2

    std::cout << "Shani coins: " << gov.coins() << std::endl;
    std::cout << "Noa coins: " << bar.coins() << std::endl;

    // sanction test (shani sanctions noa)
    gov.sanction(bar);
    std::cout << "Shani sanctioned Noa." << std::endl;

    // try to gather with sanctioned player (should do nothing)
    try {
        bar.gather(); // Noa is sanctioned → no coin should be added
        std::cout << "Noa coins (should be unchanged): " << bar.coins() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // bribe test (fail: not enough coins)
    try {
        bar.bribe();  // Should throw since noa has <4 coins
    } catch (const std::exception& e) {
        std::cerr << "Bribe failed as expected: " << e.what() << std::endl;
    }

    // make sure turn rotation still works after sanction
    bar.gather();   // noa
    std::cout << "Noa coins (should be unchanged): " << bar.coins() << std::endl;
    std::cout << "Current player: " << g.turn() << std::endl;

    std::cout << "is sanctioned: " <<  bar.getSan() << std::endl;

    bar.arrest(gov); // noa
    
    std::cout << "is sanctioned: " <<  bar.getSan() << std::endl;


    std::cout << "Current player: " << g.turn() << std::endl;

    gov.gather(); // shani

    std::cout << "Current player: " << g.turn() << std::endl;

    bar.gather();

    gov.gather(); // shani

    bar.gather();

    gov.gather(); // shani

    bar.gather();

    gov.gather(); // shani

    bar.gather();

    std::cout << "Baron before sanction, coins: " << bar.coins() << std::endl;
    gov.sanction(bar);
    std::cout << "Baron after sanction, coins: " << bar.coins() << std::endl;

    try {
        g.winner();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    

    std::cout << "is alive before coup: " << gov.getAlive() << std::endl;
    
    try {
        bar.coup(gov);
    } catch (const std::exception& e) {
        std::cerr << "Coup failed: " << e.what() << std::endl;
    }

    std::cout << "is alive after coup: " << gov.getAlive() << std::endl;


    try {
        gov.gather();
    } catch (const std::exception& e) {
        std::cerr << "Gather failed as expected: " << e.what() << std::endl;
    }

    std::cout << "The winner is: " << g.winner() << std::endl;


    return 0;
}
