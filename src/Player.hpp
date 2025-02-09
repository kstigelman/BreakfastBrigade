#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>

#include "Shot.hpp"
#include "Entity.hpp"
#include "PlayerHealthbar.hpp"
#include "PlayerHUD.hpp"

class Player : public Entity
{
	protected:
		int playerID;
		//Animator animator;
		PlayerHealthbar healthbar;
		sf::View camera;
		//PlayerHUD hud;
		const std::string str = "resources/sprites/Hearts.png";

		sf::RectangleShape shape;
		//GUI gui = GUI(str, 7);

		sf::Clock shotTimer;
		sf::Clock dmgTimer;
		
		float shotCooldown = 0.3f;
		float invincibilityCooldown = 1.f;
		double kbMult = 2000.f;

		std::set<int> inputs;
	public:
		std::vector<Shot> bullets;
		bool canMoveUp = true;
		bool canMoveDown = true;
		bool canMoveLeft = true;
		bool canMoveRight = true;
		
		
		
		//sf::Vector2f bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
		//sf::RectangleShape hitbox = sf::RectangleShape(sf::Vector2f(32, 64));
		/*
		Player ()
		{
			hud = PlayerHUD (&healthbar);

			texture.loadFromFile("index/assets/sprites/Buddy.png");

			sprite.setTextureRect(sf::IntRect(0, 0, 16, 20));
			sprite.setTexture(texture);
			sprite.setPosition(100, 200);
			sprite.setScale(1.f, 1.f);
			
			//animator = Animator (texture, sprite, 2, 2);
		}*/
		Player(World* world, int id = 1)
		: Entity (world, sf::RectangleShape (sf::Vector2f (8, 16)))
		{
			Entity::setName ("Player");
			//hud = PlayerHUD (&healthbar);
			playerID = id;
			
			sprite.setScale (1.f, 1.f);
			sprite.setOrigin (0, 0);
			
			if (texture.loadFromFile("resources/sprites/Buddy.png")) {
				sprite.setTextureRect(sf::IntRect(16 * (id - 1), 0, 16, 20));
				sprite.setTexture(texture);
				sprite.setPosition(180, 240);
			}
			else {
				//drawHitbox = true;
			}

			camera.setSize (576, 576);
			camera.zoom (1.f);
			camera.setCenter (sprite.getPosition ().x, sprite.getPosition ().y);
			camera.setViewport (sf::FloatRect (0, 0.2, 1, 0.8));
			//shape.setSize (sf::Vector2f (24, 32));
			//shape.setFillColor (sf::Color::Blue);
			
			animator = Animator (&sprite, 2, 4);
			
			
		}
		/*
		Player (const Player& p) 
		{
			*this = p;
		}*/
		~Player()
		{
			
			//gui = nullptr;

			//delete gui;
		}
		void update(float dt)
		{
			//hitbox.setPosition(sprite.getPosition());
			//bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
			//animator.update ();
			/*
			if(sprite.getPosition().x >= 360 - 8)
				canMoveRight = false;
			else
				canMoveRight = true;

			if(sprite.getPosition().x <= 0 + 8)
				canMoveLeft = false;
			else
				canMoveLeft = true;

			if(sprite.getPosition().y <= 120 + 8)
				canMoveUp = false;
			else
				canMoveUp = true;

			if(sprite.getPosition().y >= 480 - 10)
				canMoveDown = false;
			else
				canMoveDown = true;
			*/
			movement(dt);


			shoot(dt);
			camera.setCenter (sprite.getPosition ());
		}
		void draw(sf::RenderWindow& window)
		{
			//Entity::draw (window);
			window.setView (camera);
			window.draw (sprite);
			
			
			collider.draw (window);
			//window.draw(sprite);
			//gui->Draw(window);
			healthbar.draw (window);
			window.setView (camera);
			/*for(size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].draw(window);
			}*/
			//hud.draw (window);
		}
		
		std::set<int>
		keysPressed ()
		{
			std::set<int> keys;

			if (sf::Keyboard::isKeyPressed (sf::Keyboard::W))
				keys.insert (1);
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::A))
				keys.insert (2);
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::S))
				keys.insert (3);
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
				keys.insert (4);
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space))
				keys.insert (5);
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::E))
				keys.insert (6);

			return keys;
		}
		std::set<int> &getInputs () {
			return inputs;
		}
		int pressingButton()
		{
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::W))
				return 1;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				return 2;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				return 3;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				return 4;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				return 5;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				return 6;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				return 7;
			return 0;
		}
		void movement(float dt)
		{
			inputs = keysPressed ();
			int keyInput = pressingButton();
			if(keyInput != 0)
			{
				animator.nextFrame();
			}
			switch(keyInput)
			{
				case 1:
					if(canMoveUp)
						move (sf::Vector2f (0, -100 * dt));
					break;
				case 2:
					if(canMoveLeft)
						move (sf::Vector2f (-100 * dt, 0));
					break;
				case 3:
					if(canMoveDown)
						move (sf::Vector2f (0, 100 * dt));
					break;
				case 4:
					if(canMoveRight)
						move (sf::Vector2f (100 * dt, 0));
					break;
				case 5:
					damage (sf::Vector2f (100 * dt, 100 * dt), 1);
					break;
				case 7:
					canDraw = true;
					printf ("Now showing hitbox");
					break;
				default:
					break;
			}
			collider.setPosition (sprite.getPosition ());
			//sprite.move (velocity.x * dt, velocity.y * dt);
			
		}
		void
		move (sf::Vector2f vec) {
			sprite.move (vec);
			shape.setPosition (sprite.getPosition ());
			setColliderPosition (sprite.getPosition ());
		}
		sf::Vector2f getPosition()
		{
			return sprite.getPosition();
		}
		sf::Vector2f getCopyPosition ()
		{
			return sprite.getPosition ();
		}
		int shootDirection()
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				return 1;
				
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				return 2;
				
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				return 3;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				return 4;
			
			return 0;
		}
		void shoot(float dt)
		{
			int direction = shootDirection();
			if(direction != 0)
			{
				if(canShoot())
				{
					//b.SetPosition(sprite.getPosition().x, sprite.getPosition().y);
					bullets.push_back(Shot(sprite.getPosition(), direction));
					shotTimer.restart();
				}
			}
			for(size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].move(dt);
					
				if(bullets[i].getPosition().x < -20 || bullets[i].getPosition().x > 380 || bullets[i].getPosition().y > 480 || bullets[i].getPosition().y < 100)
				{
					bullets.erase(bullets.begin() + i);
				}
			}
			
		}
		void damage(sf::Vector2f source, int amount)
		{
			if (canTakeDamage ())
			{
				healthbar.takeDamage (amount);
				dmgTimer.restart ();
			}
			else {
				//if (dmgTimer.getElapsedTime ().asSeconds () <= invincibilityCooldown * 0.5)
				
					
			}

				/*
				if(health != 1)
				{
					
					//gui->NextFrame();
					
				}
				else
				{
					dead = true;
				}*/
				
			
		}
		void takeKnockback (sf::Vector2f source) {
			takeKnockback (source, 1.0f);
		}
		void takeKnockback (sf::Vector2f source, double multiplier)
		{
			sprite.move (source.x * multiplier, source.y * multiplier);
		}
		bool gameOver()
		{
			return dead;
		}
		bool isDead () {
			return healthbar.dead();
		}
		bool canTakeDamage()
		{
			return dmgTimer.getElapsedTime ().asSeconds () >= invincibilityCooldown;
		}
		bool canShoot()
		{
			return shotTimer.getElapsedTime ().asSeconds () >= shotCooldown;
		}
		sf::View& getCamera () {
			return camera;
		}
		/*
		Player& operator=(const Player& rhs)
		{
			if (this == &rhs)
				return *this;

			playerID = rhs.playerID;
			//animator = rhs.animator;
			//healthbar = rhs.healthbar;

			//hud = rhs.hud;

			shotTimer = rhs.shotTimer;
			dmgTimer = rhs.dmgTimer;

			shotCooldown = rhs.shotCooldown;
			invincibilityCooldown = rhs.invincibilityCooldown;
			kbMult = rhs.kbMult;
		
			bullets = rhs.bullets;
			canMoveUp = rhs.canMoveUp;
			canMoveDown = rhs.canMoveDown;
			canMoveLeft = rhs.canMoveLeft;
			canMoveRight = rhs.canMoveRight;

			return *this;
		}*/
		

			
};
