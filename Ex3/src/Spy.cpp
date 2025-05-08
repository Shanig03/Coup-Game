
// Spy.cpp
#include "Spy.hpp"
#include <iostream>

namespace coup {
Spy::Spy(Game& game, const std::string& name) : Player(game, name, "Spy") {}

void Spy::spy_on(Player& other) {
    std::cout << other.name() << " has " << other.coins() << " coins." << std::endl;
}

void Spy::prevent_arrest(Player& target) {
    target.set_arrest_blocked(true);
}
}