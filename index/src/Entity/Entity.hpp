#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/Collider.hpp"
#include "../UI/HealthBar.hpp"

#include "../Scenes/Scene.hpp"
#include "../Engine/GameObject.hpp"

class Entity : public GameObject
{
	private:
		double BASE_CRIT_CHANCE = 0.05;
		double BASE_MOVEMENT_SPEED = 100.f;
		double BASE_ATTACK_DAMAGE = 1.f; 
		double BASE_ATTACK_SPEED = 2.f; //Represents how many attack per second.
		double BASE_SHIELD = 0.f;
		double BASE_HEALTH = 100.f;
	protected:
		class Level* m_world;

		sf::Texture texture;
		sf::Sprite sprite;

		
		//Animator* animator;
		//HealthBar healthbar;
		Animator animator;
		Collider collider;
		 
		std::string name;
		std::string tag;

		double critChance = BASE_CRIT_CHANCE;
		double movementSpeed = BASE_MOVEMENT_SPEED;
		double attackDamage = BASE_ATTACK_DAMAGE;
		double attackSpeed = BASE_ATTACK_SPEED;
		double shield = BASE_SHIELD;
		double health = BASE_HEALTH;

		bool drawHitbox = false;
	protected:

		bool dead;
	public:
		enum Types { Null, Player };
		
		
		
		Types type;

		
		sf::Vector2f velocity;
		sf::Vector2f externalVelocity;
		

		
		Entity (Level* scene)
		{

			//animator = Animator (texture, 1, 2);
			m_world = scene;
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
		Entity (Level* scene, sf::RectangleShape hitbox)
		{
			m_world = scene;
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

		}
		virtual void spawn (Scene* scene) {
			level->registerObject (this);
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
		Level* getScene () {
			return m_world;
		}
		virtual void update (float dt) {
			sf::Vector2f prevPosition = getPosition();
			move (sf::Vector2f (velocity.x * dt, velocity.y * dt));

			if (collider.isBlocked())
				setPosition (prevPosition);
		}
		virtual void draw(sf::RenderWindow& window)
		{
			window.draw(sprite);
			collider.draw (window);
		}
		sf::Vector2f getPosition() const {
			return sprite.getPosition();
		}
		void setPosition(sf::Vector2f position) {
			transform.position = position;
			sprite.setPosition(position);
			setColliderPosition (sprite.getPosition ());
		}
		sf::Vector2f getVelocity () {
			return velocity;
		}
		sf::FloatRect getBounds() {
			return sprite.getGlobalBounds();
		}
		virtual void move(sf::Vector2f velocity) {
			transform.position += velocity;
			sprite.move(velocity);
			setColliderPosition (sprite.getPosition ());
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
		bool isDead () {
			return dead;
		} 
		void setDead (bool val) {
			dead = val;
		}

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
