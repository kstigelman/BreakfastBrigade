#pragma once

class GameState {
    private:
        unsigned difficulty = 0;
        bool bSpawningPaused = false;
        const unsigned MAX_ENTITY_LIMIT = 100;
        unsigned currentEntityLimit = 20;
    public:
        GameState () {
        }
        bool isSpawningPaused () {
            return bSpawningPaused;
        }
        void setSpawningPaused (bool paused) {
            bSpawningPaused = paused;
        }
        unsigned getDifficulty () {
            return difficulty;
        }

};