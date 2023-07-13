#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Broccoli : public Enemy
{
	protected:
	
	public:
		Broccoli(int id = 0)
		{
			setName ("Broccoli" + std::to_string (id));
			setPosition(getPosition());
			movementSpeed = 20.f;
			
			//animator = new Animator (&texture, &sprite, 2, 2);
			healthBar = HealthBar(5, sf::Vector2f(20, 3));
			//sprite.setOrigin(animator->getFrameDim().x / 2, animator->getFrameDim().y/ 2);
		}
		~Broccoli()
		{
		
		
		}
	
	
};
