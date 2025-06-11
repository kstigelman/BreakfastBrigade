#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "../Engine/GameSettings.hpp"

enum class Anchor {
    TOP_LEFT,
    TOP_RIGHT,
    CENTER,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

class UIElement {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect element;

    std::string type;
    std::set<std::string> tags;
    sf::Vector2f anchorPoint = sf::Vector2f (0.0, 0.0);
    Anchor anchor = Anchor::TOP_LEFT;

    GameSettings* gameSettings;
protected:
    bool bShouldUpdate = true;
    bool bVisible = true;
    bool bClicked = false;


public:
    UIElement (GameSettings* settings, sf::Vector2f position, sf::Vector2f size)
     : position(position), size(size), element (sf::FloatRect (position, size))
    {      
        gameSettings = settings;
    }
    const sf::FloatRect getElement () {
        return element;
    }
    void setSize (sf::Vector2f newSize) {
        size = newSize;
        element = sf::FloatRect (position, size);
    }
    GameSettings* getSettings () {
        return gameSettings;
    }
    void setAnchor (Anchor newAnchor) {
        switch (newAnchor) {
            case Anchor::TOP_LEFT:
                anchorPoint = sf::Vector2f (0.0, 0);
                break;
            case Anchor::TOP_RIGHT:
                anchorPoint = sf::Vector2f (gameSettings->WIDTH, 0.0);
                break;            
            case Anchor::CENTER:
                anchorPoint = sf::Vector2f (gameSettings->WIDTH / 2, gameSettings->HEIGHT);
                break;
            case Anchor::BOTTOM_LEFT:
                anchorPoint = sf::Vector2f (0.0, gameSettings->HEIGHT);    
                break;
            case Anchor::BOTTOM_RIGHT:
                anchorPoint = sf::Vector2f (gameSettings->WIDTH, gameSettings->HEIGHT);
                break;  
        }
        anchor = newAnchor;
        setPosition (position);

    }
    Anchor getAnchor () {
        return anchor;
    }
    sf::Vector2f getPosition () {
        return position;
    }

    bool isVisible () {
        return bVisible;
    }
    void setVisibility (bool bNewVis) {
        bVisible = bNewVis;
    }
    bool shouldUpdate () {
        return bShouldUpdate;
    }

    virtual void setPosition (sf::Vector2f newPosition) {
        position = newPosition + anchorPoint;
        element = sf::FloatRect (position + anchorPoint, size);
    }

    virtual void update (float dt) {

    }
    virtual void eventHandler (sf::Event& e) = 0;

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