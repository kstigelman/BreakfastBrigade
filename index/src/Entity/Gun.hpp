#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.hpp"
#include "Spawner.hpp"

class Gun {
    private:
        class Level* scene;

        float damage = 1.0;
        float bulletSpeed = 1.0;

        float reloadTime = 0.4f;

        sf::Clock reloadClock;
        SpawnerFor<Projectile*>* projectileSpawner;

        std::string ownerTag;
    public:
        Gun (Level* scene, float damage = 1.0, float bulletSpeed = 1.0) : scene(scene), damage(damage), bulletSpeed(bulletSpeed) {
            //scene->registerObject ();
        }
        ~Gun () {

        }
        virtual void shoot (sf::Vector2f direction) {
            if (!canShoot ())
                return;

            reloadClock.restart();
            scene->registerProjectile (new Projectile (scene, direction, ownerTag));
        }
        bool canShoot () {
            return reloadClock.getElapsedTime().asSeconds () >= reloadTime;
        }    
        void setOwnerTag (std::string tag) {
            ownerTag = tag;
        }   
};