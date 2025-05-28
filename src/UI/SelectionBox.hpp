#pragma once
#include "UI/Button.hpp"
#include <tuple>

class SelectionBox {
private:
    Button left;
    Button right;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<std::tuple<std::string, sf::Texture>> slots;

    sf::Vector2f position = sf::Vector2f(0.0, 0.0);
    sf::Vector2f offset = sf::Vector2f (100.0, 0.0);

    int currentSelection = 0;
public:
    SelectionBox (UIRegistry* registry) 
    : left (registry, "Left", sf::Vector2f (0, 0), sf::Vector2f (50, 50)),
      right (registry, "Right", sf::Vector2f (0, 0), sf::Vector2f (50, 50))
    {
      left.setImage ("resources/sprites/Arrow.png");
      right.setImage ("resources/sprites/Arrow.png");

      left.setOnClicked ([this](){
        previousSlot ();
      });
      right.setOnClicked ([this](){
        nextSlot ();
      });
      right.mirror ();
    }
    void setPosition (sf::Vector2f newPosition) {
      position = newPosition;
      sprite.setPosition (position);
      left.setPosition (position - offset);
      right.setPosition (position + offset);
    }
    sf::Vector2f getPosition () {
      return position;
    }
    void addSlot (std::string name, sf::Texture texture) {
      slots.push_back (std::pair(name, texture));
      if (slots.size() == 1)
        sprite.setOrigin (texture.getSize().x / 2, texture.getSize().y / 2);
        setPosition (getPosition ());
    }

    void nextSlot () {
      if (currentSelection < slots.size () - 1) {
        ++currentSelection;
        left.setVisibility (true);
      }
      else
        right.setVisibility (false);

      updateSprite ();
    }
    void previousSlot () {
      if (currentSelection > 0) {
        --currentSelection;
        right.setVisibility (true);
      }
      else
        left.setVisibility (false);

      updateSprite ();
    }
    void updateSprite () {
      sprite.setTexture (std::get<1>(slots[currentSelection]));
    }
    void draw (sf::RenderWindow& window) {
      window.draw (sprite);
      left.draw (window);
      right.draw (window);
    }
};