#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collision.hpp"

class Collider {
	private:
		std::vector<Collision> collisions;

		sf::RectangleShape hitbox;
		bool bBlocking = false;
		bool bBlocked = false;
		short mask = 0;
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
			hitbox.setOutlineThickness (1.f);
			hitbox.setOutlineColor (sf::Color::White);
			hitbox.setFillColor(sf::Color::Transparent);
			hitbox.setOrigin (hitbox.getSize().x / 2, hitbox.getSize ().y / 2);
		}
		Collider (const Collider& c) {
			*this = c;
		}
		bool
		isBlocking () {
			return bBlocking;
		}
		void
		setBlocking (bool bNewBlocking) {
			bBlocking = bNewBlocking;
		}

		void 
		addLayer (short newLayer) {
			if (newLayer >= 16)
				return;
			mask = mask | (1 << newLayer);
		}
		void removeLayer (short newLayer) {
			mask = mask & ~(1 << newLayer);
		}
		short
		isLayerBlocking (short layer) {
			return mask & (2 ^ layer);
		}
		void
		clear () {
			mask = 0;
		}
		sf::Vector2f* getFourCorners () {
			float width = hitbox.getGlobalBounds().width;
			float height = hitbox.getGlobalBounds().height;
			float left = hitbox.getGlobalBounds().left;
			float top = hitbox.getGlobalBounds().top;

			sf::Vector2f corners[4] = {
				sf::Vector2f (left, top),
				sf::Vector2f (left + width, top),
				sf::Vector2f (left + width, top + height),
				sf::Vector2f (left, top + height)
			};
			
			return corners;
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
		bool isBlocked () {
			return bBlocked;
		}
		void setBlocked (bool newVal) {
			bBlocked = newVal;
		}
		bool 
		contains (sf::Vector2f location) {
			return hitbox.getGlobalBounds ().contains (location);
		}
		bool intersects (Collider& other) {
			sf::Vector2f otherSize = other.getHitbox().getSize();
			sf::Vector2f otherPosition = other.getPosition();

			if ((otherPosition.x - (otherSize.x / 2) < getPosition().x + (hitbox.getSize().x / 2)) &&
				(otherPosition.x + (otherSize.x / 2) > getPosition().x - (hitbox.getSize().x / 2)) &&
				(otherPosition.y - (otherSize.y / 2) < getPosition().y + (hitbox.getSize().y / 2)) &&
				(otherPosition.y + (otherSize.y / 2) > getPosition().y - (hitbox.getSize().y / 2)))
				return true;

			return false;
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
		void 
		draw(sf::RenderWindow& window) {
			if (shouldDraw)
				window.draw (hitbox);
		}
		
};