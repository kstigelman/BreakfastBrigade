#include <SFML/Graphics.hpp>

class HUD
{
	protected:
		sf::RectangleShape hud;
		sf::Font font;
		sf::Text text;
		bool fontLoaded;
	public:
		
		HUD (sf::Vector2f size = sf::Vector2f (0.f, 0.f), sf::Vector2f pos = sf::Vector2f (0, 0))
		{
			fontLoaded = false;
			
			hud.setSize (size);
			//hud.setFillColor (sf::Color::White);
			hud.setPosition (pos);
			fontLoaded = font.loadFromFile ("resources/fonts/PixeloidSans.ttf");
				
			

			text.setFont (font);
			text.setFillColor (sf::Color::White);	
			text.setCharacterSize (24);
			text.setString ("");
			text.setPosition (sf::Vector2f (getHudPosition ().x + 100, getHudPosition ().y - 40));
		}
		virtual void draw (sf::RenderWindow& window)
		{
			window.draw (hud);
			//if (fontLoaded)
			//	window.draw (text);
			//if (fontLoaded)
		//	window.draw (text);
			/*for(int i = 0; i < std::length (text); i++)
			{
				window.draw(text[i]);
			}*/
		}
		sf::Vector2f getHudPosition () {
			return hud.getPosition ();
		}
		void setText (std::string str) {
			//text.setString (str);
		}
		
	
	
	
	
};
