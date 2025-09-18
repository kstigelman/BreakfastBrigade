#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class EntityCollider : public Collider {
	private:
		sf::RectangleShape hitbox;
		bool rigid = false;
		unsigned mask = 0;
	public:
		bool shouldDraw = false;
		EntityCollider (sf::RectangleShape hb = sf::RectangleShape ()) {
			hitbox = hb;
			hitbox.setOutlineThickness (3.f);
			hitbox.setOutlineColor (sf::Color::White);
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		EntityCollider (float width, float height) {
			hitbox = sf::RectangleShape (sf::Vector2f (width, height));
			hitbox.setOutlineThickness (1.f);
			hitbox.setOutlineColor (sf::Color::White);
			hitbox.setFillColor(sf::Color::Transparent);
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		EntityCollider (const EntityCollider& c) {
			*this = c;
		}
		void 
		addMask (unsigned newMask) {
			mask = mask | newMask;
		}
		void 
		setMask (unsigned newMask) {
			mask = newMask;
		}
		unsigned
		getMask () {
			return mask;
		}
		void
		clear () {
			mask = 0;
		}
		void
		removeMask (unsigned newMask) {
			mask = mask & ~newMask;
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
		void
		setOrigin (sf::Vector2f pos) {
			hitbox.setOrigin (pos);
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
		bool 
		isRigid () {
			return rigid;
		}
		void 
		setRigid (bool val) {
			rigid = val;
		}
		void 
		draw(sf::RenderWindow& window) {
			if (shouldDraw)
				window.draw (hitbox);
		}
		
};