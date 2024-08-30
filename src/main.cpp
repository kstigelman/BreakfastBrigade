#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

int main (int argc, char* argv[])
{
	Game game;
	game.run ();

	return 0;
}
/*
#include <SFML/Graphics.hpp>
#include <iostream>


int fishType (int strength) //Student made procedure. Uses random chance to determine which rarity of fish you will catch
{
	int random_num = std::rand () % 100;
	int decrease_chance_by = 0;

	if (strength > 50)
	{
		decrease_chance_by = 1;
		if (strength > 75)
		{
			decrease_chance_by = 3;
			if (strength > 90)
			{
				decrease_chance_by = 5;
				if (strength > 95)
				{
					decrease_chance_by = 7;
				}
			}
		}
	}
	if (random_num > 45 - decrease_chance_by)
	{
		if (random_num > 75 - decrease_chance_by)
		{
			if (random_num > 90 - decrease_chance_by)
			{
				if (random_num > 94 - decrease_chance_by)
				{
					if (random_num > 97 - decrease_chance_by)
					{
						if (random_num >= 99 - decrease_chance_by)
						{
							return 5;
						}
					}
					else
					{
						return 4;
					}
				}
				else
				{
					return 3;
				}
			}
			else
			{
				return 2;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

int rarestFish (int fish_caught[256]) //Student made procedure. Determines what fish you have caught is the rarest
{
	int highest_num = -1;
	bool foundFishTypes[5] = { false };
	for (int i = 0; i < 256; i++)
	{
		if (fish_caught[i] > highest_num)
		{
			highest_num = fish_caught[i];
		}
	}
	if (highest_num != -1)
	{
		return highest_num;
	}
	else
	{
		return -1;
	}
}

int main ()
{
	int fish_caught[256]; //Main list

	sf::Texture textures[5];
	sf::Sprite sprites[6];

	int fish_chance = 1;
	int fish_count = 0;
	int line_percent = 0;

	float line_length = 0;

	bool casting = false;
	bool throwing = false;
	bool bite = false;
	bool reel_in = false;
	bool got_fish = false;



	//Timers to run game processes
	sf::Clock timer;
	sf::Clock refreshClock;
	sf::Clock deltaClock;

	sf::Font font;
	sf::Text text[2];
	//Load font and text
	sf::RectangleShape meter[2];
	for (int i = 0; i < 2; i++)
	{
		meter[i].setSize (sf::Vector2f (100, 30));
		meter[i].setPosition (400, 20);
	}
	meter[0].setFillColor (sf::Color::Green);
	meter[1].setFillColor (sf::Color::Black);
	meter[1].setOutlineColor (sf::Color::White);
	meter[1].setOutlineThickness (4);

	//Load fonts and texts
	font.loadFromFile ("sprites/ArialCE.ttf");
	text[0].setFont (font);
	text[0].setString ("Fish caught: 0");
	text[0].setCharacterSize (20);
	text[1].setFont (font);
	text[1].setString ("Rarest fish found: ");
	text[1].setCharacterSize (12);
	text[1].setPosition (0, 30);

	//Load sprites and change variables for them
	for (int i = 0; i < 5; i++)
	{
		std::string filepath = "sprites/" + std::to_string (i) + ".png";
		textures[i].loadFromFile (filepath);
		sprites[i].setTexture (textures[i]);
		sprites[i].setScale (4.f, 4.f);
	}
	sprites[0].setScale (3.f, 3.f); //Pier
	sprites[0].setPosition (-20, 40);
	sprites[1].setPosition (180, 60); //Fisherman
	sprites[2].setOrigin (5, 0); //Fishing bobber
	sprites[2].setScale (1.5, 1.5);
	sprites[2].setPosition (280, 80);
	sprites[3].setTextureRect (sf::IntRect (0, 0, 20, 21)); //Fish
	sprites[3].setOrigin (26, -5);
	sprites[3].setScale (2, 2);
	sprites[3].setPosition (-100, -100);
	sprites[3].setRotation (-45);
	sprites[4].setPosition (0, 150); //Water
	sprites[5].setTexture (textures[3]); //Rarest fish
	sprites[5].setPosition (100, 30);

	//Fishing line
	sf::Vertex vertices[2] =
	{
		sf::Vertex (sf::Vector2f (280, 80)),
		sf::Vertex (sf::Vector2f (280, 80))
	};

	sf::RenderWindow window (sf::VideoMode (800, 600), "Fishing!"); //Game window
	std::srand (time (NULL));

	while (window.isOpen ())
	{
		float dt = deltaClock.getElapsedTime ().asSeconds (); //The amount of time that passes in one loop of the code
		deltaClock.restart ();

		sf::Event event;
		//Ends code processes if window is closed
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close ();
			}
		}

		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space) && !casting) //Checks if user presses spacebar and not currently casting their fishing line
		{
			casting = true;
			throwing = true;
		}
		if (casting) //Loop for after user casts fishing line
		{
			if (throwing) //Determines how far fishing line will be thrown
			{
				line_length += 420 * dt; //Increases and sets length of fishing line
				if (line_length < 420)
				{
					line_percent = (line_length / 420) * 100;
					meter[0].setSize (sf::Vector2f (line_percent, meter[0].getSize ().y));
				}
				else
				{
					meter[0].setSize (sf::Vector2f (0, meter[0].getSize ().y));
				}
				if (!sf::Keyboard::isKeyPressed (sf::Keyboard::Space)) //When spacebar is released, cast fishing line at distance determined above
				{
					if (line_length > 420)
					{
						throwing = false;
						reel_in = true;
					}
					else
					{
						vertices[1] = sf::Vertex (sf::Vector2f (line_length + 280, 270));
					}
					throwing = false;
				}
			}
			else
			{
				if (!bite && !reel_in) //Determine chance for fish to bite line
				{
					int random = std::rand () % (line_percent * -40 + 7500);
					if (random == fish_chance)
					{
						bite = true; //Chances match, wait for reel in
						timer.restart ();
					}
				}
			}
			if (bite) //If fish has bitten, determine if player reels line in
			{
				if (timer.getElapsedTime ().asSeconds () < 0.4f) //Animation on bobber to indicate fish bite
				{
					float t = timer.getElapsedTime ().asSeconds () * 0.1;
					t = std::pow (t - 0.04, 2);
					t = -t + 0.1;
					vertices[1].position.y = vertices[1].position.y + t;
				}
				else
				{
					vertices[1].position.y = 270;
				}
				if (timer.getElapsedTime ().asSeconds () < 0.5f) //User has 0.5 seconds to reel in line after fish bites
				{
					if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space))
					{
						//Fish is caught
						reel_in = true;
						bite = false;
						got_fish = true;

						refreshClock.restart ();
					}
				}
				else //User missed catching the fish
				{
					bite = false;
					reel_in = true;

				}
			}
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space) && !bite && !reel_in && !throwing) //User reels in fishing line without a fish biting
			{
				refreshClock.restart ();
				reel_in = true;
			}
			if (reel_in) //Code after user presses space to reel in line
			{
				vertices[1].position = vertices[0].position;

				if (got_fish) //Reeled in and fish is caught
				{
					sprites[3].setPosition (vertices[0].position);
					int select_fish = fishType (line_percent); //Call student made procedure
					fish_caught[fish_count] = select_fish;
					sprites[3].setTextureRect (sf::IntRect (select_fish * 20, 0, 20, 21));
					fish_count++;
					text[0].setString ("Total fish caught: " + std::to_string (fish_count));
					got_fish = false;
				}
				if (refreshClock.getElapsedTime ().asSeconds () > 1) //Delay after reeling in before casting line again, otherwise, fishing line gets stuck
				{
					reel_in = false;
					casting = false;
					sprites[3].setPosition (500, 500);
				}
			}
		}
		else
		{
			line_length = 0;
			line_percent = 0;
			meter[0].setSize (sf::Vector2f (0, meter[0].getSize ().y));
		}

		sprites[2].setPosition (vertices[1].position);

		//Begin drawing all objects on screen
		window.clear ();
		//Set visual for rarest fish found
		int rarest_fish = rarestFish (fish_caught);  //Call student made procedure
		if (rarest_fish > -1)
		{
			sprites[5].setTextureRect (sf::IntRect (rarest_fish * 20, 0, 20, 21));
			window.draw (sprites[5]);
		}

		for (int i = 0; i < 5; i++)
		{
			window.draw (sprites[i]);
		}
		window.draw (vertices, 2, sf::Lines);
		window.draw (text[0]);
		window.draw (text[1]);

		for (int i = 1; i > -1; i--)
		{
			window.draw (meter[i]);
		}

		window.display ();
		//End drawing objects on screen
	}
	return 0;
}
*/