// Spy.hpp
#pragma once
#include "Player.hpp"

namespace coup {
class Spy : public Player {
public:
    Spy(Game& game, const std::string& name);
    void spy_on(Player& other);
    void prevent_arrest(Player& target);
};
}