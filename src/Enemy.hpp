#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include "Animator.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
	protected:
		const float rad = 180 / 3.14;
		HealthBar healthBar;
		Animator* animator;
		Entity* target;
	public:
		Enemy()
		{
			//movementSpeed = 20;
			
			sprite.setPosition(sf::Vector2f(200, 100));
			texture.loadFromFile("resources/sprites/Enemy.png");
			sprite.setTexture(texture);
			
			sprite.setScale(2.f, 2.f);
			animator = new Animator(&sprite, 2, 2);
			//healthBar = new HealthBar(5, sf::Vector2f(), sf::Color::Red);
			sprite.setOrigin(animator->getFrameDim().x / 2, animator->getFrameDim().y/ 2);			
			
		}
	    ~Enemy()
		{
			destruct ();
		}
		virtual void destruct () {
			//delete healthBar;
			//delete target;
			//Entity::Destruct (); I dont think this is necessary
		}
		virtual void damage(sf::Vector2f source, int amount)
		{
			healthBar.takeDamage(1);
		}
		virtual void draw (sf::RenderWindow& window)
		{
			if(isActive())
			{
				animator->nextFrame();
				window.draw(sprite);
				healthBar.draw(window);
			}
		}
		void setTarget (Entity* targetCollider)
		{
			target = targetCollider;
			//target = targetPosition;
		}
		std::string GetTarget () {
			return getName () + " is targetting " + target->getName () + " at position: " + target->printPosition ();
		}
		void pathfinding (float dt)
		{
			sf::Vector2f targetPos = target->getPosition ();

			float dx = targetPos.x - sprite.getPosition().x;
			float dy = targetPos.y - sprite.getPosition().y;
				
			float a = std::atan2(dy, dx);
			
			velocity = sf::Vector2f( std::cos(a) * getMovementSpeed(), std::sin(a) * getMovementSpeed());
			/*
			if(dx > 0 && dy > 0)
			{
				velocity = sf::Vector2f(std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else if(dx > 0 && dy < 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else if(dx < 0 && dy > 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed,std::sin(a) * dt * movementSpeed);
			}
			else if(dx < 0 && dy < 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed,  std::sin(a) * dt * movementSpeed);
			}*/
			
			
			//velocity = sf::Vector2f(dx * dt / movementSpeed, dy * dt / movementSpeed);
		}
		virtual void update (float dt)
		{
			if (isActive())
			{
				pathfinding (dt);
				Entity::update (dt);
				healthBar.update(dt, getPosition());
				
				if(healthBar.knockedOut())
				{
					active = false;
				}
			}
		}
		
		Enemy& operator=(const Enemy& rhs) {
			if (this == &rhs)
				return *this;

			destruct ();
			//Entity::Destruct () might be necessary here instead.
			healthBar = rhs.healthBar;
			target = rhs.target;
			animator = rhs.animator;

			return *this;
		}
};
