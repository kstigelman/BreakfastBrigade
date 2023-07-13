#pragma once

#include <SFML/Graphics.hpp>


#include "Joint.hpp"

class BodyComponent
{
	private:
		int angles[2];
		std::vector<Joint> joints;
		sf::RectangleShape element;
	public:
		BodyComponent()
		{
			
		}
		void Rotate(double degree)
		{
			if(element.getRotation() < angles[1] ||
			   element.getRotation() > angles[0])
				element.rotate (degree);
			if(element.getRotation() < angles[0] ||
			   element.getRotation() > angles[1])
				element.rotate (degree);
		}
		void SetPivot (sf::Vector2f pivot)
		{
			element.setCenter;
		}
		void SetPosition (sf::Vector2f pos)
		{
			element.setPosition (pos);
		}
		sf::Vector2f GetSize()
		{
			return element.getSize ();
		}
}
