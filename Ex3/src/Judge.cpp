#include "Judge.hpp"

namespace coup {
Judge::Judge(Game& game, const std::string& name) : Player(game, name, "Judge") {}

void Judge::undo(Player& other) {
    if (other.last_action() != "bribe") {
        throw std::runtime_error("Can only undo bribe actions");
    }
    other.undo_bribe();
}
} 