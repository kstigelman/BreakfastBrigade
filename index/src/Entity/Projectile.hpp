#pragma once
#include "../Scenes/Scene.hpp"
#include "../Engine/GameObject.hpp"

class Projectile : public GameObject {
    private:
        const static float DEFAULT_LIFETIME = 5.0f;

        sf::CircleShape body;
        sf::Vector2f velocity;

        float damage = 1.0;
        float lifetime = 5.0;

        bool bDestroyOnImpact = true;

    public:
        Projectile(Level* level, sf::Vector2f velocity, float damage = 1.0, float lifetime = DEFAULT_LIFETIME) 
        : damage(damage), velocity(velocity), lifetime(lifetime) {
        }
        ~Projectile(){}

		virtual void spawn (Scene* scene) {
			level->registerObject (this);
		}
        void update (float dt) {
            if (active) {
                lifetime -= dt;

                if (lifetime <= 0) {
                    active = false;
                    bShouldDraw = false;
                }

                body.move (velocity * dt);
            }
        }
        void setVelocity (sf::Vector2f newVelocity) {
            velocity = newVelocity;
        }
        void setDamage (float newDamage) {
            damage = newDamage;
        }
        sf::Vector2f getVelocity () {
            return velocity;
        }
        float getDamage () {
            return damage;
        }
        float getLifetimeRemaining () {
            return lifetime;
        }
        void draw (sf::RenderWindow& window) {
            if (canDraw ())
                window.draw (body);
        }
        void onCollision (Entity* other) {
            other->damage(body.getPosition(), damage);
            if (bDestroyOnImpact) {
                active = false;
                bShouldDraw = false;
            }
        }
};