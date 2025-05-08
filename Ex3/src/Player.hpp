#pragma once
#include <string>
#include "Game.hpp"

namespace coup {
class Player {
protected:
    Game& _game;
    std::string _name;
    std::string _role;
    int _coins;
    bool _active;
    std::string _last_action;
    Player* _last_target;
    bool _arrest_blocked = false;
    bool _coup_blocked = false;  // NEW

public:
    Player(Game& game, const std::string& name, const std::string& role);
    virtual ~Player() = default;

    const std::string& name() const;
    const std::string& get_role() const;
    int coins() const;
    bool is_active() const;
    const std::string& last_action() const;

    virtual void gather();
    virtual void tax();
    virtual void bribe();
    virtual void arrest(Player& target);
    virtual void sanction(Player& target);
    virtual void coup(Player& target);

    virtual void undo(Player& other); // for Governor and Judge

    void add_coins(int amount);
    void pay_coins(int amount);
    void eliminate();
    void revive();

    void undo_tax();
    void undo_bribe();

    void check_turn();
    void next_turn();

    void set_arrest_blocked(bool blocked);
    bool is_arrest_blocked() const;

    void set_coup_blocked(bool blocked);
    bool is_coup_blocked() const;    
    virtual void start_turn();
};
} // namespace coup
