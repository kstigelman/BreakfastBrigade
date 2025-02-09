#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Title.hpp"
#include "World.hpp"


using std::vector;

class Game
{
	private:
		World world;
		//Window window;
		unsigned WIDTH = 576; //360
		unsigned HEIGHT = 720; //480

		unsigned framerate = 60;
		bool windowNeedsScaled = false;
		sf::RenderWindow window;

		float deltaTime;
		int state = 0;

		Title title;

		sf::Music musicPlayer;
	public:
		Game()
		{
			window.create(sf::VideoMode(WIDTH, HEIGHT), "The Breakfast Brigade");
			musicManager ();
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
		void musicManager () {
			if (state == 0) {
				musicPlayer.stop();
				musicPlayer.openFromFile ("resources/audio/Theme.wav");
				musicPlayer.setLoopPoints (sf::Music::TimeSpan (sf::milliseconds (17600), sf::milliseconds (33270)));
				musicPlayer.setLoop (true);
				musicPlayer.play();
			}
			if (state == 1) {
				musicPlayer.stop();
				musicPlayer.openFromFile ("resources/audio/Microbial_Undertone.wav");
				musicPlayer.setLoopPoints (sf::Music::TimeSpan (sf::milliseconds (12000), sf::milliseconds (40000)));
				musicPlayer.setLoop (true);
				musicPlayer.play();
			}
		}
		void run () {
			//std::srand(std::time(NULL));
			sf::Clock clock;

			while(window.isOpen())
			{
				eventManager ();
				if (state == 0) {
					title.update (deltaTime);
					window.clear();
					title.draw (window);
					window.display();
				}
				if (state == 1) {
					update();
					window.clear();
					draw();
					window.display();
				}
				
				
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
			
			if (deltaTime >= 1 / framerate) {
				world.update (deltaTime);
			}
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
