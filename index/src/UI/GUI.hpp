#pragma once

#include <SFML/Graphics.hpp>

#include "Animator.hpp"

class GUI
{
	protected:
		Animator animator;
	private:
		sf::Font* font;
		sf::Text* text;

		sf::Texture texture;
		sf::Sprite sprite;

		sf::IntRect spriteSource;
		int framerate;
		int nFrames;
		sf::Vector2i frameSize;
		bool drawText;
	public:
		void draw(sf::RenderWindow &window)
		{
			//window.setView(sf::View(sf::FloatRect(2720.f, 3280.f, 1280.f, 720.f)));
			window.draw(sprite);
		}
		GUI()
		{

		}
		GUI(std::string filepath, int frames)
		{
			
			texture.loadFromFile(filepath);
			sprite.setTexture(texture);
			//font->loadFromFile("index/assets/fonts/ka1.ttf");
			//text->setFont(*font);
			nFrames = frames;
			frameSize = sf::Vector2i(texture.getSize().x / frames, texture.getSize().y);

			animator = Animator (&sprite, nFrames, -1);
			spriteSource.left = 0;
			spriteSource.top = 0;
			spriteSource.width = frameSize.x;
			spriteSource.height = frameSize.y;
			sprite.setTextureRect(spriteSource);
			sprite.setScale(0.5f, 0.5f);
			
			sprite.setPosition(10, 10);

			drawText = false;
		}
		~GUI()
		{
			text = nullptr;
			font = nullptr;
			delete text;
			delete font;
		}
		void nextFrame()
		{
			if (spriteSource.left < texture.getSize().x - frameSize.x)
				spriteSource.left += frameSize.x;
			else
				spriteSource.left = 0;
			sprite.setTextureRect(spriteSource);

		}
		void gotoFrame(int frameNum)
		{
			if (frameNum - 1 < nFrames && nFrames - frameNum != 7)
			{
				spriteSource.left = frameSize.x * (nFrames - frameNum);
			}
			else
			{
				//std::cout << "Error: frameNum > framerate\n";//I felt like implementing this one day, I dont know why 
															   //then another day helped me fix a bug... Imagine that.
			}
			sprite.setTextureRect(spriteSource);

		}
		void backFrame()
		{
			if (spriteSource.left != 0)
			{
				spriteSource.left -= frameSize.x;

			}
			else
			{
				spriteSource.left = texture.getSize().x - frameSize.x;
			}
			sprite.setTextureRect(spriteSource);

		}
		Animator& getAnimator () {
			return animator;
		}


};
