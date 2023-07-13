#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "World.hpp"

using std::vector;

class Game
{
	private:
		World world;
		//Window window;
		unsigned WIDTH = 360; //360
		unsigned HEIGHT = 480; //480

		bool windowNeedsScaled = false;
		sf::RenderWindow window;

		float deltaTime;
	public:
		Game()
		{
			window.create(sf::VideoMode(WIDTH, HEIGHT), "The Breakfast Brigade");
		}
		~Game()
		{

		}
		void windowRescaleEvent()
		{
			if(window.getSize().x != WIDTH || window.getSize().y != HEIGHT)
			{
				windowNeedsScaled = true;
			}
			if(windowNeedsScaled == true)
			{
				window.setSize(sf::Vector2u(WIDTH, HEIGHT));
				std::cout << "Please change window dimensions in Settings\n";
				windowNeedsScaled = false;
			}
			
		}
		void eventManager () {
				sf::Event event;
				while (window.pollEvent (event))
				{
					if (event.type == sf::Event::Closed)
						window.close ();

					if (event.type == sf::Event::Resized)
						windowRescaleEvent ();
				}
				
		}
		void stateManager () {

		}
		void run () {
			//std::srand(std::time(NULL));
			sf::Clock clock;

			while(window.isOpen())
			{
				eventManager ();
				update();
				window.clear();
				draw();
				window.display();
				
				sf::Time time = clock.restart();
				float dt = time.asSeconds();
				deltaTime = dt;
			}
		}
		void draw()
		{
			world.draw (window);
		}
		void update()
		{
			world.update (deltaTime);
			/*
			enemy->Update(deltaTime, player->GetPosition());
			//enemy2->Update(deltaTime, player->GetPosition());
			player->Update(deltaTime);
			
			for(size_t i = 0; i < player->bullets.size(); i++)
			{
				if(player->bullets[i].IsColliding(enemy) && enemy->Active())
				{
					enemy->Damage(1);
					player->bullets.erase(player->bullets.begin() + i);
				}
				/*if(player->bullets[i].IsColliding(enemy2) && enemy2->Active())
				{
					enemy2->Damage(1);
					player->bullets.erase(player->bullets.begin() + i);
				}****
			}*/
		}
		
};
