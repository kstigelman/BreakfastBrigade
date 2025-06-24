#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TextBox {
	protected:

		sf::View textView;
		const sf::Vector2f offset = sf::Vector2f (-9712, -9640);

		sf::Image profile;
		sf::Font font;
		
		sf::RectangleShape background;

		sf::String textString;
		sf::Text text;

		sf::Vector2f boxSize;

		float displayLength = 3.0f;
		sf::Clock displayTimer;

		bool active = true;

		bool drawBackground = true;

		bool fixedPosition = true;
	public:
		TextBox (std::string msg, sf::Vector2f position, float length = 3.f, unsigned size = 24, sf::Color color = sf::Color::White, bool fixed = true, bool background = true) {

			displayLength = length;

			font.loadFromFile ("resources/fonts/PixeloidSans.ttf");
			
			textString = msg;
			if (textString.getSize () > 0)
				text.setString (textString);
			else
				text.setString ("Placeholder text");
			text.setColor (color);
			text.setFont (font);
			text.setCharacterSize (size);

			fixedPosition = fixed;
			setPosition (position);

			drawBackground = background;

			textView.setSize (576, 720);
			textView.setCenter (-9712, -9640);
			textView.setViewport (sf::FloatRect (0, 0, 1, 1));
			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

		}
		void setText (std::string newMsg) {
			textString = newMsg;
			if (textString.getSize () > 0)
				text.setString (textString);
			else
				text.setString ("Placeholder text");
		}
		bool isActive () {
			return active;
		}
		void update (float dt) {
			if (displayLength < 0)
				return;
			if (displayTimer.getElapsedTime ().asSeconds () >= displayLength)
				active = false;
		}
		void setPosition (sf::Vector2f position) {
			if (fixedPosition)
				text.setPosition (offset + position);
			else
				text.setPosition (position);
		}
		void draw (sf::RenderWindow& window) {
			if (fixedPosition)
				window.setView (textView);

			window.draw (text);
		}
		void setColor (sf::Color color) {
			text.setColor (color);
		}
		

};