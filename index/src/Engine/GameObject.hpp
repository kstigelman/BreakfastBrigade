#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Transform.hpp"

class GameObject{
    private:
        std::vector<std::string> tags;

    protected:
        bool bDraw;
		bool active;
        Transform transform;
    public:
        GameObject () {
            active = true;
            bDraw = true;
        }
        ~GameObject () {
            
        }
        virtual void spawn (class Scene* scene) = 0;
        virtual void update (float dt) = 0;
        virtual void draw (sf::RenderWindow& window) = 0;

        void setPosition (sf::Vector2f pos) {
            transform.position = pos;
        }
        Transform& getTransform () {
            return transform;
        }
        bool canDraw () {
            return bDraw;
        }
        bool isActive () {
            return active;
        }
        void setActive (bool newVal) {
            active = newVal;
        }
        void setShouldDraw (bool newVal) {
            bDraw = newVal;
        }
        void addTag (std::string newTag) {
            tags.push_back (newTag);
        }
        std::vector<std::string>& getTags () const {
            return tags;
        }
};