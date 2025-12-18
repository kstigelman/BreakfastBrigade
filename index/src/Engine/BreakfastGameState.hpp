#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class BreakfastGameState : public GameState {
    private:
        bool bPlayerAlive = true;
        bool bPlayerWon = false;

        int nFriendsFound = 0;

        int score = 0;
        float timePassed = 0;
    public:
        BreakfastGameState ();

        void addTimePassed (float dt) {
            timePassed += dt;
        }
        void addScore (int addedAmount) {
            score += addedAmount;
        }

        bool isPlayerAlive () {
            return bPlayerAlive;
        }

        void setPlayerAlive (bool newAliveValue) {
            bPlayerAlive = newAliveValue;
        }
        void setPlayerWon (bool newWonValue) {
            bPlayerWon = newWonValue;
        }
};