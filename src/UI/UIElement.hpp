#pragma once
#include <SFML/Graphics.hpp>
#include <set>

class UIElement {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect element;

    std::string type;
    std::set<std::string> tags;
public:
    UIElement (sf::Vector2f position, sf::Vector2f size)
     : position(position), size(size), element (sf::FloatRect (position, size))
    {      
    }
    const sf::FloatRect getElement () {
        return element;
    }
    void setSize (sf::Vector2f newSize) {
        size = newSize;
        element = sf::FloatRect (position, size);
    }
    virtual void setPosition (sf::Vector2f newPosition) {
        position = newPosition;
        element = sf::FloatRect (position, size);
    }

    virtual void update (float dt) {

    }
    virtual void draw (sf::RenderWindow& window) {

    }

    std::set<std::string> getTags() {
        return tags;
    }
    bool hasTag (std::string tag) {
        return tags.count (tag);
    }
    void addTag (std::string tag) {
        tags.insert (tag);
    }
    std::string getType () {
        return type;
    }
    void setType (std::string newType) {
        type = newType;
    }
};