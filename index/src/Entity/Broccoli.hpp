#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Broccoli : public Enemy
{
	protected:
	
	public:
		Broccoli(Level* world, Entity* entityTarget = nullptr, float difficulty = 0.f) : Enemy (world, entityTarget, difficulty)
		{
			//setName ("Broccoli" + std::to_string (id));
			setPosition(sf::Vector2f(300, 180));
			movementSpeed = 10.f;
			
			//animator = new Animator (&texture, &sprite, 2, 2);
			healthBar = HealthBar(5 + (difficulty / 5), sf::Vector2f(20 + (difficulty / 50.f), 3 + (difficulty / 50.f)));
			
			texture.loadFromFile ("resources/sprites/Broccoli.png");
			sprite.setTexture (texture);
			animator = Animator(&sprite, 2, 2);
			sprite.setOrigin(animator.getFrameDim().x / 2, animator.getFrameDim().y / 2);
			
			

			sprite.setScale(2.f + (difficulty / 50.f), 2.f + (difficulty / 50.f));
			/*collider.setHitbox (sf::RectangleShape (sf::Vector2f (
				sprite.getScale().x * collider.getHitbox ().getSize().x,
				sprite.getScale().y * collider.getHitbox ().getSize().y
			)));*/
			collider.setHitbox (sf::RectangleShape (sf::Vector2f (16, 16)));
			//sprite.setOrigin(animator->getFrameDim().x / 2, animator->getFrameDim().y/ 2);
		}
		~Broccoli()
		{
			
		}
		virtual void attack () override {

		}
	
	
};
