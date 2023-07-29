#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Collider {
	private:
		sf::FloatRect hitbox;
	public:
		Collider (sf::FloatRect hb = sf::FloatRect (0, 0, 0, 0)) {
			hitbox = hb;
		}
		Collider (const Collider& c) {
			*this = c;
		}
		void 
		setHitbox (sf::FloatRect newHb) {
			hitbox = newHb;
		}
		sf::FloatRect 
		getHitbox () {
			return hitbox;
		}
		void 
		setPosition (sf::Vector2f pos) {
			hitbox.left = pos.x;
			hitbox.top = pos.y;
		}
		sf::Vector2f 
		getPosition () {
			return sf::Vector2f (hitbox.left, hitbox.top);
		}
		bool 
		isColliding (Collider& other) {
			return hitbox.intersects (other.getHitbox ());
		}
		bool 
		contains (sf::Vector2f location) {
			return hitbox.contains (location);
		}
		Collider& 
		operator= (const Collider& rhs) 
		{
			if (this == &rhs)
				return *this;

			hitbox = rhs.hitbox;

			return *this;
		}
		
};