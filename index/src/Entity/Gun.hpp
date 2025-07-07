#pragma once
#include <SFML/Graphics.hpp>
#include "Shot.hpp"

class Gun {
    private:
        class Level* scene;

        float damage = 1.0;
        float bulletSpeed = 1.0;

        float reloadTime = 0.4f;

        sf::Clock reloadClock;
        SpawnerFor<Projectile*>* projectileSpawner;
    public:
        Gun (Level* scene, float damage = 1.0, float bulletSpeed = 1.0) : scene(scene), damage(damage), bulletSpeed(bulletSpeed) {
            scene->registerObject ();
        }
        ~Gun () {

        }
        virtual void shoot (sf::Vector2f direction) {
            if (!canShoot ())
                return;

            reloadClock.restart();
            scene->registerProjectile (new Projectile (direction, damage));
        }
        bool canShoot () {
            return reloadClock.getElapsedTime( ).asSeconds () >= reloadTime;
        }       
};