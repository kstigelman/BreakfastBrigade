#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>

#include "Shot.hpp"
#include "Entity.hpp"
#include "../UI/PlayerHealthbar.hpp"
#include "../UI/PlayerHUD.hpp"
#include "Gun.hpp"
#include "../Engine/Controls.hpp"

class Player : public Entity
{
	protected:
		int playerID;
		//Animator animator;
		PlayerHealthbar healthbar;
		sf::View camera;

		Gun gun;
		//PlayerHUD hud;
		const std::string str = "resources/sprites/Hearts.png";

		sf::RectangleShape shape;
		//GUI gui = GUI(str, 7);

		std::set<sf::Keyboard::Key>* controller;

		sf::Clock shotTimer;
		sf::Clock dmgTimer;
		
		float shotCooldown = 0.3f;
		float invincibilityCooldown = 1.f;
		double kbMult = 2000.f;

	public:
		std::vector<Shot> bullets;
		bool canMoveUp = true;
		bool canMoveDown = true;
		bool canMoveLeft = true;
		bool canMoveRight = true;

		bool moving = false;
		
		
		void setController (std::set<sf::Keyboard::Key>* newController) {
			controller = newController;
		}
		std::set<sf::Keyboard::Key>* getController () {
			return controller;
		}
		
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
		Player(Level* world, std::string character, int id = 1)
		: Entity (world, sf::RectangleShape (sf::Vector2f (8, 16))), gun(world)
		{
			Entity::setName ("Player");
			//hud = PlayerHUD (&healthbar);
			playerID = id;
			
			sprite.setScale (1.f, 1.f);
			sprite.setOrigin (0, 0);
			
			if (texture.loadFromFile("resources/sprites/Buddy.png")) {
				sf::IntRect textureRect = sf::IntRect(16 * (id - 1), 0, 16, 20);
				sprite.setTextureRect(textureRect);
				sprite.setTexture(texture);
				sprite.setPosition(180, 240);
				sprite.setOrigin (sf::Vector2f(textureRect.width / 2, textureRect.height / 2));
			}
			else {
				//drawHitbox = true;
			}

			camera.setSize (576, 576);
			camera.zoom (0.8f);
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
			processInput (dt);
			//movement(controller, dt);


			//shoot(dt);
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
		void processInput (float dt) {
			/*if (controller == nullptr || controller->empty()) {
				moving = false;
				return;
			}*/

			if (sf::Keyboard::isKeyPressed (MOVE_UP)) {
				move (sf::Vector2f (0, -100 * dt));
				moving = true;
			}
			else if (sf::Keyboard::isKeyPressed (MOVE_LEFT)) {
				move (sf::Vector2f (-100 * dt, 0));
				moving = true;
			}
			else if (sf::Keyboard::isKeyPressed (MOVE_DOWN)) {
				move (sf::Vector2f (0, 100 * dt));
				moving = true;
			}
			else if (sf::Keyboard::isKeyPressed (MOVE_RIGHT)) {
				move (sf::Vector2f (100 * dt, 0));
				moving = true;
			}
			else {
				moving = false;
			}

			if (sf::Keyboard::isKeyPressed (SHOOT_UP)) {
				shoot (sf::Vector2f (0, -100));
			}
			else if (sf::Keyboard::isKeyPressed (SHOOT_LEFT)) {
				shoot (sf::Vector2f (-100 * dt, 0));
			}
			else if (sf::Keyboard::isKeyPressed (SHOOT_DOWN)) {
				shoot (sf::Vector2f (0, 100));
			}
			else if (sf::Keyboard::isKeyPressed (SHOOT_RIGHT)) {
				shoot (sf::Vector2f (100 * dt, 0));
			}


			if (moving)
				animator.nextFrame();
		}
		void movement(float dt)
		{
			//inputs = keysPressed ();

			if (controller == nullptr) 
				return;

			int keyInput = pressingButton();

			if(keyInput != 0)
			{
				
			}
			
			

			switch(keyInput)
			{
				case 1:
					if(canMoveUp)
						
					break;
				case 2:
					if(canMoveLeft)
						
					break;
				case 3:
					if(canMoveDown)
						
					break;
				case 4:
					if(canMoveRight)
						
					break;
				case 5:
					damage (sf::Vector2f (100 * dt, 100 * dt), 1);
					break;
				case 7:
					bDraw = true;
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
		void shoot(sf::Vector2f direction)
		{
			gun.shoot (direction);
			/*
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
			}*/
			
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
