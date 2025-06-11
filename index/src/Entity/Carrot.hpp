#pragma once

#include <SFML/Graphics.hpp>

#include "Enemy.hpp"

class Carrot : public Enemy
{
	protected:
	
	public:
		Carrot()
		{
			
			setPosition(sf::Vector2f(100, 400));
			
			texture.loadFromFile("resources/sprites/Carrot.png");
			
			
			sprite.setTexture(texture);
			//movementSpeed = 25.f;
			
			
			animator = Animator(&texture, &sprite, 2, 2);
			healthBar = new HealthBar(8, sf::Vector2f(20, 3));
			sprite.setOrigin(animator.getFrameDim().x / 2, animator.getFrameDim().y/ 2);
			
			
		}
		virtual ~Carrot()
		{
			healthBar = nullptr;
			target = nullptr;
		}
	
	
};

