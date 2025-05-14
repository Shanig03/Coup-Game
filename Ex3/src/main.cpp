
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
#include "Merchant.hpp"
#include "Judge.hpp"

using namespace coup;

int main() {
    Game g;
    Governor gov(g, "shani");
    Baron bar(g, "noa");
    Judge gen(g, "shir");

    g.addPlayer(&gov);
    g.addPlayer(&bar);
    g.addPlayer(&gen);
    g.startGame();

    std::cout << "Players in game order:" << std::endl;
    for (std::string s : g.players()) {
        std::cout << s << std::endl;
    }

    gov.gather();
    bar.gather();
    gen.gather();

    gov.gather();
    bar.gather();
    gen.gather();

    gov.gather();
    bar.gather();
    gen.gather();

    gov.gather();
    bar.gather();
    gen.gather();

    std::cout << "gov coins before bribe:  " << gov.coins() << std::endl;
    gov.bribe();
    std::cout << "gov coins after bribe:  " << gov.coins() << std::endl;
    gov.gather();
    gov.gather();
    std::cout << "gov coins after turnes:  " << gov.coins() << std::endl;
    bar.gather();
    gen.gather();
    /*
    // First round of gathers
    gov.gather(); bar.gather(); gen.gather();

    // Second round: tax by governor
    gov.tax(); bar.gather(); gen.gather();

    // Governor tax action
    std::cout << "Governor coins before tax: " << gov.coins() << std::endl;
    gov.tax();
    std::cout << "Governor coins after tax: " << gov.coins() << std::endl;

    std::cout << "current turn : " << g.turn() << std::endl;
    bar.gather(); gen.gather();
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
    std::cout << "gov coins before gather:  " << gov.coins() << std::endl;
    gov.gather(); 
    std::cout << "gov coins after gather: " << gov.coins() << std::endl;

    std::cout << "bar coins before gather:  " << bar.coins() << std::endl;
    bar.gather(); //wont be able to use gather
    std::cout << "bar coins after gather: " << bar.coins() << std::endl;

    try { std::cout << "Winner: " << g.winner() << std::endl; }
    catch (const std::exception& e) { std::cout << "No winner yet: " << e.what() << std::endl; }
    
    std::cout << "current turn : " << g.turn() << std::endl;
    std::cout << "is bar sanctioned : " << bar.getSan() << std::endl;
    std::cout << "is gen sanctioned : " << gen.getSan() << std::endl;
    gen.gather();
    std::cout << "current turn : " << g.turn() << std::endl;

    gov.gather(); 
    std::cout << "bar coins before gather:  " << bar.coins() << std::endl;
    bar.gather(); 
    std::cout << "gen coins before gather: " << gen.coins() << std::endl;

    gen.tax();
    gov.gather(); 

    std::cout << "gen coins before arrest: " << gen.coins() << std::endl;
    std::cout << "bar coins before arrest: " << bar.coins() << std::endl;
    bar.arrest(gen);
    std::cout << "gen coins after arrest: " << gen.coins() << std::endl; 
    std::cout << "bar coins before arrest: " << bar.coins() << std::endl;

    std::cout << "gen coins : " << gen.coins() << std::endl;
    gen.coup(bar);

    gov.gather();
    gen.gather();

    std::cout << "gov coins : " << gov.coins() << std::endl;
    gov.bribe();
    std::cout << "gov coins : " << gov.coins() << std::endl;

    gov.tax();
    std::cout << "gov coins : " << gov.coins() << std::endl;

    gov.gather();
    std::cout << "gov coins : " << gov.coins() << std::endl;


    gen.gather();
    std::cout << "gen coins : " << gen.coins() << std::endl;

    */
    return 0;
}
