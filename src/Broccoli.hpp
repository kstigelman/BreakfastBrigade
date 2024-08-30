#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Broccoli : public Enemy
{
	protected:
	
	public:
		Broccoli(World* world, float difficulty = 0.f) : Enemy (world, difficulty)
		{
			//setName ("Broccoli" + std::to_string (id));
			setPosition(getPosition());
			movementSpeed = 20.f;
			
			//animator = new Animator (&texture, &sprite, 2, 2);
			healthBar = HealthBar(5 + (difficulty / 5), sf::Vector2f(20 + (difficulty / 50.f), 3 + (difficulty / 50.f)));
			animator = Animator(&sprite, 2, 2);

			sprite.setScale(2.f + (difficulty / 50.f), 2.f + (difficulty / 50.f));
			collider.setHitbox (sf::RectangleShape (sf::Vector2f (
				sprite.getScale().x * collider.getHitbox ().getSize().x,
				sprite.getScale().y * collider.getHitbox ().getSize().y
			)));
			//sprite.setOrigin(animator->getFrameDim().x / 2, animator->getFrameDim().y/ 2);
		}
		~Broccoli()
		{
		
		
		}
	
	
};
