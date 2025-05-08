// Governor.cpp
#include "Governor.hpp"

namespace coup {
Governor::Governor(Game& game, const std::string& name) : Player(game, name, "Governor") {}

void Governor::tax() {
    check_turn();
    add_coins(3);
    next_turn();
}

void Governor::undo(Player& other) {
    if (other.get_role() == "Governor") {
        throw std::runtime_error("Cannot undo another Governor");
    }
    if (other.last_action() != "tax") {
        throw std::runtime_error("Can only undo tax actions");
    }
    other.undo_tax();
}
}