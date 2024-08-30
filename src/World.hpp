#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"
#include "Broccoli.hpp"
#include "Map.hpp"

class World {
    private:
        Map map;
        Player* player;
        //Broccoli* enemy;
        //Broccoli* enemy2;
        std::vector<Entity> entities;
        //std::vector<Enemy> enemies;
    public:
        World () {
            player = new Player (this);
            //enemy = new Broccoli (1, 50.f);
            //enemy2 = new Broccoli ();
            spawn (Broccoli(this, 1));
            spawn (Broccoli(this, 10));
            entities[0].setPosition (sf::Vector2f (500, 500));
            //enemy->setTarget (player);
            //enemy.isActive = false;
            /*for (int i = 0; i < 4; ++i) {
                enemies.push_back (enemy);
            //    enemies[i].isActive = true;
                enemies[i].SetPosition (sf::Vector2f (50 * i, enemies[i].GetPosition ().y));
            }*/
        }
        ~World () {
           delete player;
        }
        void update (float dt) {
            player->update (dt);
            //enemy->update (dt);

            for (Entity e : entities) {
                e.update (dt);

                if (e.isActive ())
                    if (player->getBounds().intersects (e.getBounds ()))
                        player->damage (e.getVelocity (), 1);
            
                for (size_t i = 0; i < player->bullets.size (); i++)
                {
                    if (e.isActive () && player->bullets[i].isColliding (&e)) {
                        e.damage (player->getPosition (), 1);
                        player->bullets.erase (player->bullets.begin () + i);
                    }
                
                }
            }
            //enemy2->update (dt);
            //std::cout << enemy.GetTarget () << std::endl;
            
            /*
            for (size_t i = 0; i < enemies.size (); ++i) 
            {
                if (!enemies[i].isActive)
                {
                    enemies[i] = enemies[enemies.size () - 1];
                    enemies.pop_back ();
                    break;
                }
                    
                if (player.GetBounds ().intersects (enemies[i].GetBounds ()))
                    player.Damage (enemies[i].getVelocity (), 1);
            }
            */
            
           
        }
        void draw(sf::RenderWindow& window) {
            //room.draw (window);
            //player.draw (window);
           map.Draw (window);
           player->draw (window);
           //enemy->draw (window);
           //enemy->getCollider().shouldDraw = true;
            player->getCollider().shouldDraw = true;
           //enemy2->draw (window);
        }
        void spawn (Entity e) {
            entities.push_back (e);
        }
        Player* getPlayer () {
            return player;
        }
};