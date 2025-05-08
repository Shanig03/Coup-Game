
// Game.cpp
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
Game::Game() : _current_turn(0) {}

void Game::add_player(Player* player) {
    if (_players.size() >= 6) {
        throw std::runtime_error("Maximum number of players reached.");
    }
    _players.push_back(player);
}

std::string Game::turn() const {
    if (_players.empty()) {
        throw std::runtime_error("No players in game.");
    }
    return _players.at(_current_turn)->name();
}

std::vector<std::string> Game::players() const {
    std::vector<std::string> names;
    for (auto* p : _players) {
        if (p->is_active()) {
            names.push_back(p->name());
        }
    }
    return names;
}

std::string Game::winner() const {
    std::string winner_name;
    int count = 0;
    for (auto* p : _players) {
        if (p->is_active()) {
            winner_name = p->name();
            count++;
        }
    }
    if (count == 1) {
        return winner_name;
    }
    throw std::runtime_error("Game is still ongoing.");
}

void Game::advance_turn() {
    size_t original = _current_turn;
    do {
        _current_turn = (_current_turn + 1) % _players.size();
    } while (!_players[_current_turn]->is_active() && _current_turn != original);
}

size_t Game::current_turn_index() const {
    return _current_turn;
}
}