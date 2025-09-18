#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "TextBox.hpp"
class IterativeTextBox : public TextBox {
	private:
		sf::Vector2f size;

		float textSpeed = 0.2f;
		sf::Clock textTimer;

		int stringIndex = 0;
		bool active = true;

		bool drawBackground = true;
		bool drawProfile = false;
	public:
		IterativeTextBox (std::string msg, unsigned size = 24, bool background = true) {
			font.loadFromFile ("resources/fonts/PixeloidSans.ttf");
			
			textString = msg;
			if (textString.getSize () > 0)
				text.setString (textString.substring (0, stringIndex));
			else
				text.setString ("Placeholder text");
			text.setColor (sf::Color::White);
			text.setFont (font);
			text.setCharacterSize (size);

			drawBackground = background;
		}
		bool isActive () {
			return active;
		}
		void update (float dt) {
			if (stringIndex < text.getString ().getSize ()) {
				if (textTimer.getElapsedTime ().asSeconds () >= textSpeed) {
					++stringIndex;
					text.setString (textString.substring (0, stringIndex));
					textTimer.restart ();
				}
			}
		}
		void draw (sf::RenderWindow& window) {
			
		}

		

};