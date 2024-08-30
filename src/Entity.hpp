#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "HealthBar.hpp"

class Entity
{
	private:
		double BASE_CRIT_CHANCE = 0.05;
		double BASE_MOVEMENT_SPEED = 100.f;
		double BASE_ATTACK_DAMAGE = 1.f; 
		double BASE_ATTACK_SPEED = 2.f; //Represents how many attack per second.
		double BASE_SHIELD = 0.f;
		double BASE_HEALTH = 100.f;
		
	protected:
		class World* m_world;

		sf::Texture texture;
		sf::Sprite sprite;

		
		//Animator* animator;
		//HealthBar healthbar;
		Collider collider;
		 
		std::string name;

		double critChance = BASE_CRIT_CHANCE;
		double movementSpeed = BASE_MOVEMENT_SPEED;
		double attackDamage = BASE_ATTACK_DAMAGE;
		double attackSpeed = BASE_ATTACK_SPEED;
		double shield = BASE_SHIELD;
		double health = BASE_HEALTH;

		bool drawHitbox = false;
	public:
		enum Types { Null, Player };
		bool dead;
		
		
		Types type;

		
		sf::Vector2f velocity;
		sf::Vector2f externalVelocity;
		
		bool canDraw;
		bool active;

		Entity (World* world)
		{
			//animator = Animator (texture, 1, 2);
			m_world = world;
			name = "nullentity";
			type = Null;
			active = true;
			dead = false;
			movementSpeed = 0.45f;
			//maxMovementSpeed = 0.7;
			//texture.loadFromFile("index/assets/sprites/null.png");
			//sprite.setTexture(texture);
			//sprite.setPosition(100, 100);
			velocity = sf::Vector2f(0, 0);
			externalVelocity = sf::Vector2f(0, 0);
		}
		Entity (World* world, sf::RectangleShape hitbox)
		{
			m_world = world;
			//animator = Animator (texture, 1, 2);
			name = "nullentity";
			type = Null;
			active = true;
			dead = false;
			movementSpeed = 0.45f;
			//maxMovementSpeed = 0.7;
			//texture.loadFromFile("index/assets/sprites/null.png");
			//sprite.setTexture(texture);
			//sprite.setPosition(100, 100);
			velocity = sf::Vector2f(0, 0);
			externalVelocity = sf::Vector2f(0, 0);
			collider.setHitbox (hitbox);
		}
		Entity (const Entity& e) 
		{
			*this = e;
		}
		~Entity()
		{
			destruct ();
		}
		virtual void init ()
		{

		}
		virtual void destruct ()
		{
		}
		void setName (std::string newName) {
			name = newName;
		}
		std::string getName () {
			return name;
		}
		virtual void update (float dt) {
			setColliderPosition (sprite.getPosition ());
			move (sf::Vector2f (velocity.x * dt, velocity.y * dt));
		}
		virtual void draw(sf::RenderWindow& window)
		{
			window.draw(sprite);
		}
		sf::Vector2f getPosition() const {
			return sprite.getPosition();
		}
		void setPosition(sf::Vector2f position) {
			sprite.setPosition(position);
		}
		sf::Vector2f getVelocity () {
			return velocity;
		}
		sf::FloatRect getBounds() {
			return sprite.getGlobalBounds();
		}
		virtual void move(sf::Vector2f velocity) {
			sprite.move(velocity);
		}
		bool isActive() {
			return active;
		}
		Collider& getCollider () {
			return collider;
		}
		void setColliderPosition (sf::Vector2f loc) {
			collider.setPosition (loc);
		}
		std::string printPosition () const {
			return "(" + std::to_string (getPosition ().x) + ", " + std::to_string (getPosition ().y) + ")";
		}
			
		virtual void damage (sf::Vector2f source, int amount)
		{
			//healthbar.takeDamage (amount);
		}
		double getAttackSpeed () { return attackSpeed; }
		double getMaxAttackSpeed () { return attackSpeed; }
		double getMovementSpeed () { return movementSpeed; }
		void setMovementSpeed (double newSpeed) { movementSpeed = newSpeed;  }
		//double getMaxMovementSpeed () { return maxMovementSpeed; }
		//void setMaxMovementSpeed (double newSpeed) { maxMovementSpeed = newSpeed; }
		//double getHealth () { return healthbar.getHealth (); }
		//double getMaxHealth () { return healthbar.getMaxHealth (); }
		
		friend std::ostream& operator<< (std::ostream& os, const Entity& e) {
			os << e.name << ": " << e.printPosition () << "\n";
			return os;
		}
		/*
		Entity& operator=(const Entity& e) 
		{
			if (this == &e)
				return *this;

			texture = e.texture;
			collider = e.collider;
			name = e.name;
			dead = e.dead;
			movementSpeed = e.movementSpeed;
			//maxMovementSpeed = e.maxMovementSpeed;

			attackDamage = e.attackDamage;
			//maxAttackDamage = e.maxAttackDamage;

			attackSpeed = e.attackSpeed;
			//maxAttackSpeed = e.maxAttackSpeed;

			shield = e.shield;
			//maxShield = e.maxShield;

			sprite = e.sprite;
			velocity = e.velocity;
			externalVelocity = e.externalVelocity;
			canDraw = e.canDraw;
			active = e.active;
			
			return *this;
		}*/
};
