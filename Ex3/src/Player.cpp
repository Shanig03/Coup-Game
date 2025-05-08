
// Player.cpp
#include "Player.hpp"
#include <stdexcept>

namespace coup {
Player::Player(Game& game, const std::string& name, const std::string& role)
    : _game(game), _name(name), _role(role), _coins(0), _active(true), _last_action(""), _last_target(nullptr), _arrest_blocked(false) {
    game.add_player(this);
}

const std::string& Player::name() const {
    return _name;
}

const std::string& Player::get_role() const {
    return _role;
}

int Player::coins() const {
    return _coins;
}

bool Player::is_active() const {
    return _active;
}

const std::string& Player::last_action() const {
    return _last_action;
}

void Player::add_coins(int amount) {
    _coins += amount;
}

void Player::pay_coins(int amount) {
    if (_coins < amount) {
        throw std::runtime_error("Not enough coins.");
    }
    _coins -= amount;
}

void Player::eliminate() {
    _active = false;
}

void Player::revive() {
    _active = true;
}

void Player::check_turn() {
    if (!_active) {
        throw std::runtime_error("Player is not active.");
    }
    if (_game.turn() != _name) {
        throw std::runtime_error("Not this player's turn.");
    }
    if (_coins >= 10) {
        throw std::runtime_error("Must perform coup when having 10 or more coins.");
    }
}

void Player::next_turn() {
    _game.advance_turn();
}

void Player::gather() {
    check_turn();
    add_coins(1);
    _last_action = "gather";
    next_turn();
}

void Player::tax() {
    check_turn();
    add_coins(2);
    _last_action = "tax";
    next_turn();
}

void Player::bribe() {
    check_turn();
    pay_coins(4);
    _last_action = "bribe";
    next_turn();
}

void Player::arrest(Player& target) {
    check_turn();
    if (_last_target == &target) {
        throw std::runtime_error("Cannot arrest the same player twice in a row.");
    }
    if (!target.is_active()) {
        throw std::runtime_error("Target is not active.");
    }
    if (target.is_arrest_blocked()) {
        throw std::runtime_error("Arrest is currently blocked for this player.");
    }
    target.pay_coins(1);
    add_coins(1);
    _last_action = "arrest";
    _last_target = &target;
    next_turn();
}

void Player::sanction(Player& target) {
    check_turn();
    pay_coins(3);
    _last_action = "sanction";
    next_turn();
}

void Player::coup(Player& target) {
    check_turn();
    if (coins() < 7) {
        throw std::runtime_error("Not enough coins to perform coup.");
    }
    if (target.is_coup_blocked()) {
        throw std::runtime_error("Coup blocked by another player.");
    }
    pay_coins(7);
    target.eliminate();
    _last_action = "coup";
    next_turn();
}


void Player::undo(Player& other) {
    throw std::runtime_error("Undo not supported by this role.");
}

void Player::undo_tax() {
    if (_last_action != "tax") {
        throw std::runtime_error("No tax action to undo.");
    }
    pay_coins(2);
    _last_action = "";
}

void Player::undo_bribe() {
    if (_last_action != "bribe") {
        throw std::runtime_error("No bribe action to undo.");
    }
    _last_action = ""; // Lost the 4 coins anyway
}

void Player::set_arrest_blocked(bool blocked) {
    _arrest_blocked = blocked;
}

bool Player::is_arrest_blocked() const {
    return _arrest_blocked;
}

void Player::set_coup_blocked(bool blocked) {
    _coup_blocked = blocked;
}

bool Player::is_coup_blocked() const {
    return _coup_blocked;
}

void Player::start_turn() {
    // Default behavior: do nothing.
}


} // namespace coup
