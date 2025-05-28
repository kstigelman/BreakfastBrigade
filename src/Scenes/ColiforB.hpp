#pragma once
#include <SFML/Graphics.hpp>
#include "Scenes/Scene.hpp"

#include "Player.hpp"
#include "Broccoli.hpp"
#include "Map.hpp"
#include "Ship.hpp"
#include "TextBox.hpp"

class ColiforB : public Scene {
    private:

        Map map;
        Player* player;
        Ship ship = Ship (this);
        //Broccoli* enemy;
        //Broccoli* enemy2;
        std::vector<Entity*> entities;
        std::vector<TextBox*> textboxes;
        //std::vector<Enemy> enemies;
        bool toggleKeys = false;
        bool toggle = false;
        bool gameOver = false;
    public:
        ColiforB (Game* game) : Scene (game) {
            setName ("COLIFOR-B");
            
            player = new Player (this);
            //enemy = new Broccoli (1, 50.f);
            //enemy2 = new Broccoli ();

            spawn (new Broccoli(this, player, 1));
            spawn (new Broccoli(this,  &ship, 10));
            entities[0]->setPosition (sf::Vector2f (500, 500));

            textboxes.push_back (new TextBox ("COLIFOR-B", sf::Vector2f (0, -110), 5, 24, sf::Color::White, true));
            textboxes.push_back (new TextBox ("The Verdant Forest", sf::Vector2f (0, -90), 5, 14, sf::Color::White, true));
            std::cout << "Scene loaded: " << getName() << std::endl;
        }
        ~ColiforB () {
           delete player;
           for (Entity* e : entities)
                delete e;

            for (TextBox* tb : textboxes)
                if (tb != nullptr)
                    delete tb;
            textboxes.clear ();
            entities.clear ();
        }
        void update (float dt) override {
            if (!player->isDead ()) {
                player->update (dt);

                 ship.update (dt);

                
                for (auto i = textboxes.begin (); i != textboxes.end (); ++i) {
                    if (*i == nullptr)
                        continue;

                    (*i)->update (dt);

                    // "Garbage collector" for textboxes
                    if ((*i)->isActive () == false) {
                        delete *i;
                        *i = nullptr;
                        //textboxes.erase (i);
                    }
                }
                if (sf::Keyboard::isKeyPressed (sf::Keyboard::C)) {
                    if (!toggleKeys) {
                        toggleKeys = true;
                        toggle = !toggle;
                        if (toggle)
                            printf ("Toggled on\n");
                        else
                            printf ("Toggled off\n");
                        for (Entity* e : entities) {
                            e->getCollider().shouldDraw = toggle;
                        }
                        player->getCollider().shouldDraw = toggle;
                    }
                }
                else {
                    toggleKeys = false;
                }
                for (Entity* e : entities) {
                    if (e == nullptr)
                        continue;
                    e->update (dt);

                    if (e->isActive ())
                        if (player->getBounds().intersects (e->getBounds ()))
                            player->damage (e->getVelocity (), 1);
                
                    for (size_t i = 0; i < player->bullets.size (); i++)
                    {
                        if (e->isActive () && player->bullets[i].isColliding (e)) {
                            e->damage (player->getPosition (), 1);
                            player->bullets.erase (player->bullets.begin () + i);
                        }

                    }
                }
                if (player->getInputs ().find (6) != player->getInputs ().end()) {
                    if (ship.getInteractionZone().isColliding (player->getCollider ())) {
                        printf ("Healing...\n");
                    }
                }
            }
            else {
               if (!gameOver) {
                    gameOver = true;
                    textboxes.push_back (new TextBox ("GAME OVER!", sf::Vector2f (0, 0), -1, 60, sf::Color::Red, true));
                    
               }
            }
        }
        void spawn (Entity* e) {
            entities.push_back (e);
        }
        Player* getPlayer () {
            return player;
        }
        void draw (sf::RenderWindow& window) override {
                        //room.draw (window);
            //player.draw (window);
            //window.setView (window.getDefaultView ());
            map.Draw (window);
            
            ship.draw (window);

            
            player->draw (window);
           
            //enemy->draw (window);
            //enemy->getCollider().shouldDraw = true;
            player->getCollider().shouldDraw = true;
            for (Entity* e : entities) {
                if (e != nullptr)
                    e->draw (window);
            }
            for (TextBox* tb : textboxes) {
                if (tb != nullptr)
                    tb->draw (window);
            }
            window.setView (player->getCamera ());
        }
};