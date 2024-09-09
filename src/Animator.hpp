#pragma once
/* File: Animator.hpp
 * Author: Kyler Stigelman
 *
 * 
 */
#include <SFML/Graphics.hpp>


class Animator
{
private:
	bool updateFrame;
	int framerate;
	int totalFrames;
	sf::IntRect frameBox;
	sf::Clock frameClock;
	bool isActive;

public:
	sf::Texture texture;
	sf::Sprite* sprite;
	//Entity* owner;
	Animator () {
		//texture = new sf::Texture ();
		//sprite = new sf::Sprite ();
		//texture = nullptr;
		//sprite = nullptr;
	}
	/*Animator (const Animator& a)
	{
		*this = a;
	}*/
	/*Animator (sf::Texture m_Texture, int frames, int fr) {
		texture = new sf::Texture;
		*texture = m_Texture;
		
		sprite = new sf::Sprite;
		sprite->setTexture (*texture);

		isActive = true;
		totalFrames = frames;
		framerate = fr;

		updateFrame = false;



		frameBox.width = texture->getSize ().x / totalFrames;

		frameBox.height = texture->getSize ().y;
		sprite->setTextureRect (frameBox);

		frameClock.restart ();

	}*/
	Animator (sf::Texture m_Texture, sf::Sprite* m_Sprite, int frames, int fr)
	{

		isActive = true;
		texture = m_Texture;
		//texture = sprite->getTexture ();
		sprite = m_Sprite;
		
		totalFrames = frames;
		framerate = fr;

		updateFrame = false;


		frameBox.width = m_Texture.getSize().x / totalFrames;
		frameBox.height = m_Texture.getSize().y;
	
		sprite->setTextureRect(frameBox);

		frameClock.restart ();
		
	}
	Animator (sf::Sprite* m_Sprite, int frames, int fr)
	{

		isActive = true;
		//texture = sprite->getTexture ();
		sprite = m_Sprite;
		texture = *sprite->getTexture();
		
		totalFrames = frames;
		framerate = fr;

		updateFrame = false;

		
	
		frameBox.width = texture.getSize().x / totalFrames;
		frameBox.height = texture.getSize().y;


		sprite->setTextureRect(frameBox);

		frameClock.restart ();
		
	}
	~Animator()
	{
		destruct ();
	}
	void destruct () 
	{
		//sprite = nullptr;
		//texture = nullptr;
		//sprite = nullptr;
		//delete texture;
		//delete sprite;
	}
	//If the sprite has multiple rows, advance to the next row
	void nextRow() {
		frameBox.top += frameBox.height;

		if (frameBox.top >= texture.getSize().y)
			frameBox.top = 0;
	}
	bool setRow (int num) {
		if (frameBox.height * num > texture.getSize ().y)
			return false;

		frameBox.top = frameBox.height * num;
		sprite->setTextureRect (frameBox);
		return true;
	}
	int getCurrentFrame () {
		return frameBox.left / frameBox.width;
	}
	void nextFrame()
	{

		if (sprite == nullptr)
			printf ("Sprite");
		if (sprite == nullptr)
			return;
		
		if (frameClock.getElapsedTime().asMilliseconds() > 1000 / framerate && !updateFrame)
		{
			updateFrame = true;
			frameClock.restart();
		}
		if (updateFrame)
		{
			updateFrame = false;
			frameBox.left += frameBox.width;

			if (frameBox.left >= texture.getSize ().x)
				frameBox.left = 0;
			
			sprite->setTextureRect (frameBox);
		}
	}
	bool setFrame (int frameNum)
	{
		if (frameBox.width * frameNum > texture.getSize ().x)
			return false;

		frameBox.left = frameBox.width * frameNum;
		sprite->setTextureRect (frameBox);
		return true;
	}
	void backFrame ()
	{
		if (frameBox.left != 0)
			frameBox.left -= frameBox.width;
		else
			frameBox.left = texture.getSize ().x - frameBox.width;

		sprite->setTextureRect (frameBox);
	}
	sf::Vector2u getFrameDim ()
	{
		return sf::Vector2u (frameBox.width, frameBox.height);
	}
	int getOffset ()
	{
		return frameBox.left;
	}
	virtual void update () {
		//if (texture == nullptr)
		//	std::cout << "null update" << std::endl;
	}

	virtual void draw (sf::RenderWindow& window)
	{
		if (sprite == nullptr)
			return;
		window.draw (*sprite);
	}
	sf::IntRect getRect ()
	{
		return sprite->getTextureRect ();
	}
	int getFramerate () {
		return framerate;
	}
	bool canUpdateFrame () {
		return updateFrame;
	}
	void setSpritePos (sf::Vector2f pos) {
		sprite->setPosition (pos);
	}
	/*
	Animator& operator=(const Animator& rhs)
	{
		if (this == &rhs)
			return *this;
		updateFrame = rhs.updateFrame;
		framerate = rhs.framerate;
		totalFrames = rhs.totalFrames;
		frameBox = rhs.frameBox;
		frameClock = rhs.frameClock;
		isActive = rhs.isActive;


		//destruct ();
		//*texture = *rhs.texture;
		//*sprite = *rhs.sprite;

		return *this;
	}*/
};