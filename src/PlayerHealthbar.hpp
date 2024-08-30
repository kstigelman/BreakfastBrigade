#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "HealthBar.hpp"

class PlayerHealthbar : public HealthBar
{
	private:
		std::vector<Animator> hearts;
		std::vector<sf::Sprite*> sprites;
		sf::Texture texture;
		sf::Sprite s;
	public:
		PlayerHealthbar (int health = 6)
		: HealthBar (health, sf::Vector2f (0, 0)) 
		{
			texture.loadFromFile ("resources/sprites/Hearts.png");
			
			for (int i = 0; i < health / 2; ++i)
			{
				sprites.push_back (new sf::Sprite (texture));
				hearts.push_back (Animator (texture, sprites[i], 3, 3));
				hearts[i].setSpritePos (sf::Vector2f ((i * 50) + 4, 10));
			}
			
		}
		~PlayerHealthbar () {
			for (size_t i = sprites.size() - 1; i >= 0; --i)
				delete sprites[i];
		}
		
		virtual void destruct () {
			
		}
		virtual void setPosition (sf::Vector2f position) {
			for (size_t i = 0; i < hearts.size(); ++i) {
				hearts[i].setSpritePos (sf::Vector2f ((i * 50) + position.x, position.y));
			}
		}
		virtual void updateHealth () {

			int hR = HealthBar::getHealth();
			std::cout << "health is " << hR << "\n";
			//Invariant: Health must not be less than 0 to update frames, so check out here if it is
			if (hR < 0)
				return;
			//Each heart represents 2 HP. so, we can calculate which heart we need to update
			//with the following equation.
			//int nextHeart = hearts.size() - ((hR + 1) / 2);
			//hearts[hR].NextFrame ();
			
			int nextHeart = hR / 2;
			if (hearts[nextHeart].getCurrentFrame () == 2)
				return;
			hearts[nextHeart].nextFrame ();
			/*
			for (size_t i = 0; i < hearts.size (); ++i)
			{
				std::cout << i << " : " << hearts[i].getFrameDim ().x << ", " << hearts[i].getFrameDim ().y << ". " << hearts[i].getOffset() << std::endl;
				if (hR / 2 < i)
					hearts[i].setFrame (2);
				else if (hR / 2 > i)
					hearts[i].setFrame (0);
				else if (hR / 2 == i) {
					if (hR % 2 == 0)
						hearts[i].setFrame (2);
					else
						hearts[i].setFrame (1);
				}
			}	
			*/
			/*
			for (size_t i = 0; i < hearts.size (); ++i) {
				if (hR > 4)
					hearts[0].nextFrame ();
				else if (hR > 2)
					hearts[1].nextFrame ();
				else if (hR > 0)
					hearts[2].nextFrame ();
			}*/
			
		}
		void SetFull () {
			HealthBar::setHealth (HealthBar::getMaxHealth ());
			for (size_t i = 0; i < hearts.size (); ++i)
				hearts[i].setFrame (0);
		}
		void draw(sf::RenderWindow& window) {
			//window.draw(sprites[0]);
			for (size_t i = 0; i < sprites.size(); ++i)
				window.draw (*sprites[i]);
		}

};