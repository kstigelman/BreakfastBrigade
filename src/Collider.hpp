#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Collider {
	private:
		sf::RectangleShape hitbox;
		bool rigid = false;
	public:
		bool shouldDraw = false;
		Collider (sf::RectangleShape hb = sf::RectangleShape ()) {
			hitbox = hb;
			hitbox.setOutlineThickness (3.f);
			hitbox.setOutlineColor (sf::Color::White);
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		Collider (float width, float height) {
			hitbox = sf::RectangleShape (sf::Vector2f (width, height));
			hitbox.setOutlineThickness (3.f);
			hitbox.setOutlineColor (sf::Color::White);
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		Collider (const Collider& c) {
			*this = c;
		}
		void 
		setHitbox (sf::RectangleShape newHb) {
			hitbox = newHb;
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		sf::RectangleShape 
		getHitbox () {
			return hitbox;
		}
		void 
		setPosition (sf::Vector2f pos) {
			hitbox.setPosition (pos);
		}
		sf::Vector2f 
		getPosition () {
			return hitbox.getPosition();
		}
		bool 
		isColliding (Collider& other) {
			return hitbox.getGlobalBounds ().contains (other.getHitbox ().getPosition ());
		}
		bool 
		contains (sf::Vector2f location) {
			return hitbox.getGlobalBounds ().contains (location);
		}
		/*
		Collider& 
		operator= (const Collider& rhs) 
		{
			if (this == &rhs)
				return *this;

			hitbox = rhs.hitbox;

			return *this;
		}*/
		bool isRigid () {
			return rigid;
		}
		void setRigid (bool val) {
			rigid = val;
		}
		void draw(sf::RenderWindow& window) {
			if (shouldDraw)
				window.draw (hitbox);
		}
		
};