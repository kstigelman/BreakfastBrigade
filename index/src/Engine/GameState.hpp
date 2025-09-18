#pragma once
#include "../Entity/Spawner.hpp"
#include "../Scenes/Level.hpp"

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
        void incrementDifficulty () {
            ++difficulty;
        }
        void setDifficulty (unsigned newDifficulty) {
            difficulty = newDifficulty;
        }
        Spawner* getSpawnerForDifficulty (unsigned diff) {
            switch (diff) {
                case 1:
                    return new SpawnerFor<Broccoli>();
                /*case 2:

                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                default:*/
            }
            return nullptr;
        }
        float getNextDifficultyTime () {
            return 60.0 * difficulty;
        }

};