#include "Baron.hpp"

namespace coup {
Baron::Baron(Game& game, const std::string& name) : Player(game, name, "Baron") {}

void Baron::invest() {
    if (coins() < 3) {
        throw std::runtime_error("Not enough coins to invest");
    }
    pay_coins(3);
    add_coins(6);
    _last_action = "invest";
}
}
