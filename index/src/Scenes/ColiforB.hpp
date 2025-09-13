#pragma once
#include <SFML/Graphics.hpp>
#include "Level.hpp"

#include "../Entity/Player.hpp"
#include "../Entity/Friend.hpp"
#include "../Entity/Broccoli.hpp"
#include "../Map/Map.hpp"
#include "../Entity/Ship.hpp"
#include "../UI/TextBox.hpp"
#include "../Engine/GameState.hpp" 
#include "../Engine/GameFunctions.hpp"
#include "../Entity/Spawner.hpp"

class ColiforB : public Level {
    private:
        GameState gameState;

        Map map;
        TileMap* tilemap;

        Player* player;
        Ship ship = Ship (this);
        //Broccoli* enemy;
        //Broccoli* enemy2;
        //std::vector<Entity*> entities;
        //std::vector<Projectile*> projectiles;
        //std::vector<TextBox*> textboxes;
        //std::vector<Enemy> enemies;
        bool toggleKeys = false;
        bool toggle = false;
        bool gameOver = false;

        sf::Clock spawnTimer;
        float spawnInterval = 0.05;

        sf::Clock difficultyTimer;

        sf::Clock garbageCollectorTimer;

        std::vector<TextBox*> textboxes;

        //SpawnerFor<Projectile*> projectiles;
        std::vector<std::tuple<Spawner*, int>> spawners;
    public:
        ColiforB (GameSettings* gameSettings, std::string character) : Level (gameSettings) {
            printf ("ColiforB: Constructor");
            
            setName ("COLIFOR-B");
            

            player = new Player (this, character);
            
            player->setController (getController ());
            

            registerObject (new Broccoli (this, player));
            //enemy = new Broccoli (1, 50.f);
            //enemy2 = new Broccoli ();

            //spawn (new Broccoli(this, player, 1));
            //spawn (new Broccoli(this,  &ship, 10));
            //entities[0]->setPosition (sf::Vector2f (500, 500));
            
            textboxes.push_back (new TextBox ("COLIFOR-B", sf::Vector2f (0, -110), 5, 24, sf::Color::White, true));
            textboxes.push_back (new TextBox ("The Verdant Forest", sf::Vector2f (0, -90), 5, 14, sf::Color::White, true));
            
            tilemap = map.getTileMap ();

            std::cout << "Scene loaded: " << getName() << std::endl;

            difficultyTimer.restart();
        }
        ~ColiforB () {
           delete player;

            /*for (Projectile* p : projectiles) {
                if (p == nullptr)
                    continue;
                delete p;
                p = nullptr;
            }

            for (Entity* e : entities) {
                if (e == nullptr)
                    continue;
                delete e;
                e = nullptr;
            }

            for (std::tuple<Spawner*, int> p : spawners) {
                Spawner* s = std::get<0>(p);

                if (s == nullptr)
                    continue;
                delete s;
                s = nullptr;
            }*/

            for (TextBox* tb : textboxes)
                if (tb != nullptr)
                    delete tb;
            textboxes.clear ();
            //entities.clear ();
        }
        void update (float dt) override {
            for (TextBox* tb : textboxes)
                tb->update (dt);

            if (!player->isDead ()) {
                player->update (dt);

                ship.update (dt);

                //updateSpawners ();
                //updateDifficulty ();
                
                if (sf::Keyboard::isKeyPressed (sf::Keyboard::C)) {
                    if (!toggleKeys) {
                        toggleKeys = true;
                        toggle = !toggle;
                        if (toggle)
                            printf ("Toggled on\n");
                        else
                            printf ("Toggled off\n");
                        /*for (Entity* e : entities) {
                            e->getCollider().shouldDraw = toggle;
                        }*/
                        player->getCollider().shouldDraw = toggle;
                    }
                }
                else {
                    toggleKeys = false;
                }
                /*for (Projectile* p : projectiles) {
                    p->update (dt);
                }*/

                auto entities = getGameObjects ();
                
                for (int i = entities.size() - 1; i >= 0; --i) {
                    Entity* e = (Entity*) entities[i];

                    if (e == nullptr || !e->isActive ())
                        continue;
                    
                    e->update (dt);
                    // Check tilemap collision
                    if (!tilemap->isCoordinateOutsideOfMap (e->getPosition ())) {
                        if (tilemap->isTargetBlocked (e->getCollider ())) {
                            e->getCollider ().setBlocked (true);
                        }
                    }
                    // Check for friends
                    if (e->getTags ().count ("Friend")) {
                        Friend* f = (Friend*) e;

                        if (!f->isFound ()) {
                            if (player->getBounds().intersects (f->getBounds ())) {
                                f->setTarget (&ship);
                            }
                        }
                    }
                    // Check for enemies
                    else if (e->getTags().count ("Enemy")) {
                        if (player->getBounds().intersects (e->getBounds ()))
                            player->damage (e->getVelocity (), 1);
                
                        for (int i = 0; i < player->bullets.size (); i++)
                        {
                            if (player->bullets[i].isColliding (e)) {
                                e->damage (player->getPosition (), 1);
                                player->bullets.erase (player->bullets.begin () + i);

                                if (e->isDead ()) {
                                    e->setActive (false);
                                    //delete e;
                                    //e = nullptr;
                                    //entities.erase(entities.begin () + i);
                                }
                            }

                        }
                    }
                    
                }
                /*if (player->getInputs ().find (6) != player->getInputs ().end()) {
                    if (ship.getInteractionZone().isColliding (player->getCollider ())) {
                        printf ("Healing...\n");
                    }
                }*/
            }
            else {
                if (!gameOver) {
                    gameOver = true;
                    textboxes.push_back (new TextBox ("GAME OVER!", sf::Vector2f (0, 0), -1, 60, sf::Color::Red, true));
                }
                else {
                    
                }
            }
            cleanupAllContainers ();
        }
        void registerProjectile (Projectile* p) {
            //projectiles->push_back (p);
        }
        virtual void setController (std::set<sf::Keyboard::Key>* newController) {
            Scene::setController (newController);
            player->setController (newController);
        }
        void cleanupAllContainers () {

            // Clear projectiles
           /* size_t endIndex = projectiles.size() - 1;

            for (size_t i = projectiles.size () - 1; i >= 0; --i) {
                if (projectiles[i]->isActive ())
                    continue;

                delete projectiles[i];

                projectiles[i] = projectiles[endIndex];
                projectiles[endIndex] = nullptr;
                --endIndex;
            }

            //Clear entites
            endIndex = entities.size() - 1;

            for (size_t i = entities.size () - 1; i >= 0; --i) {
                if (entities[i]->isActive ())
                    continue;

                delete entities[i];

                entities[i] = entities[endIndex];
                entities[endIndex] = nullptr;
                --endIndex;
            }
            */
            // Clear textboxes
            /*size_t endIndex = textboxes.size() - 1;
            for (int i = textboxes.size () - 1; i >= 0; --i) {
                if (textboxes[i]->isActive ())
                    continue;

                delete textboxes[i];

                textboxes[i] = textboxes[endIndex];
                textboxes[endIndex] = nullptr;
                --endIndex;
            }*/
        

        }
        void clearProjectiles () {
             // Clear projectiles
            /*size_t endIndex = projectiles.size() - 1;

            for (size_t i = projectiles.size () - 1; i >= 0; --i) {
                if (projectiles[i]->isActive ())
                    continue;

                delete projectiles[i];

                projectiles[i] = projectiles[endIndex];
                projectiles[endIndex] = nullptr;
                --endIndex;
            }*/
        }
        /*void clearEntities () {

            //Clear entites
            size_t endIndex = entities.size() - 1;

            for (size_t i = entities.size () - 1; i >= 0; --i) {
                if (entities[i]->isActive ())
                    continue;

                delete entities[i];

                entities[i] = entities[endIndex];
                entities[endIndex] = nullptr;
                --endIndex;
            }
        }
        void clearTextboxes () {
            // Clear textboxes
            endIndex = textboxes.size() - 1;

            for (size_t i = textboxes.size () - 1; i >= 0; --i) {
                if (textboxes[i]->isActive ())
                    continue;

                delete textboxes[i];

                textboxes[i] = textboxes[endIndex];
                textboxes[endIndex] = nullptr;
                --endIndex;
            }
        }*/
        /*void cleanupContainer (std::vector& container) {
            
        }*/
        void garbageCollector () {
            if (garbageCollectorTimer.getElapsedTime().asSeconds() > 3.0f) {
                garbageCollectorTimer.restart();
                clearProjectiles ();
                //clearEntities ();
            }
        }
        void updateSpawners () {
            if (spawnTimer.getElapsedTime().asSeconds() < spawnInterval)
                return;
            spawnEnemies ();
            spawnTimer.restart();
        }

        void
        updateDifficulty () {
            if (difficultyTimer.getElapsedTime().asSeconds() < gameState.getNextDifficultyTime ())
                return;

             difficultyTimer.restart ();
            gameState.incrementDifficulty();

            Spawner* newSpawner = getSpawnerForDifficulty (gameState.getDifficulty());
            if (newSpawner != nullptr)
                addSpawner (newSpawner, 1);
        }

        void spawn (Entity* e) {
            //entities.push_back (e);
        }
        Player* getPlayer () {
            return player;
        }
        void addSpawner (Spawner* spawner, unsigned weight) {
            spawners.push_back(std::pair(spawner, weight));
        }
        void draw (sf::RenderWindow& window) override {
                        //room.draw (window);
            //player.draw (window);
            //window.setView (window.getDefaultView ());
            map.draw (window);
            
            ship.draw (window);

            
            player->draw (window);

            //enemy->draw (window);
            //enemy->getCollider().shouldDraw = true;
            //player->getCollider().shouldDraw = true;
            for (GameObject* e : getGameObjects ()) {
                if (e != nullptr && e->canDraw())
                    e->draw (window);
            }
            for (TextBox* tb : textboxes) {
                if (tb != nullptr && tb->isActive ())
                    tb->draw (window);
            }

            window.setView (player->getCamera ());
        }
        void eventHandler (sf::Event& e) override {
            getRegistry()->eventHandler (e);
        }

        Spawner* getSpawnerForDifficulty (unsigned diff) {
            switch (diff) {
                case 1:
                    return new SpawnerFor<Broccoli>();
                default:
                    return nullptr;
            }
        }
        bool
        checkSpawnLocation (int x, int y) {
            if (!map.getTileMap()->getAtCoordinate (x, y)->collidable)
                return true;
            
            return false;

        }
        
        void
        spawnEnemies () {
            int magnitude = 100;
            int distance = 500;
            sf::Vector2i vec = sf::Vector2i (getRandom() % magnitude, getRandom() % magnitude);
            sf::Vector2f normalized = sf::Vector2f (vec.x / magnitude, vec.y / magnitude);

            float scale = distance / vec.y;

            if (vec.x > vec.y)
                scale = distance / vec.x;
            
            normalized = sf::Vector2f(scale * normalized.x * magnitude, scale * normalized.y * magnitude);
            
            if (!checkSpawnLocation (player->getPosition().x + normalized.x, player->getPosition().y + normalized.y)) {
                normalized = -normalized;
                if (!checkSpawnLocation (player->getPosition().x + normalized.x, player->getPosition().y + normalized.y)) {
                    std::cout << "Error: Failed to spawn enemy" << std::endl;
                    return;
                }
            }
            selectEntity(sf::Vector2f(player->getPosition().x + normalized.x, player->getPosition().y + normalized.y));
            // Select enemy, add to world at normalized location.
        }   
        Entity* selectEntity (sf::Vector2f position) {
            unsigned random = getRandom () % 1000;
            unsigned sum = 0;

            for (auto p : spawners) {
                // Each spawner has a weight
                int weight = std::get<1>(p);
                // All weights should add up to 100. So we can select a random number based on this
                sum += weight;

                if (random <= sum) {
                    Spawner* s = std::get<0>(p);
                    s->spawn (this, position);
                    break;
                }       
            }
            return nullptr;
        }
};