#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include "../UI/Animator.hpp"
#include "Entity.hpp"
#include "PathfinderComponent.hpp"

class Enemy : public Entity
{
	private:
		PathfinderComponent pathfinderComponent;
	protected:
		const float rad = 180 / 3.14;
		HealthBar healthBar;
		//Animator animator;
		Entity* target;
		

		
	public:
		Enemy(class Level* world, Entity* entityTarget = nullptr, float difficulty = 0.f) : Entity (world, sf::RectangleShape (sf::Vector2f (8, 16)))
		{

			sprite.setPosition(sf::Vector2f(200, 100));
			setTarget (entityTarget);
			//movementSpeed = 20;
			//texture.loadFromFile("resources/sprites/Enemy.png");
			//sprite.setTexture(texture);
			
			//animator = Animator(&sprite, 2, 2);
		
			//healthBar = new HealthBar(5, sf::Vector2f(), sf::Color::Red);
			//sprite.setOrigin(animator.getFrameDim().x / 2, animator.getFrameDim().y/ 2);			
			//setTarget (world->getPlayer ());
			
		}
	    ~Enemy()
		{

		}
		virtual void destruct () {
			//delete healthBar;
			//delete target;
			//Entity::Destruct (); I dont think this is necessary
		}
		virtual void damage(sf::Vector2f source, int amount)
		{
			healthBar.takeDamage(1);
			if (healthBar.dead ()) {
				dead = true;
				active = false;
				bDraw = false;
			}
		}
		virtual void draw (sf::RenderWindow& window)
		{
			if(isActive())
			{
				//animator.nextFrame();
				window.draw(sprite);
				collider.draw (window);
				//healthBar.draw(window);
			}
		}
		void setTarget (Entity* targetCollider)
		{
			target = targetCollider;
			//target = targetPosition;
		}
		std::string GetTarget () {
			if (target == nullptr)
				return getName () + " has no target.";
			return getName () + " is targetting " + target->getName () + " at position: " + target->printPosition ();
		}
		void pathfinding (float dt)
		{
			if (target == nullptr) {
				velocity = sf::Vector2f (0, 0);
				return;
			}

			sf::Vector2f targetPos = target->getPosition ();

			float dx = targetPos.x - sprite.getPosition().x;
			float dy = targetPos.y - sprite.getPosition().y;
				
			float a = std::atan2(dy, dx);
			
			velocity = sf::Vector2f( std::cos(a) * getMovementSpeed(), std::sin(a) * getMovementSpeed());
			//get next position from pathfinder
			// calculate normal vec to move
			
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
				move (sf::Vector2f (velocity.x * dt, velocity.y * dt));
				if (velocity != sf::Vector2f (0, 0))
					animator.nextFrame ();
				healthBar.update(dt, getPosition());
				
				if (target != nullptr) {
					if (collider.isColliding (target->getCollider ())) {
						target->damage (collider.getPosition(), attackDamage);
					}
				}
				if(healthBar.dead())
				{
					active = false;
				}
			}
		}
		
		/*
		Enemy& operator=(const Enemy& rhs) {
			if (this == &rhs)
				return *this;

			destruct ();
			//Entity::Destruct () might be necessary here instead.
			healthBar = rhs.healthBar;
			target = rhs.target;
			animator = rhs.animator;

			return *this;
		}*/
};
