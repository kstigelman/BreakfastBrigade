#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "HUD.hpp"
#include "PlayerHealthbar.hpp"

class PlayerHUD : public HUD 
{
	private:
		PlayerHealthbar* playerHealth;
	public:
		PlayerHUD () {

		}
		PlayerHUD (PlayerHealthbar* hb)
			: HUD (sf::Vector2f (100, 100), sf::Vector2f (0, 0)) {
			//playerHealth = PlayerHealthbar ();
			playerHealth = hb;
			playerHealth->setPosition (sf::Vector2f (getHudPosition ().x - 100, getHudPosition ().y + 200));
			HUD::setText ("LVL-01");
		}
		~PlayerHUD () {
			//playerHealth = nullptr;
			//delete playerHealth;
		}
		virtual void draw (sf::RenderWindow& window) {
			HUD::draw (window);
			playerHealth->draw (window);
			//window.draw (text);
		}
};