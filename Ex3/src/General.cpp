#include "General.hpp"

namespace coup {
General::General(Game& game, const std::string& name) : Player(game, name, "General") {}

void General::block_coup(Player& target) {
    if (coins() < 5) {
        throw std::runtime_error("Not enough coins to block coup");
    }
    pay_coins(5);
    target.set_coup_blocked(true);
}
}