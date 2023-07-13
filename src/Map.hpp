#pragma once

#include <SFML/Graphics.hpp>

class Map
{
	protected:
		sf::RectangleShape background;
		
	public:
		Map(sf::Vector2f size = sf::Vector2f (360, 480))
		{
			background.setSize(sf::Vector2f(size.x, size.x));
			background.setPosition(0, size.y - size.x);
			background.setFillColor(sf::Color(210, 190, 165));
		}
		void Update()
		{
			
		}
		void Draw(sf::RenderWindow& window)
		{
			window.draw(background);
		}
	
};
