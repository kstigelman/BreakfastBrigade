#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI.hpp"

class HealthBar : public GUI
{
	private:
		std::string owner;
		int maxHealth;
		int health;
		bool healthDepleted;
		sf::RectangleShape bar;
		sf::RectangleShape outline;

		bool canTakeDamage = true;
		sf::Clock invincibilityTimer;
		float invincibilityLength = 1.f;
	public:
		HealthBar()
		{
			maxHealth = 100;
		}

		HealthBar(int totalHealth, sf::Vector2f size)
		{
			maxHealth = totalHealth;
			health = totalHealth;
			healthDepleted = false;
			outline.setOutlineColor(sf::Color::White);
			outline.setOutlineThickness(1);
			outline.setFillColor(sf::Color::Black);
			
			
			bar.setSize(size);
			bar.setFillColor(sf::Color::Red);
			/*switch (type)
			{
				case 0:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Cyan);
					
					break;
				case 1:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Red);
					
					break;
				default:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Cyan);
					break;
			}*/
			outline.setSize(bar.getSize());
			
		}
		HealthBar (const HealthBar& h)
		{
			*this = h;
		}
		~HealthBar () 
		{
			destruct ();
		}
		void setInvincibilityLength (float length) {
			invincibilityLength = length;
		}
		virtual void destruct ()
		{
			
		}
		virtual void setColor (sf::Color color)
		{
			bar.setFillColor (color);
		}

		/*
		 * Returns the amount of health the entity has left
		 */
		int getHealth () {
			return health;
		}
		void setHealth (int amount) {
			if (amount >= maxHealth)
				amount = maxHealth;
			health = amount;
		}
		void setMaxHealth (int newAmount) {
			maxHealth = newAmount;
			health = maxHealth;
		}
		virtual void update(float dt, sf::Vector2f position)
		{
			setPosition(sf::Vector2f(position.x - 8, position.y - 25));
		}
		virtual void updateHealth ()
		{
			bar.setSize(sf::Vector2f(outline.getSize().x * health / maxHealth, bar.getSize().y));
		}
		
		virtual void setPosition(sf::Vector2f position)
		{
			outline.setPosition(position);
			bar.setPosition(position);
		}
		virtual void draw(sf::RenderWindow& window)
		{
			window.draw(outline);
			window.draw(bar);
		}
		virtual sf::Vector2f getPosition()
		{
			return bar.getPosition();
		}
		virtual void move(sf::Vector2f movement)
		{
			outline.move(movement);
			bar.move(movement);
		}
		virtual void heal(int amount)
		{
			health += amount; 
				
			if (health > maxHealth)
				health = maxHealth;
			
			updateHealth ();
			
		}
		void takeDamage(int strength)
		{
			// Healing should be possible even if taking damage is not.
			if (strength < 0) {

				return;
			}
			if (invincibilityTimer.getElapsedTime().asSeconds() < invincibilityLength) {
				return;
			}				
			//health -= strength + opposingStat;
			health -= strength;

			if (health <= 0)
			{
				health = 0;
				healthDepleted = true;
			}
			/*
				When I removed Draw from Battle, this gives an error
				Edit: You hecking idiot, you forgot to uncomment the next line and was wondering why it wasnt working
			*/
			std::cout << std::to_string (health) << std::endl;
			updateHealth ();
			invincibilityTimer.restart();
			
		}
		bool dead() {
			return healthDepleted;
		}
		std::string getOwner() {
			return owner;
		}
		int getMaxHealth() {
			return maxHealth;
		}
		/*HealthBar& operator= (const HealthBar& rhs)
		{
				
			return *this;
		}*/
};
