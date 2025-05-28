// Email: shanig7531@gmail.com

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
#include "Spy.hpp"

using namespace coup;

int main() {

    std::cout << "Starting Game" << std::endl;

    Game g;
    Governor* governor = new Governor(g, "shani");
    Baron* baron = new Baron(g, "dan");
    General* general = new General(g, "or");
    Merchant* merchant = new Merchant(g, "shir");
    Judge* judge = new Judge(g, "noa");
    Spy* spy = new Spy(g, "shay");

    g.addPlayer(governor);
    g.addPlayer(baron);
    g.addPlayer(general);
    g.addPlayer(merchant);
    g.addPlayer(judge);
    g.addPlayer(spy);

    g.startGame();

    std::cout << "Players in the game: " << std::endl;
    for (std::string s : g.players()) {
        std::cout << s << std::endl;
    }

    std::cout << "Current turn: " << g.turn() << std::endl;

    // Round 1: Everyone gathers
    for (Player* p : g.getPlayers()) {
        std::cout << p->getName() << " gathers coins." << std::endl;
        p->gather();
    }

    // Illegal move test
    try{
        judge->gather();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    std::cout << "After round 1: " << std::endl;
    for (Player* p : g.getPlayers()) {
        std::cout << "Player " << p->getName() << " has  " << p->coins() << " coins." << std::endl;
    }

    std::cout << "Current turn: " << g.turn() << std::endl;

    // Next rounds
    governor->gather();
    baron->tax();    
    general->tax();
    merchant->gather();
    judge->gather();
    spy->tax();
    governor->undo(*spy);

    std::cout << "After round 2: " << std::endl;
    for (Player* p : g.getPlayers()) {
        std::cout << "Player " << p->getName() << " has  " << p->coins() << " coins." << std::endl;
    }

    governor->gather();
    baron->invest();
    general->gather();
    merchant->gather();
    judge->gather();
    spy->tax();

    std::cout << "After round 3: " << std::endl;
    for (Player* p : g.getPlayers()) {
        std::cout << "Player " << p->getName() << " has  " << p->coins() << " coins." << std::endl;
    }

    governor->tax();
    baron->gather();
    general->gather();
    merchant->gather();
    judge->gather();
    spy->tax();
    
    std::cout << "After round 4: " << std::endl;
    for (Player* p : g.getPlayers()) {
        std::cout << "Player " << p->getName() << " has  " << p->coins() << " coins." << std::endl;
    }

    governor->tax();
    std::cout << governor->getName() << " has " << governor->coins() << " coins." << std::endl;

    // Coup actions
    baron->coup(*governor);
    general->tax();
    merchant->tax();
    judge->gather();
    spy->gather();

    std::cout << "Remaining Players: " << std::endl;
    for (Player* p : g.getPlayers()) {
        if (p->getAlive()) {
            std::cout << "- " << p->getName() << " (" << p->coins() << " coins)" << std::endl;
        }
    }

    baron->tax();
    general->gather();
    merchant->coup(*general);
    judge->gather();
    spy->gather();

    std::cout << "Remaining Players: " << std::endl;
    for (Player* p : g.getPlayers()) {
        if (p->getAlive()) {
            std::cout << "- " << p->getName() << " (" << p->coins() << " coins)" << std::endl;
        }
    }

    baron->tax();
    merchant->tax();
    judge->gather();
    spy->coup(*baron);

    std::cout << "Remaining Players: " << std::endl;
    for (Player* p : g.getPlayers()) {
        if (p->getAlive()) {
            std::cout << "- " << p->getName() << " (" << p->coins() << " coins)" << std::endl;
        }
    }

    merchant->tax();
    judge->coup(*spy);
    try{
        spy->gather(); // Spy got eliminated, can't play. 
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    std::cout << "Remaining Players: " << std::endl;
    for (Player* p : g.getPlayers()) {
        if (p->getAlive()) {
            std::cout << "- " << p->getName() << " (" << p->coins() << " coins)" << std::endl;
        }
    }

    // Trying to check if there a winner before the game ended.
    try{
        g.winner();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    

    merchant->tax();
    judge->tax();

    merchant->coup(*judge);
    try{
        judge->gather(); // Judge got eliminated, can't play. 
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    

    std::cout << "Remaining Players: " << std::endl;
    for (Player* p : g.getPlayers()) {
        if (p->getAlive()) {
            std::cout << "- " << p->getName() << " (" << p->coins() << " coins)" << std::endl;
        }
    }

    // Checking agaain, now that there is only one player in the game.
    try{
        std::cout << "Game ended. Winner: " << g.winner() << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
