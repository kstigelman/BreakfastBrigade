#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Title.hpp"
#include "World.hpp"
#include "Scenes/Scene.hpp"
#include "Controls.hpp"
#include "Scenes/MainMenu.hpp"
#include "Scenes/ColiforB.hpp"
#include "UI/UIRegistry.hpp"

#include "Globals.hpp"

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

		std::set<sf::Keyboard::Key> input;
		
		float deltaTime;
		int state = 1;

		Title title;

		UIRegistry uiRegistry;

		sf::Music musicPlayer;
	public:

		Game()
		{
			window.create(sf::VideoMode(WIDTH, HEIGHT), "The Breakfast Brigade");
			musicManager ();

			currentScene = new MainMenu (&uiRegistry, this);
		}
		~Game()
		{
			if (currentScene != nullptr) {
				delete currentScene;
				currentScene = nullptr;
			}
		}
		void setScene (Scene* newScene) {
			Scene* oldScene = currentScene;
			currentScene = newScene;
			delete oldScene;
			oldScene = nullptr;
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
				bLeftClicked = false;
				input.clear ();
				while (window.pollEvent (event))
				{
					uiRegistry.eventHandler (event);

					if (event.type == sf::Event::Closed)
						window.close ();

					if (event.type == sf::Event::Resized)
						windowRescaleEvent ();
					
					if (event.type == sf::Event::MouseMoved) 
						mousePos = sf::Vector2i (event.mouseButton.x, event.mouseButton.y);

					if (sf::Keyboard::isKeyPressed (sf::Keyboard::P)) {
						state = 1;
					}



					if (sf::Keyboard::isKeyPressed (MOVE_UP))
						input.insert (MOVE_UP);
				
					if (sf::Keyboard::isKeyPressed (MOVE_DOWN))
						input.insert (MOVE_DOWN);
					
					if (sf::Keyboard::isKeyPressed (MOVE_LEFT))
						input.insert (MOVE_LEFT);

					if (sf::Keyboard::isKeyPressed (MOVE_RIGHT))
						input.insert (MOVE_RIGHT);

					if (sf::Keyboard::isKeyPressed (SELECT_BUTTON))
						input.insert (SELECT_BUTTON);
						
					if (sf::Mouse::isButtonPressed (sf::Mouse::Left))
						bLeftClicked = true;
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
				update();
				draw();

				/*if (state == 0) {
					title.update (deltaTime);
					window.clear();
					title.draw (window);
					window.display();
				}
				if (state == 1) {
					
					window.clear();
					
					window.display();
				}*/
				
				
				sf::Time time = clock.restart();
				float dt = time.asSeconds();
				deltaTime = dt;
			}
		}
		void draw()
		{
			window.clear();
			if (currentScene == nullptr)
				return;

			currentScene->draw (window);

			//uiRegistry.draw (window);
			window.display();
		}
		void update()
		{
			
			if (currentScene == nullptr)
				return;

			if (deltaTime >= 1 / framerate) {
				currentScene->update (deltaTime);
			}
			uiRegistry.update (deltaTime);

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
