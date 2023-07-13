#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Broccoli.hpp"
class World {
    private:
        Map map;
        Player player;
        Broccoli enemy;
        //std::vector<Enemy> enemies;
    public:
        World () {
            enemy.setTarget (&player);
            //enemy.isActive = false;
            /*for (int i = 0; i < 4; ++i) {
                enemies.push_back (enemy);
            //    enemies[i].isActive = true;
                enemies[i].SetPosition (sf::Vector2f (50 * i, enemies[i].GetPosition ().y));
            }*/
        }
        ~World () {
           
        }
        void update (float dt) {
            player.update (dt);
            enemy.update (dt);
            /*
            //std::cout << enemy.GetTarget () << std::endl;
            
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
            
            if (enemy.isActive ())
                if (player.getBounds().intersects (enemy.getBounds ()))
                    player.damage (enemy.getVelocity (), 1);
            
            for (size_t i = 0; i < player.bullets.size (); i++)
            {
                if (enemy.isActive () && player.bullets[i].isColliding (&enemy)) {
                    enemy.damage (player.getPosition (), 1);
                    player.bullets.erase (player.bullets.begin () + i);
                }
               
            }
        }
        void draw(sf::RenderWindow& window) {
           map.Draw (window);
           player.draw (window);
           enemy.draw (window);
        }
};