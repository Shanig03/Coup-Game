// Email: shanig7531@gmail.com

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

namespace coup {
    class Governor : public Player{

        public:
        Governor(Game& g, const std::string& name);

        void tax() override;

        bool undo(Player& player) override;


        /*
        private:
            bool undoAnswered = false;
            bool undoChoice = false;  // true = undo, false = skip

        public:
            void setUndoAnswer(bool choice) {
                undoChoice = choice;
                undoAnswered = true;
            }

            bool hasAnsweredUndo() const {
                return undoAnswered;
            }

            bool wantsToUndo() const {
                return undoChoice;
            }

            void resetUndoState() {
                undoAnswered = false;
                undoChoice = false;
            }
        */
    };

}




#endif




