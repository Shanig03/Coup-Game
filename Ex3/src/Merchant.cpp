// Merchant.cpp
#include "Merchant.hpp"

namespace coup {
Merchant::Merchant(Game& game, const std::string& name) : Player(game, name, "Merchant") {}

void Merchant::start_turn() {
    if (coins() >= 3) {
        add_coins(1);
    }
}
} // namespace coup
