
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Baron.hpp"
#include "General.hpp"

using namespace coup;

int main() {
    Game g;
    Governor gov(g, "shani");
    Baron bar(g, "noa");
    General gen(g, "shir");

    g.addPlayer(&gov);
    g.addPlayer(&bar);
    g.addPlayer(&gen);
    g.startGame();

    // First round of gathers
    gov.gather(); bar.gather(); gen.gather();

    // Second round: tax by governor
    gov.tax(); bar.gather(); gen.gather();

    // Governor tax action
    std::cout << "Governor coins before tax: " << gov.coins() << std::endl;
    gov.tax();
    std::cout << "Governor coins after tax: " << gov.coins() << std::endl;

    // Sanction and check
    gov.sanction(bar);
    try { bar.gather(); } 
    catch (const std::exception& e) { std::cout << "Baron sanctioned: " << e.what() << std::endl; }

    // Arrest attempt on governor
    try { bar.arrest(gov); }
    catch (const std::exception& e) { std::cout << "Arrest failed: " << e.what() << std::endl; }

    std::cout << "current turn : " << g.turn() << std::endl;
    // Final round and winner check
    gen.gather(); 
    std::cout << "bar coins before gather:  " << bar.coins() << std::endl;
    gov.gather(); 
    std::cout << "gen coins before gather: " << gen.coins() << std::endl;
    bar.gather();
    try { std::cout << "Winner: " << g.winner() << std::endl; }
    catch (const std::exception& e) { std::cout << "No winner yet: " << e.what() << std::endl; }

    return 0;
}
