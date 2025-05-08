// Game.hpp
#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace coup {
class Player;

class Game {
private:
    std::vector<Player*> _players;
    size_t _current_turn;

public:
    Game();

    void add_player(Player* player);
    std::string turn() const;
    std::vector<std::string> players() const;
    std::string winner() const;
    void advance_turn();
    size_t current_turn_index() const;
};
} 